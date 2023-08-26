/*
 *@Note
 USART Print debugging routine:
 USART1_Tx(PA9).
 This example demonstrates using USART1(PA9) as a print debug port output.
*/

#include "debug.h"
#include "LCD/LCD.h"
#include "CHobby_GPIO.h"
#include "CHobby_RTC.h"

/* Global typedef */


/* Global define */
#define LCD1602 16
#define LCD2004 20
#define LCD LCD2004
#define FOUR_BIT 1

/* Global Variable and Function Prototypes */
// extern uint8_t displayfunction;
extern void TIM1_PWMOut_Init( u16 ccp );
extern u8   RTC_Init();
extern vu8 hour, sec;

/**********************************************************************/
int main(void)
{
	int q = 1, last_sec = 99; // i = 0, j = 0
	int alrm_trig = 9;  //  trigger alarm every 29 deconds
	int alrm_dur  = 4;   //  alarm continues for 5 secs after trigger

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    CHobby_GPIO_INIT( LED_PORT, LED_PIN );
//  Set the Contrast PWN ( PA8 ) = Timer 1 in Mode 2
    TIM1_PWMOut_Init( 55 );  //  54 % Contrast is a good starting point.

    last_sec = RTC_Init();

    printf("\nRTC_Init = %d, LCD_pll SystemClk = %dMHz\r\n", last_sec, SystemCoreClock/1000000 );

	   printf("RS = 0x%04X\r\n", RS );
	   printf("EN = 0x%04X\r\n", EN );


	    LCD_init( LCD, FOUR_BIT );
//		printf("\nDF = 0x%02X\r\n", displayfunction );

		setCursor( (LCD-11)/2, 0 );  //  Fancy math to center on the line --  11 = string length
		LCDprint( "CanHobby.ca" );
		Delay_Ms( 1000 );
		setCursor( (LCD-15)/2, 1 );
		LCDprint( "RISC-V LCD with" );
		Delay_Ms( 1000 );
		setCursor( (LCD-13)/2, 2 );
		LCDprint( "PWM Contrast," );
		Delay_Ms( 1000 );
		setCursor( (LCD-18)/2, 3 );
		LCDprint( "RTC and GPIO Blink" );
		Delay_Ms( 2000 );

    while( 1 )
    {

    	   GPIO_WriteBit( LED_PORT, LED_PIN, (q) ? (q=0) : (q=1) );
		   printf("RTC sec = %d\n", sec );
    	   if( (sec >= alrm_trig) && (sec < alrm_trig+alrm_dur ) ) {
    		   printf("\nRTC Alarm\n");
    	   }
//    	   GPIO_WriteBit( CtlPort, EN, (w) ? (w=0) : (w=1) );
//    	   write( w & 0x40 );
//    	   send( w, 1 );
//    	   pulseEnable();
//    	   write4bits( 0xFF );
//    	   pulseEnable();
    	   Delay_Ms( 900 );
    }
}
