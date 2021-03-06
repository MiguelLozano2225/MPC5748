/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
/* ###################################################################
**     Filename    : main.c
**     Project     : stm_periodic_interrupt_mpc5748g
**     Processor   : MPC5748G_324
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-04-07, 13:31, # CodeGen: 6
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */
/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "clockMan1.h"
#include "pin_mux.h"
#include "stm1.h"
#include "interrupt_manager.h"
volatile int exit_code = 0;
/* User includes (#include below this line is not maintained by Processor Expert) */
/* This example is setup to work by default with DEVKIT. To use it with other boards
   please comment the following line */
#define DEVKIT
#ifdef DEVKIT
  #define PORT PTA
  #define LED 10  /* pin PA[10] - LED DS4 on DEV-KIT */
#else
  #define PORT PTG
  #define LED 2  /* pin PG[2] - LED DS2 on Motherboard */
#endif
uint32_t ticks; /* The number of ticks */
void STM0_Ch0_IRQHandler(void)
{
    /* Clear channel interrupt flag */
    STM_DRV_ClearStatusFlags(INST_STM1, stm1_ChnConfig0.channel);
    /* Toggle Led to check period */
    PINS_DRV_TogglePins(PORT, (1 << LED));
    /* Increase the number of ticks in compare register to create a periodic for next event */
    STM_DRV_IncrementTicks(INST_STM1, stm1_ChnConfig0.channel, ticks);
}
/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{
    /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
    #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT(); /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
    #endif
    /*** End of Processor Expert internal initialization. ***/
    /* Initialize clock gate*/
    CLOCK_SYS_Init(g_clockManConfigsArr,   CLOCK_MANAGER_CONFIG_CNT,
                   g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
    CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);
    /* Initialize and configure pins */
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
    /* Initialize STM */
    STM_DRV_Init(INST_STM1, &stm1_InitConfig0);
    /* Compute the number of ticks from microseconds */
    STM_DRV_ComputeTicksByUs(INST_STM1, 1000000U, &ticks);
    /* Initialize channel 0 */
    stm1_ChnConfig0.compareValue = ticks;
    STM_DRV_InitChannel(INST_STM1, &stm1_ChnConfig0);
    /* Enable Interrupt for STM0 channel 0 */
    INT_SYS_EnableIRQ(STM0_Ch0_IRQn);
    /* Start running the common timer counter */
    STM_DRV_StartTimer(INST_STM1);
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/
/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the NXP C55 series of microcontrollers.
**
** ###################################################################
*/
