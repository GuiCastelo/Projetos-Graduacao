import matplotlib.pyplot as plt
from numpy import cos, linspace
from math import pi

plt.figure(figsize=[10, 6])
plt.grid(visible=True)
plt.title("Variando as frequências angulares de cossenoides")
plt.ylabel("y [adimensional]")
plt.xlabel("t [adimensional]")
plt.ylim((-1.05, 1.05))
plt.xlim((-3.25, 3.25))

tiposDeLinhas = ["--", ":", "-."]
for m in range(1, 4):
    x = linspace(-pi, pi, m * 50)
    y = cos(m* x)
    plt.plot(x, y, c='k', ls=tiposDeLinhas[m-1], label=f"m = {m}")

plt.legend(loc="best")
plt.show()