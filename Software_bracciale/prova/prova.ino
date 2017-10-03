
int blinkPin = 8;
int blinkPin_2 = 13;
int num = 0, led = 0;

void setup() {

  pinMode(blinkPin,OUTPUT);
  pinMode(blinkPin_2,OUTPUT);
  
  // Initializes Timer1
  TCCR1A = 0x00; // DISABLE OUTPUTS AND PWM ON DIGITAL PINS 9 & 10
  TCCR1B = 0b00001101; // CTC, PRE 1024
  TCCR1C = 0x00; // DON'T FORCE COMPARE
  OCR1A = 0xFF; // 255
  TIMSK1 = 0x02; // ENABLE INTERRUPT ON MATCH BETWEEN TIMER1 AND OCR2A
  
  // IMPULSO OGNI 0.02s 50Hz (0.19968s)
  TCCR2A = 0x02;     // DISABLE PWM ON DIGITAL PINS 3 AND 11, AND GO INTO CTC MODE
  TCCR2B = 0x07;     // DON'T FORCE COMPARE, 1024 PRESCALER
  OCR2A = 0X4D;      // 77
  TIMSK2 = 0x02;     // ENABLE INTERRUPT ON MATCH BETWEEN TIMER2 AND OCR2A
  sei();             // MAKE SURE GLOBAL INTERRUPTS ARE ENABLED

}

void loop() {
  
  if(led == 0){
  digitalWrite(blinkPin,LOW);
  digitalWrite(blinkPin_2,LOW);
  }

  else {
    delay(100);
    led = 0;
  }

}

ISR(TIMER2_COMPA_vect){             
  cli();                                   // disable interrupts while we do this

  num++;
  
  if(num == 500){ //5s
    digitalWrite(blinkPin,HIGH); 
    led = 1;
    num = 0;
  }
  
  sei();                                   // enable interrupts when youre done!
}// end isr

ISR(TIMER1_COMPA_vect){                       
  cli();
  
    digitalWrite(blinkPin_2,HIGH);
    led = 1;
  
  sei();                                   // enable interrupts when youre done!
}// end isr 
