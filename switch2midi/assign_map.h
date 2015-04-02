#ifndef _ASSIGN_MAP_H_
#define _ASSIGN_MAP_H_

//#define PIN_SW0 2
#define PIN_SW0 15
#define PIN_SW1 16
#define PIN_SW2 3
#define PIN_SW3 4
#define PIN_SW4 6
#define PIN_SW5 5

#define PIN_AD0 A0

#define MAX_RES 50
#define PULLUP_RES 10

//unsigned int AD_MAX = (unsigned int)((double)1024 * MAX_RES / (MAX_RES + PULLUP_RES));
//#define AD_MAX 564
#define AD_MAX 1024
double AD_DIV = (double)AD_MAX/128;

const char pins[6] = {PIN_SW0, PIN_SW1, PIN_SW2, PIN_SW3, PIN_SW4, PIN_SW5};

#define MIDI_0_0 0xb0
#define MIDI_0_1 0x01
#define MIDI_0_2 0x7f

#define MIDI_1_0 0xb0 
#define MIDI_1_1 0x02
#define MIDI_1_2 0x7f

#define MIDI_2_0 0xb0
#define MIDI_2_1 0x03
#define MIDI_2_2 0x7f

#define MIDI_3_0 0xb0
#define MIDI_3_1 0x04
#define MIDI_3_2 0x7f

#define MIDI_4_0 0xb0
#define MIDI_4_1 0x05
#define MIDI_4_2 0x7f

#define MIDI_5_0 0xb0
#define MIDI_5_1 0x06
#define MIDI_5_2 0x7f


#define MIDI_AD0_0 0xb0
#define MIDI_AD0_1 0x07



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

