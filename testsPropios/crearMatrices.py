from random import randint
import spam
import sys
import os
import subprocess
import time
import matplotlib.pyplot as plt

def crearMatriz(n,m):
    file = open("tests/test_" + str(n) + "_" + str(m) + ".txt"  ,"w")
    file.write(str(n) + "\n" + str(m) + "\n")
    froms = []
    tos = []
    for x in range(1,m):
        desde = randint(1,m)
        while desde in froms:
            desde = randint(1,m)
        to = randint(1,m)
        while to in tos or to == desde:
            desde = randint(1,m)
        file.write(str(desde) + " " + str(to) + "\n")
n = int(sys.argv[1])
mFinal = int(sys.argv[2])
saltos = int(sys.argv[3])
proba = sys.argv[4]

res = []
for m in range(saltos,mFinal,saltos):
    crearMatriz(n,m)
    archivo = os.path.join("tests/", "test_" + str(n) + "_" + str(m) + ".txt")
    start_time = time.time()    
    subprocess.call(["./../build/tp", archivo, proba])
    elapsed = time.time() - start_time
    os.remove(archivo)
    os.remove(archivo + ".outi")
    rales = 1- (m / (n**2))
    res.append((elapsed,rales))

plt.scatter(*zip(*res))
plt.xlabel('x')
plt.ylabel('y')
plt.show()

    
