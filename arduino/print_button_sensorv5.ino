#include "Adafruit_Thermal.h"
#include<stdio.h> 

//Printer
#include "SoftwareSerial.h"
#define TX_PIN 9 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 10 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

//Button 
#define button 2 // pin  --> switch --> gnd
#define led 13   // the built-in LED
int buttonState = 0;         // variable for reading the pushbutton status


//Color 
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
int frequency = 0;
int redReading, blueReading, greenReading, whiteReading;

void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  
  Serial.begin(9600);

  
//Sensor
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.
  mySerial.begin(19200);  // Initialize SoftwareSerial
  //Serial1.begin(19200); // Use this instead if using hardware serial
  printer.sleep();      // Tell printer to sleep

}

void loop() {

  buttonState = digitalRead(button);

   if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(led, HIGH);
  } else {
    // turn LED off:
    digitalWrite(led, LOW);
  }

  // ***********************************************
  // Configure TCS3200 to detect red setting
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Make frequency reading from OUT
  redReading = pulseIn(sensorOut, LOW);

  // ***********************************************
  // Configure TCS3200 to detect blue setting
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // Make frequency reading from OUT
  blueReading = pulseIn(sensorOut, LOW);

  // ***********************************************
  // Configure TCS3200 to detect green setting
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  // Make frequency reading from OUT
  greenReading = pulseIn(sensorOut, LOW);

  // ***********************************************
  // Configure TCS3200 to detect brightness setting
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);

  // Make frequency reading from OUT
  whiteReading = pulseIn(sensorOut, LOW);


  // ***********************************************
  // Apply scaling and brightness
  whiteReading = 255 - whiteReading;
  redReading = 255 - (redReading - 99);
  blueReading = 255 - (blueReading - 167);
  greenReading = 255 - (greenReading - 154);

  if(redReading < 0)
    redReading = 0;

  if(blueReading < 0)
    blueReading = 0;  

  if(greenReading < 0)
    greenReading = 0;
    
  if(whiteReading < 0)
    whiteReading = 0;
    
  if(redReading > 255)
    redReading = 255;

  if(blueReading > 255)
    blueReading = 255;  

  if(greenReading > 255)
    greenReading = 255;
    
  if(whiteReading > 255)
    whiteReading = 255;
    
byte R,G,B;

R = redReading;
G = greenReading;
B = blueReading;

int base_a[4]; 
int base_c[4]; 
int base_g[4]; 
int base_t[4];
 
base_a[3] = (redReading & B00000011); 
base_a[2] = ((redReading & B00001100)>>2); 
base_a[1] = ((redReading & B00110000)>>4); 
base_a[0] = ((redReading & B11000000)>>6); 

base_c[3] = (greenReading & B00000011); 
base_c[2] = ((greenReading & B00001100)>>2); 
base_c[1] = ((greenReading & B00110000)>>4); 
base_c[0] = ((greenReading & B11000000)>>6); 

base_g[3] = (whiteReading & B00000011); 
base_g[2] = ((whiteReading & B00001100)>>2); 
base_g[1] = ((whiteReading & B00110000)>>4); 
base_g[0] = ((whiteReading & B11000000)>>6); 

base_t[3] = (blueReading & B00000011); 
base_t[2] = ((blueReading & B00001100)>>2); 
base_t[1] = ((blueReading & B00110000)>>4); 
base_t[0] = ((blueReading & B11000000)>>6); 

//Serial.println("R"+ String(redReading));
//Serial.println("G" + String(greenReading));
//Serial.println("B" + String(blueReading));

//Serial.print("\r\n");
//Serial.println("Printing your genome");

for(int i=0;i<4;i++)
{
  switch(base_a[i])
  {
    case 0 : Serial.print("A");
    break;
    case 1 : Serial.print("C");
    break;
    case 2 : Serial.print("G");
    break;
    case 3 : Serial.print("T");
    break;
  }
}
for(int i=0;i<4;i++)
{
  switch(base_c[i])
  {
    case 0 : Serial.print("A");
    break;
    case 1 : Serial.print("C");
    break;
    case 2 : Serial.print("G");
    break;
    case 3 : Serial.print("T");
    break;
  }
}

for(int i=0;i<4;i++)
{
  switch(base_t[i])
  {
    case 0 : Serial.print("A");
    break;
    case 1 : Serial.print("C");
    break;
    case 2 : Serial.print("G");
    break;
    case 3 : Serial.print("T");
    break;
  }
}

for(int i=0;i<4;i++)
{
  switch(base_g[i])
  {
    case 0 : Serial.print("A");
    break;
    case 1 : Serial.print("C");
    break;
    case 2 : Serial.print("G");
    break;
    case 3 : Serial.print("T");
    break;
  }
}

Serial.println("\r\n");
//Serial.println("End of DNA sequencing");
//Serial.println("\r\n");


delay(1000);  



}


 // digitalWrite(led, !digitalRead(button));
  //if (!digitalRead(button) == HIGH){
   //   printer.begin();        // Init printer (same regardless of serial type)    
//printer.print(hex); //Print the string.
//printer.print(" ");

//printer.print(hex[3], BIN);
//printer.print(" ");

//printer.feed(2);

  //printer.sleep();      // Tell printer to sleep
  //printer.wake();       // MUST wake() before printing again, even if reset
//  }

//  }
