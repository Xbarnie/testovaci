
#include "fsl_lpsci_dma.h"
#include "board.h"
#include <stdint.h>


#define DEMO_LPSCI UART0
#define LPSCI_TX_DMA_CHANNEL 0U
#define LPSCI_RX_DMA_CHANNEL 1U
#define LPSCI_TX_DMA_REQUEST kDmaRequestMux0LPSCI0Tx
#define LPSCI_RX_DMA_REQUEST kDmaRequestMux0LPSCI0Rx
#define LPSCI_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)
#define LPSCI_DMAMUX DMAMUX0
#define LPSCI_DMA DMA0

lpsci_dma_handle_t g_lpsciDmaHandle;
dma_handle_t g_lpsciTxDmaHandle;
dma_handle_t g_lpsciRxDmaHandle;
volatile bool rxBufferEmpty = true;
volatile bool txBufferFull = false;
volatile bool txOnGoing = false;
volatile bool rxOnGoing = false;
lpsci_transfer_t xfer;

void LPSCI_UserCallback(UART0_Type *base, lpsci_dma_handle_t *handle, status_t status, void *userData){
	userData = userData;

	if (kStatus_LPSCI_TxIdle == status){
		txBufferFull = false;
		txOnGoing = false;
	}
	if (kStatus_LPSCI_RxIdle == status){
		rxBufferEmpty = false;
		rxOnGoing = false;
	}
}

void lpsci_init(){
	lpsci_config_t config;

	BOARD_InitDebugConsole();
	CLOCK_SetLpsci0Clock(0x1U);

	LPSCI_GetDefaultConfig(&config);
	config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
	config.enableTx = true;
	config.enableRx = true;

	LPSCI_Init(DEMO_LPSCI, &config, LPSCI_CLK_FREQ);

	DMAMUX_Init(LPSCI_DMAMUX);

	DMAMUX_SetSource(LPSCI_DMAMUX, LPSCI_TX_DMA_CHANNEL, LPSCI_TX_DMA_REQUEST);
	DMAMUX_EnableChannel(LPSCI_DMAMUX, LPSCI_TX_DMA_CHANNEL);
	DMAMUX_SetSource(LPSCI_DMAMUX, LPSCI_RX_DMA_CHANNEL, LPSCI_RX_DMA_REQUEST);
	DMAMUX_EnableChannel(LPSCI_DMAMUX, LPSCI_RX_DMA_CHANNEL);

	DMA_Init(LPSCI_DMA);
	DMA_CreateHandle(&g_lpsciTxDmaHandle, LPSCI_DMA, LPSCI_TX_DMA_CHANNEL);
	DMA_CreateHandle(&g_lpsciRxDmaHandle, LPSCI_DMA, LPSCI_RX_DMA_CHANNEL);

	LPSCI_TransferCreateHandleDMA(DEMO_LPSCI, &g_lpsciDmaHandle, LPSCI_UserCallback, NULL, &g_lpsciTxDmaHandle, &g_lpsciRxDmaHandle);

	/* Wait send finished */
	while (txOnGoing){
	}
}

void lpsci_send(char *buff, size_t len){
	xfer.data = (uint8_t *) buff;
	xfer.dataSize = len;
	txOnGoing = true;
	LPSCI_TransferSendDMA(DEMO_LPSCI, &g_lpsciDmaHandle, &xfer);
}

void lpsci_send_vals_f(float *vals, uint8_t len){
	char buffer[4+(2*len)];

	buffer[0] = 0xAB;
	buffer[1] = 0xCD;
	buffer[2] = 2*len;
	buffer[3] = 0x00;

	for(uint8_t i=0; i<len; i++){
		int16_t tmp = *(vals+i) * 1000;
		buffer[4+(2*i)] = tmp & 0xFF;
		buffer[5+(2*i)] = tmp >> 8;
	}

	lpsci_send(buffer, 4+(2*len));
}

void lpsci_send_vals_i(int16_t *vals, uint8_t len){
	char buffer[4+(2*len)];

	buffer[0] = 0xAB;
	buffer[1] = 0xCD;
	buffer[2] = 2*len;
	buffer[3] = 0x00;

	for(uint8_t i=0; i<len; i++){
		buffer[4+(2*i)] = *(vals+i) & 0xFF;
		buffer[5+(2*i)] = *(vals+i) >> 8;
	}

	lpsci_send(buffer, 4+(2*len));
}
