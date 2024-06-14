#include <TaskScheduler.h>
//#include <FIR.h>
#define pot A0
#define AVERAGES 40

float averagedSample(uint8_t averages);
float calcNewMovingAverage(uint8_t averages);

 

void Muestreo();
Task Tarea_muestreo(5, TASK_FOREVER, &Muestreo);
Scheduler runner;
float result, result2, result3;
float movingAverageBuffer [AVERAGES];

 


float EMA_ALPHA_LOW = 0.15;
float EMA_ALPHA_HIGH = 0.45;
int EMA_LP_LOW = 0;
int EMA_LP_HIGH = 0;
int EMA_BP = 0;
int EMA_BS = 0;

 

void setup()
{  
  Serial.begin(9600);
  
  runner.addTask(Tarea_muestreo);
  Tarea_muestreo.enable();
  

}

 

void loop()
{
  runner.execute();
}

 

void Muestreo()
{  
  result2 = averagedSample(AVERAGES);
  EMA_LP_LOW = EMA_ALPHA_LOW * result2 + (1 - EMA_ALPHA_LOW) * EMA_LP_LOW;
  EMA_LP_HIGH = EMA_ALPHA_HIGH * result2 + (1 - EMA_ALPHA_HIGH) * EMA_LP_HIGH;
  EMA_BP = EMA_LP_HIGH - EMA_LP_LOW;
 

  //Serial.println(analogRead(A0));
  
  Serial.println(EMA_BP);
  //Serial.print(result2);
  //Serial.print(fir_filter.processReading(result));
  //Serial.print(fir_filter.processReading(EMA_BP));
  Serial.println();
}

 


int averagedSample(int averages)
{
 int Sum = 0;  
 for(int i = 0; i < averages; i++)
  {
    Sum += analogRead(A0);
  }
  return(Sum/averages);
}
