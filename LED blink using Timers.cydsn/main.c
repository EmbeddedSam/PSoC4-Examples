/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

uint8 volatile interruptFlag = 0;

int main()
{
    uint8 LEDValue = 1; //counter to keep track of interrupts
    uint16 count = 0; //keep track of number of interrupts
    
    Timer_Start();
    timer_ISR_Start();

    CyGlobalIntEnable; 
    
    P0_2_LED_Write(1); //turn LED off..
    
    for(;;)
    {
        /* Place your application code here. */
        if(interruptFlag == 1)
        {
            count++;
            interruptFlag = 0; //reset the flag
            Timer_ReadStatus(); //interrupt will not restart till this is done..
            
            
            if(LEDValue == 1)
            {
                LEDValue = 0;
                P0_2_LED_Write(LEDValue); //flash LED on..
            }
            else
            {
                LEDValue = 1;
                P0_2_LED_Write(LEDValue); //flash LED off..
            }         
        }
        
    }
}

/* [] END OF FILE */
