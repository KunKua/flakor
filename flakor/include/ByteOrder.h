/***************************************************************************
 * Copyright (c) 2013-2016 Flakor.org All Rights Reserved.
 * Author: Steve Hsu (steve@kunkua.com,saint@aliyun.com)
 * last edited: 2016-5-18
 ***************************************************************************/
#ifndef FK_BYTEORDER_H
#define FK_BYTEORDER_H

static bool isLittleEndian = true;

#ifndef __BYTE_ORDER__
static bool checkLittleEndian() {
	int i = 1;
	unsigned char* ptr;
	ptr = (unsigned char*)&i;
	if(*ptr == 1) {
		return true;
	}else {
		return false;
	}
}
#endif

#ifdef __BYTE_ORDER__
	#if __BYTE_ORDER__ ==__ORDER_BIG_ENDIAN__
		isLittleEndian = false;
	#else
		isLittleEndian = true;
	#endif
#else
	isLittleEndian = checkLittleEndian();
#endif

#endif
