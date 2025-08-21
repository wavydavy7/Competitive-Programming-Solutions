import numpy as np
import matplotlib.pyplot as plt
x = np.linspace(0, 100, 51)
#print(x) 
# b = np.arange(12).reshape(4, 3)
# print(b)
# print(b.cumsum(axis = 1))
# print(b[:, 1])

# for elem in b.flat:
#     print(elem)

# a = np.arange(9).reshape(3, 3)
# print(np.vstack((a, b)))  #stacked along the first axes
# i = np.array([[0, 1], [2, 1]])
# j = np.array([[1, 2], [0, 0]])
# print(b[i, j])

def mandelbrot(h, w, maxit=20, r=2):
    """Returns an image of the Mandelbrot fractal of size (h,w)."""
    x = np.linspace(-2.5, 1.5, 4*h+1)
    y = np.linspace(-1.5, 1.5, 3*w+1)
    A, B = np.meshgrid(x, y)
    C = A + B*1j
    z = np.zeros_like(C)
    divtime = maxit + np.zeros(z.shape, dtype=int)

    for i in range(maxit):
        z = z**2 + C
        diverge = abs(z) > r                    # who is diverging
        div_now = diverge & (divtime == maxit)  # who is diverging now
        divtime[div_now] = i                    # note when
        z[diverge] = r                          # avoid diverging too much

    return divtime
plt.clf()
plt.imshow(mandelbrot(400, 400))
#1j is the imaginary unit