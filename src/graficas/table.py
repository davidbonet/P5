import matplotlib.pyplot as plt
import numpy as np
import wave
import sys

dumb = wave.open("distortion.wav", "r")
seno = wave.open("sinus.wav", "r")
cut1 = 400
cut2 = cut1+900
fm = 44100

dumbSignal = dumb.readframes(-1)
dumbSignal = np.frombuffer(dumbSignal,dtype='int16')
dumbSignal = dumbSignal[cut1 : cut2] / -min(dumbSignal)
senoSignal = seno.readframes(-1)
senoSignal = np.frombuffer(senoSignal,dtype='int16')
senoSignal = senoSignal[cut1 : cut2] / -min(senoSignal)

time = np.linspace(0,(cut2-cut1)/fm,(cut2-cut1))
plt.plot(time,dumbSignal,'-r', markersize = 2,label='Distortion effect')
plt.plot(time,senoSignal, '-o', markersize = 1.5, label='Original Pure Sine')
plt.title('Distortion effect')
plt.grid(linestyle='dotted')
plt.legend()
plt.margins(0)
plt.ylim([min(senoSignal)-0.3, max(senoSignal)+0.3])
plt.xlabel('Tiempo [s]')
plt.ylabel('Amplitud')
plt.show()