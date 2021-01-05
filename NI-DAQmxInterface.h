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
    double  date;
    uInt32  stream0;
    uInt32  stream1;
    uInt32  stream2;
    uInt32  stream3;
    uInt32  stream4;
    uInt32  stream5;
    uInt32  stream6;
    uInt32  stream7;
    uInt32  stream8;
    uInt32  stream9;
    uInt32  stream10;
    uInt32  stream11;
    uInt32  stream12;
    uInt32  stream13;
    uInt32  stream14;
    uInt32  stream15;
    uInt32  stream16;
    uInt32  stream17;
    uInt32  stream18;
    uInt32  stream19;
    uInt32  stream20;
    uInt32  stream21;
    uInt32  stream22;
    uInt32  stream23;
    uInt32  stream24;
    uInt32  stream25;
    uInt32  stream26;
    uInt32  stream27;
    uInt32  stream28;
    uInt32  stream29;
    uInt32  stream30;
    uInt32  stream31;
    uInt32  stream32;
    uInt32  stream33;
    double  template;
    char*   unit;
} BasicTEDS;

int32 getBasicTEDS (const char* channel, BasicTEDS* userdata);
uInt8 * getTedsDataStream(const char* channel);
uInt8 getTedsTemplate(uInt8 * data);
uInt8 getSelector(uInt8 * data);
double getSensitivity(uInt8 * data, uInt8 _template);
double getDate(uInt8 * data, uInt8 _template);
char * getUnit(uInt8 * data, uInt8 _template, uInt8 _selector);

int32 resetDevice (const char* device);
