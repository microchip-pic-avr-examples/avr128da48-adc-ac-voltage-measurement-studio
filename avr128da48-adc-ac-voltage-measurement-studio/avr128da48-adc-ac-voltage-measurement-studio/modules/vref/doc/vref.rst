======================
VREF driver
======================

The Voltage Reference (VREF) provides control registers for the voltage reference sources
used by several peripherals. The user can select the reference voltages for the ADCn by writing to the
ADCn Reference Select bit field (ADCnREFSEL) in the Control A or C registe, and for both
ACn and DACn by writing to the DACn and ACn Reference Select bit field DACnREFSEL in
VREF.CTRL{A,C,D}.

A voltage reference source is enabled automatically when requested by a peripheral. The user can
enable the reference voltage sources (and thus, override the automatic disabling of unused sources) by
writing to the respective Force Enable bit (ADCnREFEN, DACnREFEN) in the Control B register
(VREF.CTRLB). This may be desirable to decrease start-up time, at the cost of increased power
consumption.


Features
--------
* Initialization

Applications
------------
* Select voltage reference for AC, ADC, and DAC peripherals

Note
----
* ISR will be generated only when Global Interrupt checkbox and driver_isr Harness checkbox are enabled


Dependencies
------------
N/A

Concurrency
-----------
N/A

Limitations
-----------
N/A

Knows issues and workarounds
----------------------------
N/A

