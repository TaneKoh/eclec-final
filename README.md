I2S digital input

1. DMA moves I2S data to memory

2. I2S half/full interrupt triggers DSP function

3. DSP Math:
a. convert to float
b. biquad filters
c. volume control
d. convert back to int

4. write to output buffer


order of operations approach:

1. hardware bring-up (do blinking LED)

2. do pass-through config (no filtering)

3. config actual DSP

