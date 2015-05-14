/////////////////////////////////////
/// coding as "add-up mode"
/////////////////////////////////////

#define ON_OFF_SW_PIN 5

#define DECREASING_SLOPE 700
#define MAX_ADDUP 3000

#define MIDI_1ST_BYTE 0xB5
#define MIDI_2ND_BYTE 0x00

#define LOOP_DELAY 1

#define MINI_DIFF (double)MAX_ADDUP/127*2

//#define _DEBUG_

void setup() {
// initialize serial communication at 57600 bits per second:
Serial.begin(57600);
Bean.setLed(0,0,0);
pinMode(ON_OFF_SW_PIN, INPUT);
digitalWrite(ON_OFF_SW_PIN, HIGH);
}

double sum = 0.0;
double previous_sum = sum;
 
// the loop routine runs over and over again forever:
void loop() {
  AccelerationReading accel = {0, 0, 0};
 
  while(digitalRead(ON_OFF_SW_PIN) == LOW){;}
  
  if(sum > MAX_ADDUP){ sum = MAX_ADDUP; }
  
  accel = Bean.getAcceleration();
  sum += abs(accel.xAxis) + abs(accel.yAxis) + abs(accel.zAxis);
  if(sum > 0){
    sum -= DECREASING_SLOPE;
    if(sum < 0){ sum = 0.0; }
  }
  
//  if(abs(sum - previous_sum) > MINI_DIFF){

  if(abs(sum - previous_sum) > 1){
    Serial.print("$");
    Serial.print(MIDI_1ST_BYTE);
    Serial.print(",");
    Serial.print(MIDI_2ND_BYTE);
    Serial.print(",");
    int temp = (int)(sum/MAX_ADDUP * 127);
    if(temp > 127){ temp = 127; }
    Serial.print(temp);//, HEX);
    Serial.println("%");
    previous_sum = sum;
  }
  #ifdef _DEBUG_
    Serial.println(sum);
  #endif

  Bean.sleep(LOOP_DELAY);
}
