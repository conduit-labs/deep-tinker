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
