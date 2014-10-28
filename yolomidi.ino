#include<MIDI.h>
#define NUMBER_BUTTONS 18


MIDI_CREATE_DEFAULT_INSTANCE();

const int buttonPins[NUMBER_BUTTONS] = {  53, 51,
                                          52, 50, 48, 46,
                                          44, 42, 40, 38,
                                          36, 34, 32, 30,
                                          28, 26, 24, 22 };

int buttonStates[NUMBER_BUTTONS] = { 0, 0,
                                     0, 0, 0, 0,
                                     0, 0, 0, 0,
                                     0, 0, 0, 0,
                                     0, 0, 0, 0 };

int buttonStatesNew[NUMBER_BUTTONS] = { 0, 0,
                                        0, 0, 0, 0,
                                        0, 0, 0, 0,
                                        0, 0, 0, 0,
                                        0, 0, 0, 0 };
                            
int *buttonStatesPtr;
int *buttonStatesNewPtr;


void setup() { 
  buttonStatesPtr = (int*)&buttonStates;
  
  buttonStatesNewPtr = (int*)&buttonStatesNew;
  
  for(int i=0; i<NUMBER_BUTTONS; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop(){
  for(int i=0; i<NUMBER_BUTTONS; i++) {
    buttonStatesNewPtr[i] = digitalRead(buttonPins[i]);
  }

  for(int i=0; i<NUMBER_BUTTONS; i++) {
    if(buttonStatesNewPtr[i] != buttonStatesPtr[i]) {
      if(buttonStatesNewPtr[i] == 0) {
        MIDI.sendNoteOn(80+i, 17, 1);   
      } else {
        MIDI.sendNoteOff(80+i, 17, 1);
      }  
    } 
  }

  int *tmp = buttonStatesPtr; 
  buttonStatesPtr = buttonStatesNewPtr;
  buttonStatesNewPtr = tmp;
}
