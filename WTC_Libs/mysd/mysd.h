/*
 * mysd.h
 *
 *  Created on: May 15, 2018
 *      Author: Ben
 */

#ifndef MYSD_MYSD_H_
#define MYSD_MYSD_H_

#define GP_NOT_FOUND -1
#define GP_FRES_ERR -2
#define GP_BAD_MALLOC -3

int32_t get_next_packet(FIL* pifile, uint8_t** packet_buf);
int32_t get_packet_num(uint32_t packet_num, FIL* pifile, uint8_t** packet_buf);

#endif /* MYSD_MYSD_H_ */
