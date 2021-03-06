/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */

#define KEY_VALUE1 0x5AF0ul
#define KEY_VALUE2 0xA50Ful

extern void xcptn_xmpl(void);

void hw_init(void)
{
#if defined(DEBUG_SECONDARY_CORES)
	uint32_t mctl = MC_ME.MCTL.R;
#if defined(TURN_ON_CPU1)
	/* enable core 1 in all modes */
	MC_ME.CCTL[2].R = 0x00FE;
	/* Set Start address for core 1: Will reset and start */
#if defined(START_FROM_FLASH)
    MC_ME.CADDR[2].R = 0x11d0000 | 0x1;
#else
    MC_ME.CADDR[2].R = 0x40040000 | 0x1;
#endif /* defined(START_FROM_FLASH) */ 

#endif	
#if defined(TURN_ON_CPU2)
	/* enable core 2 in all modes */
	MC_ME.CCTL[3].R = 0x00FE;
	/* Set Start address for core 2: Will reset and start */
#if defined(START_FROM_FLASH)
    MC_ME.CADDR[3].R = 0x13a0000 | 0x1;
#else
    MC_ME.CADDR[3].R = 0x40080000 | 0x1;
#endif /* defined(START_FROM_FLASH) */ 

#endif
	MC_ME.MCTL.R = (mctl & 0xffff0000ul) | KEY_VALUE1;
	MC_ME.MCTL.R =  mctl; /* key value 2 always from MCTL */
#endif /* defined(DEBUG_SECONDARY_CORES) */
}

void PLL_160MHz(void);
void system160mhz(void);


int main(void)
{
	xcptn_xmpl ();              /* Configure and Enable Interrupts */

	MC_ME.RUN_PC[0].R = 0x00000000;  /* Gate off clock for all RUN modes */
	MC_ME.RUN_PC[1].R = 0x000000FE;  /* Configures peripheral clock for all RUN modes */
	MC_ME.PCTL[91].B.RUN_CFG = 0x1;  /* PIT: select peripheral configuration RUN_PC[1] */

    system160mhz();

	SIUL2.MSCR[88].B.OBE = 1U;
	PIT.MCR.B.MDIS = 0;
  //  PIT.MCR.B.FRZ = 1;  /* Freeze PIT timers in debug mode */
    PIT.TIMER[0].TCTRL.B.TIE = 1;      	/* Enable interrupt */
    INTC.PSR[226].B.PRC_SELN0 = 1;  /* IRQ sent to Core 0 */
    INTC.PSR[226].B.PRIN =10;        /* IRQ priority = 10 (15 = highest) */
	PIT.TIMER[0].LDVAL.R =   10000000;
	PIT.TIMER[0].TCTRL.B.TEN = 1;


	/* Loop forever */
	for(;;)
	{
	}
}

void PIT0_isr(void)
{

	SIUL2.GPDO[88].B.PDO_4n ^= 1;
    PIT.TIMER[0].TFLG.R = 1;  	/* Clear interrupt flag */
}

void system160mhz(void)
{

	/****	RM Page: 1246******/
  /* F160 - max 160 MHz */
  MC_CGM.SC_DC0.B.DIV = 0;  /* Freq = sysclk / (0+1) = sysclk */
  MC_CGM.SC_DC0.B.DE  = 1;  /* Enable divided clock */

  /* S80 - max 80 MHz */
  /* MC_CGM_SC_DC1[DIV] and MC_CGM_SC_DC5[DIV] must be equal at all times */
  MC_CGM.SC_DC1.B.DIV = 1;  /* Freq = sysclk / (1+1) = sysclk/2 */
  MC_CGM.SC_DC1.B.DE  = 1;  /* Enable divided clock */

  /* FS80 - max 80 MHz */
  /* MC_CGM_SC_DC1[DIV] and MC_CGM_SC_DC5[DIV] must be equal at all times */
  MC_CGM.SC_DC5.R = MC_CGM.SC_DC1.R;  /* 80 MHz max */

  /* S40 - max 40 MHz */
  MC_CGM.SC_DC2.B.DIV = 3;  /* Freq = sysclk / (3+1) = sysclk/4 */
  MC_CGM.SC_DC2.B.DE  = 1;  /* Enable divided clock */

  /* F40 - max 40 MHz (for PIT, etc.) - use default values */

  /* F80 - max 80 MHz - use default values*/

  /* F20 - clock out configured at clock_out* function */

  PLL_160MHz();
}

void PLL_160MHz(void)
{
  /* Connect XOSC to PLL */
  MC_CGM.AC5_SC.B.SELCTL=1;

  /* Configure PLL0 Dividers - 160MHz from 40Mhx XOSC */
  /* PLL input = FXOSC = 40MHz
     VCO range = 600-1200MHz
  */
  PLLDIG.PLLDV.B.PREDIV  = 1; 	/* Divide input clock by 1, resulting clock will be reference input for the PLL analog loop */
  PLLDIG.PLLDV.B.MFD     = 16; 	/* Loop multiplication factor 16*40 MHz */
  PLLDIG.PLLDV.B.RFDPHI  = 1; 	/* VCO post divider = 4 so 16*40/40 = 160MHz */

  PLLDIG.PLLCAL3.R = 0x09C3C000; /* Contains the denominator of the fractional loop division factor */
  	  	  	  	  	  	  	  	 /* MFDEN = 9C3C000h = 163823616 */
  PLLDIG.PLLFD.B.SMDEN = 1;		 /* Sigma delta modulation enabled */
  /* switch to PLL */
  MC_ME.DRUN_MC.R = 0x00130072;	/* MVRON = 1, FLAON = RUN mode, PLLON=1, FXOSCON = 1, FIRCON = 1, SYSCLK = PLL PHI_0 */
  MC_ME.MCTL.R = 0x30005AF0; 	/* Target mode = DRUN, KEY = 5AF0 */
  MC_ME.MCTL.R = 0x3000A50F; 	/* Target mode = DRUN, KEY = A50F */

  while(MC_ME.GS.B.S_MTRANS == 1);      /* Wait for mode transition complete */
}

