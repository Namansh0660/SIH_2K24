/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.13 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.14.08 or later version;
     - for iOS 1.11.2 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// you can enable debug logging to Serial at 115200
//#define REMOTEXY__DEBUGLOG    

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__WIFI_CLOUD

#include <WiFi.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_MPU6050 mpu;

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "Spectra_5063"
#define REMOTEXY_WIFI_PASSWORD "Spectra@123"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "acde5a4997d5d28bbb8786178f604a6d"


#include <RemoteXY.h>

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 161 bytes
  { 255,0,0,24,0,154,0,18,0,0,0,31,1,106,200,1,1,4,0,68,
  4,12,99,81,51,16,36,135,205,65,99,99,88,0,65,99,99,89,0,65,
  99,99,90,0,71,5,110,30,30,56,0,5,24,135,0,0,112,193,0,0,
  112,65,0,0,160,65,0,0,32,65,0,0,0,64,24,109,47,115,50,0,
  71,36,112,30,30,56,1,5,24,135,0,0,112,193,0,0,112,65,0,0,
  160,65,0,0,32,65,0,0,0,64,24,109,47,115,50,0,135,0,0,0,
  0,0,0,72,66,71,69,110,30,30,56,0,5,24,135,0,0,112,193,0,
  0,112,65,0,0,160,65,0,0,32,65,0,0,0,64,24,109,47,115,50,
  0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // output variables
  float onlineGraph_01_var1;
  float onlineGraph_01_var2;
  float onlineGraph_01_var3;
  float instrument_01; // from -15 to 15
  float instrument_02; // from -15 to 15
  float instrument_03; // from -15 to 15

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



void setup() 
{
  RemoteXY_Init (); 
  
  
  Serial.begin(115200);
  RemoteXY_delay(500);
  Serial.println("Initialize");
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      Serial.println("Failed to find MPU6050 chip");
      RemoteXY_delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  RemoteXY_delay(100);

  Serial.print("Temp,x,y,z"); 
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  // use the RemoteXY structure for data transfer
  // do not call delay(), use instead RemoteXY_delay()
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  /* Print out the readings */
  //Serial.print("Acceleration X: ");
  Serial.print(temp.temperature);
  Serial.print(",");
  Serial.print(a.acceleration.x);
  Serial.print(",");
  //Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(",");
  //Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.print(",");
  Serial.println("");

  RemoteXY.onlineGraph_01_var1 = a.acceleration.x;
  RemoteXY.onlineGraph_01_var2 = a.acceleration.y;
  RemoteXY.onlineGraph_01_var3 = a.acceleration.z;
  RemoteXY.instrument_01 = a.acceleration.x; // from -15 to 15
  RemoteXY.instrument_02 = a.acceleration.y; // from -15 to 15
  RemoteXY.instrument_03 = a.acceleration.z; // from -15 to 15



  RemoteXY_delay(50);
  


}