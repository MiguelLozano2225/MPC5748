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

int main(void)
{
	volatile int counter = 0;

	xcptn_xmpl ();              /* Configure and Enable Interrupts */

	/*PTA4 as output*/
	SIUL2.MSCR[4].B.OBE = 1;
	/*PTA3 as Input*/
	SIUL2.MSCR[3].B.IBE = 1;


	/* Loop forever */
	for(;;)
	{
	   	counter++;
	   	if(1U == SIUL2.GPDI[3].B.PDI_4n )
	   	{
	   		SIUL2.GPDO[4].B.PDO_4n = 0;
	   	}
	   	else
	   	{
	   		SIUL2.GPDO[4].B.PDO_4n = 1;
	   	}
	}
}


