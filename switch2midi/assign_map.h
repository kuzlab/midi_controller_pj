#ifndef _ASSIGN_MAP_H_
#define _ASSIGN_MAP_H_

#define DSW_NUM 14
#define ASW_NUM 6

//#define PIN_SW0 2
#define PIN_SW0 0
#define PIN_SW1 1
#define PIN_SW2 2
#define PIN_SW3 3
#define PIN_SW4 4
#define PIN_SW5 5
#define PIN_SW6 6
#define PIN_SW7 7
#define PIN_SW8 8
#define PIN_SW9 9

#define PIN_MSW0_0 10
#define PIN_MSW0_1 11
#define PIN_MSW1_0 12
#define PIN_MSW1_1 13
/*
#define PIN_AD0 "A0"
#define PIN_AD1 "A1"
#define PIN_AD2 "A2"
#define PIN_AD3 "A3"
#define PIN_AD4 "A4"
#define PIN_AD5 "A5"
*/
#define PIN_AD0 A0
#define PIN_AD1 A1
#define PIN_AD2 A2
#define PIN_AD3 A3
#define PIN_AD4 A4
#define PIN_AD5 A5

#define MAX_RES 50
#define PULLUP_RES 10

//unsigned int AD_MAX = (unsigned int)((double)1024 * MAX_RES / (MAX_RES + PULLUP_RES));
//#define AD_MAX 564
#define AD_MAX 1023
double AD_DIV = (double)AD_MAX/127l;

/*
const char dpins[DSW_NUM] = {PIN_SW0, PIN_SW1, PIN_SW2, PIN_SW3, PIN_SW4, PIN_SW5
                            , PIN_SW6, PIN_SW7, PIN_SW8, PIN_SW9, PIN_MSW0_0, PIN_MSW0_1
                            , PIN_MSW1_0, PIN_MSW1_1 };

const char apins[ASW_NUM] = { PIN_AD0, PIN_AD1, PIN_AD2, PIN_AD3, PIN_AD4, PIN_AD5 };
*/

#define MIDI_0_0 0xb0
#define MIDI_0_1 0x00
#define MIDI_0_2 0x7f

#define MIDI_1_0 0xb0 
#define MIDI_1_1 0x01
#define MIDI_1_2 0x7f

#define MIDI_2_0 0xb0
#define MIDI_2_1 0x02
#define MIDI_2_2 0x7f

#define MIDI_3_0 0xb0
#define MIDI_3_1 0x03
#define MIDI_3_2 0x7f

#define MIDI_4_0 0xb0
#define MIDI_4_1 0x04
#define MIDI_4_2 0x7f

#define MIDI_5_0 0xb0
#define MIDI_5_1 0x05
#define MIDI_5_2 0x7f


#define MIDI_AD0_0 0xb0
#define MIDI_AD0_1 0x10

#define MIDI_AD1_0 0xb0
#define MIDI_AD1_1 0x11


const unsigned int mapping[3*6] = 
{
  MIDI_0_0, MIDI_0_1, MIDI_0_2,
  MIDI_1_0, MIDI_1_1, MIDI_1_2,
  MIDI_2_0, MIDI_2_1, MIDI_2_2,
  MIDI_3_0, MIDI_3_1, MIDI_3_2,
  MIDI_4_0, MIDI_4_1, MIDI_4_2,
  MIDI_5_0, MIDI_5_1, MIDI_5_2,
};



#endif

