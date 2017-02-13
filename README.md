# Welcome to Deep Tinker! 

## Important Links: 
 
* [Create an account](https://developer.mbed.org)
* [Choose a board] (https://developer.mbed.org/platform) 
* [Programming environment] (https://developer.mbed.org/compiler)

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

#### Hello World! and a Peek into HEX Files 

To get started, we'll get our micro:bits to display 'Hello World!' on the LEDs. This is easy: 

    #include "MicroBit.h" 

    // Create an instance of the MicroBit class
    MicroBit uBit;

    int main()
    {
        // Initialize the uBit object. This initializes the scheduler, memory allocator and Bluetooth stack. 
        uBit.init();

        uBit.display.scroll("HELLO WORLD!");
        release_fiber();
    }

When you click compile, the compiler converts the source code to machine code and outputs it into a HEX file. Before we flash the code onto our device by importing the file to the enumerated MICROBIT, let's go ahead and take a look at the contents of the generated HEX file.  

#### HEX Files 

Use your favorite text editor to view the contents of your HEX file. You'll see lines of ASCII text that are separated by return characters. Each text line contains hexadecimal characters that encode multiple binary numbers. The binary numbers may represent data, memory addresses, or other values, depending on their position in the line and the type and length of the line. Each text line is called a record.

    :020000040000FA
    :10000000C0070000D1060000D1000000B1060000CA
    :1000100000000000000000000000000000000000E0

A record consists of six fields that appear in order from left to right:

*   Start code, one character, an ASCII colon ':'.
*   Byte count, two hex digits, indicating the number of bytes (hex digit pairs) in the data field. The maximum byte count is 255 (0xFF). The byte code here is 16 (0x10) and is one of two commonly used byte counts, the other being 32 (0x20). 
*   Address, four hex digits, representing the 16-bit beginning memory address offset of the data. The physical address of the data is computed by adding this offset to a previously established base address, 
*   Record type, two hex digits, 00 to 05, defining the meaning of the data field.
*   Data, a sequence of n bytes of data, represented by 2n hex digits. Some records omit this field (n equals zero). The meaning and interpretation of data bytes depends on the application.
*   Checksum, two hex digits, a computed value that can be used to verify the record has no errors.

The first record is known as an Extended Linear Address. The address field `0000` is ignored  and the byte count is always `02`. The data bytes for this record when combined with the lower 16 bits of all subsequent data records (type 00) specify their absolute address. 

#### Flash! 

Drag and drop your HEX file onto the micro:bit. You'll notice the status LED blink several times and the words 'Hello World!' appear across the front of your micro:bit.  

# Create and Display Images 

Images are a good way to create icons and emojis in your code. They're pretty easy to create -- we just create them like a variable, but provide some additional details that the `MicrobitImage` constructor requests.  

The constructor we will use to create our `MicrobitImage` takes three inputs: the first two arguments represent the width and height of the image, and the last argument is a 2D array representing the image. Armed with this information, it’s possible to create a new image like this:

    #include "MicroBit.h"
    
    MicroBit uBit;
    
    const uint8_t empty_heart_arr[] {
                          0, 1, 0, 1, 0,
                          1, 0, 1, 0, 1,
                          1, 0, 0, 0, 1,
                          0, 1, 0, 1, 0,
                          0, 0, 1, 0, 0, };
                          
    int main()
    {
        // Initialise the micro:bit runtime.
        uBit.init();
    
        MicroBitImage empty_heart(5,5,empty_heart_arr);
             
        while(1)
            uBit.display.print(empty_heart);
    
    }  
      
Modify the `empty_heart_arr[]` to change your image. If you'd prefer to display a static image instead of an animated/scrolling one, replace `uBit.display.scroll(empty_heart, 80)` with `uBit.display.print(empty_heart)`. 

# Micro:bit Button Press Events  

Often times, you need your program to hang around waiting for something to happen before it responds. In our goal for this workshop, it's going to be detecting a *friendly* micro:bit. Before we jump right to the end, let's learn how to detect that an event has occured by simulating some input event. The most obvious means of input on the micro:bit are its two buttons, labelled A and B.

The `MicroBitMessageBus` records which events your program is interested in, and delivers those `MicroBitEvents` to your program as they occur through the `MicroBitMessageBus` `listen` function. This lets you attach a callback to a function when a specified event (or events) occur. `MicroBitButton` will send events on a range of button up, down, click and hold events. 

This may sound a little complicated at first, but it's fairly intuitive once you learn how to implement it. For example, to find out when Button A is clicked or when Button B is clicked, we write some code like this: 
 
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

In addition to being a general purpose CPU, what makes the micro:bit pretty cool is its ability to interact wirelessly with the world around it using a 2.4GHz radio module. This radio can be configured in a number of ways, and is primarily designed to run the Bluetooth Low Energy (BLE) protocol. However, it can also be placed into a much simpler mode of operation that allows simple, direct micro:bit to micro:bit communication.

The radio module allows you to specify two pieces of information: an address and a group. The address is like a postal address whereas a group is like a specific recipient at the address. The important thing is the radio will filter out messages that it receives that do not match your address and group. As a result, it’s important to pre-arrange the address and group your application is going to use.

Our example uses the micro:bit radio to show if another micro:bit running the same code is nearby. Each micro:bit is periodically broadcasting a group name, and listening to see if another micro:bit in that group is also in-range. When another micro:bit in the same group is detected, the display of the detecting micro:bit will show a filled-in heart shape. Otherwise, the display will show an empty heart shape. 

To write our radio enabled application, we will be using the `MicroBitRadioDatagram` class. It lets you easily send and receive up to 32 bytes of data at a time. This data can be provided as array of bytes, a text string, or a buffer.

We will use the `uBit.radio.datagram.send` function to send data. Any other micro:bits in range will detect the transmitted packet, and make the packet available through the `uBit.radio.datagram.recv` function.

Any micro:bits receiving a datagram packet will also raise a `MICROBIT_RADIO_EVT_DATAGRAM` event to indicate that some data is ready to be read.

    #include "MicroBit.h"

    #if MICROBIT_BLE_ENABLED 
     #ifdef YOTTA_CFG
      #error "This example needs BLE to be disabled. Use the yotta config.json in the proximit-heart directory to do this"
     #else
      #error "This example needs BLE to be disabled in the microbit config file in the microbit-dal: MicroBitConfig.h"
     #endif
    #endif

    MicroBit    uBit;

    // Have we seen a friend recently?
    uint8_t friend_seen = 0;

    // Are we currently sending out messages?
    uint8_t broadcast = 1;

    /* We have a group name, and if any micro:bit is in range and in the group
     * then the others will see it.
     */
    const char group_name[] = "tiger";

    const uint8_t empty_heart_arr[] {
                              0, 1, 0, 1, 0,
                              1, 0, 1, 0, 1,
                              1, 0, 0, 0, 1,
                              0, 1, 0, 1, 0,
                              0, 0, 1, 0, 0, };

    const uint8_t full_heart_arr[] {
                              0, 1, 0, 1, 0,
                              1, 1, 1, 1, 1,
                              1, 1, 1, 1, 1,
                              0, 1, 1, 1, 0,
                              0, 0, 1, 0, 0, }; 

    const uint8_t small_heart_arr[] {
                              0, 0, 0, 0, 0,
                              0, 1, 0, 1, 0,
                              0, 1, 1, 1, 0,
                              0, 0, 1, 0, 0,
                              0, 0, 0, 0, 0, };

    MicroBitImage empty_heart(5,5,empty_heart_arr);
    MicroBitImage full_heart(5,5,full_heart_arr);
    MicroBitImage small_heart(5,5,small_heart_arr);

    /* We send messages when people press buttons 'A' and 'B'.
     * At the moment, all micro:bits listening for messages
     * will see these and can respond to them
     * Challenge: make only certain micro:bits respond to these
     */
    void onButtonA(MicroBitEvent)
    {
        uBit.radio.datagram.send("1");    
    }

    void onButtonB(MicroBitEvent)
    {
        uBit.radio.datagram.send("2");    
    }

    /* We toggle broadcasting if both buttons are pressed together */
    void onButtonAB(MicroBitEvent)
    {
        broadcast = !broadcast;
        uBit.display.print("!");
    }


    void onData(MicroBitEvent)
    {
        ManagedString s = uBit.radio.datagram.recv();
        int rssi = uBit.radio.getRSSI();

        if (s == "1")
            uBit.display.print(full_heart);

        if (s == "2")
            uBit.display.print(small_heart);
        
        /* For detecting the presence of our friend, we require them to be sending
         * the same group name as we are in 
         */ 
        if (s == group_name && rssi < 70) {
            // We can make this larger to allow more missed packets
            friend_seen = 3;
        }
    }

    int main()
    {
        // Initialise the micro:bit runtime.
        uBit.init();

        // Setup some button handlers to allow direct heartbeat control with buttons
        uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_EVT_ANY, onButtonA);
        uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_EVT_ANY, onButtonB);
        uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_EVT_ANY, onButtonAB);

        //Setup a hander to run when data is received
        uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);

        uBit.radio.enable();

        while(1) {
            if (friend_seen) {
            uBit.display.print(full_heart); 
                friend_seen -= 1;
            } else {
                uBit.display.print(empty_heart);
            }
            
            if (broadcast)
                uBit.radio.datagram.send(group_name);

            uBit.sleep(1000);
        }
    }
   

## Challenge  

Make only certain microbits respond to messages. Work with your partner to figure out how to do this. Instructors will walk around to offer guidance. 



