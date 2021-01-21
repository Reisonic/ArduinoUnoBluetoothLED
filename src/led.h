#include <Arduino.h>
#include <SoftwareSerial.h>
#include <string.h>

SoftwareSerial btm(0,1); // HC-05 module RX=0 TX=1

class led{

    private:

    // RGB pins
    int red_light_pin = 13;
    int blue_light_pin = 12;
    int green_light_pin = 11;

    //LED pins
    int red_led_pin = 7;
    int blue_led_pin = 6;
    int green_led_pin = 5;

    // Main message
    String string;

    // Received data (byte)
    char command;

    public:

    // Activate RGB color
    void RGB_color(int red_light_value, int green_light_value, int blue_light_value){
        analogWrite(red_light_pin, red_light_value); // Red color (0-255)
        analogWrite(green_light_pin, green_light_value); // Green color (0-255)
        analogWrite(blue_light_pin, blue_light_value); // Blue color (0-255)
    }

    // On/Off LED
    void LED_On_Off(int led, int status){
        digitalWrite(led, status);
    }

    // Parsing string message to hex value
    void LED_RGB(String string){

        int massiv[3];
        massiv[0] = convert(string.begin()); // Receiving first byte
        massiv[1] = convert(string.begin()+2); // Receiving second byte
        massiv[2] = convert(string.begin()+4); // Receiving third byte

        RGB_color(massiv[0], massiv[1], massiv[2]);
    }

    /**
     * Converter hex value to decimal value
     **/
    int convert(String str) {
        int len = 2;
        int base = 1;
        int temp = 0;
        for (int i=len-1; i>=0; i--) {
            if (str[i]>='0' && str[i]<='9') {
                temp += (str[i] - 48)*base;
                base = base * 16;
            }
            else if (str[i]>='A' && str[i]<='F') {
                temp += (str[i] - 55)*base;
                base = base*16;
            }
        }
        return temp;
    }

    /**
     * Initialization of primary parameters
     **/
    void init(){
        btm.begin(9600); // Bluetooth speed 9600
        // For LED using OUTPUT mode
        pinMode(red_led_pin, OUTPUT);
        pinMode(blue_led_pin, OUTPUT);
        pinMode(green_led_pin, OUTPUT);
        pinMode(red_light_pin, OUTPUT);
        pinMode(blue_light_pin, OUTPUT);
        pinMode(green_light_pin, OUTPUT);
    }

    /**
     * Main function
     **/
    void body(){
        if (btm.available() > 0){
            string = "";
        }    
        while(btm.available() > 0){
            command = ((byte)btm.read());
            if(command == ':'){
                break;
            } else {
                string += command;
            }
            delay(1);
        }
        if (string.length() > 3)
        {
            LED_RGB(string); // Activate RGB LED color
        }
        if (string == String(command)) { // if current string equals received string
            if(string == "1")
            {
                LED_On_Off(red_led_pin, HIGH); // On Red LED
            }   
            else if(string =="2")
            {
                LED_On_Off(red_led_pin, LOW); // Off Red LED
            }
            else if(string == "3")
            {
                LED_On_Off(blue_led_pin, HIGH); // On Blue LED
            }   
            else if(string =="4")
            {
                LED_On_Off(blue_led_pin, LOW); // Off Blue LED
            }
            else if(string == "5")
            {
                LED_On_Off(green_led_pin, HIGH); // On Green LED
            }   
            else if(string =="6")
            {
                LED_On_Off(green_led_pin, LOW); // Off Green LED
            }
        }
    }
};