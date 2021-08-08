# HP3466A-and-HP3465B
Modification for reading the HP3466A and HP3465B 


The HP 3466A uses a dual-ramp ADC. The Arduino is used to measure the discharge ramp time of the integrator capacitor (C402), RunDown (fig. 8.4 of the manual). The charge time (RunUp) of C402 is always fixed at 100 ms and the accumulated (integrated) charge in C402 is proportional to the multimeter's input signal.
