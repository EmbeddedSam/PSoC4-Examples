/*******************************************************************************
* File Name: timerInterrupt.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_timerInterrupt_H)
#define CY_ISR_timerInterrupt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void timerInterrupt_Start(void);
void timerInterrupt_StartEx(cyisraddress address);
void timerInterrupt_Stop(void);

CY_ISR_PROTO(timerInterrupt_Interrupt);

void timerInterrupt_SetVector(cyisraddress address);
cyisraddress timerInterrupt_GetVector(void);

void timerInterrupt_SetPriority(uint8 priority);
uint8 timerInterrupt_GetPriority(void);

void timerInterrupt_Enable(void);
uint8 timerInterrupt_GetState(void);
void timerInterrupt_Disable(void);

void timerInterrupt_SetPending(void);
void timerInterrupt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the timerInterrupt ISR. */
#define timerInterrupt_INTC_VECTOR            ((reg32 *) timerInterrupt__INTC_VECT)

/* Address of the timerInterrupt ISR priority. */
#define timerInterrupt_INTC_PRIOR             ((reg32 *) timerInterrupt__INTC_PRIOR_REG)

/* Priority of the timerInterrupt interrupt. */
#define timerInterrupt_INTC_PRIOR_NUMBER      timerInterrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable timerInterrupt interrupt. */
#define timerInterrupt_INTC_SET_EN            ((reg32 *) timerInterrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the timerInterrupt interrupt. */
#define timerInterrupt_INTC_CLR_EN            ((reg32 *) timerInterrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the timerInterrupt interrupt state to pending. */
#define timerInterrupt_INTC_SET_PD            ((reg32 *) timerInterrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the timerInterrupt interrupt. */
#define timerInterrupt_INTC_CLR_PD            ((reg32 *) timerInterrupt__INTC_CLR_PD_REG)



#endif /* CY_ISR_timerInterrupt_H */


/* [] END OF FILE */
