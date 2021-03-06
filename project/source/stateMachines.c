#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

char tone = 0;
char on = 0;
char dimLights = 0;
char dimLevel = 0;
char button = 0;

void turn_on(){
  red_on = 1;
  green_on = 1;
  led_changed = 1;
  on = 1;
  led_update();
}

void turn_off(){
  red_on = 0;
  green_on = 0;
  led_changed = 1;
  on = 0;
  led_update();
}

void dimBothLights(){
  if(dimLights){
    static int state = 1;
    switch(state){
    case 1:
      dimLow();
      dimLevel = 0;
      state++;
      break;
    case 2:
      dimHigh();
      dimLevel = 1;
      state = 1;
      break;
    }
  }
}

void dimLow(){
  if(dimLights){
    if(!dimLevel){
      static int state = 1;
      switch(state){
      case 1:
	turn_off();
	state++;
	break;
      case 2:
	turn_on();
	state = 1;
	break;
      }
    }
  }
}

void dimHigh(){
  if(dimLights){
    if(dimLevel){
      static int state = 1;
      switch(state){
      case 1:
      case 2:
      case 3:
	turn_off();
	state++;
	break;
      case 4:
	turn_on();
	state = 1;
	break;
      }
    }
  }
}

void state_advance_buttons(){
  switch(button){
  case 0:
    turn_on();
    break;
  case 1:
    turn_off();
    break;
  case 2:
    if(dimLights)
      dimLights = 0;
    else
      dimLights = 1;
    break;
  case 3:
    if(on)
      tone = 1;
    else
      tone = 0;
    break;
  }
}

void state_advance(){
  static int state = -1;
  if(tone){
    state++;
      switch(state){
      case 0: buzzer_set_period(3432); break;
      case 1: buzzer_set_period(4575); break;
      case 2: buzzer_set_period(5432); break;
      case 3: buzzer_set_period(4234); break;
      case 4: buzzer_set_period(3234); break;
      case 5: buzzer_set_period(6522); break;
      case 6: state = 0; break;
      }
  }
  else{
    buzzer_set_period(0);
  }
}
    
