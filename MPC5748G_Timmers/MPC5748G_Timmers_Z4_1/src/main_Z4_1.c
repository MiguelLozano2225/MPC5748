/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */

extern void xcptn_xmpl(void);

int main(void)
{
	AXBS_0.PORT[3].CRS.B.ARB = 1;  /* Round-robin (rotating) priority */
	
	xcptn_xmpl ();              /* Configure and Enable Interrupts */
	SIUL2.MSCR[89].B.OBE = 1U;
	SIUL2.MSCR[87].B.OBE = 1U;


    INTC.PSR[36].B.PRC_SELN1 = 1;  /* IRQ sent to Core 1 */
    INTC.PSR[36].B.PRIN = 9;        /* IRQ priority = 10 (15 = highest) */
    INTC.PSR[40].B.PRC_SELN1 = 1;  /* IRQ sent to Core 1 */
    INTC.PSR[40].B.PRIN = 1;        /* IRQ priority = 10 (15 = highest) */

	STM_0.CR.B.TEN = 0;			/* Disable module for configuration */
	STM_0.CR.B.CPS = 0;			/* Counter prescaler */

	STM_0.CNT.B.CNT = 75000000;
	STM_0.CHANNEL[0].CMP.B.CMP = 80000000;
	STM_0.CR.B.TEN = 1;			/* Enable module for configuration */
	STM_0.CHANNEL[0].CCR.B.CEN = 1;	/* Enable channel */

	STM_1.CR.B.TEN = 0;			/* Disable module for configuration */
	STM_1.CR.B.CPS = 0;			/* Counter prescaler */
	STM_1.CR.R |= (1<<4);		/* FXOSC as clock source */

	STM_1.CNT.B.CNT = 75000000;
	STM_1.CHANNEL[0].CMP.B.CMP = 80000000;
	STM_1.CR.B.TEN = 1;			/* Enable module for configuration */
	STM_1.CHANNEL[0].CCR.B.CEN = 1;	/* Enable channel */

	/* Loop forever */
	for(;;)
	{

	}
}

void STM0_CH0_isr(void)
{
	STM_0.CHANNEL[0].CMP.B.CMP += 80000000;
	SIUL2.GPDO[89].B.PDO_4n ^= 1;
	STM_0.CHANNEL[0].CIR.B.CIF = 1U;
}

void STM1_CH0_isr(void)
{
	STM_1.CHANNEL[0].CMP.B.CMP += 80000000;
	SIUL2.GPDO[87].B.PDO_4n ^= 1;
	STM_1.CHANNEL[0].CIR.B.CIF = 1U;
}
