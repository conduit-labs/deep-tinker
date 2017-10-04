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
    
    MicroBitImage onImage(5, 5, smile_arr);
    MicroBitImage offImage(5, 5, off_arr);
    
    while(1) {
        uBit.display.print(onImage);
        uBit.display.print(offImage);
    }
}
