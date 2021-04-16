#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){

  static char blink_count = 0;
  static char blink_light = 0;
  static char change_dim = 0;
  if(++blink_count == 75){
    state_advance();
    blink_count = 0;
  }
  if(++blink_light == 1){
    dimLow();
    dimHigh();
    blink_light = 0;
  }
  if(++change_dim == 125){
    dimBothLights();
    change_dim = 0;
  }
}
