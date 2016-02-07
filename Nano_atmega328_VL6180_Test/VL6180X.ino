
uint8_t VL6180X_Who()
{
  int result;
  uint8_t data;
  
  Wire.beginTransmission(VL6180X_ADD);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(VL6180X_ADD, 1);
  data = Wire.read();
  
  // return 0xB4 if VL6180X connected correctly
  return data;
}

void VL6180X_StartMeasure()
{
  Wire.beginTransmission(VL6180X_ADD);
  Wire.write(0x16); // SYSTEM_FRESH_OUT_OF_RESET = 0x018
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  
  Wire.beginTransmission(VL6180X_ADD);
  Wire.write(0x1B); // SYSRANGE_INTERMEASUREMENT_PERIOD = 0x01B
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  
  Wire.beginTransmission(VL6180X_ADD);
  Wire.write(0x18); // SYSRANGE_START = 0x018
  Wire.write(0x00);
  Wire.write(0x03);
  Wire.endTransmission();
}

uint8_t VL6180X_GetRange()
{
  Wire.beginTransmission(VL6180X_ADD);
  Wire.write(0x62); // RESULT_RANGE_VAL = 0x062
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(VL6180X_ADD, 1);
  
  return Wire.read();  
}
  
