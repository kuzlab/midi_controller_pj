#define ON_OFF_SW_PIN 5

void setup() {
// initialize serial communication at 57600 bits per second:
Serial.begin(57600);
Bean.setLed(0,0,0);
pinMode(ON_OFF_SW_PIN, INPUT);
digitalWrite(ON_OFF_SW_PIN, HIGH);
}
 
// the loop routine runs over and over again forever:
void loop() {
  AccelerationReading accel = {0, 0, 0};
 
  while(digitalRead(ON_OFF_SW_PIN) == LOW){;}
  
  accel = Bean.getAcceleration();
 
//uint16_t r = (abs(accel.xAxis)) / 4;
//uint16_t g = (abs(accel.yAxis)) / 4;
//uint16_t b = (abs(accel.zAxis)) / 4;
 
//Bean.setLed((uint8_t)r,(uint8_t)g,(uint8_t)b);

//String senddata = "$" + char(accel.xAxis) + "," + char(accel.yAxis) + "," + char(accel.zAxis) + "$";

//uint8_t buffer[1];
//buffer[0] = uint8_t(r/2);
  Serial.print("$");
  Serial.print(accel.xAxis);
  Serial.print(",");
  Serial.print(accel.yAxis);
  Serial.print(",");
  Serial.print(accel.zAxis);
  Serial.print("$");


//Serial.write("hello");
//Serial.print("hello");
 
//Bean.sleep(10);
}
