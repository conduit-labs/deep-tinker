# Welcome to Deep Tinker! 

## To Get Started: 
 
* [Create an account](https://developer.mbed.org)
* [Choose a board](https://developer.mbed.org/platforms/Microbit/) 
* [Programming environment](https://developer.mbed.org/compiler)

## What is the BBC micro:bit? 
The micro:bit is an open development board that allows you to run code on it and have access to all the hardware. It can be used to make all sorts of things, from robots to musical instruments -- wherever your imagination takes you. It's packed with a whole lot of features, a few of which we'll be using today to detect when a friendly micro:bit is nearby: 

#### LEDs 
The LEDs on the front form a 5 x 5 grid. They can be set to on/off and the brightness can be controlled.

If you turn your micro:bit over, you'll also see a yellow LED called the status LED. It flashes yellow when the system wants to tell the user that something has happened.

#### Buttons 
Buttons A and B are a form of input. The micro:bit can detect either of its two buttons being pressed and un-pressed and be programmed to act on that or send the information to another device.

Button R on the back of the micro:bit is a system button. When you have downloaded and run your code onto your BBC micro:bit, press Button R to restart and run your program from the beginning.

#### Bluetooth 
You will see a labelled BLE ANNTENA on the back of your micro:bit. The micro:bit is a peripheral device which can talk to a central device like a smart phone or tablet that has Bluetooth Low Energy (BLE). The BBC micro:bit can send signals and receive signals from a central device so another BLE device can control the micro:bit or the micro:bit can control another BLE device. Bluetooth Low Energy is just a power-friendly version of Bluetooth wireless technology.

## Programming the BBC micro:bit 
The micro:bit can be connected to your computer or device with a micro USB. When you plug your micro:bit into your computer, it shows up as a mass storage device labeled MICROBIT. Data can be sent and received between the micro:bit and the computer so programs can be downloaded from Windows and Macs onto the micro:bit via USB data connection. 

The way we'll do this today is by dragging and dropping HEX files to the enumerated MICROBIT. Intel HEX is a file format that conveys binary information in ASCII text form and is commonly used for programming microcontrollers.

#### Hello, Blinky! 

In this module, we will: 

* Make a single LED light up
 * Put it in a loop – toggle periodically
 * Change things up -- create our own images!

Let's get started  

# Display a single LED 

We'll use the `MicrobitImage` class to help us light up an LED here. Images are a good way to create icons and emojis in your code. We just create them like a variable, but provide some additional details that the `MicrobitImage` constructor requests.  

The constructor we will use to create our `MicrobitImage` takes three inputs: the first two arguments represent the width and height of the image, and the last argument is a 2D array representing the image. Armed with this information, it’s possible to create a new image like this:

```
#include "MicroBit.h" 

//Create an instance of the Microbit class 
MicroBit uBit; 

const uint8_t image_arr[] {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 
        0, 0, 1, 0, 0
    };

int main() {
    //Initialize the microbit runtime 
    uBit.init();
    
    MicroBitImage easyImage(5, 5, image_arr);
    
    while(1) 
        uBit.display.print(easyImage);
}
```

When you click compile, the compiler converts the source code to machine code and outputs it into a HEX file. Before we flash the code onto our device by importing the file to the enumerated MICROBIT, let's go ahead and take a look at the contents of the generated HEX file.  

#### Flash! 

Drag and drop your HEX file onto the micro:bit. You'll notice the status LED blink several times and the words 'Hello World!' appear across the front of your micro:bit.  

#### Blinking 

If we want the LED to blink, we need to change the `while()` loop to overlay a blank image on top of the existing one. 

```
while(1) {
        uBit.display.print(onImage);
        uBit.display.print(offImage);
    }
```

#### Playtime 

Modify the `image_arr[]` to change your image. Here, I've chosen to print a smiley face. 

```
const uint8_t smile_arr[] {
        0, 1, 0, 1, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        1, 0, 0, 0, 1, 
        0, 1, 1, 1, 0
    };

```

If you'd prefer to display a scrolling image instead of a static one, replace `uBit.display.print(easyImage)` with `uBit.display.scroll(easyImage, 80)`. 

# Micro:bit Button Press Events  

Often times, you need your program to hang around waiting for something to happen before it responds. In our goal for this workshop, it's going to be detecting a *friendly* micro:bit. Before we jump right to the end, let's learn how to detect that an event has occured by simulating some input event. The most obvious means of input on the micro:bit are its two buttons, labelled A and B.

The `MicroBitMessageBus` records which events your program is interested in, and delivers those `MicroBitEvents` to your program as they occur through the `MicroBitMessageBus` `listen` function. This lets you attach a callback to a function when a specified event (or events) occur. 

To find out when Button A is clicked or when Button B is clicked, we write some code like this: 
 
    #include "MicroBit.h"

    MicroBit uBit;

    void onButtonA(MicroBitEvent) {
        uBit.display.scroll("A", 80);
        uBit.sleep(1000); 
    }

    void onButtonB(MicroBitEvent) { 
        uBit.display.scroll("B", 80);
        uBit.sleep(1000); 
    }

    int main() {
        // Initialise the micro:bit runtime.
        uBit.init();
       
        // Register to receive events when any buttons are clicked, including the A+B virtual button (both buttons at once).
        uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_DOWN, onButtonA);
        uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_DOWN, onButtonB);

        // We're done, so just enter a power efficient sleep while we wait for an event. 
        while (1) {
            uBit.sleep(10000);
        }
    }
 
Now, whenever the `MICROBIT_BUTTON__DOWN` event is raised by MICROBIT_ID_BUTTON_A, your code inside function onButtonA will be automatically run.
   
# Radio 

#### Medium - send information over a network 
The micro:bit comes with a 2.4GHz radio module primarily designed to run the Bluetooth Low Energy (BLE) protocol. However, it can also be placed into a much simpler mode of operation that allows simple, direct micro:bit to micro:bit communication. 

#### Datagram 
To write our radio enabled application, we will be using the `MicroBitRadioDatagram` class. It lets you easily send and receive up to 32 bytes of data at a time. This data can be provided as array of bytes, a text string, or a buffer. We will use the `uBit.radio.datagram.send` function to send data. Any other micro:bits in range will detect the transmitted packet, and make the packet available through the `uBit.radio.datagram.recv` function.

Any micro:bits receiving a datagram packet will also raise a `MICROBIT_RADIO_EVT_DATAGRAM` event to indicate that some data is ready to be read.

#### Addressing 
The radio module allows you to specify two pieces of information: an address and a group. The address is like a postal address whereas a group is like a specific recipient at the address. The important thing is the radio will filter out messages that it receives that do not match your address and group. As a result, it’s important to pre-arrange the address and group your application is going to use.

Our example uses the micro:bit radio to show if another micro:bit running the same code is nearby. Each micro:bit is periodically broadcasting a group name, and listening to see if another micro:bit in that group is also in-range. When another micro:bit in the same group is detected, the display of the detecting micro:bit will show a filled-in heart shape. Otherwise, the display will show an empty heart shape. 

```
// Have we seen a friend recently?
uint8_t friend_seen = 0;

// Are we currently sending out messages?
uint8_t broadcast = 1;

/* We have a group name, and if any micro:bit is in range and in the group
 * then the others will see it.
 */
const char group_name[] = "mHUB";

const uint8_t smile[] {
        0, 1, 0, 1, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        1, 0, 0, 0, 1, 
        0, 1, 1, 1, 0
    };
    
const uint8_t frown[] {
        0, 1, 0, 1, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 1, 1, 1, 0, 
        1, 0, 0, 0, 1
    };

const uint8_t heart[] {
        0, 1, 0, 1, 0,
        1, 0, 1, 0, 1,
        1, 0, 0, 0, 1,
        0, 1, 0, 1, 0, 
        0, 0, 1, 0, 0
    }; 
    
MicroBitImage smileImg(5, 5, smile);
MicroBitImage frownImg(5, 5, frown);
MicroBitImage heartImg(5, 5, heart);

/* We send messages when people press buttons 'A' and 'B'.
 * At the moment, all micro:bits listening for messages
 * will see these and can respond to them
 */
void onButtonA(MicroBitEvent)
{
    uBit.radio.datagram.send("1");    
}

void onButtonB(MicroBitEvent)
{
    uBit.radio.datagram.send("2");    
}

void onData(MicroBitEvent)
{
    ManagedString recdString = uBit.radio.datagram.recv();

    if (recdString == "1")
        uBit.display.print(smileImg);

    if (recdString == "2")
        uBit.display.print(frownImg);
    
    /* For detecting the presence of our friend, we require them to be sending
     * the same group name as we are in 
     */ 
    if (recdString == group_name) {
        // We can make this larger to allow more missed packets
        friend_seen = 3;
    }
}

int main() {
    //Initialize the microbit runtime 
    uBit.init();
    uBit.radio.enable();
    
    //Setup button handlers to send data
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_EVT_ANY, onButtonA);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_EVT_ANY, onButtonB);
    
    //Setup a hander to run when data is received
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);

    while(1) {
        if (friend_seen) {
            uBit.display.print(heartImg); 
            friend_seen -= 1;
        } else {
            uBit.display.print(frownImg);
        }
        if (broadcast) {
            uBit.radio.datagram.send(group_name);
        }
        uBit.sleep(1000);
    }
}
```

## Challenge  

Make only certain microbits respond to messages. Work with your partner to figure out how to do this. Instructors will walk around to offer guidance. 



