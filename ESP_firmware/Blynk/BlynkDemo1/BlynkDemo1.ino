/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_MPU6050 mpu;

#define BLYNK_TEMPLATE_ID "TMPL3lQS1qx7y"
#define BLYNK_TEMPLATE_NAME "Test MPU6050"
#define BLYNK_AUTH_TOKEN "JltmaobzBdG3O4TfkES97oVoChixaTNT"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Spectra_5063";
char pass[] = "Spectra@123";

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
/*
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
    digitalWrite(2,value);
}
*/
// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Blynk.virtualWrite(V0,a.acceleration.x);
  Blynk.virtualWrite(V1,a.acceleration.y);
  Blynk.virtualWrite(V2,a.acceleration.z);

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

  if(a.acceleration.x>15){
    Blynk.logEvent("warning");
  }

}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
  pinMode(2,OUTPUT);

  // Setup a function to be called twice a second
  timer.setInterval(500L, myTimerEvent);
  
  delay(500);
  Serial.println("Initialize");
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      Serial.println("Failed to find MPU6050 chip");
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(100);

  Serial.print("Temp,x,y,z");
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
  //sensor reading
  
  /* Print out the readings */
  //Serial.print("Acceleration X: ");
  
  
}
