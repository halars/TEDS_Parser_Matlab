//  Author:     Kent Stark Olsen <kent.stark.olsen@gmail.com>
//  Created:    06-26-2014

#include "resetDevice.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    char* inputStr;
	int status;
    size_t bufLen;

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
    
    //  Reset device
    status = (int)resetDevice(inputStr);
    
    printf("Status: %d\n", status);
    
    //  Free allocated memory
    mxFree(inputStr);
    
	return;
}
