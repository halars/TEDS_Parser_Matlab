TEDS Parser for Matlab v1.0a (Experimental)
==================
This mex-interface is written in C up against National Instruments (NI) NIDAQmx driver. It serves as a base for further implementation of TEDS support in MatLab. This was developed due to the lack of such support in MatLab DAQ Toolbox.

The implementation is made according to the *IEEE 1451.4 Sensor Templates Overview* and *IEEE 1451.4 Smart Transducers Template Description Language* (TDL) documents. A vital clue was delivered by [*Andrew Walsh*](http://awalsh128.blogspot.dk/2011/08/writing-teds-ieee-14514-parser.html).

Devices on which it has been tested:
* NI-PXIe
* CompactDAQ
* USB Carrier

#Compiling
Compile from MatLab console through mex-interface as follows:
* Compiling (getTEDS 64-bit) - **mex getTEDS.c NI-DAQmxInterface.c -L./lib/ -lNIDAQmx64 -v**
* Compiling (resetDevice 64-bit) - **mex resetDevice.c NI-DAQmxInterface.c -L./lib/ -lNIDAQmx64 -v**

#Usage:
Call the functions from MatLab console or implement them in scripts. The following are examples of calling the functions:
* getTEDS([channel]) - **getTEDS('PXI1Slot2/ai4')**
* resetDevice([device]) - **resetDevice('PXI1Slot2')**
