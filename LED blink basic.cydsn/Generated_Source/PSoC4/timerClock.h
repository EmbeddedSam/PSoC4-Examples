/*******************************************************************************
* File Name: timerClock.h
* Version 2.10
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_timerClock_H)
#define CY_CLOCK_timerClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void timerClock_Start(void);
void timerClock_Stop(void);

void timerClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 timerClock_GetDividerRegister(void);
uint8  timerClock_GetFractionalDividerRegister(void);

#define timerClock_Enable()                         timerClock_Start()
#define timerClock_Disable()                        timerClock_Stop()
#define timerClock_SetDividerRegister(clkDivider, reset)  \
                        timerClock_SetFractionalDividerRegister((clkDivider), 0u)
#define timerClock_SetDivider(clkDivider)           timerClock_SetDividerRegister((clkDivider), 1u)
#define timerClock_SetDividerValue(clkDivider)      timerClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/

#define timerClock_DIV_REG    (*(reg32 *)timerClock__REGISTER)
#define timerClock_ENABLE_REG timerClock_DIV_REG

#endif /* !defined(CY_CLOCK_timerClock_H) */

/* [] END OF FILE */
