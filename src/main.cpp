//SEAI - Distribution 
//Servos using Arduino Functions
#include <Arduino.h>
#include <Servo.h>

#define FCPU 16000000ul

int angle = 0; 
uint8_t selected_servo = 0; 
uint8_t addr; 
uint8_t aux; 

void setup() {

  // SERVO as OUT
  DDRE |= 1 << PINE4; //Digital Pin 2, OC3B
  DDRE |= 1 << PINE5; //Digital Pin 3, OC3C
  DDRB |= 1 << PINB5; //Digital Pin 11, OC1A 
  DDRE |= 1 << PINE3; //Digital Pin 5, OC3A
  DDRH |= 1 << PINH3; //Digital Pin 6, OC4A
  DDRH |= 1 << PINH4; //Digital Pin 7, OC4B
  DDRH |= 1 << PINH5; //Digital Pin 8, OC4C

  //Fast PWM (TOP: ICR3, Update on BOTTOM, TOV3 Flag on TOP)
  TCNT3 = 0; 
  ICR3 = 2499;
  TCCR3A |= (1 << WGM31) | (1 << COM3A1) | (1 << COM3B1) | (1 << COM3C1); //Clear OC3A/B/C on Compare Match, set OC3A/B/C at BOTTOM (non-inverting mode)
	TCCR3B |= (1 << WGM32) | (1 << WGM33) | (1 << CS31); 

  TCNT4 = 0; 
  ICR4 = 2499;
  TCCR4A |= (1 << WGM41) | (1 << COM4A1) | (1 << COM4B1) | (1 << COM4C1); 
	TCCR4B |= (1 << WGM42) | (1 << WGM43) | (1 << CS41); 

  TCNT1 = 0; 
  ICR1 = 2499;
  TCCR1A |= (1 << WGM11) | (1 << COM1A1); 
	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11); 

  OCR1A = 175;
  OCR3A = 175;
  OCR3B = 175;
  OCR3C = 175;
  OCR4A = 175;
  OCR4B = 175;
  OCR4C = 175;

  Serial.begin(9600);  // initialize UART with baud rate of 9600 bps
}

void loop() {

  if(Serial.available() >= 2) { // wait for buffer to have data

    aux = Serial.read() >> 8; //read MSB (ADDR) from serial buffer
    addr = aux >> 4; //read MSB (ADDR) from serial buffer
    selected_servo = Serial.read();  //read LSB (DATA) from serial buffer

    if(addr == 0x03){ //message is to Distribution
      switch (selected_servo) {
        case 1:
          OCR3B = 600;
          delay(15);
          // now scan back from 180 to 0 degrees
          OCR3B = 175;
          break;
        
        case 2:
          OCR3C = 600;
          delay(15);
          // now scan back from 180 to 0 degrees
          OCR3C = 175;
          break;

        case 3:
          OCR1A = 600;
          delay(15);
          // now scan back from 180 to 0 degrees
          OCR1A = 175;
          break;

        case 4:
          OCR3A = 600;
          delay(15);
          // now scan back from 180 to 0 degrees
          OCR3A = 175;
          break;

        case 5:
          OCR4A = 600;
          delay(15);
          // now scan back from 180 to 0 degrees
          OCR4B = 175;
          break; 

        case 6:
          OCR4B = 600;
          delay(15);
          // now scan back from 180 to 0 degrees
          OCR4B = 175;
          break;

        case 7:
          OCR4C = 600;
          delay(15);
          // now scan back from 180 to 0 degrees
          OCR4C = 175;
          break;
      
        default:
          break;
      }
    }  
  }
}