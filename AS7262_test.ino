/***************************************************************************
  This is a library for the Adafruit AS7262 6-Channel Visible Light Sensor

  This sketch reads the sensor

  Designed specifically to work with the Adafruit AS7262 breakout
  ----> http://www.adafruit.com/products/3779
  
  These sensors use I2C to communicate. The device's I2C address is 0x49
  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!
  
  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include "Adafruit_AS726x.h"


//create the object
Adafruit_AS726x ams;

//buffer to hold raw values
uint16_t sensorValues[AS726x_NUM_CHANNELS];

//buffer to hold calibrated values (not used by default in this example)
//float calibratedValues[AS726x_NUM_CHANNELS];

void setup() {
  Serial.begin(9600);
  while(!Serial);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  //begin and make sure we can talk to the sensor
  if(!ams.begin()){
//    Serial.println("could not connect to sensor! Please check your wiring.");
    while(1);
  }
}

void loop() {

  //read the device temperature
  uint8_t temp = ams.readTemperature();
  
  ams.drvOn(); //un  comment this if you want to use the driver LED for readings
  ams.startMeasurement(); //begin a measurement
  
  //wait till data is available
  bool rdy = false;
  while(!rdy){
    delay(5);
    rdy = ams.dataReady();
  }
//  ams.drvOff(); //uncomment this if you want to use the driver LED for readings

  //read the values!
  ams.readRawValues(sensorValues);
  //ams.readCalibratedValues(calibratedValues);


// compare red with all other wavelength
// if red is the greatest value, then the scanned color is red
 if((sensorValues[AS726x_RED]>sensorValues[AS726x_BLUE])&&
      sensorValues[AS726x_RED]>sensorValues[AS726x_GREEN]&&
      sensorValues[AS726x_RED]>sensorValues[AS726x_YELLOW]&&
      sensorValues[AS726x_RED]>sensorValues[AS726x_ORANGE]&&
      sensorValues[AS726x_RED]>sensorValues[AS726x_VIOLET]&&
      sensorValues[AS726x_GREEN]<100
  
  ){
      Serial.println("it's red");
    }

// compare green with all other wavelength
// if green is the greatest value, then the scanned color is green
 if((sensorValues[AS726x_GREEN]>sensorValues[AS726x_BLUE])&&
      sensorValues[AS726x_GREEN]>sensorValues[AS726x_RED]&&
      sensorValues[AS726x_GREEN]>sensorValues[AS726x_YELLOW]&&
      sensorValues[AS726x_GREEN]>sensorValues[AS726x_ORANGE]&&
      sensorValues[AS726x_GREEN]>sensorValues[AS726x_VIOLET]&&
      sensorValues[AS726x_RED]<70
  
  ){
      Serial.println("it's green");
    }
    
// check if the scanned color is blue

// first, check if violet is the largest value
    if(sensorValues[AS726x_VIOLET]>sensorValues[AS726x_BLUE]&&
        sensorValues[AS726x_VIOLET]>sensorValues[AS726x_GREEN]&&
        sensorValues[AS726x_VIOLET]>sensorValues[AS726x_YELLOW]&&
        sensorValues[AS726x_VIOLET]>sensorValues[AS726x_ORANGE]&&
        sensorValues[AS726x_VIOLET]>sensorValues[AS726x_RED]&&
// second, check if blue is the second largest value
        sensorValues[AS726x_BLUE]>sensorValues[AS726x_GREEN]&&
        sensorValues[AS726x_BLUE]>sensorValues[AS726x_YELLOW]&&
        sensorValues[AS726x_BLUE]>sensorValues[AS726x_ORANGE]&&
        sensorValues[AS726x_BLUE]>sensorValues[AS726x_RED]
        ){
        Serial.println("it's blue");
       }   

// check if the scanned color is magenta
    if(sensorValues[AS726x_VIOLET]>150&&
       sensorValues[AS726x_ORANGE]>100&&
       sensorValues[AS726x_RED]>100&&
//     blue is a bit ambiguous depending on brightness, so I excepted blue in this scenario
       sensorValues[AS726x_GREEN]<100&&
       sensorValues[AS726x_YELLOW]<100){
        Serial.println("it's magenta");
       }

// check if the scanned color is cyan
// check if violet a large value
    if(sensorValues[AS726x_VIOLET]>sensorValues[AS726x_YELLOW]&&
        sensorValues[AS726x_VIOLET]>sensorValues[AS726x_ORANGE]&&
        sensorValues[AS726x_VIOLET]>sensorValues[AS726x_RED]&&
// check if green is a large value
        sensorValues[AS726x_GREEN]>sensorValues[AS726x_YELLOW]&&
        sensorValues[AS726x_GREEN]>sensorValues[AS726x_ORANGE]&&
        sensorValues[AS726x_GREEN]>sensorValues[AS726x_RED]&&
// check if blue is a large value
        sensorValues[AS726x_BLUE]>sensorValues[AS726x_YELLOW]&&
        sensorValues[AS726x_BLUE]>sensorValues[AS726x_ORANGE]&&
        sensorValues[AS726x_BLUE]>sensorValues[AS726x_RED]
        ){
        Serial.println("it's cyan");
       } 
       
// check if the scanned color is yellow
    if(
// check if green is a large value
        sensorValues[AS726x_GREEN]>sensorValues[AS726x_BLUE]&&
        sensorValues[AS726x_GREEN]>sensorValues[AS726x_VIOLET]&&
// check if red is a large value
        sensorValues[AS726x_RED]>sensorValues[AS726x_BLUE]&&
        sensorValues[AS726x_RED]>sensorValues[AS726x_VIOLET]&&
        sensorValues[AS726x_YELLOW]>100
        ){
        Serial.println("it's yellow");
       } 





Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" Violet: "); Serial.print(sensorValues[AS726x_VIOLET]);
  Serial.print(" Blue: "); Serial.print(sensorValues[AS726x_BLUE]);
  Serial.print(" Green: "); Serial.print(sensorValues[AS726x_GREEN]);
  Serial.print(" Yellow: "); Serial.print(sensorValues[AS726x_YELLOW]);
  Serial.print(" Orange: "); Serial.print(sensorValues[AS726x_ORANGE]);
  Serial.print(" Red: "); Serial.print(sensorValues[AS726x_RED]);
  Serial.println();
  Serial.println();
  Serial.write(12);
//Serial.println("meow");
}
