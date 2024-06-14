
    

#include "EasyNextionLibrary.h" // Include EasyNextionLibrary
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

EasyNex myNex(Serial);   // Create an object of EasyNex class with the name < myNex >
                        // Set as parameter the Serial you are going to use
                        
uint16_t ECG;  // a variable to store the reading
                 // for simplicity Reasons we do not use float and we are going to take the measure in millivolts
uint16_t PO2;
uint16_t FC;

 

const int REFRESH_TIME = 100;           // time to refresh the Nextion page every 100 ms
unsigned long refresh_timer = millis();  // timer for refreshing Nextion's page

PulseOximeter muestra;    //création de l'objet

int periodo=1000;         // période de la mesure
int duracion=0;

void Deteccion()
{
    Serial.println("Espera!");
}

void setup() {
  //ECG
  Serial.begin(9600);
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -

  //PO2
  Serial.begin(9600);
  Serial.print("Inicialización...");
    if (!muestra.begin()) 
    {
        Serial.println("CHECK");
        while(1);
    } 
    else 
    {
        Serial.println("EXITOSO");
    }
muestra.setOnBeatDetectedCallback(Deteccion);
  
  //Conexión Nextion
  pinMode(A0, INPUT); // set 34 pin as INPUT
 
  myNex.begin(9600); // Begin the object with a baud rate of 9600
                     // If no parameter was given in the begin(), the default baud rate of 9600 will be used

}

void loop() {

  //ECG
  if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
  Serial.println('!');
  }
  else{
  // send the value of analog input 0:
  Serial.println(analogRead(A0));
  }
  //Wait for a bit to keep serial data from saturating
  delay(10);

  //PO2
  muestra.update();
  if (millis() - duracion > periodo) 
   {
    Serial.print("Frecuancia Cardiaca:");
    Serial.print(muestra.getHeartRate());
    Serial.print(" Espera/s");
    Serial.print("\t");
    Serial.print("Saturación de oxígeno:");
    Serial.print(muestra.getSpO2());
    Serial.println(" %");
    duracion = millis();
   }

  //Enviar info a Nextion
  if((millis()-refresh_timer) > REFRESH_TIME){ //IMPORTANT do not have serial print commands in the loop without a delay
                                              // or an if statement with a timer condition like this one.
 for( int i=0;i<5000;i++){                                            
      ECG=A0;
      PO2=muestra.getSpO2();
      FC=muestra.getHeartRate();
      //int tempData = (i);  //analogRead(34);  // Read the analog pin
      //voltage = map(tempData, 0, 1024, 0, 5000); // same like: voltage = analogRead(34)*5000/1024
      //Serial.println(i);
      myNex.writeNum("Nvoltage1.val", ECG); // Nvoltage.val is a variable that we have create on Nextion.        
      myNex.writeNum("Nvoltage2.val", PO2); // Nvoltage.val is a variable that we have create on Nextion.        
      myNex.writeNum("Nvoltage3.val", FC); // Nvoltage.val is a variable that we have create on Nextion.        
      
      delay(100);      

      
      
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
}
