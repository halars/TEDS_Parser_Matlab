//  Author:     Kent Stark Olsen <kent.stark.olsen@gmail.com>
//  Created:    03-12-2013

#include "getTEDS.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	BasicTEDS basicTEDS;
    char* inputStr;
	int status;
    uInt8* stream;
    size_t bufLen;
    mwSize dims[2] = {1,1};
    mxArray* mxErrorCode        = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxManufacturerId   = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxModelNum         = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxVersionNum       = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxSerialNum        = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxSensitivity      = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxStream1          = mxCreateDoubleMatrix(1, 1, mxREAL); //mxCreateNumericMatrix(1, 1, mxREAL, mxUINT8_CLASS);
    mxArray* mxStream2          = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxStream3          = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxStream4          = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxStream5          = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxStream6          = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxStream7          = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxStream8          = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxStream9          = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxStream10         = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxStream11         = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxStream12         = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxStream13         = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxStream14         = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxStream15         = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxStream16         = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxStream17         = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxTemplate         = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxUnit             = mxCreateDoubleMatrix(1, 1, mxREAL);
            
    const char* basicTEDSFields[] = {	"Channel",
    "ErrorCode",
    "ManufacturerId",
    "ModelNumber",
    "VersionLetter",
    "VersionNumber",
    "SerialNumber",
    "Sensitivity",
    "Stream1",
    "Stream2",
    "Stream3",
    "Stream4",
    "Stream5",
    "Stream6",
    "Stream7",
    "Stream8",
    "Stream9",
    "Stream10",
    "Stream11",
    "Stream12",
    "Stream13",
    "Stream14",
    "Stream15",
    "Stream16",
    "Stream17",
    "Template",
    "Unit"};

    unsigned int numberOfBasicTEDSFields = sizeof(basicTEDSFields)/sizeof(*basicTEDSFields);

    //	Check for proper number of arguments
	if (nrhs != 1)
		mexErrMsgTxt("One string input required");
	if (nlhs > 1)
		mexErrMsgTxt("Too many output arguments");

	//	Input must be a string
	if (mxIsChar(prhs[0]) != 1)
		mexErrMsgTxt("Input must be a string");

	//	Input must be a row vector
	if (mxGetM(prhs[0]) != 1)
		mexErrMsgTxt("Input must be a row vector");

	//	Get the length of the input string
	bufLen = (mxGetM(prhs[0]) * mxGetN(prhs[0])) + 1;

	//	Allocate memory for input and output strings
	inputStr = mxCalloc(bufLen, sizeof(char));

	//	Copy the string data from prhs[0] into a C string inputStr
	status = mxGetString(prhs[0], inputStr, (int)bufLen);
	if (status != 0)
		mexWarnMsgTxt("Not enough space, string is truncated");

	//	Create output struct
	plhs[0] = mxCreateStructArray(2, dims, numberOfBasicTEDSFields, basicTEDSFields);

	//  Initialize basic TEDS struct
    basicTEDS.channel = inputStr;
    basicTEDS.errorCode = 0;
    basicTEDS.versionLetter = mxCalloc(1, sizeof(char));

    //	Read basic sensor information and put it into a struct
	status = getBasicTEDS(inputStr, &basicTEDS);
    basicTEDS.errorCode = status;
    
    //	Check if any error occurred
	if (status)
	{
        basicTEDS.manufacturerId = 0;
        basicTEDS.modelNumber = 0;
        basicTEDS.versionLetter = " ";
        basicTEDS.versionNumber = 0;
        basicTEDS.serialNumber = 0;
        basicTEDS.sensitivity = 0;
        basicTEDS.stream1 = 0;
        basicTEDS.stream2 = 0;
        basicTEDS.stream3 = 0;
        basicTEDS.stream4 = 0;
        basicTEDS.stream5 = 0;
        basicTEDS.stream6 = 0;
        basicTEDS.stream7 = 0;
        basicTEDS.stream8 = 0;
        basicTEDS.stream9 = 0;
        basicTEDS.stream10 = 0;
        basicTEDS.stream11 = 0;
        basicTEDS.stream12 = 0;
        basicTEDS.stream13 = 0;
        basicTEDS.stream14 = 0;
        basicTEDS.stream15 = 0;
        basicTEDS.stream16 = 0;
        basicTEDS.stream17 = 0;
        basicTEDS.template = 0;
        basicTEDS.unit = " ";
	}
        
    //	Deep copy data to MatLab struct
    //  Channel
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Channel"), mxCreateString(basicTEDS.channel));

    //  Error code    
    *mxGetPr(mxErrorCode) = basicTEDS.errorCode;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "ErrorCode"), mxErrorCode);
    
    //  Manufacturer ID
    *mxGetPr(mxManufacturerId) = basicTEDS.manufacturerId;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "ManufacturerId"), mxManufacturerId);

    //  Model number
    *mxGetPr(mxModelNum) = basicTEDS.modelNumber;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "ModelNumber"), mxModelNum);

    //  Version letter
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "VersionLetter"), mxCreateString(basicTEDS.versionLetter));

    //  Version number
    *mxGetPr(mxVersionNum) = basicTEDS.versionNumber;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "VersionNumber"), mxVersionNum);

    //  Serial number
    *mxGetPr(mxSerialNum) = basicTEDS.serialNumber;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "SerialNumber"), mxSerialNum);
    
    //  Sensitivity
    *mxGetPr(mxSensitivity) = basicTEDS.sensitivity;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Sensitivity"), mxSensitivity);
    
    //  Stream
    *mxGetPr(mxStream1) = basicTEDS.stream1;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Stream1"), mxStream1);
    *mxGetPr(mxStream2) = basicTEDS.stream2;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Stream2"), mxStream2);
    *mxGetPr(mxStream3) = basicTEDS.stream3;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Stream3"), mxStream3);
    *mxGetPr(mxStream4) = basicTEDS.stream4;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Stream4"), mxStream4);
    *mxGetPr(mxStream5) = basicTEDS.stream5;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Stream5"), mxStream5);
    *mxGetPr(mxStream6) = basicTEDS.stream6;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Stream6"), mxStream6);
    *mxGetPr(mxStream7) = basicTEDS.stream7;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Stream7"), mxStream7);
    *mxGetPr(mxStream8) = basicTEDS.stream8;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Stream8"), mxStream8);
    *mxGetPr(mxStream9) = basicTEDS.stream9;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Stream9"), mxStream9);
    *mxGetPr(mxStream10) = basicTEDS.stream10;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Stream10"), mxStream10);
    *mxGetPr(mxStream11) = basicTEDS.stream11;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Stream11"), mxStream11);
    *mxGetPr(mxStream12) = basicTEDS.stream12;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Stream12"), mxStream12);
    *mxGetPr(mxStream13) = basicTEDS.stream13;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Stream13"), mxStream13);
    *mxGetPr(mxStream14) = basicTEDS.stream14;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Stream14"), mxStream14);
    *mxGetPr(mxStream15) = basicTEDS.stream15;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Stream15"), mxStream15);
    *mxGetPr(mxStream16) = basicTEDS.stream16;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Stream16"), mxStream16);
    *mxGetPr(mxStream17) = basicTEDS.stream17;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Stream17"), mxStream17);
    
    //  Template
    *mxGetPr(mxTemplate) = basicTEDS.template;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Template"), mxTemplate);
    
    //  Unit
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Unit"), mxCreateString(basicTEDS.unit));
    
    //  Free allocated memory
    mxFree(inputStr);
    
	return;
}
