#include "stdint.h"
#include "stdbool.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"

#include "GPIOInit.h"
#include "Timers.h"
#include "InterruptHandler.h"
#include "tm4c123gh6pm.h"
#include "types.h"
#include "bitwise_operation.h"



void main()
{
  
  //initialize portE
  PortEInit();
  
  //initialize portC
  PortCInit();

  //initialize portF
  PortFInit();
  
  //initialize Timer0
  timer0_init();

  //initialize Timer1
  timer1_init();

  //wait for 1 sec
  timer0A_delay1000MS();

  //for the processor to allow the interrupts
  __asm("CPSIE   I");

     
  while(1)
  {
     
      // __asm("    WFI\n");
  }

}










