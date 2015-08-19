/****************************************************************************
Copyright (c) 2013 Steve Hsu
****************************************************************************/

#ifndef FK_STDC_H
#define FK_STDC_H

#include <float.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>

#ifndef MIN
	#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
	#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

#endif
