#include "MicroBit.h" 

#if MICROBIT_BLE_ENABLED 
 #ifdef YOTTA_CFG
  #error "This example needs BLE to be disabled. Use the config.json in the microsoft-blinky directory to do this"
 #else
  #error "This example needs BLE to be disabled in the microbit config file in the microbit-dal: MicroBitConfig.h"
 #endif
#endif

//Create an instance of the Microbit class 
MicroBit uBit; 

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
