AC voltage measurement using differential mode ADC
==================================================

Introduction
============

The AVR128DA48 features one 12-bit differential ADC. Differential ADC is used to measure the voltage difference between the two input channels. This example demonstrates the AC voltage measurement using differential ADC.

Note :This example could be generated with all the pin variants of AVR DA family of microcontrollers.


Demo Description
================

*	AC input to be measured is fed to the voltage stepdown circuit.
*	Stepped down AC voltage is fed to the ADC +ve channel after offset voltage addition. And reference offset voltage is given as input to the -ve channel of the ADC.
*	Periodic interrupt is used as a trigger for the ADC to start the conversion for every 500 microsecs delay. 
*	After capturing the required number of samples, RMS voltage is calculated using the captured sampled result.
*	Calculated RMS voltage is displayed on terminal window through USART peripheral.

This example is also posted at GitHub, please, refer to the link to see the configuration details of the peripherals:  https://github.com/microchip-pic-avr-examples/avr128da48-adc-ac-voltage-measurement-studio.git

The example is also generated using MPLAB X IDE and is available on GitHub here : https://github.com/microchip-pic-avr-examples/avr128da48-adc-ac-voltage-measurement-mplab.git


Supported evaluation kit
========================

*   `AVR128DA48 Curiosity Nano Evaluation Kit <https://www.microchip.com/developmenttools/ProductDetails/DM164151>`_

Demo Operation
==============

*	After the Curiosity Nano board is powered on, load the firmware to AVR128DA48 MCU.
*	To observe data, open terminal window by connecting to serial port control panel and click on connect button.
*	Set the desired AC input voltage from the AC source and observe the measured RMS voltage displayed on the terminal window.

NOTE: Use suitable voltage stepdown/isolation circuit before feeding the AC input voltage to the MCU. Appropriate precautions should be taken when working with High Voltage levels.


Running the demo
================

*	In Atmel START web page, select "EXPORT PROJECT" tab and click "Download Pack" to save the .atzip file.
*	Import .atzip file to Atmel Studio 7 IDE (File->Import->Atmel Start Project).
*	Build Solution and make sure the build is successful without any errors.
*	Press "Start without debugging" or use "CTRL+ALT+F5" hotkeys to run the application.
