/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
extern void xcptn_xmpl(void);

int main(void)
{
	volatile int counter = 0U;
	xcptn_xmpl ();              	/* Configure and Enable Interrupts */
	SIUL2.MSCR[3].B.IBE = 1U;		/* PTA3 as input*/
	SIUL2.MSCR[4].B.OBE = 1U;		/* PT4 as OUTPUT **/

    INTC.PSR[243].B.PRC_SELN0 = 1;  /* IRQ sent to Core 0 */
    INTC.PSR[243].B.PRIN =10;        /* IRQ priority = 10 (15 = highest) */

    /*Excel - 512*/
	SIUL2.IMCR[144].B.SSS = 1U;

	SIUL2.IRER0.B.EIRE0 =1U;		/* Enable interrupt */
	SIUL2.IREER0.B.IREE0 = 1; 		/* For rising edge*/
	//SIUL2.IFEER0.B.IFEE0 = 1; 	/* For falling edge*/

	/* Loop forever */
	for(;;)
	{
	   	counter++;
		SIUL2.GPDO[4].B.PDO_4n = 1;
	}
}

void SIUL2_CH0_ISR(void)
{
	SIUL2.ISR0.B.EIF0 = 1;			/* W1C (Write 1 to clean) */
	SIUL2.GPDO[4].B.PDO_4n = 0;
}
