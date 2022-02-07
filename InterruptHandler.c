#include "stdint.h"
#include "stdbool.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"


#include "tm4c123gh6pm.h"
#include "types.h"
#include "bitwise_operation.h"

//Interrupt Handlers

uint32 count = 0; 


//Traffic light Interrupt handler
void TrafficDelayHandler(){
  
 TIMER0_ICR_R = 0x01;
 
 //At first, the NS traffic light is green and the EW traffic light is red
 if(count < 5)
 {
   //turn off the NS traffic lights
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1,0);
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2,0);
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3,0);
    
    //turn EW traffic light red 
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,GPIO_PIN_4); // red
    
    //turn NS traffic light green
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3,GPIO_PIN_3); // green 5sec
    
    //turn off the green NS pedestrian light
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,0);
    
    //turn NS pedestrian traffic light red
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_5,GPIO_PIN_5);
    
    //turn off the red EW pedestrian light
     GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,0);
     
    //turn EW pedestrian traffic light green
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2); 
 }
 // NS traffic light changes to yellow, while EW traffic light remains red
 else if(count < 7 && count >= 5)
 {
    //turn off the NS traffic lights
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1,0);
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2,0);
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3,0);
    
    //turn NS traffic light yellow
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2,GPIO_PIN_2); //yellow 2sec
 }
 
 // NS traffic light changes to red
 else if(count <8 && count >=7)
 {
    //turn off the NS traffic lights
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1,0);
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2,0);
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3,0);
    
    //turn NS traffic light red
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1,GPIO_PIN_1);//red 1sec 
    
     //turn off the red NS pedestrian light
     GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_5,0);
     
     //turn NS pedestrian traffic light green
     GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,GPIO_PIN_4);
 }
 
 // After one second, EW traffic light turns green while the NS traffic light remains red
 else if(count <13 && count >=8)
 {
    //turn off the EW traffic lights
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,0);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,0);
    
    //turn EW traffic light green
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,GPIO_PIN_6);  // green
    
    //turn off the green EW pedestrian light
   GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0); 
   
   //turn EW pedestrian traffic light red
   GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,GPIO_PIN_3); 
 }
   
 // EW traffic light turns yellow while NS traffic light remains red
  else if(count <15 && count >=13)
 {
   //turn off the EW traffic lights
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,0);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,0);

     //turn EW traffic light yellow
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,GPIO_PIN_5); //yellow
 }
 
 // After one second, EW traffic light turns red
   else if(count <16 && count >=15)
 {
   //turn off the EW traffic lights
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,0);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,0);
    
    //turn EW traffic light red
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,GPIO_PIN_4); //red
    
     //turn off the red EW pedestrian light
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,0);
    
    //turn EW pedestrian traffic light green
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2); 
 }
 
  else if(count == 16)
  {
    count = -1; //start a new cycle for each
  }
 count++;
}

//actions taken when pedestrian presses NS pedestrian light button
void pedestrian_NS_Actions( )
{
    //save the last states of both traffic light (the NS and the EW)
    uint32 ledState1 = GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_1) ;
    uint32 ledState2 = GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_2) ;
    uint32 ledState3 = GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_3) ;
    uint32 ledState4 = GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4) ;
    uint32 ledState5 = GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_5) ;
    uint32 ledState6 = GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_6) ;
    
    //turn off the NS traffic lights
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1,0);
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2,0);
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3,0);
    
    //turn the NS traffic light red
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1,GPIO_PIN_1); //red
 
    //turn off the EW traffic lights
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,0);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,0); 
    
    //turn the EW traffic light green
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,GPIO_PIN_6);  //green
    
    //turn off the red NS pedestrian light
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_5,0); //red pedestrian stop
    
     //turn NS pedestrian traffic light green
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,GPIO_PIN_4); //green pedestrian
    
     //turn off the green EW pedestrian light
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0); //green pedestrian stop
    
    //turn EW pedestrian traffic light red
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,GPIO_PIN_3); //red pedestrian 
    
     // wait 2 secs
     timer1A_delay1000MS();
     timer1A_delay1000MS();
     
     //turn off the green NS pedestrian light
     GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,0); //green pedestrian stop
     
     //turn NS pedestrian traffic light red
     GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_5,GPIO_PIN_5); //red pedestrian
     
     //turn off the red EW pedestrian light
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,0); //red pedestrian stop 
    
    //turn EW pedestrian traffic light green
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2); //green pedestrian 
  
     //start from previous states
     GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1,ledState1);
     GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2,ledState2);
     GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3,ledState3);
    
     GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,ledState4);
     GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,ledState5);
     GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,ledState6);  
}
 

//actions taken when pedestrian presses EW pedestrian light button
void pedestrian_EW_Actions( )
{
  //save the last states
    uint32 ledState1 = GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_1) ;
    uint32 ledState2 = GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_2) ;
    uint32 ledState3 = GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_3) ;
    uint32 ledState4 = GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4) ;
    uint32 ledState5 = GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_5) ;
    uint32 ledState6 = GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_6) ;
    
    //turn off the EW traffic lights
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,0);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,0);  

    //turn the EW traffic light red
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,GPIO_PIN_4);  //red
    
    //turn off the NS traffic lights
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1,0);
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2,0);
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3,0);
    
    //turn the NS traffic light green
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3,GPIO_PIN_3); //green
    
    //turn off the red EW pedestrian light
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,0); //red pedestrian stop
    
    //turn EW pedestrian traffic light green
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2); //green pedestrian
    
    //turn off the green NS pedestrian light
     GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,0); //green pedestrian stop
  
    //turn NS pedestrian traffic light red
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_5,GPIO_PIN_5); //red pedestrian

     // wait 2 secs
     timer1A_delay1000MS();
     timer1A_delay1000MS();
     
      //turn off the green EW pedestrian light
     GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0); //green pedestrian stop
     
     //turn EW pedestrian traffic light red
     GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,GPIO_PIN_3); //red pedestrian
     
     //turn off the red NS pedestrian light
     GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_5,0); //red pedestrian stop

     //turn NS pedestrian traffic light green
     GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,GPIO_PIN_4); //green pedestrian 
  
     //start from previous states
     GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1,ledState1);
     GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2,ledState2);
     GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3,ledState3);
    
     GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,ledState4);
     GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,ledState5);
     GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,ledState6);  
}

// Pedestrian Interrupt Handler
void PedestrianHandler()
{   
    //clear interrupts
    GPIOIntClear(GPIO_PORTF_BASE,GPIO_PIN_0 | GPIO_PIN_4);
    
   //if a pedestrian pressed NS pedestrian traffic light button and another one pressed EW pedestrain traffic light button
   if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==0 && GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==0)
    {
        //if NS traffic light green and EW traffic light red 
       if (GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_3)== 1 && GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4) == 1)
       {
         //actions taken when pedestrian presses NS pedestrian light button
         pedestrian_NS_Actions();
       }
    
       //if EW traffic light green and NS traffic light red 
       else if(GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_6)== 1 && GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_5) == 1)
       {
        //actions taken when pedestrian presses EW pedestrian light button
        pedestrian_EW_Actions();
       }
    }
    
    // if pedestrian presses NS pedestrian traffic light button and NS traffic light is green
    else if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==0 && GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_3) == 1)
    {
      //actions taken when pedestrian presses NS pedestrian light button
      pedestrian_NS_Actions();
    }   
    
    // if pedestrian presses EW pedestrian traffic light button and EW traffic light is green
   else if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==0 && GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_6) == 1)
    {
      //actions taken when pedestrian presses EW pedestrian light button
      pedestrian_EW_Actions();
    }
}


