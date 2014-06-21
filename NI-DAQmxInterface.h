//  Author:     Kent Stark Olsen <kent.stark.olsen@gmail.com>
//  Created:    03-12-2013

#include <stdio.h>
#include <math.h>
#include "./include/mex.h"
#include "./include/NIDAQmx.h"		//	Include NI-DAQmx interface

typedef struct
{
	char*	channel;
    int32 	errorCode;
	uInt32 	manufacturerId;
	uInt32 	modelNumber;
	char* 	versionLetter;
	uInt32 	versionNumber;
	uInt32 	serialNumber;
    double  sensitivity;
    char*   unit;
} BasicTEDS;

int32 getBasicTEDS (const char* channel, BasicTEDS* userdata);
uInt8 * getTedsDataStream(const char* channel);
uInt8 getTedsTemplate(uInt8 * data);
double getSensitivity(uInt8 * data, uInt8 _template);
char * getUnit(uInt8 * data, uInt8 _template);