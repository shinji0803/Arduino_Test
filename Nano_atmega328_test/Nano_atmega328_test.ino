
uint32_t fast_timer, mid_timer, slow_timer;
volatile uint16_t pwm_in[2];

void setup()
{
  Serial.begin(115200);

  Init_Port();

  attachInterrupt(0, PWM_Capture1, CHANGE);
}

void loop()
{
  uint32_t now = millis();

  if(now - slow_timer >= 1000){ // 1Hz Loop
    slow_timer = now;
    slow_loop();
  }

  if(now - mid_timer >= 50){ // 20Hz Loop
    mid_timer = now;
    mid_loop();
  }

  if(now - fast_timer >= 10){ // 100Hz Loop
    fast_timer = now;
    fast_loop();
  }
}

void slow_loop()
{
  PORTB = (PORTB & ~(1 << 5)) | ~(PORTB & (1 << 5));

  //Serial.println(interval >> 1);
}

void mid_loop()
{
  Serial.print(pwm_in[0]);
  Serial.print("\t");
  Serial.println(pwm_in[1]);
}

void fast_loop()
{
}

void PWM_Capture1(){
  static uint16_t oldTCNT1;
  uint16_t count;
  uint8_t oldSREG = SREG;

  cli();
  count = TCNT1;
  SREG = oldSREG;

  if(!((PIND >> 2) & 0x01)){
    if(count < oldTCNT1){
      pwm_in[0] = (40000 - oldTCNT1) + count;
    }
    else pwm_in[0] = count - oldTCNT1;
    
    pwm_in[0] = pwm_in[0] >> 1;
  }

  oldTCNT1 = count;
}





