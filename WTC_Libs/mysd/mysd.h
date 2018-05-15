/*
 * mysd.h
 *
 *  Created on: May 15, 2018
 *      Author: Ben
 */

#ifndef MYSD_MYSD_H_
#define MYSD_MYSD_H_

#define GP_NOT_FOUND -1
#define GP_END_LTE_BEGIN -2
#define GP_F_OPEN_ERR -3

int32_t get_packet(uint32_t packet_num, uint8_t** packet_buf);

#endif /* MYSD_MYSD_H_ */
