#include <stdint.h>
#include <math.h>

#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_gpio.h"
#include "board.h"

#include "mma8451.h"
#include "iic.h"
#include "lpsci.h"
#include "filter.h"

#ifndef M_PI
#define M_PI 3.1415926535
#endif

#define DEMO_MODE
#define DEMO_AXIS 0


volatile char acc_data_rdy = 0;

void PORTA_IRQHandler(){
	if(GPIO_GetPinsInterruptFlags(GPIOA) & (1<<15)){
		GPIO_ClearPinsInterruptFlags(GPIOA, (1 << 15));
		acc_data_rdy = 1;
	}
	if(GPIO_GetPinsInterruptFlags(GPIOA) & (1<<14)){
		GPIO_ClearPinsInterruptFlags(GPIOA, (1 << 14));
		LED_RED_TOGGLE();
	}
}

void acc_normalize(int16_t *raw, float *norm){
	*(norm+0) = (float) *(raw+0) / 2048;
	*(norm+1) = (float) *(raw+1) / 2048;
	*(norm+2) = (float) *(raw+2) / 2048;
}

int main(void){
	BOARD_InitPins();
	BOARD_BootClockRUN();

	BOARD_InitPins();
	BOARD_BootClockRUN();
	lpsci_init();
	iic_init();
	mma8451_init();

	EnableIRQ(PORTA_IRQn);

	int16_t acc_raw[3];
	float acc_normalized[3];
	float acc_filtered[3] = {0};

	while(1){
		while(!acc_data_rdy);
		acc_data_rdy = 0;
		mma8451_get_accel(acc_raw);

		acc_normalize(acc_raw, acc_normalized);
//		filter_iir(acc_normalized, filtered);
		filter_fir(acc_normalized, acc_filtered);


#ifdef DEMO_MODE
		float demovals[3];

		demovals[0] = acc_normalized[DEMO_AXIS];
		demovals[1] = acc_filtered[DEMO_AXIS];
		demovals[2] = acc_normalized[DEMO_AXIS] - acc_filtered[DEMO_AXIS];
		lpsci_send_vals_f(demovals, 3);
#else
		int16_t roll_pitch[2];
		roll_pitch[0] = atan2(acc_filtered[1], sqrt((acc_filtered[0] * acc_filtered[0])+(acc_filtered[2]*acc_filtered[2]))) * (180.0 / M_PI);
		roll_pitch[1] = atan2(acc_filtered[0], sqrt((acc_filtered[1] * acc_filtered[1])+(acc_filtered[2]*acc_filtered[2]))) * (180.0 / M_PI);
		lpsci_send_vals_i(roll_pitch, 2);

#endif

	}
}
