import corner
import numpy as np

infile = open("sismo.dat",'r')
text = infile.readlines()
x = np.ones(14)
y = np.ones(14)
p = np.ones(14)

for i in range(14):
    x[i] = text[i].split("\t")[0]
    y[i] = text[i].split("\t")[1]
    p[i] = text[i].split("\t")[2]

data = np.vstack([x, y,p]).T
figure = corner.corner(data, labels=[r"$x$", r"$y$"],quantiles=[0.7,0.8, 0.9, 0.95])
figure.savefig("sismo.png")
