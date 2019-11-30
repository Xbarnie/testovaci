#include <Akcelerometer.h>

volatile bool pitIsrFlag = false;
MMA8451Q* akcelerometer;

/*extern "C" void PORTA_IRQHandler(void){  //asi netreba..asi az pre volny pad----treba riesi PIT PRERUSENIE
	GPIO_ClearPinsInterruptFlags(GPIOA, (1<<15));

	PRINTF("Interrupt!\n\r");

	//akcelerometer->FreeFall_Detect();
}*/


int main(void){

	INIT_BOARD();		//init board
	INIT_PIT();

	NVIC_EnableIRQ(PORTA_IRQn);  //tiez asi az  pre volny pad
	MMA8451Q acc(0x1D);
	akcelerometer= &acc;


	float dpf_os[3]={0,0,0};
	float akt_os[3]={0,0,0};
	int naklonXY[2];
	int naklonXYC[2];

	while(1) {

		//SMC_PreEnterStopModes();  ///asi PIT/PRERUSENIE

	    	if(true == pitIsrFlag) //PIT
	    	{
	    		LED_BLUE_TOGGLE();//CYAN
	    		LED_GREEN_TOGGLE();//



				akt_os[0] = acc.getAccX();
				dpf_os[0] = dolnoPriepustnyFilter(dpf_os[0], akt_os);


				akt_os[1] = acc.getAccY();
				dpf_os[1] = dolnoPriepustnyFilter(dpf_os[1], akt_os+1);


				akt_os[2] = acc.getAccZ();
				dpf_os[2] = dolnoPriepustnyFilter(dpf_os[2], akt_os+2);

				PRINTF("\n\rDolno priepustny filter:");
				PRINTF(" x=%d",(int)(dpf_os[0]*100));
				PRINTF(", y=%d",(int)(dpf_os[1]*100));
				PRINTF(", z=%d\r\n",(int)(dpf_os[2]*100));

				//PRINTF("\n%d",(int)(dpf_os[0]*100));
				//PRINTF(",%d",(int)(dpf_os[1]*100));
				//PRINTF(",%d\r\n",(int)(dpf_os[2]*100));

				naklonXYDP(dpf_os, naklonXY);
				PRINTF("Naklon\n\r");
				if(naklonXY[0] < 0) {
				   PRINTF("x : -%d\n\r", naklonXY[0]);
				}
				else PRINTF("x : %d\n\r", naklonXY[0]);

				if(naklonXY[1] < 0) {
				   PRINTF("y : -%d\n\r", naklonXY[1]);
				}
				else PRINTF("y : %d\n\r", naklonXY[1]);




				for( int a = 4000000; a>0 ;a-- ) {//funguje ako timer....Aby to nevypisovalo tak rychlo
				}
				pitIsrFlag = false;
	    	}
	    	LED_GREEN_TOGGLE();// Zlta
	    	LED_RED_TOGGLE();//   LED

	    	// Uspatie procesora
	    	//PRINTF("Vykonavam cyklus\n\r");
	    	//SMC_SetPowerModeStop(SMC, kSMC_PartialStop);  // nič nezobudi procesor
	    	//SMC_SetPowerModeVlpw(SMC);					// procesor bude zobudeny iba pri GPIO a PIT
	    	//SMC_SetPowerModeLls(SMC);					// procesor bude zobudeny iba pri GPIO
	    	//SMC_PostExitStopModes();



	    }
	    return 0;
	}
