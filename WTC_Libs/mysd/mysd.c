/*
 * mysd.c
 *
 *  Created on: May 15, 2018
 *      Author: Ben
 */

#include "mysd.h"

#include <stdlib.h>
#include <string.h>

const char name_head_file[] = "head.bin";

uint8_t recall_heads(mysd* msd) {
	if(!msd)
		return SD_MSD_NULL;

	UINT bytes_read;
	BYTE head_buff[sizeof msd->r_head + sizeof msd->w_head + sizeof msd->w_wrap];

	FRESULT fres = f_lseek(msd->head_file, 0);
	if(fres != FR_OK)
		return SD_SEEK_ERR;

	fres = f_read(msd->head_file, head_buff, sizeof head_buff, &bytes_read);
	if(fres != FR_OK || bytes_read < sizeof head_buff)
		return SD_READ_ERR;

	// Building ints from bytes, hooray! Stored big-endian.
	msd->r_head = (uint32_t)head_buff[3] | (uint32_t)head_buff[2] << 8
			| (uint32_t)head_buff[1] << 16 | (uint32_t)head_buff[0] << 24;

	msd->w_head = (uint32_t)head_buff[7] | (uint32_t)head_buff[6] << 8
			| (uint32_t)head_buff[5] << 16 | (uint32_t)head_buff[4] << 24;

	msd->w_wrap = head_buff[8];

	return SD_OK;
}

uint8_t flush_heads(mysd* msd) {
	if(!msd)
		return SD_MSD_NULL;

	BYTE head_buff[sizeof msd->r_head + sizeof msd->w_head + sizeof msd->w_wrap];

	// Dumping the head integers into byte arrays through the magic of bit shifting.
	// head_buff: 0-3 = read head, 4-7 = write head, both stored big-endian
	head_buff[0] = (msd->r_head >> 24) & 0xFF;
	head_buff[1] = (msd->r_head >> 16) & 0xFF;
	head_buff[2] = (msd->r_head >> 8) & 0xFF;
	head_buff[3] = msd->r_head & 0xFF;

	head_buff[4] = (msd->w_head >> 24) & 0xFF;
	head_buff[5] = (msd->w_head >> 16) & 0xFF;
	head_buff[6] = (msd->w_head >> 8) & 0xFF;
	head_buff[7] = msd->w_head & 0xFF;

	head_buff[8] = msd->w_wrap;

	FRESULT fres = f_lseek(msd->head_file, 0);
	if(fres != FR_OK)
		return SD_SEEK_ERR;

	UINT bytes_written;
	fres = f_write(msd->head_file, head_buff, sizeof head_buff, &bytes_written);
	if(fres != FR_OK || bytes_written < sizeof head_buff)
		return SD_WRITE_ERR;

	fres = f_sync(msd->head_file);
	if(fres != FR_OK)
		return SD_SYNC_ERR;

	return SD_OK;
}

uint8_t change_file(uint8_t new_file, mysd* msd) {
	if(!msd)
		return SD_MSD_NULL;

	if(new_file == msd->active_file)
		return SD_OK;

	FRESULT fres = f_close(msd->data_file);
	if(fres != FR_OK)
		return SD_CLOSE_ERR;

	msd->active_file = new_file;
	snprintf(msd->active_file_name, sizeof msd->active_file_name, "%u", msd->active_file);

	fres = f_open(msd->data_file, msd->active_file_name, FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
	if(fres != FR_OK)
		return SD_OPEN_ERR;

	return SD_OK;
}

uint8_t set_active(uint32_t head, mysd* msd) {
	if(!msd)
		return SD_MSD_NULL;

	uint32_t packet_offset = (head % MSD_PACKETS_PER_FILE) * MSD_PACKET_SIZE;
	uint8_t packet_file = head / MSD_PACKETS_PER_FILE;

	uint8_t res = change_file(packet_file, msd);
	if(res != SD_OK)
		return res;

	// Move file pointer to specified head.
	FRESULT fres = f_lseek(msd->data_file, packet_offset);
	if(fres != FR_OK)
		return SD_SEEK_ERR;

	return SD_OK;
}

uint32_t increment_head(uint32_t* head, mysd* msd) {
	if(!msd || !head)
		return UINT32_MAX;

	if(((++(*head)) % (MSD_PACKETS_PER_FILE * msd->max_files)) == 0) {
		(*head) = 0;
		if(head == &msd->w_head)
			msd->w_wrap = 1;
		else if(msd->w_wrap)
			msd->w_wrap = 0;
	}

	return *head;
}

uint8_t sd_init(mysd* msd) {
	if(!msd)
		return SD_MSD_NULL;

	msd->r_head = msd->w_head = 0;

	if(!msd->sd_fs || !msd->head_file || !msd->data_file) {
		msd->sd_fs = calloc(1, sizeof(FATFS));
		msd->head_file = calloc(1, sizeof(FIL));
		msd->data_file = calloc(1, sizeof(FIL));

		if(!msd->sd_fs || !msd->head_file || !msd->data_file) {
			free(msd->head_file);
			free(msd->data_file);
			free(msd->sd_fs);

			msd->sd_fs = NULL;
			msd->head_file = NULL;
			msd->data_file = NULL;

			return SD_BAD_MALLOC;
		}
	}

	FATFS_UnLinkDriver(USERPath);
	uint8_t ret = FATFS_LinkDriver(&USER_Driver, USERPath);
	if(ret)
		return SD_FF_LINK_ERR;

	FRESULT fres = f_mount(msd->sd_fs, "", 1);
	if(fres != FR_OK)
		return SD_MOUNT_ERR;

	fres = f_open(msd->head_file, name_head_file, FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
	if(fres != FR_OK)
		return SD_OPEN_ERR;

	if(f_size(msd->head_file) < (sizeof msd->r_head + sizeof msd->w_head)) {
		flush_heads(msd);
	} else {
		recall_heads(msd);
	}

	msd->active_file = 0;
	snprintf(msd->active_file_name, sizeof msd->active_file_name, "%u", msd->active_file);

	uint32_t tot_sect = (msd->sd_fs->n_fatent - 2) * msd->sd_fs->csize;
	uint32_t total_packets = (tot_sect - 2000000) * (512 / 128); // tot_sect - 2mil sectors to accommodate ~gig of err and overhead

	msd->max_files = total_packets / MSD_PACKETS_PER_FILE; // TODO: disbaled for testing
	//msd->max_files = 8; // force a very small number for head rollover testing

	fres = f_open(msd->data_file, msd->active_file_name, FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
	if(fres != FR_OK)
		return SD_OPEN_ERR;

	return SD_OK;
}

void sd_deinit(mysd* msd) {
	if(!msd)
		return;

	if(msd->sd_fs && msd->head_file) {
		flush_heads(msd);
		f_close(msd->head_file);
	}

	if(msd->sd_fs && msd->data_file)
		f_close(msd->data_file);

	if(msd->sd_fs)
		f_mount(NULL, "", 1);

	free(msd->head_file);
	free(msd->data_file);
	free(msd->sd_fs);

	msd->sd_fs = NULL;
	msd->head_file = NULL;
	msd->data_file = NULL;
}

uint8_t refresh_data(mysd* msd) {
	if(!msd)
		return SD_MSD_NULL;

	f_close(msd->data_file);
	return f_open(msd->data_file, msd->active_file_name, FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
}

uint8_t save_data(mysd* msd) {
	if(!msd)
		return SD_MSD_NULL;

	uint8_t res = flush_heads(msd);
	if(res != SD_OK)
		return res;

	FRESULT fres = f_sync(msd->data_file);
	if(fres != FR_OK)
		return SD_SYNC_ERR;

	return SD_OK;
}

int16_t get_next_packet(uint8_t* packet_buf, mysd* msd) {
	if(!msd)
		return GP_MSD_NULL;
	if(!packet_buf)
		return GP_PACKET_NULL;

	if(msd->r_head >= msd->w_head && msd->w_wrap == 0)
		return 0;

	uint8_t res = set_active(msd->r_head, msd);
	if(res != SD_OK)
		return res;

	UINT bytesRead = 0;
	FRESULT fres = f_read(msd->data_file, packet_buf, MSD_PACKET_SIZE, &bytesRead);
	if(fres != FR_OK)// || bytesRead < MSD_PACKET_SIZE) TODO: ?
		return GP_READ_ERR;

	if(bytesRead > 0)
		increment_head(&msd->r_head, msd);

	return bytesRead;
}

uint8_t write_next_packet(uint8_t* packet_buf, size_t in_size, mysd* msd) {
	if(!msd)
		return SD_MSD_NULL;
	if(!packet_buf)
		return SD_PACKET_NULL;

	if(msd->w_head >= msd->r_head && msd->w_wrap == 1)
		return SD_OUT_OF_SPACE;

	uint8_t res = set_active(msd->w_head, msd);
	if(res != SD_OK)
		return res;

	uint8_t* write_buf = packet_buf;

	if(in_size < MSD_PACKET_SIZE) {
		write_buf = calloc(1, MSD_PACKET_SIZE);
		memcpy(write_buf, packet_buf, in_size);
	}

	UINT bytes_written;
	FRESULT fres = f_write(msd->data_file, write_buf, MSD_PACKET_SIZE, &bytes_written);
	if(fres != FR_OK || bytes_written < MSD_PACKET_SIZE)
		return SD_WRITE_ERR;

	if(in_size < MSD_PACKET_SIZE)
		free(write_buf);

	increment_head(&msd->w_head, msd);

	return SD_OK;
}
