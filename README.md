# HP3466A-and-HP3465B
Modification for reading the HP3466A and HP3465B 

 >Prof. Edson M. Kakuno <br /> 

 [Física](http://cursos.unipampa.edu.br/cursos/licenciaturaemfisica/) - Unipampa Bagé <br /> 


The HP 3466A uses a dual-ramp ADC. The Arduino is used to measure the discharge ramp time of the integrator capacitor (C402), RunDown (fig. 8.4 of the manual). The charge time (RunUp) of C402 is always fixed at 100 ms and the accumulated (integrated) charge in C402 is proportional to the multimeter's input signal.

Capacitor C402 charges with positive or negative polarity depending on the selected function / scale. The controller generates 2 signals to unload C402 (RunDown), Ramp- (RMM) and Ramp+ (RMP). These two signals are extracted from U916, pins 7 and 9, and feed an OR gate formed by 2x 2N7000 (MOSFET), the temporal width of this pulse corresponds to the RunDown, i.e. the multimeter's input reading value.

To determine the polarity of the input signal, the “+” signal is read through two signals on pin 3 of U906 and pin 10 of U901. It supplies two BAT54 diodes and one FET 2N7000, which generates a negative pulse of the order of 700 us if the “+” signal is activated and no pulse if the “+” signal is not activated.
RunDown starts with a pulse on the RUE (RunUp Enable) line. This signal feeds a FET (2N7000) which triggers the interrupt on the Arduino and the interrupt routine starts reading the pulse width (Ramp- or Ramp+).


<p align="center">
<img src="RMM_RMP.jpg" width="700">
</p>


Fig.1: Reading the RunDown time.


<p align="center">
<img src="RUE.jpg" width="700">
</p>


Fig.2: Reading of “+” sign and start of interrupt (reading of RUE signal).


<p align="center">
<img src="Hp3466_timing.jpg" width="700">
</p>


Fig.3: ADC timing diagram.

The counting process starts with RUE line transitioning to level "1", after 1.68 ms the RMM (or RMP) line changes to level "0", starting the counting time (which is proportional to the multimeter input value) and discharging C402. When C402 is fully discharged, it ends the count by changing the RMM (or RMP) line to level “1”.

The RUE line transition triggers the Arduino interrupt (pin 2). In the interrupt routine there are 2 commands:
(a) One to measure the temporal width (pulseIn) of pin 4 of the Arduino that corresponds to the RMM or RMP lines.
(b) The second command measures the temporal width (pulseIn) of pin 6 of the Arduino that corresponds to the triggering of the “+” signal. If the reading of pin 6 returns “zero”, it means that the polarity of the input signal is “-”.

Obs.1: Measurements of Vac, Iac and Resistance (Ohms) no signal (“+” or “-”) is triggered and therefore the reading returns as if it were a negative value.

Obs.2: in the “Ohms” function, OVL (over load) corresponds to ~270 ms.

Obs.3: The diagram of the LED display represented on page 8.34 is incorrect. Consult the HP5082 display data sheet (see material list).

- It is always possible to correct the Arduino readings, by a multiplicative factor, close to 1.  


<p align="center">
<img src="Hp3466_Arduino.jpg" width="700">
</p>


Fig.4: Arduino connection diagram



The Arduino's serial communication lines are connected through an electrical isolator (Si8441AA) which allows the HP3466A (battery-powered) to carry out measurements in non-Earth referenced systems. It has not been tested but is believed to support at least 500 Vdc isolation. 

Above is the base code that can be modified for each specific need. The first block (from top to bottom) defines the variables: RUE (triggers the interrupt) the pin number of the Arduino that receives this signal (pin 2 in this case, the Arduino interrupts are on pins 2 and 3) and similarly to the Ramp (pulse width proportional to the measured value, RunDown) and Sign (signal of the measured value). The variables “signal” and “read” are of the volatile type, as their values are assigned within the interrupt routine. In the second block (void setup()), the parameters are defined, (a) “Serial.begin(9600)” defines the serial communication speed in 9600 baunds; (b) “pinMode(Ramp, INPUT)” defines pin 2 of the Arduino as digital input and same as for “Ramp” and “Sign”; (c) “attachInterrupt(digitalPinToInterrupt(RUE), readADC, FALLING)” enables interrupt on pin 2, and calls routine “readADC” when a falling edge occurs on pin2. The third block (void loop()) runs a loop routine, initially activates digital pin 13 (lights the Led of the Arduino board), sends the value of the variable “read” to the serial port, the “ln” of the print does skips a line (CR+LF) and sends the “signal” value, turns off the Led and waits for 400 ms (within this time another reading from the multimeter is expected, i.e. another interrupt must appear before this time elapses. The last block corresponds the interrupt routine: (a) “read = pulseIn (Ramp,LOW,250000)” pulseIn reads the time that pin 4 (Ramp) remains in the low state (Low) and the value of 250000 us corresponds to the maximum time for execution of this command, if pin 4 does not have a low level, “read” will be equal to “zero.” If the low pulse remains for more than 250 ms, reading also returns “zero.” Note that the expected value is from zero to 200 ms (which corresponds to the reading of the multimeter from zero to full scale), there are cases of overload (OVL) in which this value is greater, for example on the scale of Ohms, the OVL corresponds to approximately 270 ms, so it is interesting to adjust this value to close to 300 ms. It is important to remember that from the total measurement time, there is 100 ms for the Run Up, a few ms for the zero adjustment and almost 2 ms to determine the signal. The total time for a multimeter measurement is 400 ms. The pulseIn returns the time read in us (microseconds). (b) "signal = pulseIn (Sign,LOW,5000);" in an same way, it reads the lapsed time of pin 6, if the sign is “+” it returns a value around 700 us and if there is no sign “+” it returns “zero”. Note that the “-” sign is not defined and has measurements that do not have “+” or “-” sign, Ohms, AC voltage and current and that the program may mistakenly insert the “-” sign! 

