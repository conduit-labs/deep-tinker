#include "MicroBit.h" 

//Create an instance of the Microbit class 
MicroBit uBit; 

const uint8_t smile_arr[] {
        0, 1, 0, 1, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        1, 0, 0, 0, 1, 
        0, 1, 1, 1, 0
    };
    
MicroBitImage onImage(5, 5, smile_arr);
    
void buttonA(MicroBitEvent) {
        uBit.display.print(onImage);
    }

int main() {
    //Initialize the microbit runtime 
    uBit.init();
    
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, buttonA);
    
    while(1) {
        uBit.sleep(100);
    }
}
