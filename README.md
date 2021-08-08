# HP3466A-and-HP3465B
Modification for reading the HP3466A and HP3465B 


The HP 3466A uses a dual-ramp ADC. The Arduino is used to measure the discharge ramp time of the integrator capacitor (C402), RunDown (fig. 8.4 of the manual). The charge time (RunUp) of C402 is always fixed at 100 ms and the accumulated (integrated) charge in C402 is proportional to the multimeter's input signal.

Capacitor C402 charges with positive or negative polarity depending on the selected function / scale. The controller generates 2 signals to unload C402 (RunDown), Ramp- (RMM) and Ramp+ (RMP). These two signals are extracted from U916, pins 7 and 9, and feed an OR gate formed by 2x 2N7000 (MOSFET), the temporal width of this pulse corresponds to the RunDown, i.e. the multimeter's input reading value.

To determine the polarity of the input signal, the “+” signal is read through two signals on pin 3 of U906 and pin 10 of U901. It supplies two BAT54 diodes and one FET 2N7000, which generates a negative pulse of the order of 700 us if the “+” signal is activated and no pulse if the “+” signal is not activated.
RunDown starts with a pulse on the RUE (RunUp Enable) line. This signal feeds a FET (2N7000) which triggers the interrupt on the Arduino and the interrupt routine starts reading the pulse width (Ramp- or Ramp+).
