/*
The MIT License (MIT)

Copyright (c) 2016 British Broadcasting Corporation.
This software is provided by Lancaster University by arrangement with the BBC.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include "MicroBit.h"

MicroBit uBit;

void onButtonA(MicroBitEvent)
{
    uBit.serial.printf("BUTTON A: ");
    uBit.serial.printf("\r\n");
    uBit.display.scroll("A", 80);
    uBit.sleep(1000); 
}

void onButtonB(MicroBitEvent)
{
    uBit.serial.printf("BUTTON B: ");
    uBit.serial.printf("\r\n");
    uBit.display.scroll("B", 80);
    uBit.sleep(1000); 
}

int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();
    uBit.serial.baud(9600);

    // Register to receive events when any buttons are clicked, including the A+B virtual button (both buttons at once).
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_DOWN, onButtonA);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_DOWN, onButtonB);

    // We're done, so just enter a power efficient sleep while we wait for an event.
    while (1)
        uBit.sleep(10000);
}

