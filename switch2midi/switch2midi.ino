#include "assign_map.h"

#include <MIDI.h>


uint8_t switch_state[DSW_NUM] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t temp[DSW_NUM]         = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

uint16_t ad_value[ASW_NUM] = {0, 0, 0, 0, 0, 0};

#define DEBUG 0
#define ANALOG_SLIDER_ENABLE 1

#define LOOP_DELAY 50
#define SEND_MIDI_DELAY 100

const char dpins[DSW_NUM] = {PIN_SW0, PIN_SW1, PIN_SW2, PIN_SW3, PIN_SW4, PIN_SW5
                            , PIN_SW6, PIN_SW7, PIN_SW8, PIN_SW9, PIN_MSW0_0, PIN_MSW0_1
                            , PIN_MSW1_0, PIN_MSW1_1 };
const char apins[ASW_NUM] = { PIN_AD0, PIN_AD1, PIN_AD2, PIN_AD3, PIN_AD4, PIN_AD5 };

void setup()
{
  Serial.begin(57600);  
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
      Serial.print(i);
      Serial.print(": ad_temp = ");
      Serial.println(ad_temp);
      Serial.print("ad_value[i] = ");
      Serial.println(ad_value[i]);
      Serial.print("AD_DIV ");
      Serial.println(AD_DIV);
    #endif
    
    if(abs(ad_temp - ad_value[i]) > 10* AD_DIV){
      uint8_t first_byte = 0xb0 + 2 * switch_state[0] + switch_state[1];
      uint8_t second_byte = 0x20 + i;
      Serial.print('$');
      Serial.print(first_byte);
      Serial.print(',');
      Serial.print(second_byte);
      Serial.print(',');
      ad_value[i] = ad_temp;
      ad_temp = (uint8_t)((double)ad_temp/AD_DIV);
      if(ad_temp > 0x7F){ad_temp = 0x7F;}
      Serial.print(ad_temp);
      Serial.println('%');
      delay(SEND_MIDI_DELAY);
    }
  }
#endif  
  for(int i = 0; i < DSW_NUM; i++){
    temp[i] = digitalRead(dpins[i]);    

    if(temp[i] != switch_state[i] && temp[i] == 0){
      uint8_t first_byte = 0xb0 + 2 * switch_state[0] + switch_state[1];
      uint8_t second_byte = 0x00 + i;

      Serial.print("$");      
      Serial.print(first_byte);
      Serial.print(",");
      Serial.print(second_byte);
      Serial.print(",");
      Serial.print(127);
      Serial.println('%');
      delay(SEND_MIDI_DELAY);
    }    
    switch_state[i] = temp[i];
  }
  delay(LOOP_DELAY);
  
}

