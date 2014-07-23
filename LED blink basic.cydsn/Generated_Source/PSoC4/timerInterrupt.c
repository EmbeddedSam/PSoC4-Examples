/*******************************************************************************
* File Name: timerInterrupt.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <timerInterrupt.h>

#if !defined(timerInterrupt__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START timerInterrupt_intc` */
extern uint8 volatile interruptFlag;
/* `#END` */

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: timerInterrupt_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void timerInterrupt_Start(void)
{
    /* For all we know the interrupt is active. */
    timerInterrupt_Disable();

    /* Set the ISR to point to the timerInterrupt Interrupt. */
    timerInterrupt_SetVector(&timerInterrupt_Interrupt);

    /* Set the priority. */
    timerInterrupt_SetPriority((uint8)timerInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    timerInterrupt_Enable();
}


/*******************************************************************************
* Function Name: timerInterrupt_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void timerInterrupt_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    timerInterrupt_Disable();

    /* Set the ISR to point to the timerInterrupt Interrupt. */
    timerInterrupt_SetVector(address);

    /* Set the priority. */
    timerInterrupt_SetPriority((uint8)timerInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    timerInterrupt_Enable();
}


/*******************************************************************************
* Function Name: timerInterrupt_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
void timerInterrupt_Stop(void)
{
    /* Disable this interrupt. */
    timerInterrupt_Disable();

    /* Set the ISR to point to the passive one. */
    timerInterrupt_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: timerInterrupt_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for timerInterrupt.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(timerInterrupt_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START timerInterrupt_Interrupt` */
    interruptFlag = 1; /* Set the flag */
    /* `#END` */
}


/*******************************************************************************
* Function Name: timerInterrupt_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling timerInterrupt_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use timerInterrupt_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void timerInterrupt_SetVector(cyisraddress address)
{
    CyRamVectors[CYINT_IRQ_BASE + timerInterrupt__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: timerInterrupt_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress timerInterrupt_GetVector(void)
{
    return CyRamVectors[CYINT_IRQ_BASE + timerInterrupt__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: timerInterrupt_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling timerInterrupt_Start
*   or timerInterrupt_StartEx will override any effect this method would 
*   have had. This method should only be called after timerInterrupt_Start or 
*   timerInterrupt_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 3, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void timerInterrupt_SetPriority(uint8 priority)
{
	uint8 interruptState;
    uint32 priorityOffset = ((timerInterrupt__INTC_NUMBER % 4u) * 8u) + 6u;
    
	interruptState = CyEnterCriticalSection();
    *timerInterrupt_INTC_PRIOR = (*timerInterrupt_INTC_PRIOR & (uint32)(~timerInterrupt__INTC_PRIOR_MASK)) |
                                    ((uint32)priority << priorityOffset);
	CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: timerInterrupt_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 3, 0 being the highest.
*
*******************************************************************************/
uint8 timerInterrupt_GetPriority(void)
{
    uint32 priority;
	uint32 priorityOffset = ((timerInterrupt__INTC_NUMBER % 4u) * 8u) + 6u;

    priority = (*timerInterrupt_INTC_PRIOR & timerInterrupt__INTC_PRIOR_MASK) >> priorityOffset;

    return (uint8)priority;
}


/*******************************************************************************
* Function Name: timerInterrupt_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void timerInterrupt_Enable(void)
{
    /* Enable the general interrupt. */
    *timerInterrupt_INTC_SET_EN = timerInterrupt__INTC_MASK;
}


/*******************************************************************************
* Function Name: timerInterrupt_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 timerInterrupt_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*timerInterrupt_INTC_SET_EN & (uint32)timerInterrupt__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: timerInterrupt_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void timerInterrupt_Disable(void)
{
    /* Disable the general interrupt. */
    *timerInterrupt_INTC_CLR_EN = timerInterrupt__INTC_MASK;
}


/*******************************************************************************
* Function Name: timerInterrupt_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void timerInterrupt_SetPending(void)
{
    *timerInterrupt_INTC_SET_PD = timerInterrupt__INTC_MASK;
}


/*******************************************************************************
* Function Name: timerInterrupt_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void timerInterrupt_ClearPending(void)
{
    *timerInterrupt_INTC_CLR_PD = timerInterrupt__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
