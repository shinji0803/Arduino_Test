
uint32_t fast_timer, mid_timer, slow_timer;

extern volatile uint8_t change;
extern volatile uint16_t pwm_in;

void setup()
{
  Serial.begin(115200);
  DDRB |= (1 << 5);
  
  Init_PWM_In();
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
  PORTB ^= (1 << 5);

}

void mid_loop()
{
  Serial.print(pwm_in);
  Serial.print("\t");
  Serial.println(change);
}

void fast_loop()
{
}





