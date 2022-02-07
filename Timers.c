#include "stdint.h"
#include "stdbool.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/timer.h"

#include "Timers.h"
#include "tm4c123gh6pm.h"
#include "types.h"
#include "bitwise_operation.h"

//Initializing timers and delays

//initialize Timer1
void timer1_init()
{
  //enable the Timer1 peripheral
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);   

  //wait for the Timer1 module to be stable
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1)){}
  
  //disable the timer
  TimerDisable(TIMER1_BASE, TIMER_BOTH); 

  //configure the timer as down counting periodic timer
  TimerConfigure(TIMER1_BASE, TIMER_CFG_A_PERIODIC); 

  //stop the timer when debugging
  TimerControlStall(TIMER1_BASE, TIMER_A, true);    

  //enable the timer
  TimerEnable(TIMER1_BASE, TIMER_A);
}

//delay Timer1A one second
void timer1A_delay1000MS()
{
    //disbale the timer
    TimerDisable(TIMER1_BASE, TIMER_A);
    
    //load the value which is equivalent to 1 sec
    TimerLoadSet(TIMER1_BASE, TIMER_A, 16000000-1);
    
    //clear interrupt that arised when the timer timed out
    TIMER1_ICR_R = 0x01;
    
    //enable the timer
    TimerEnable(TIMER1_BASE, TIMER_A);

   //wait for the timer to time out
    while((TIMER1_RIS_R & 0x01) == 0);
}

//initialize Timer0
void timer0_init()
{
  //enable the Timer0 peripheral
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

  //wait for the Timer1 module to be stable   
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)){}
  
  //disable the timer
  TimerDisable(TIMER0_BASE, TIMER_BOTH); 
  
  //configure the timer as down counting periodic timer
  TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC); 

  //stop the timer when debugging
  TimerControlStall(TIMER0_BASE, TIMER_A, true); 

  //allow interrupts
  TIMER0_IMR_R |= 0x01;
  NVIC_EN0_R= 1<<19;

  //enable the timer
  TimerEnable(TIMER0_BASE, TIMER_A);
}

//delay Timer0A one second
void timer0A_delay1000MS()
{
    //disable the timer
    TimerDisable(TIMER0_BASE, TIMER_A);

    //load the value which is equivalent to 1 sec
    TimerLoadSet(TIMER0_BASE, TIMER_A, 16000000-1);

    //clear interrupt that arised when the timer timed out
    TIMER0_ICR_R = 0x01;
    
    //enable the timer
    TimerEnable(TIMER0_BASE, TIMER_A);

    //wait for the timer to time out
    while((TIMER0_RIS_R & 0x01) == 0);
}