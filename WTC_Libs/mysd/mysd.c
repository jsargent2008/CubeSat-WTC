/*
 * mysd.c
 *
 *  Created on: May 15, 2018
 *      Author: Ben
 */

#include "fatfs.h"
#include <stdlib.h>
#include <string.h>
#include "mysd.h"

const char packet_header[] = { '_', '.', ',', '_' };

static int32_t get_next_packet_bounds(FIL* pifile) {
	if(f_tell(pifile) == f_size(pifile))
			return 0; // hit end of file, return 0 bytes

	FRESULT fres;

	DWORD p_begin = f_tell(pifile);

	uint8_t header_found = 0;

	uint8_t next_found = 0;
	uint32_t next_begin = 0;

	uint8_t readBuf[512];
	UINT bytesRead = 0;

	// while loop to find beginning of the next header
	while(!next_found) {
		fres = f_read(pifile, readBuf, sizeof readBuf, &bytesRead);
		if(fres != FR_OK)
			return GP_FRES_ERR;
		else if(bytesRead == 0)
			break;

		uint32_t block_start = (f_tell(pifile) - bytesRead);

		for(int i = 0; i < bytesRead; i++) {
			if(block_start + i > p_begin && readBuf[i] == packet_header[header_found++]) {
				if(header_found == 1) {
					next_begin = block_start + i;
				} else if(header_found == sizeof packet_header) {
					next_found = 1;
					break;
				}
			} else {
				header_found = 0;
			}
		}
	}

	if(!next_found)
		next_begin = f_size(pifile);

	f_lseek(pifile, p_begin);

	return (next_begin - p_begin);
}

int32_t get_next_packet(FIL* pifile, uint8_t** packet_buf) {
	int32_t p_size = get_next_packet_bounds(pifile);
	if(p_size <= 0)
		return p_size; // less than zero, error out without malloc-ing

	*packet_buf = malloc(p_size);
	memset(*packet_buf, 0, p_size);

	UINT bytesRead = 0;
	f_read(pifile, *packet_buf, p_size, &bytesRead);
	if(bytesRead != p_size)
		return bytesRead; // WTF?! TODO: Handle this error, if it's even possible?

	return p_size;
}

// Takes in a packet number and a pointer to a pointer to a uint8_t,
// which will be populated with the selected packet. Returns positive
// buffer size on success, negative value on failure. packer_num starts
// from 1 and counts upwards. TODO: update these docs, they're wrong.
int32_t get_packet_num(uint32_t packet_num, FIL* pifile, uint8_t** packet_buf) {
	// Store old tell point and seek to beginning of file.
	DWORD old_tell = f_tell(pifile);

	int32_t p_size = 0;
	f_lseek(pifile, p_size);

	// Repeat n times to get our file packet at the start of n-th packet.
	// Note, returns n-th packet, 1-based. 0th packet returns nothing.
	for(uint32_t i = 0; i < packet_num; i++) {
		// Seek to the beginning of this packet, returned by the previous iteration.
		f_lseek(pifile, f_tell(pifile) + p_size);

		p_size = get_next_packet_bounds(pifile);
		if(p_size <= 0)
			return p_size; // error, probably end of file?
	}

	if(p_size <= 0)
		return p_size; // less than zero, error out without malloc-ing

	*packet_buf = malloc(p_size);
	memset(*packet_buf, 0, p_size);

	UINT bytesRead = 0;
	f_read(pifile, *packet_buf, p_size, &bytesRead);
	if(bytesRead != p_size)
		return bytesRead; // WTF?! TODO: Handle this error, if it's even possible?

	f_lseek(pifile, old_tell);

	return p_size;
}
