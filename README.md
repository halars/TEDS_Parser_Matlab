TEDS Parser for Matlab
==================
Compile from MatLab console through mex-interface as follows:
* Compiling (getTEDS 64-bit):     mex getTEDS.c NI-DAQmxInterface.c -L./lib/ -lNIDAQmx64 -v
* Compiling (resetdevice 64-bit): mex resetDevice.c NI-DAQmxInterface.c -L./lib/ -lNIDAQmx64 -v
