/************************************************************************
*                                                                                                                                        
*    Test du module "Heart rate Click"                                            
*                                                                    
*************************************************************************
* Description:  MIKROE-2000                                                
* La fréquence cardiaque et la saturation en oxygène du sang sont affichés 
* dans le moniteur série.
* 
* Matériel
*        1. Arduino Uno                                       
*        2. Module "Heart rate Click" 
*        3. Shifter Level TXB0108
*        
* Bibliothèques 
*        1. https://github.com/oxullo/Arduino-MAX30100/
*       
*  
************************************************************************/

// Appel des bibliothèques
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

PulseOximeter muestra;    //création de l'objet

int periodo=1000;         // période de la mesure
int duracion=0;

void Deteccion()
{
    Serial.println("Espera!");
}

void setup(void) 
{
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
}

void loop() 
{
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
}
