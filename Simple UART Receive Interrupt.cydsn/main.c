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
#include <interrupts.h>

uint8 flag = 0;

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    uint8 volatile ch;  
    /* Start the SCB UART */
    UART_Start();
    
    /* Start the Interrupt */
    UART_RX_ISR_StartEx(uartInterrupt); 
    
    /* Transmit string through UART */
    UART_UartPutString("UART Initialised");

    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    
    for(;;)
    {         
        if(flag == 1)
        {
          flag = 0;
          ch = UART_UartGetChar();
          UART_UartPutChar(ch);
          TX_LED_Write(!TX_LED_Read());       
        }      
    }
}

/* [] END OF FILE */
