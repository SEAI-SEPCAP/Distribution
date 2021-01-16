//SEAI - Distribution 
//Servos using Arduino Functions
#include <Arduino.h>
#include <Servo.h>
#include <avr/io.h>

#define FCPU 16000000ul

#define PWMTOP 39999   // TIMER1 TOP for PRESC=8
#define P_FCLK 2000 // (16M/1000)/8

#define MAX1 1500 // aberto
#define ZERO1 2800 
#define MAX3 1400 // aberto
#define ZERO3 2800 
#define MAX2 1600
#define ZERO2 2800
#define MAX4 1700
#define ZERO4 2800
#define MAX5 1900
#define ZERO5 3100
#define MAX6 2700
#define ZERO6 3700
#define MAX7 1800
#define ZERO7 3400

double angle = 0; 
uint8_t selected_servo = 0; 
uint8_t addr; 
uint8_t aux; 

void setup_servos(){

    // SERVO as OUT
  DDRE |= 1 << PINE4; //Digital Pin 2, OC3B
  DDRE |= 1 << PINE5; //Digital Pin 3, OC3C
  DDRB |= 1 << PINB5; //Digital Pin 11, OC1A 
  DDRE |= 1 << PINE3; //Digital Pin 5, OC3A
  DDRH |= 1 << PINH3; //Digital Pin 6, OC4A
  DDRH |= 1 << PINH4; //Digital Pin 7, OC4B
  DDRH |= 1 << PINH5; //Digital Pin 8, OC4C

}

void setup_timer_servos() {

  TCNT1 = 0;     // Set timer1 count zero
  ICR1 = PWMTOP; // TOP count for timer1 -> FPWM = FOSC/(N*(1+TOP)) with
                  // FPWM=50 and N=8
  TCCR1A = _BV(COM1A1) | (0 << COM1A0);            // Non inverter PWM
  TCCR1A |= _BV(WGM11) | (0 << WGM10);             // Fast PWM: TOP: ICR1
  TCCR1B = _BV(WGM13) | _BV(WGM12);                // Fast PWM: TOP: ICR1
  TCCR1B |= (0 << CS12) | _BV(CS11) | (0 << CS10); // Preesc = 8

  TCNT3 = 0;     // Set timer1 count zero
  ICR3 = PWMTOP; // TOP count for timer1 -> FPWM = FOSC/(N*(1+TOP)) with
                  // FPWM=50 and N=8
  TCCR3A = _BV(COM3B1) | _BV(COM3C1)| _BV(COM3A1) | (0 << COM3A0);            // Non inverter PWM
  TCCR3A |= _BV(WGM31) | (0 << WGM30);             // Fast PWM: TOP: ICR1
  TCCR3B = _BV(WGM33) | _BV(WGM32);                // Fast PWM: TOP: ICR1
  TCCR3B |= (0 << CS32) | _BV(CS31) | (0 << CS30); // Preesc = 8

  TCNT4 = 0;     // Set timer1 count zero
  ICR4 = PWMTOP; // TOP count for timer1 -> FPWM = FOSC/(N*(1+TOP)) with
                  // FPWM=50 and N=8
  TCCR4A = _BV(COM4B1) | _BV(COM4C1)| _BV(COM4A1) | (0 << COM4A0);            // Non inverter PWM
  TCCR4A |= _BV(WGM41) | (0 << WGM40);             // Fast PWM: TOP: ICR1
  TCCR4B = _BV(WGM43) | _BV(WGM42);                // Fast PWM: TOP: ICR1
  TCCR4B |= (0 << CS42) | _BV(CS41) | (0 << CS40); // Preesc = 8

  OCR3B = ZERO1;
  OCR3C = ZERO2;
  OCR1A = ZERO3;
  OCR3A = ZERO4;
  OCR4A = ZERO5;
  OCR4B = ZERO6;
  OCR4C = ZERO7;

}

void setup_uart(){

  /* Set baud rate */
  long BAUD = 9600;
  int UBBR_VAL = 16000000/(BAUD*16)-1;
  UBRR0H = (uint8_t) UBBR_VAL>>8; // Define Baudrate
  UBRR0L = (uint8_t) UBBR_VAL;

  UCSR0C |= (3<<UCSZ01);  // 8 Data bits configuration
  UCSR0C |= (0<<USBS0);   // 1 stop bit
  UCSR0B |= (1<<RXEN0) | (1<<TXEN0); // Activate Rx, Tx 
 
}

void setup(){
 
  setup_servos();
  setup_timer_servos();
  setup_uart();
  selected_servo = 1; 

}

void receive_Data(){
  
  while(!(UCSR0A & (1<<RXC0))); // Waits until has new data to be read
  aux = UDR0;                   // Saves the data to be analised below
  addr = aux >> 4;              //read MSB (ADDR) from serial buffer
  while(!(UCSR0A & (1<<RXC0))); // Waits until has new data to be read
  selected_servo = UDR0;        // Saves the data to be analised below

}

void send_Data(uint8_t Data){
  
  while(!(UCSR0A & (1<<UDRE0))); // Wait until the buffer is empty
  UDR0 = Data;                   // Copy to UDR0 the correspondent data
  
}

void loop() {

  receive_Data();

  if(addr == 0x03){ //message is to Distribution
  switch (selected_servo) {
      case 1:
        delay(800);
        OCR3B = MAX1;
        delay(800);
        OCR3B = ZERO1;
        break;
      
      case 2:
        delay(800);
        OCR3C = MAX2;
        delay(800);
        // now scan back from 180 to 0 degrees
        OCR3C = ZERO2;
        break;

      case 3:
        delay(800);
        OCR1A = MAX3;
        delay(800);
        // now scan back from 180 to 0 degrees
        OCR1A = ZERO3;
        break;

      case 4:
        delay(800);
        OCR3A = MAX4;
        delay(800);
        // now scan back from 180 to 0 degrees
        OCR3A = ZERO4;
        break;

      case 5:
        delay(800);
        OCR4A = MAX5;
        delay(800);
        // now scan back from 180 to 0 degrees
        OCR4A = ZERO5;
        break; 

      case 6:
        delay(800);
        OCR4B = MAX6;
        delay(800);
        // now scan back from 180 to 0 degrees
        OCR4B = ZERO6;
        break;

      case 7:
        delay(800);
        OCR4C = MAX7;
        delay(800);
        // now scan back from 180 to 0 degrees
        OCR4C = ZERO7;
        break;

      default:
        break;

    }

  selected_servo ++;
  }  

}