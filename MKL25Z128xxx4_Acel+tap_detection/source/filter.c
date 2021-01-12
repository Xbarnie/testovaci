#include <stdint.h>

#define IIR_SILA 0.059	//1Hz
#define FIR_LEN 30
#include "filter.h"


void filter_iir(float *raw, float *filtered){
	*(filtered+0) = (*(raw+0) * IIR_SILA) + (*(filtered+0) * (1 - IIR_SILA));
	*(filtered+1) = (*(raw+1) * IIR_SILA) + (*(filtered+1) * (1 - IIR_SILA));
	*(filtered+2) = (*(raw+2) * IIR_SILA) + (*(filtered+2) * (1 - IIR_SILA));
}

void filter_fir(float *raw, float *filtered){
	static float taps_vals[3][FIR_LEN+1] = {0};

	*(filtered+0) = 0;
	*(filtered+1) = 0;
	*(filtered+2) = 0;
	taps_vals[0][FIR_LEN] = *(raw+0);
	taps_vals[1][FIR_LEN] = *(raw+1);
	taps_vals[2][FIR_LEN] = *(raw+2);

	for(uint8_t i=0; i<FIR_LEN; i++){
		taps_vals[0][i] = taps_vals[0][i+1];
		taps_vals[1][i] = taps_vals[1][i+1];
		taps_vals[2][i] = taps_vals[2][i+1];

		*(filtered+0) += taps_vals[0][i] * taps_coeffs[i];
		*(filtered+1) += taps_vals[1][i] * taps_coeffs[i];
		*(filtered+2) += taps_vals[2][i] * taps_coeffs[i];
	}
}
