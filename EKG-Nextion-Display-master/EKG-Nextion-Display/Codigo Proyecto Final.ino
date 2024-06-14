/** ##############################################################
**
**  Filename  : EKG-Nextion-Display.ino
**  Project   : EKG-Nextion-Display
**  Processor : AUNO
**  Version   : 1.0
**  Compiler  : Arduino IDE
**  Date/Time : 22/09/2017
**  Aluno     : A Noriega; O Lopez; C Rios
**  Last Mod  : 31/05/2021
**
** ##############################################################*/

/*****************************************************************
Hardware:

  # AD8232
      >OUT - pin A0
      >LO- - pin 5
      >LO+ - pin 6
      
  #Nextion Display 3.2 - NX4024T032_011R
    >TX - pin RX0
    >RX - pin TX1
          
  # Buzzer - pin 2  
******************************************************************/
#include "Nextion.h"

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define LEVEL_LOW   (0)
#define CH0_OFFSET  (25) //Normal shaft height
#define NOTE  1000 //Tint set to buzzer

NexWaveform s0 = NexWaveform(0, 2, "s0");
NexDSButton bt0   = NexDSButton(0, 12, "bt0"); //Button Pause/Play
NexText txt_bpm  = NexText(0, 32, "t0"); //bpm
NexText txt_po2  = NexText(0, 33, "t1"); //bpm
static uint8_t ch0_data = LEVEL_LOW;
int speakerPin=2;
int value=0;
int c=0;
uint32_t dual_state;

//***********************************************
int LastTime = 0;
bool BPMTiming = false;
bool BeatComplete = false;
int BPM = 0;    
#define UpperThreshold 80
#define LowerThreshold 40    
int Signal; // holds the incoming raw data. Signal value can range from 0-1024.
char buffer[100] = {0};//bpm
//***********************************************

PulseOximeter muestra;    //création de l'objet

int periodo=1000;         // période de la mesure
int duracion=0;

void Deteccion()
{
}
char buf[100]={0};
int PO2;
//***********************************************

void setup() {
  pinMode(speakerPin,OUTPUT);
  nexInit(); //Initializes communication with the Nextion Display.
  if (!muestra.begin()) 
    {
        while(1);
    } 
    else 
    {
    }
muestra.setOnBeatDetectedCallback(Deteccion);

}

void loop() {
    value=500-analogRead(A0);
    ch0_data = value/5;
    s0.addValue(0, CH0_OFFSET + ch0_data);  

    muestra.update();
if (millis() - duracion > periodo) 
{
  PO2=muestra.getSpO2();
  duracion = millis();
  txt_po2.setText(buf); //bpm
  memset(buf, 0, sizeof(buf)); //bpm
  utoa(PO2, buf, 10);
}

    
    if (value > UpperThreshold) {
      if (BeatComplete) {
        BPM = millis() - LastTime;
        BPM = int(60 / (float(BPM) / 1000));
        BPMTiming = false;
        BeatComplete = false;
      }
      if (BPMTiming == false) {
        LastTime = millis();
        BPMTiming = true;
      }
    }
    if ((value < LowerThreshold) & (BPMTiming))
      BeatComplete = true;
     
    Signal = analogRead(A0);
    if (Signal > UpperThreshold) {
      tone(speakerPin, NOTE);
    } else {
      noTone(speakerPin);
    }
    c++;

    if(c>100){// display bpm
      txt_bpm.setText(buffer); //bpm
      memset(buffer, 0, sizeof(buffer)); //bpm
      itoa(BPM, buffer, 10); //bpm
      c=0;
    }
}
