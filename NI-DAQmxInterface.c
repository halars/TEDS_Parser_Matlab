//  Author:     Kent Stark Olsen <kent.stark.olsen@gmail.com>
//  Created:    03-12-2013

#include "NI-DAQmxInterface.h"

int32 getBasicTEDS (const char* channel, BasicTEDS* data)
{
    int32 status;
    uInt8 * stream;
    uInt8 _template, _selector;
    
	status = DAQmxConfigureTEDS(channel, "");

    //  Get manufacturer ID
    if (!status)	//	No warnings or errors
		status = DAQmxGetPhysicalChanTEDSMfgID(channel, &data->manufacturerId);
    
    //  Get model number
    if (!status)	//	No warnings or errors
		status = DAQmxGetPhysicalChanTEDSModelNum(channel, &data->modelNumber);
    
    //  Get version letter
    if (!status)	//	No warnings or errors
        status = DAQmxGetPhysicalChanTEDSVersionLetter(channel, data->versionLetter, 5);
    
    //  Get version number
    if (!status)	//	No warnings or errors
		status = DAQmxGetPhysicalChanTEDSVersionNum(channel, &data->versionNumber);
    
    //  Get serial number
	if (!status)	//	No warnings or errors
		status = DAQmxGetPhysicalChanTEDSSerialNum(channel, &data->serialNumber);
    
    //  Get sensitivity/units
    if (!status)
    {
        stream = getTedsDataStream(channel);
        _template = getTedsTemplate(stream);
        _selector = getSelector(stream);
        
        data->unit = getUnit(stream, _template, _selector);
        data->sensitivity = getSensitivity(stream, _template);
    }

    return status;
}

uInt8 * getTedsDataStream(const char* channel)
{
    static uInt8 data[495];
    
    DAQmxGetPhysicalChanTEDSBitStream(channel, data, 495);
    
    return data;
}

uInt8 getTedsTemplate(uInt8 * data)
{
    uInt32 _template;
    
    //  Get TEDS template    
    _template = 0;
    _template |= ((uInt32)data[9] & 3) << 8;
    _template |= (uInt32)data[8];
    _template = _template >> 2;
    
   return (uInt8)_template;
}

uInt8 getSelector(uInt8 * data)
{
    uInt8 _selector;
    
    //  Extract selector
    _selector = 0;
    _selector |= (data[9] & 12) >> 2;
    
    return _selector;
}

char * getUnit(uInt8 * data, uInt8 _template, uInt8 _selector)
{
    static char * unit;
    
    //  Decide unit from template according to IEEE 1451.4
    if (_template == 25)
        if (!_selector)
            unit = "V/(m/s^2)";
        else
            unit = "V/N";
    else
        unit = "Unknown";
        
    return unit;
}

double getSensitivity(uInt8 * data, uInt8 _template)
{
    uInt32 sensitivityData;
    double sensitivity;
    
    //  Get sensitivity @ ref. conditions (Accelerometer)
    if (_template == 25)
    {
        sensitivityData = 0;
        sensitivityData |= ((uInt32)data[11] & 15) << 16;
        sensitivityData |= (uInt32)data[10] << 8;
        sensitivityData |= (uInt32)data[9];
        sensitivityData = sensitivityData >> 4;

        //  Convert ConRelRes to real number
        sensitivity =  0.0000005 * pow(1. + 2. * 0.00015,(double)_template); // 0.0000005 * pow(1. + 2. * 0.00015,
    } 
	else if (_template == 12)
	{
		sensitivityData = 0;
        	sensitivityData |= ((uInt32)data[11] & 15) << 16;
        	sensitivityData |= (uInt32)data[10] << 8;
        	sensitivityData |= (uInt32)data[9];
        	sensitivityData = sensitivityData >> 4;
		sensitivity = sensitivityData;
		// sensitivity = 0.0001 * pow(1.0001999461431,(double)_template) * 1000;
	}
	else if (_template == 27)
	{
		sensitivityData = 0;
        	sensitivityData |= ((uInt32)data[11] & 15) << 16;
        	sensitivityData |= (uInt32)data[10] << 8;
        	sensitivityData |= (uInt32)data[9];
        	sensitivityData = sensitivityData >> 4;
		sensitivity = 0.00001 * pow(1.0001999959,(double)_template) * 1000;
	}
    else
    {
        sensitivity = 0;
    }
    
    return sensitivity;
}

int32 resetDevice (const char* device)
{
    return DAQmxResetDevice(device);
}
