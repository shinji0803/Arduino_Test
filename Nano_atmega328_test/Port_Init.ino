
void Init_Port()
{
  // PB0 = D8
  pinMode(8, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
  DDRB = (DDRB & ~(1 << 5))|(1 << 5); // Hertbeat LED

  uint8_t oldSREG = SREG;
  cli();
  TCNT1 = 0;
  TIFR1 = 0;

  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11);
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS11);

  ICR1 = 40000;
  OCR1A = 0xFFFF;
  OCR1B = 0xFFFF;
  
  SREG = oldSREG;
}


