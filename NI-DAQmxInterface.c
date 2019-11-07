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
        data->stream0 = (uInt32)stream[0];
        data->stream1 = (uInt32)stream[1];
        data->stream2 = (uInt32)stream[2];
        data->stream3 = (uInt32)stream[3];
        data->stream4 = (uInt32)stream[4];
        data->stream5 = (uInt32)stream[5];
        data->stream6 = (uInt32)stream[6];
        data->stream7 = (uInt32)stream[7];
        data->stream8 = (uInt32)stream[8];
        data->stream9 = (uInt32)stream[9];
        data->stream10 = (uInt32)stream[10];
        data->stream11 = (uInt32)stream[11];
        data->stream12 = (uInt32)stream[12];
        data->stream13 = (uInt32)stream[13];
        data->stream14 = (uInt32)stream[14];
        data->stream15 = (uInt32)stream[15];
        data->stream16 = (uInt32)stream[16];
        data->stream17 = (int32)stream[1];
        _template = getTedsTemplate(stream);
        _selector = getSelector(stream);
        
        data->date = getDate(stream, _template);
        data->unit = getUnit(stream, _template, _selector);
        data->sensitivity = getSensitivity(stream, _template);
        data->template = _template;
        
    }

    return status;
}

uInt8 * getTedsDataStream(const char* channel)
{
    static uInt8 data[1000];
    
    DAQmxGetPhysicalChanTEDSBitStream(channel, data, 495);
    
    return data;
}

uInt8 getTedsTemplate(uInt8 * data)
{
    uInt32 _template;
    uInt32 A;
    
    //  Get TEDS template    
    _template = 0;
    _template |= ((uInt32)data[9] & 3) << 8;
   
    _template |= (uInt32)data[8];
     A = _template;
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
    else if (_template == 12)
        unit = "V/Pa";
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
        sensitivity = 0.0000005 * pow(1. + 2. * 0.00015, (double)sensitivityData);

    } 
	else if (_template == 12)
	{
        // NOT CORRECT!
		sensitivityData = 0;
        	sensitivityData |= ((uInt32)data[11] & 3) << 16;
        	sensitivityData |= (uInt32)data[10] << 8;
        	sensitivityData |= (uInt32)data[9];
        	sensitivityData = sensitivityData >> 2;
        sensitivity = 100e-6 * pow(1. + 2. * 0.0001, (double)sensitivityData);

	}
	else if (_template == 27)
	{
        // NOT CORRECT!
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
    sensitivity = (double)sensitivityData;
    //sensitivity = (double)data[12];
    
    return sensitivity;
}


double getDate(uInt8 * data, uInt8 _template)
{
    uInt32 timeData;
    double date;
    
    //  Get sensitivity @ ref. conditions (Accelerometer)
    if (_template == 25)
    {
        // who knows...
        timeData = 0;
        timeData |= ((uInt32)data[11] & 15) << 16;
        timeData |= (uInt32)data[10] << 8;
        timeData |= (uInt32)data[9];
        timeData = timeData >> 4;

    } 
	else if (_template == 12)
	{
        
		timeData = 0;
        	timeData |= ((uInt32)data[11] & 3) << 16;
        	timeData |= (uInt32)data[10] << 8;
        	timeData |= (uInt32)data[9];
        	timeData = timeData >> 2;
        
        

	}
    else
    {
        date = 0;
    }
    date = (double)timeData;
    
    return date;
}


int32 resetDevice (const char* device)
{
    return DAQmxResetDevice(device);
}
