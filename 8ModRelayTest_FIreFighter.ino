/* Langster's Test Code for 
 *  Elegoo 8 Channel Relay PCB
 *  07/07/2019
 *  Test circuit output is a Green 5 mm LED 
 *  and a 220 Ohm resistor connected
 *  between common and Normally Closed screw
 *  terminals on the channel 1 relay outputs
 *  
 *  The Elegoo relay module is connected to
 *  an Arduino Uno R3 on the following pins:
 *  
 *  GND connects to GND of the Arduino
 *  IN1 connects to Pin 11 of the Arduino
 *  IN1 connects to Pin 10 of the Arduino
 *  IN2 connects to Pin 9 of the Arduino
 *  IN3 connects to Pin 8 of the Arduino
 *  IN4 connects to Pin 7 of the Arduino
 *  IN5 connects to Pin 6 of the Arduino
 *  IN6 connects to Pin 5 of the Arduino
 *  IN7 connects to Pin 4 of the Arduino
 *  VCC connects to Vin pin of the Arduino
 */

int eightChanRelayIN1 = 11;   //variable for relay channel 1 drive pin
int eightChanRelayIN2 = 10;   //variable for relay channel 2 drive pin
int eightChanRelayIN3 = 9;   //variable for relay channel 3 drive pin
int eightChanRelayIN4 = 8;   //variable for relay channel 4 drive pin
int eightChanRelayIN5 = 7;   //variable for relay channel 5 drive pin
int eightChanRelayIN6 = 6;   //variable for relay channel 6 drive pin
int eightChanRelayIN7 = 5;   //variable for relay channel 7 drive pin
int eightChanRelayIN8 = 4;   //variable for relay channel 8 drive pin

int relayDwellTimeMS1 = 100; //variable for setting the dwell time a relay is actuated for
int relayDwellTimeMS2 = 7500; //variable for setting the dwell time a relay is actuated for
int relayDwellTimeMS3 = 5000; //variable for setting the dwell time a relay is actuated for
int relayDwellTimeMS4 = 2500; //variable for setting the dwell time a relay is actuated for

int relayDwellTimeMS5 = 100; //variable for setting the dwell time a relay is actuated for
int relayDwellTimeMS6 = 750; //variable for setting the dwell time a relay is actuated for
int relayDwellTimeMS7 = 500; //variable for setting the dwell time a relay is actuated for
int relayDwellTimeMS8 = 250; //variable for setting the dwell time a relay is actuated for



void setup() {

Serial.begin(9600);      // open the serial port at 9600 bps:
pinMode(eightChanRelayIN1, OUTPUT); //set the relay drive pin for channel 1 to be an output
pinMode(eightChanRelayIN2, OUTPUT); //set the relay drive pin for channel 2 to be an output
pinMode(eightChanRelayIN3, OUTPUT); //set the relay drive pin for channel 3 to be an output
pinMode(eightChanRelayIN4, OUTPUT); //set the relay drive pin for channel 4 to be an output
pinMode(eightChanRelayIN5, OUTPUT); //set the relay drive pin for channel 5 to be an output
pinMode(eightChanRelayIN6, OUTPUT); //set the relay drive pin for channel 6 to be an output
pinMode(eightChanRelayIN7, OUTPUT); //set the relay drive pin for channel 7 to be an output
pinMode(eightChanRelayIN8, OUTPUT); //set the relay drive pin for channel 8 to be an output

}

void loop() {
digitalWrite(eightChanRelayIN1, LOW);   //switch relay channel 1
//delay(relayDwellTimeMS1);                //wait for the dwell time (10000 ms)
digitalWrite(eightChanRelayIN1, HIGH);  //switch relay channel 1
//delay(relayDwellTimeMS2);               //wait for the dwell time (10000 ms)
//digitalWrite(eightChanRelayIN1, LOW);   //switch relay channel 1
//delay(relayDwellTimeMS1);                //wait for the dwell time (10000 ms)
//
digitalWrite(eightChanRelayIN2, LOW);   //switch relay channel 2
//delay(relayDwellTimeMS1);                //wait for the dwell time (7500 ms)
digitalWrite(eightChanRelayIN2, HIGH);  //switch relay channel 2
//delay(relayDwellTimeMS2);                //wait for the dwell time (7500 ms)
//digitalWrite(eightChanRelayIN2, LOW);   //switch relay channel 2
//delay(relayDwellTimeMS1);                //wait for the dwell time (7500 ms)

digitalWrite(eightChanRelayIN3, LOW);   //switch relay channel 3
//delay(relayDwellTimeMS1);                //wait for the dwell time (5000 ms)
digitalWrite(eightChanRelayIN3, HIGH);  //switch relay channel 3
//delay(relayDwellTimeMS1);                //wait for the dwell time (5000 ms)
//digitalWrite(eightChanRelayIN3, LOW);   //switch relay channel 3
//delay(relayDwellTimeMS1);                //wait for the dwell time (5000 ms)

digitalWrite(eightChanRelayIN4, LOW);   //switch relay channel 4
//delay(relayDwellTimeMS1);                //wait for the dwell time (2500 ms)
digitalWrite(eightChanRelayIN4, HIGH);  //switch relay channel 4
//delay(relayDwellTimeMS1);                //wait for the dwell time (2500 ms)
//digitalWrite(eightChanRelayIN4, LOW);   //switch relay channel 4
//delay(relayDwellTimeMS1);                //wait for the dwell time (2500 ms)

}
