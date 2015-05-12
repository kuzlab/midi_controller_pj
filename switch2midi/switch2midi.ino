#include "assign_map.h"

#include <MIDI.h>


uint8_t switch_state[DSW_NUM] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t temp[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

uint16_t ad_value[ASW_NUM] = {0, 0, 0, 0, 0, 0};

#define DEBUG 0
#define ANALOG_SLIDER_ENABLE 1

#define LOOP_DELAY 50

void setup()
{
  Serial.begin(57600);
  
//  Serial1.begin(31250);
  
  delay(3000);
  
  for(int i = 0; i < DSW_NUM; i++){
    pinMode(dpins[i], INPUT);
    digitalWrite(dpins[i], HIGH);
    switch_state[i] = digitalRead(dpins[i]);    
  }
#if ANALOG_SLIDER_ENABLE
  for(int i = 0; i < ASW_NUM; i++){
    ad_value[i] = analogRead(apins[i]);
  }
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
  
  uint16_t ad_temp;

#if ANALOG_SLIDER_ENABLE
  for(int i = 0; i < ASW_NUM; i++){
    ad_temp = analogRead(apins[i]);
    #if DEBUG
      Serial.print("AD = ");
      Serial.println(ad_temp);
    #endif
    
    if(abs(ad_temp - ad_value[i]) > 5* AD_DIV){    
        Serial.print('$');
        Serial.print(MIDI_AD0_0);
//        delay(1);
        Serial.print(',');
        Serial.print(MIDI_AD0_1);
//        delay(1);
        Serial.print(',');
        ad_value[i] = ad_temp;
        ad_temp = (uint8_t)((double)ad_temp/AD_DIV);
        if(ad_temp > 0x7F){ad_temp = 0x7F;}
        Serial.print(ad_temp);
        Serial.println('%');
//        delay(10);
    }
#endif  
  for(int i = 0; i < DSW_NUM; i++){
    temp[i] = digitalRead(dpins[i]);    

    if(temp[i] != switch_state[i] && temp[i] == 0){
//      Serial1.write(mapping[3*i]);
//      Serial1.write(mapping[3*i + 1]);
//      Serial1.write(mapping[3*i + 2]);
      uint8_t first_byte = 0xb0 + 2 * switch_state[0] + switch_state[1];
      uint8_t second_byte = 0x00 + i;

      Serial.print("$");      
      Serial.print(first_byte);//mapping[3*i]);//, HEX);
//      delay(1);
      Serial.print(",");
      //Serial.print(' ');
      Serial.print(second_byte);//mapping[3*i + 1]);//, HEX);
      //Serial.print(' ');
//      delay(1);      
      Serial.print(",");
      Serial.print(127);//mapping[3*i + 2]);//, HEX);
//      Serial.print('\n');
      Serial.println('%');
//      delay(1);      
    }
    
    switch_state[i] = temp[i];
  }
  delay(LOOP_DELAY);
}

