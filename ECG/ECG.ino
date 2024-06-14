void setup() {
// initialize the serial communication:
Serial.begin(9600);
pinMode(6, INPUT); // Setup for leads off detection LO +
pinMode(5, INPUT); // Setup for leads off detection LO -
int FC=0; 
}
 
void loop() {
 
if((digitalRead(6) == 1)||(digitalRead(5) == 1)){
Serial.println('!');
}
else{
// send the value of analog input 0:
Serial.println(analogRead(A0));
}
//Wait for a bit to keep serial data from saturating
delay(10);

}
