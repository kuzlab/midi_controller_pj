#include "assign_map.h"

#include <MIDI.h>

uint8_t switch_state[6] = {0, 0, 0, 0, 0, 0};
uint8_t temp[6] = {0, 0, 0, 0, 0, 0};

uint16_t ad_value = 0;

#define DEBUG 0
#define ANALOG_SLIDER_ENABLE 1

void setup()
{
  Serial.begin(38400);
  
//  Serial1.begin(31250);
  
  delay(5000);
  
  for(int i = 0; i < 6; i++){
    pinMode(pins[i], INPUT);
    digitalWrite(pins[i], HIGH);
    switch_state[i] = digitalRead(pins[i]);    
  }
#if ANALOG_SLIDER_ENABLE
  ad_value = analogRead(PIN_AD0);
#endif

#if DEBUG
  Serial.print("AD_MAX = ");
  Serial.println(AD_MAX);
  Serial.print("AD_DIV = ");
  Serial.println(AD_DIV);
#endif
}

void loop()
{
  uint8_t data[3];
  
  uint16_t ad_temp = analogRead(PIN_AD0);
#if DEBUG  
  Serial.print("AD = ");
  Serial.println(ad_temp);
#endif

#if ANALOG_SLIDER_ENABLE
  if(abs(ad_temp - ad_value) > 2* AD_DIV){    
      Serial.print('$');
      Serial.print(MIDI_AD0_0);
//      delay(1);
      Serial.print(',');
      Serial.print(MIDI_AD0_1);
//      delay(1);
      Serial.print(',');
      ad_value = ad_temp;
      ad_temp = (uint8_t)((double)ad_temp/AD_DIV);
      if(ad_temp > 0x7F){ad_temp = 0x7F;}
      Serial.print(ad_temp);
      Serial.println('$');
//      delay(10);
  }
#endif  
  for(int i = 0; i < 6; i++){
    temp[i] = digitalRead(pins[i]);    

    if(temp[i] != switch_state[i] && temp[i] == 0){
//      Serial1.write(mapping[3*i]);
//      Serial1.write(mapping[3*i + 1]);
//      Serial1.write(mapping[3*i + 2]);

      Serial.print("$");      
      Serial.print(mapping[3*i]);//, HEX);
//      delay(1);
      Serial.print(",");
      //Serial.print(' ');
      Serial.print(mapping[3*i + 1]);//, HEX);
      //Serial.print(' ');
//      delay(1);      
      Serial.print(",");
      Serial.print(mapping[3*i + 2]);//, HEX);
//      Serial.print('\n');
      Serial.println('$');
      delay(1);      
    }
    
    switch_state[i] = temp[i];
  }
  delay(50);
}

