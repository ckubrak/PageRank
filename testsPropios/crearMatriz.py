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
        desde = randint(1,n)
        while desde in froms:
            desde = randint(1,n)
        to = randint(1,n)
        while to in tos or to == desde:
            desde = randint(1,n)
        file.write(str(desde) + " " + str(to) + "\n")
n = int(sys.argv[1]) #Tam
m = int(sys.argv[2]) #Links
#saltos = int(sys.argv[3])
proba = sys.argv[3]

res = []

	#for m in range(saltos,mFinal,saltos):
crearMatriz(n,m)
archivo = os.path.join("tests/", "test_" + str(n) + "_" + str(m) + ".txt")
start_time = time.time()    
subprocess.call(["./../build/tp", archivo, proba])
elapsed = time.time() - start_time
    #os.remove(archivo)
    #os.remove(archivo + ".outi")

sparsity = 1-( m / (n**2))
res.append((elapsed,sparsity))

print ('Tamaño matriz: ' + repr(n))
print ('Cantidad de links: ' +repr(m))
print ('Tiempo transcurrido en el .py: ' + repr(elapsed))
print ('Sparsity: ' + repr(sparsity))
print(" \n ")

#plt.scatter(*zip(*res))
#plt.xlabel('x')
#plt.ylabel('y')
#plt.show()
