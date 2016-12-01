import corner
import numpy as np

infile = open("a.dat",'r')
text = infile.readlines()
a = np.ones(100000)
for i in range(100000):
    a[i] = text[i]

figure = corner.corner(a, labels=[r"$x$", r"$y$"],quantiles=[0.7,0.8, 0.9, 0.95])
figure.savefig("a.png")

infile = open("b.dat",'r')
text = infile.readlines()
b = np.ones(100000)
for i in range(100000):
    b[i] = text[i]

figure = corner.corner(b, labels=[r"$x$", r"$y$"],quantiles=[0.7,0.8, 0.9, 0.95])
figure.savefig("b.png")


infile = open("c.dat",'r')
text = infile.readlines()
c = np.ones(100000)
for i in range(100000):
    c[i] = text[i]

figure = corner.corner(c, labels=[r"$x$", r"$y$"],quantiles=[0.7,0.8, 0.9, 0.95])
figure.savefig("c.png")

infile = open("d.dat",'r')
text = infile.readlines()
d = np.ones(100000)
for i in range(100000):
    d[i] = text[i]

figure = corner.corner(d, labels=[r"$x$", r"$y$"],quantiles=[0.7,0.8, 0.9, 0.95])
figure.savefig("d.png")







