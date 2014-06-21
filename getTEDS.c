//  Author:     Kent Stark Olsen <kent.stark.olsen@gmail.com>
//  Created:    03-12-2013

#include "getTEDS.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	BasicTEDS basicTEDS;
    char* inputStr;
	int status;
    size_t bufLen;
    mwSize dims[2] = {1,1};
    mxArray* mxErrorCode        = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxManufacturerId   = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxModelNum         = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxVersionNum       = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxSerialNum        = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxSensitivity      = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxArray* mxUnit             = mxCreateDoubleMatrix(1, 1, mxREAL);
            
    const char* basicTEDSFields[] = {	"Channel",
                                        "ErrorCode",
                                        "ManufacturerId",
										"ModelNumber",
										"VersionLetter",
										"VersionNumber",
										"SerialNumber",
                                        "Sensitivity",
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
    
    //  Unit
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], "Unit"), mxCreateString(basicTEDS.unit));
    
    //  Free allocated memory
    mxFree(inputStr);
    
	return;
}
