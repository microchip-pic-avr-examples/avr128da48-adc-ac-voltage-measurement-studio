#include <atmel_start.h>
#include <stdio.h>
#include <math.h>

#define ADC_SAMPLES (uint8_t)200 // Number of ADC samples taken
#define ADC_REF_V (float)3.33
#define ADC_GAIN (float)(ADC_REF_V / 4096) // ADC digital to analog voltage factor
#define ANALOG_GAIN (float)1750            // Hardware gain
#define ADC_CH_POS 6                       // AC signal input channel
#define ADC_CH_NEG 7                       // AC signal reference point input channel (ADC_REF_V/2)

void  ADC_Handler(void);
float Calculate_RMS(void);

volatile uint8_t SamplesCount    = 0;
volatile uint8_t ADCSumReadyFlag = 0;
float            VolRMS          = 0;

int32_t ADCRes;
int32_t ADCSqr;
int64_t ADCSqrSum;
int64_t ADCSumSave;
float   ADCSqrAvg;

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	printf("System Initialized \n");

	// Set ADC conversion complete interrupt handler
	ADC_0_register_callback(*ADC_Handler);

	/* Replace with your application code */
	while (1) {
		// ADC samples are ready for computation
		if (ADCSumReadyFlag) {
			VolRMS = Calculate_RMS();

			// Convert the voltage to integer to print it on terminal
			uint16_t tempVol = (uint16_t)VolRMS;
			printf("%d \n", tempVol);
			ADCSumReadyFlag = 0;
		}
	}
}

/*******************************************************************************
 * void ADC_Handler(void)
 *
 * API to collect ADC samples and perform squaring and summation of required number of samples.

 * @param void
 * @return void
 ******************************************************************************/
void ADC_Handler(void)
{
	// Read ADC differential conversion result
	ADCRes = (int16_t)ADC_0_get_conversion_result();
	// Square the result
	ADCSqr = ADCRes * ADCRes;
	// Summation of the squared samples
	ADCSqrSum += ADCSqr;

	SamplesCount += 1;

	// Required number of samples are collected
	if (SamplesCount >= ADC_SAMPLES) {
		// copy the squared and summed samples result
		ADCSumSave      = ADCSqrSum;
		ADCSqrSum       = 0;
		SamplesCount    = 0;
		ADCSumReadyFlag = 1;
	}
}

/*******************************************************************************
 * float calculateVrms(void)
 *
 * API to calculate RMS voltage, this API calculates RMS voltage using the acquired samples.

 * @param void
 * @return calculated rms voltage
 ******************************************************************************/
float Calculate_RMS(void)
{
	float rmsval;
	// Averaging the summation of the samples
	ADCSqrAvg = (float)ADCSumSave / ADC_SAMPLES;
	// Take square root for the Averaged result
	rmsval = sqrt(ADCSqrAvg);
	// Multiply ADC gain
	rmsval *= ADC_GAIN;
	// Multiply hardware analog gain
	rmsval *= ANALOG_GAIN;

	return (rmsval);
}

/*******************************************************************************
 * ISR(RTC_PIT_vect)
 *
 * API to generate the periodic interrupt for every 500usec ,
   ADC starts  differential conversion upon interrupt.
 * @param void
 * @return void
 ******************************************************************************/
ISR(RTC_PIT_vect)
{
	/* Insert your PIT interrupt handling code here */

	ADC_0_start_diff_conversion(ADC_CH_POS, ADC_CH_NEG);

	/* The interrupt flag has to be cleared manually */
	RTC.PITINTFLAGS = RTC_PI_bm;
}
