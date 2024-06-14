

#include <actuator.h>
#include <Dynamixel2Arduino.h>


    

#include "EasyNextionLibrary.h" // Include EasyNextionLibrary
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

EasyNex myNex(Serial);   // Create an object of EasyNex class with the name < myNex >
                        // Set as parameter the Serial you are going to use
                        
uint16_t PO2;
uint16_t FC;
uint16_t ECG;

const int REFRESH_TIME = 100;           // time to refresh the Nextion page every 100 ms
unsigned long refresh_timer = millis();  // timer for refreshing Nextion's page

PulseOximeter muestra;    //création de l'objet

int periodo=1000;         // période de la mesure
int duracion=0;

void Deteccion()
{
  
}

void setup() {

  pinMode(A0, INPUT); // set 34 pin as INPUT
 
  myNex.begin(9600); // Begin the object with a baud rate of 9600
                     // If no parameter was given in the begin(), the default baud rate of 9600 will be used

}

void loop() {
  
  if(2>1){         //(millis()-refresh_timer) > REFRESH_TIME){ //IMPORTANT do not have serial print commands in the loop without a delay
  
  int tempData1 = analogRead(A0);
  int tempData2 = muestra.getHeartRate();
  int tempData3 = muestra.getSpO2();
  
  ECG = map(tempData1, 0, 1024, 0, 255);
  if (millis() - duracion > periodo)
  {
  FC = map(tempData2, 0, 1024, 0, 1024);
  PO2 = map(tempData3, 0, 1024, 0, 1024);                                            
  duracion = millis();
  }
  // or an if statement with a timer condition like this one.
 
      //Serial.println(analogRead(A0));
      //myNex.writeNum("Nvoltage1.val", ECG); // Nvoltage.val is a variable that we have create on Nextion.        
      Serial.print(PO2);
      Serial.print('\n');
      Serial.print(FC);
      Serial.print('\n');
      //myNex.writeNum("Nvoltage2.val", FC); // Nvoltage.val is a variable that we have create on Nextion.        
      //myNex.writeNum("Nvoltage3.val", PO2); // Nvoltage.val is a variable that we have create on Nextion.        
      
      delay(10);      

      
      
      /* We Re-map the value of tempData from 0-1024 (steps) to 0-5000 millivolt
       * connect the pins of a Potentiometer on 34 pin, 5v (5000 millivolt) and GND. Outer pins to 5v and GND, middle pin to 34
       * https://www.arduino.cc/en/tutorial/potentiometer
       * Turn it over and read values from 0 to 5000 millivolts
       */
               
                                              // we send the value of the voltage variable on Arduino
                             // you can use the same name for variables on Nextion for easy recognition with a capital N in front
                             // Avoid the use of big variable names as every character is one byte to serial. 
                             // In here we use big names for the sake of example.
      refresh_timer = millis();  // Set the timer equal to millis, create a time stamp to start over the "delay"
 }
    }       


/* The rest work is on Nextion with the code on a timers user event

n0.val=Nvoltage.val         // write Nvoltage.val to n0.val
sys0=Nvoltage.val*100/5000  // use sys0 to make the calculations
j0.val=sys0                //  add the value to the Progress bar
//
//Reverse direction progress bar
j1.val=100-sys0
//
// Vertical allign
j2.val=sys0
//
// Progress bar can take values from 0-100
// we map the value from arduino 0-5000 :
// the math type for map the range is:
// return = (value - low1) * (high2 - low2) / (high1 - low1) + low2
// as both ranges start from zero low1 and low2 = 0
// the type becomes
// return = value*hight2/hight1
// return=value*100/5000

//
// And some graphic effects
if(n0.val>3300)
{
  n0.bco=RED
  j0.pco=RED
  j1.bco=RED //bco for the reversed
  j2.pco=RED
}else
{
  n0.bco=YELLOW
  j0.pco=1024
  j1.bco=1024
  j2.pco=1024
}
*/
