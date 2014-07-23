/*******************************************************************************
* File Name: timerClock.c
* Version 2.10
*
*  Description:
*   Provides system API for the clocking, interrupts and watchdog timer.
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <cydevice_trm.h>
#include "timerClock.h"


/*******************************************************************************
* Function Name: timerClock_Start
********************************************************************************
*
* Summary:
*  Starts the clock.
*
* Parameters:
*  None
*
* Returns:
*  None
*
*******************************************************************************/
void timerClock_Start(void)
{
    /* Set the bit to enable the clock. */
    timerClock_ENABLE_REG |= timerClock__ENABLE_MASK;
}


/*******************************************************************************
* Function Name: timerClock_Stop
********************************************************************************
*
* Summary:
*  Stops the clock and returns immediately. This API does not require the
*  source clock to be running but may return before the hardware is actually
*  disabled.
*
* Parameters:
*  None
*
* Returns:
*  None
*
*******************************************************************************/
void timerClock_Stop(void)
{
    /* Clear the bit to disable the clock. */
    timerClock_ENABLE_REG &= (uint32)(~timerClock__ENABLE_MASK);
}


/*******************************************************************************
* Function Name: timerClock_SetFractionalDividerRegister
********************************************************************************
*
* Summary:
*  Modifies the clock divider and the fractional divider.
*
* Parameters:
*  clkDivider:  Divider register value (0-65535). This value is NOT the
*    divider; the clock hardware divides by clkDivider plus one. For example,
*    to divide the clock by 2, this parameter should be set to 1.
*  fracDivider:  Fractional Divider register value (0-31).
* Returns:
*  None
*
*******************************************************************************/
void timerClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional)
{
#if defined (timerClock__FRAC_MASK)
	/* get all but divider bits */
    uint32 maskVal = timerClock_DIV_REG & 
                    (uint32)(~(timerClock__DIVIDER_MASK | timerClock__FRAC_MASK)); 
	/* combine mask and new divider val into 32-bit value */
    uint32 regVal = clkDivider | (((uint32)clkFractional << 16) & timerClock__FRAC_MASK) | maskVal;
#else
    /* get all but integer divider bits */
    uint32 maskVal = timerClock_DIV_REG & (uint32)(~(uint32)timerClock__DIVIDER_MASK);
    /* combine mask and new divider val into 32-bit value */
    uint32 regVal = clkDivider | maskVal;
#endif /* timerClock__FRAC_MASK */

	timerClock_DIV_REG = regVal;
}


/*******************************************************************************
* Function Name: timerClock_GetDividerRegister
********************************************************************************
*
* Summary:
*  Gets the clock divider register value.
*
* Parameters:
*  None
*
* Returns:
*  Divide value of the clock minus 1. For example, if the clock is set to
*  divide by 2, the return value will be 1.
*
*******************************************************************************/
uint16 timerClock_GetDividerRegister(void)
{
    return (uint16)timerClock_DIV_REG;
}


/*******************************************************************************
* Function Name: timerClock_GetFractionalDividerRegister
********************************************************************************
*
* Summary:
*  Gets the clock fractional divider register value.
*
* Parameters:
*  None
*
* Returns:
*  Fractional Divide value of the clock
*  0 if the fractional divider is not in use.
*
*******************************************************************************/
uint8 timerClock_GetFractionalDividerRegister(void)
{
#if defined (timerClock__FRAC_MASK)
    /* get fractional divider bits */
    uint32 maskVal = timerClock_DIV_REG & timerClock__FRAC_MASK;
    return (maskVal >> 16u);
#else
    return 0u;
#endif /* timerClock__FRAC_MASK */
}


/* [] END OF FILE */
