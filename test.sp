_aub "./aubio_onset.so" fl

"loop.wav" diskin dup _aub fe 0.001 0.01 0.1 tenvx 1000 0.1 sine * +

_aub fc
