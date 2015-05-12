#include "assign_map.h"

#define PIN0 13
#define PIN1 14
#define PIN2 15
#define PIN3 16
#define PIN4 17
#define PIN5 18
#define PIN6 19
#define PIN7 20
#define PIN8 21

#define SW0 2
#define SW1_0 0
#define SW1_1 1

#define LOOP_DELAY 30
#define SEND_MIDI_DELAY 100

//#define _DEBUG_

int inpins[5] = {
  PIN0,
  PIN2,
  PIN4,
  PIN6,
  PIN8
};  

int outpins[4] = {
  PIN1,
  PIN3,
  PIN5,
  PIN7,
};

uint8_t switch_state[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

#define THD 800

void print_inpins_all(){
  for(int i=0;i<4;i++){
//    Serial.print(digitalRead(inpins[i]));
//    Serial.print(' ');
//    Serial.print(analogRead(inpins[i]));
    if(analogRead(inpins[i]) > THD){
      Serial.print("ON ");
    }
    else{
      Serial.print("OFF");
    }
    Serial.print('(');
    Serial.print(analogRead(inpins[i]));
    Serial.print(')');    
    Serial.print('\t');
  }
  Serial.println("");
}

void set_one_pin_high_other_pins_low(int pin){
  for(int i=0;i<4;i++){
    if(pin == outpins[i]){
      digitalWrite(outpins[i], HIGH);
    }
    else{
      digitalWrite(outpins[i], LOW);      
    }
  }
}

void setup(){
  Serial.begin(57600);
  for(int i=0;i<5;i++){
    pinMode(inpins[i], INPUT);
  }
  for(int i=0;i<4;i++){
    pinMode(outpins[i], OUTPUT);
    digitalWrite(outpins[i], LOW);
  }
  pinMode(SW0, INPUT);
  pinMode(SW1_0, INPUT);
  pinMode(SW1_1, INPUT);  
  digitalWrite(SW0, HIGH);
  digitalWrite(SW1_0, HIGH);
  digitalWrite(SW1_1, HIGH);  

  delay(3000);
}

void print_SW0(){
  if(digitalRead(SW0)){
    Serial.println("SW0 : OFF");
  }
  else{
    Serial.println("SW0 : ON");
  }
}

void print_SW1(){
  if(digitalRead(SW1_0)){
    if(digitalRead(SW1_1)){
      Serial.println("SW1 : position1");
    }
    else{
      Serial.println("SW1 : position2");
    }
  }
  else{
    if(digitalRead(SW1_1)){
      Serial.println("SW1 : position4");
    }
    else{
      Serial.println("SW1 : position3");
    }
  }
}

int8_t return_pressed_button_number()
{
  for(uint8_t i=0;i<5;i++){
    if(analogRead(inpins[i]) > THD){
      return i;
    }
  }
  
  return -1;
}

uint8_t return_sw0_state()
{
  if(digitalRead(SW0)){
    return 1;
  }
  return 0;
}

uint8_t return_sw1_state(){
  if(digitalRead(SW1_0)){
    if(digitalRead(SW1_1)){
      return 0;
    }
    else{
      return 1;
    }
  }
  else{
    if(digitalRead(SW1_1)){
      return 3;
    }
  }
  return 2;
}

void send_midi(uint8_t sw0_state, uint8_t sw1_state, uint8_t num)
{
  if(sw0_state == 1){  // kaos pad mode
    uint8_t first_byte = 0xb4;
    uint8_t second_byte = 0x00 + sw1_state * 16 + num;
    Serial.print('$');
    Serial.print(first_byte);
    Serial.print(',');
    Serial.print(second_byte);
    Serial.print(',');
    Serial.print(127);
    Serial.println('%');
  }
  else{  // other modes
    
  }
  delay(SEND_MIDI_DELAY);
}

void loop(){
  int8_t num;
  for(uint8_t i=0;i<4;i++){
    set_one_pin_high_other_pins_low(outpins[i]);
    #ifdef _DEBUG_
      print_inpins_all();
    #endif
    int8_t temp = return_pressed_button_number();
    #ifdef _DEBUG_    
      Serial.print("pressed [");
      Serial.print(i);
      Serial.print(" , ");
      Serial.print(temp);
      Serial.println(" ]");
    #endif
    if(temp >= 0){
      num = temp + 5*i;
//      Serial.println(num);
      if(switch_state[num] != 1){
        send_midi(return_sw0_state(), return_sw1_state(), num);
      }
    }
    for(uint8_t j=0;j<5;j++){
      switch_state[5*i+j] = 0;
    }
    if(temp >= 0){
      switch_state[num] = 1;
    }
  }
  #ifdef _DEBUG_
    Serial.println("------------------------------------------------------------------------------------");
    Serial.print("switch_state = {");
    for(uint8_t i;i<20;i++){
      Serial.print(switch_state[i]);
      Serial.print(",");    
    }
    Serial.println("}");
    Serial.println("------------------------------------------------------------------------------------");
   #endif
//  print_SW0();
//  print_SW1();
  
  delay(LOOP_DELAY);
}
