/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */

extern void xcptn_xmpl(void);

void delay(void)
{
	int a;
	a = 5000000;
	while(a--);
}

int main(void)
{
	volatile int counter = 0;
	
	xcptn_xmpl ();              /* Configure and Enable Interrupts */

	SIUL2.MSCR[117].B.SSS = 0; 			/*gpio*/
	SIUL2.MSCR[117].B.OBE = 1;


	/* Loop forever */
	for(;;) {	   
	   	counter++;

	   	SIUL2.GPDO[117].B.PDO_4n ^=1;
	   	delay();
	}
}
