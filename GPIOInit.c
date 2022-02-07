#include "stdint.h"
#include "stdbool.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"

#include "GPIOInit.h"
#include "tm4c123gh6pm.h"
#include "types.h"
#include "bitwise_operation.h"

//initialize PORTE
void PortEInit( )
{
  //enable the GPIOE peripheral
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
  
  //wait for the GPIOE module to be stable
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
  {
  }
  
  //unlock
  GPIO_PORTE_LOCK_R=0x4C4F434B;
    
  //set pins 1,2,3,4,5 as output
  GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3| GPIO_PIN_4|GPIO_PIN_5);
  GPIO_PORTE_DATA_R ^= 0x00;
}


//initialize PORTC
void PortCInit( )
{
  //enable the GPIOC peripheral
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
  
  //wait for the GPIOC module to be stable
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
  {
  }
  
  //unlock
  GPIO_PORTC_LOCK_R=0x4C4F434B;
  
  //set pins 4,5,6 as output
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 );
  GPIO_PORTC_DATA_R ^= 0x00;
}

//initialize PORTF
void PortFInit( )
{
  //enable the GPIOF peripheral
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  
  //wait for the GPIOF module to be stable
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
  {
  }
  
   //unlock
  GPIO_PORTF_LOCK_R=0x4C4F434B;
  
  //set pin 0 to one
  Set_bit(GPIO_PORTF_CR_R,0)
    
  //set pins 0 and 4 as input  
  GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_0 | GPIO_PIN_4);  
  
  //set pins 2 and 3 as output
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_2 | GPIO_PIN_3);
  
  //set the pad configuraion for pins 0 and 4
  GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0 | GPIO_PIN_4 ,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
  GPIO_PORTF_DATA_R ^= 0x00;
  
  //interrupt enable
  NVIC_EN0_R= 1<<30;
  GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0);
}