
// PWM Read Functions
// use pin change interrupt

#define MAX_INPUT_NUM 2

volatile uint16_t oldTimer;
volatile uint8_t oldPinState;

static uint16_t pwm_in[2];
static uint16_t oldIntTimer[2];

void Init_PWM_In(void)
{
  uint8_t oldSREG = SREG;
  cli();

  // Init PWM input port
  // Input port: PD2(PCINT18) PD3(PCINT19)
  DDRD &= ~((1 << 2) | (1 << 3));
  PORTD |= ((1 << 2) | (1 << 3));

  PCMSK2 |= (1 << 2) | (1 << 3);
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
  uint16_t currentTimer;
  uint8_t currentPinState, changePin, checkPin;

  checkPin = 2;

  currentTimer = TCNT1;
  currentPinState = PIND & ((1 << 2) | (1 << 3));

  changePin = currentPinState ^ oldPinState;
  oldPinState = currentPinState;

  while(1){ 
    if(changePin & (1 << checkPin)){

      if(!(currentPinState & (1 << checkPin))){
        if(currentTimer < oldIntTimer[checkPin - 2]){
          pwm_in[checkPin - 2] = ((40000 - oldIntTimer[checkPin - 2]) + currentTimer) >> 1;
        }
        else{
          pwm_in[checkPin - 2] = (currentTimer - oldIntTimer[checkPin - 2]) >> 1;
        }
      }
      oldIntTimer[checkPin - 2] = currentTimer;
      changePin &= ~(1 << checkPin);
    }
    if(changePin <= 0 || checkPin >= (2 + MAX_INPUT_NUM - 1)){
      break;
    }
    checkPin ++;
  }
}

void getPWMIn(uint8_t length, uint16_t *data)
{
  for(uint8_t i = 0; i < length; i ++){
    data[i] = pwm_in[i];
  }
}


