#include <Wire.h>

#define VL6180X_ADD 41

uint32_t fast_timer, mid_timer, slow_timer;

void setup()
{
  Serial.begin(115200);
  DDRB |= (1 << 5);
  
  Wire.begin();
  VL6180X_StartMeasure();
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

  Serial.println(VL6180X_Who());
}

void mid_loop()
{
  Serial.println(VL6180X_GetRange());
}

void fast_loop()
{
}


