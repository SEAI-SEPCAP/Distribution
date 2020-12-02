//SEAI - Distribution 
//Servos using Arduino Functions
#include <Arduino.h>
#include <Servo.h>

#define FCPU 16000000ul

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;

int angle = 0; 
int selected_servo = 0; 
char data_rcvd; 

void setup() {
  // put your setup code here, to run once:
  servo1.attach(1);
  servo2.attach(2);
  servo3.attach(3);
  servo4.attach(4);
  servo5.attach(5);
  servo6.attach(6);
  servo7.attach(7);
  
  servo1.write(angle);
  servo2.write(angle);
  servo3.write(angle);
  servo4.write(angle);
  servo5.write(angle);
  servo6.write(angle);
  servo7.write(angle);

  Serial.begin(9600);       // initialize UART with baud rate of 9600 bps

}

void loop() {

  if(Serial.available()) { // wait for buffer to be available
    data_rcvd = Serial.read();   // read one byte from serial buffer and save to data_rcvd

    if(data_rcvd == '1') selected_servo = 1; 
    else if(data_rcvd == '2') selected_servo = 2; 
    else if(data_rcvd == '3') selected_servo = 3; 
    else if(data_rcvd == '4') selected_servo = 4; 
    else if(data_rcvd == '5') selected_servo = 5; 
    else if(data_rcvd == '6') selected_servo = 6; 
    else if(data_rcvd == '7') selected_servo = 7; 
    else selected_servo = 0; 
  }
  switch (selected_servo) {
    case 1:
        for(angle = 0; angle <= 100; angle = angle+10)  
        {                                  
          servo1.write(angle); 
          delay(15); 
        } 
    	delay(15);
        // now scan back from 180 to 0 degrees
        for(angle = 100; angle >= 0; angle = angle-10)    
        {                                
          servo1.write(angle);  
          delay(15); 
        } 
        break;
    
    case 2:
        for(angle = 0; angle <= 100; angle = angle+10)  
        {                                  
          servo2.write(angle); 
          delay(15); 
        } 
    	delay(15);
        // now scan back from 180 to 0 degrees
        for(angle = 100; angle >= 0; angle = angle-10)    
        {                                
          servo2.write(angle);  
          delay(15); 
        } 
        break;

    case 3:
        for(angle = 0; angle <= 100; angle = angle+10)  
        {                                  
          servo3.write(angle); 
          delay(15); 
        } 
    	delay(15);
        // now scan back from 180 to 0 degrees
        for(angle = 100; angle >= 0; angle = angle-10)    
        {                                
          servo3.write(angle);  
          delay(15); 
        } 
        break;   

    case 4:
        for(angle = 0; angle <= 100; angle = angle+10)  
        {                                  
          servo4.write(angle); 
          delay(15); 
        } 
    	delay(15);
        // now scan back from 180 to 0 degrees
        for(angle = 100; angle >= 0; angle = angle-10)    
        {                                
          servo4.write(angle);  
          delay(15); 
        } 
        break;   


    case 5:
        for(angle = 0; angle <= 100; angle = angle+10)  
        {                                  
          servo5.write(angle); 
          delay(15); 
        } 
    	delay(15);
        // now scan back from 180 to 0 degrees
        for(angle = 100; angle >= 0; angle = angle-10)    
        {                                
          servo5.write(angle);  
          delay(15); 
        } 
        break;   


    case 6:
        for(angle = 0; angle <= 100; angle = angle+10)  
        {                                  
          servo6.write(angle); 
          delay(15); 
        } 
    	delay(15);
        // now scan back from 180 to 0 degrees
        for(angle = 100; angle >= 0; angle = angle-10)    
        {                                
          servo6.write(angle);  
          delay(15); 
        } 
        break;

    case 7:
        for(angle = 0; angle <= 100; angle = angle+10)  
        {                                  
          servo7.write(angle); 
          delay(15); 
        } 
    	delay(15);
        // now scan back from 180 to 0 degrees
        for(angle = 100; angle >= 0; angle = angle-10)    
        {                                
          servo7.write(angle);  
          delay(15); 
        } 
        break;
   
    default:
      break;
  }

}