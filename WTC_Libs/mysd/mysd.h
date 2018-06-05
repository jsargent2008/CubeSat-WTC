/*
 * mysd.h
 *
 *  Created on: May 15, 2018
 *      Author: Ben
 */

#ifndef MYSD_MYSD_H_
#define MYSD_MYSD_H_

#define SD_OK			0
#define SD_MSD_NULL		1
#define SD_PACKET_NULL	2
#define SD_SEEK_ERR		3
#define SD_READ_ERR		4
#define SD_WRITE_ERR	5
#define SD_SYNC_ERR		6
#define SD_OPEN_ERR		7
#define SD_CLOSE_ERR	8
#define SD_MOUNT_ERR	9
#define SD_BAD_MALLOC	10
#define SD_OUT_OF_SPACE	11
#define SD_FF_LINK_ERR	12

#define GP_MSD_NULL		-1
#define GP_PACKET_NULL	-2
#define GP_READ_ERR		-3

#include <stdint.h>
#include "fatfs.h"

#define MSD_PACKET_SIZE 128
#define MSD_PACKETS_PER_FILE 33554431 // = floor of (4294967295 / 128) = [4GiB-1 max FAT32 file size / current PACKET_SIZE]
//#define MSD_PACKETS_PER_FILE 8 // very small number, used for head rollover testing, not suitable for flight

typedef struct {
	uint32_t r_head, w_head;
	uint8_t w_wrap;

	uint32_t max_files;
	uint16_t active_file;
	char active_file_name[6];

	FATFS* sd_fs;
	FIL* head_file;
	FIL* data_file;
} mysd;

/**
 * Populates a `mysd` struct, initializing the FatFs filesystem, opening the head file, loading the stored
 * read and write heads into memory, then opening the 0 data file. (If this is not the correct file, that
 * will be remedied on the first read or write operation.) The passed pointer to a `mysd` struct must not
 * be NULL, as it is not created allocated by this function and must be handled by the caller. The passed
 * `mysd` struct will be required for all subsequent calls to this SD library, so it should be kept in
 * a safe place in the heap or static storage. This function does allocate memory for the FatFs members
 * contained within the struct. Any calls to this library with a `mysd` that has not yet been passed into
 * this function are undefined behavior and must be avoided. Returns according to the `SD_*` defines.
 */
uint8_t sd_init(mysd* msd);

/**
 * Safely closes all open files and dismounts the FatFs filesystem. This call destroys the integrity of the
 * `mysd` struct by freeing and nullifying the FatFs members contained within. Any subsequent calls to this
 * library with the destroyed `mysd` struct are undefined behavior and must be avoided. The passed `mysd`
 * may be reinitizled for further use with a subsequent call to `sd_init`.
 */
void sd_deinit(mysd* msd);



/**
 * Writes the in-memory head locations to the head file, then forces the FatFs subsystem to flush any pending
 * cached writes to the disk. Prior to this call, no guarantees are made about the persistence of written
 * data in even of power loss. This call may be expensive, so it is recommended at the conclusion of a series
 * of writes, but not after each packet. Returns according to the `SD_*` defines.
 */
uint8_t save_data(mysd* msd);

/**
 * This call closes and re-opens the current active data file. It was mostly used for testing as a method of
 * reseting the FatFs file object err flag upon corruption. Since the addition of the `SD_CS` pin, this has not
 * been necessary and is slated for removal from the public interface. Returns according to the `SD_*` defines.
 */
uint8_t refresh_data(mysd* msd);



/**
 * Retrieves the packet at the location of `msd->r_head`. The buffer pointed to by the argument `packet_buf`
 * MUST be at least of size MSD_PACKET_SIZE. This function WILL attempt to write MSD_PACKET_SIZE bytes to the
 * pointed-to packet_buf and will make no attempt at bounds checking. The returned value, if positive, is the
 * number of bytes read from the file and written to the buffer, guaranteed to be less than or equal to
 * MSD_PACKET_SIZE. A value of 0 indicates there is no packet to read at that location. If r_head `!= w_head`,
 * this may indicate a write error when `w_head` was at `r_head`'s current location; increment `msd->r_head` and
 * attempt to continue reading. `r_head == w_head` indicates no more data to read, wait for subsequent rights.
 * A negative return value indicates an error, refer to the `GP_*` defines.
 */
int16_t get_next_packet(uint8_t* packet_buf, mysd* msd);

/**
 * Writes the data in the buffer pointed to by the `packet_buf` argument as the `msd->w_head`-th packet.
 * The written packet will be of size MSD_PACKET_SIZE. If `packet_size == MSD_PACKET_SIZE`, `packet_buf`
 * is passed directly to the underlying write function. If `packet_size < MSD_PACKET_SIZE`, the contents
 * of `packet_buf` are copied to the beginning of a zero'd buffer of length MSD_PACKET_SIZE, essentially
 * zero-padding the data up to MSD_PACKET_SIZE bytes. If `packet_size > MSD_PACKET_SIZE`, only the first
 * MSD_PACKET_SIZE bytes of `packet_buf` are written to disk, essentially truncating the buffer. `packet_buf`
 * is not modified in this process. Returns according to the `SD_*` defines.
 */
uint8_t write_next_packet(uint8_t* packet_buf, size_t packet_size, mysd* msd);

#endif /* MYSD_MYSD_H_ */
