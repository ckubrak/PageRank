from random import randint
import sys
import os
import subprocess
import time
#import matplotlib.pyplot as plt

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
    tiempos = []
    archivoRes = "tiempos/tiempos"+str(n)+"_"+str(mFinal)+"_"+str(proba)+ "_.txt"
    subprocess.call(["./../build/tp", archivo, proba,archivoRes])

    fh = open(archivoRes)
    for line in fh:
        tiempos.append(float(line))
    promedio = sum(tiempos)/float(len(tiempos))
    os.remove(archivo)
    os.remove(archivoRes)
    os.remove(archivo + ".outi")

    sparsity = 1-( m / (n**2))



    res.append((promedio,sparsity))

resultados = open("resultados/tiempos"+str(n)+"_"+str(mFinal)+"_"+str(proba)+ "_.txt","w") 
for tupla in res:
    resultados.write(str(tupla[0])+" "+str(tupla[1])+"\n")
resultados.close() 


# plt.scatter(*zip(*res))
# plt.xlabel('x')
# plt.ylabel('y')
# plt.show()

    
