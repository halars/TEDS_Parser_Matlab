TEDS Parser for Matlab v1.0a (Experimental)
==================
Copyright (c) 2013-2014, University of Southern Denmark, Kent Stark Olsen - kent.stark.olsen@gmail.com<br>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the organization nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#Description
This mex-interface is written in C up against National Instruments (NI) NIDAQmx driver. It serves as a base for further implementation of TEDS support in MatLab. This was developed due to the lack of such support in MatLab DAQ Toolbox.

The implementation is made according to the *IEEE 1451.4 Sensor Templates Overview* and *IEEE 1451.4 Smart Transducers Template Description Language* (TDL) documents.

Devices on which it has been tested successfully:
* NI PXIe 1073 (NI Expresscard-8360)
* NI USB-9162 (NI 9234)
* CompactDAQ (NI 9234)

##Compiling
Compile from MatLab console through mex-interface as follows:
* Compiling (getTEDS 64-bit) - **mex getTEDS.c NI-DAQmxInterface.c -L./lib/ -lNIDAQmx64 -v**
* Compiling (resetDevice 64-bit) - **mex resetDevice.c NI-DAQmxInterface.c -L./lib/ -lNIDAQmx64 -v**

##Usage
Call the functions from MatLab console or implement them in scripts. The following are examples of calling the functions:
* getTEDS([channel]) - **getTEDS('PXI1Slot2/ai4')**
* resetDevice([device]) - **resetDevice('PXI1Slot2')**
