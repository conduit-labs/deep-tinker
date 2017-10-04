#include "MicroBit.h" 

//Create an instance of the Microbit class 
MicroBit uBit; 

const uint8_t on_arr[] {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 
        0, 0, 1, 0, 0
    };
    
const uint8_t off_arr[] {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0
    };  

int main() {
    //Initialize the microbit runtime 
    uBit.init();
    
    MicroBitImage onImage(5, 5, on_arr);
    MicroBitImage offImage(5, 5, off_arr);
    
    while(1) {
        uBit.display.print(onImage);
        uBit.display.print(offImage);
    }
}
