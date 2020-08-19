/**
 * \file
 *
 * \brief ADC Basic driver example.
 *
 (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

#include <atmel_start.h>
#include <adc_basic_example.h>
#include <adc_basic.h>
#include <atomic.h>

volatile bool         ADC_0_isr_executed = false;
volatile adc_result_t ADC_0_measurement;
volatile uint8_t      ADC_0_measurement_normalized;

void ADC_0_adc_handler_cb(void)
{
	ADC_0_measurement            = ADC_0_get_conversion_result();
	ADC_0_measurement_normalized = ADC_0_measurement >> (ADC_0_get_resolution() - 8);
	ADC_0_isr_executed           = true;
}

uint8_t ADC_0_test_adc_basic(void)
{

	// Test driver functions, assume that an AIN channel is enabled and that
	// the Result Ready IRQ is enabled.

	// Test polled mode

	// Get conversion from specified ADC channel
	ADC_0_measurement = ADC_0_get_conversion(0);

	// Get 8 MSB of conversion result
	ADC_0_measurement_normalized = ADC_0_measurement >> (ADC_0_get_resolution() - 8);

	// Test IRQ mode

	ENABLE_INTERRUPTS();

	ADC_0_register_callback(ADC_0_adc_handler_cb);

	// make sure flag is false
	ADC_0_isr_executed = false;

	// Start conversion from ADC CH0
	ADC_0_start_conversion(0);

	// Wait for ISR to be executed
	while (!ADC_0_isr_executed)
		;

	DISABLE_INTERRUPTS();
	return 1;
}
