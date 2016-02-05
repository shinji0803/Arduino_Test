
// PWM Read Functions
// use pin change interrupt

volatile uint8_t old, change;
volatile uint16_t oldTimer,pwm_in;

void Init_PWM_In(void)
{
  uint8_t oldSREG = SREG;
  cli();
  
  // Init PWM input port
  // Input port: PD2(PCINT18) PD3(PCINT19) PD4(PCINT20) PD5(PCINT21) 
  DDRD &= ~((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5));
  PORTD |= ((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5));
  
  PCMSK2 |= (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);
  PCICR |= (1 << 2);
  
  // Init Timer1
  TCNT1 = 0;
  TIFR1 = 0;

  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11);
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS11);

  ICR1 = 40000;
  OCR1A = 0xFFFF;
  OCR1B = 0xFFFF;
  
  SREG = oldSREG;
}

ISR(PCINT2_vect)
{
  uint16_t currentTimer = TCNT1;
  uint16_t temp;
  uint8_t current = PIND;
  change = current ^ old;
  old = current;
  
  if(change & (1 << 2)){
    if(currentTimer < oldTimer){
      temp = (40000 - oldTimer) + currentTimer;
    }
    else{
      temp = currentTimer - oldTimer;
    }
    oldTimer = currentTimer;
    if(temp < 6000) pwm_in = temp >> 1;
  }
      
}
