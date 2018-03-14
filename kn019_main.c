/********************************************************************************************************
*
* File                : kn019_main.c
* Hardware Environment:	
* Build Environment   : 
* Version             : 
* By                  : 
*********************************************************************************************************/
//#include <inc/compiler_defs.h>    
//#include <inc/C8051F912_defs.h>

#include <compiler_defs.h>    
#include <C8051F912_defs.h>


//Local Include Files 
#include <c8051_f902_delay.h> //���������� ��������� ��������.
	   
		
		#define   SYSCLK          24500000L        //System clock frequency in 24500000 (24.5 Mhz)		
	    /**
 		 * KSZ8765 and MAX24287+ Reset
 		 */
		sbit RST_0 =  P0^6; 
        #define RST_0_PORT_MASK (0x40)  //  port  6   Reset KSZ8765 and MAX24287+
		/**
 		 * The NH_LED
 		 */
		 sbit    NH_led = P0^5; 
		#define  LED_NH_PORT_MASK (0x20)   		  // port 5 ->NH_LED_SVETODIOD
		
		
		sbit SDA = P0^3;   						  //P0.3  ->SDA  (24_from_scematic)  Smbus
		sbit SCL = P0^4;   						  //P0.4  ->SCL  (23_from_schematic) Smbus







//Function Prototype
  void select_oscilator();
  void port_init();
  
  
  

/*****************************************************************************
Syntax: !!!!!!!!!!!!!!!!!!!! void main(void)  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
Remarks:MAIN Functions			    
*******************************************************************************/
void main(void)
{
 	                             
     //Watch DOG TImer  Debug_kit
     



     PCA0MD &= ~0x40;          // WDTE = 0 (clear watchdog timer enable)
     select_oscilator();
     port_init();

 
   	//Proverka Portov
	//SCL = 0;  //CLK GET to NULL  //rozoviu 
    ////////////////////////////////////////////////////
	//SCL = 1;  //CLK GET to NULL 

     //������ ������
     //������ ������ ����� GPIO ��� ������ T = 80 [���] ������������� ��������� = 40 [���]
     //while_delay(2);=40; while_delay(2); = 40[���]   = 80 [���]
	 //while_delay(4);=70; while_delay(4); = 70[���]   = 140 [���]  
	 //while_delay(6);=100; while_delay(4); = 100[���] = 200 [���]  
	 //���� ��� while_delay_pin
	 /*
	 for(;;)
	 {
	    SCL = 0;
		while_delay(6);  
        SCL = 1;	 
        while_delay(6);
	 } 
     */


     
	 for(;;)
	 {
	    SCL = 0;
		//Wait_MS_timer2(1);  
          Wait_Sec_timer2(0);
		SCL = 1;	 
          Wait_Sec_timer2(0);
		//Wait_MS_timer2(1);
	 }





	  ///////////	
	  while(1);
 
	  /////////


}

/*****************************************************************************
Syntax:  select_oscilator()	    
Remarks: Vybor Oscilators to SYSCLK	    
*******************************************************************************/
void select_oscilator()
{
  
  volatile unsigned char  oscilator_rdy=0;
  volatile unsigned char  sysclk_rdy=0;

			
  //Ustanovka Internal Oscilator SYSCLK = 24.5 Mhz 
  OSCICL = 0x01; 
  OSCICN = 0x80;   								   			//Set internal oscillator to highest setting of 24500000 (Mhz) 
		   													//Zdes nugna proverka cto oscilator startoval u nas     
  do
  {
  oscilator_rdy=(OSCICN>>6); // + nalogit bit maska 
  oscilator_rdy = (oscilator_rdy & 1) ; 				 
  }while(!oscilator_rdy); 

  ///////////////////////////////////////////////////////////////////////////////////
  CLKSEL = 0x00;                    				//Ustanovka SYSCLK from oscilator   
  do
  {	 
  sysclk_rdy = (CLKSEL >> 7) ;	     	
  }while(!sysclk_rdy);                  			//Zdes Proverks clock Ready   

}


/*****************************************************************************
Syntax:  void port_init()	    
Remarks:			    
*******************************************************************************/
void port_init()
{	    
		//P0SKIP = 0x07;                                  //SKIP SDA SCL Pins
	    XBR0 = 0x00; 									//Enable SMBus pins all other digital pin disable
	    XBR1 = 0x00; 									//pins all other digital  pin disable 
		XBR2 = 0x40; 									//Enable crossbar and weak pull-ups 
	    P0 = 0xFF;

}
















