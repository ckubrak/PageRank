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
m = int(sys.argv[2])
proba = sys.argv[3]
epsIn = int(sys.argv[4])
epsHasta = int(sys.argv[5])

res = []



for eps in range(epsIn,epsHasta,1):
    crearMatriz(n,m)

    archivo = os.path.join("tests/", "test_" + str(n) + "_" + str(m) + ".txt")
    tiempos = []
    archivoRes = "tiempos/eps"+str(n)+"_"+str(m)+"_"+str(proba)+ "_"+ str(float(1*(10**-eps)))+ ".txt"
    subprocess.call(["./../build/tp", archivo, proba,archivoRes,str(eps)])

    fh = open(archivoRes)
    for line in fh:
        tiempos.append(float(line))
    promedio = sum(tiempos)/float(len(tiempos))
    os.remove(archivo)
    # os.remove(archivoRes)
    os.remove(archivo + ".outi")

    res.append((promedio,-eps))

resultados = open("resultados/eps"+str(n)+"_"+str(m)+"_"+str(proba)+" _" + str(eps)+".txt","w") 
for tupla in res:
    resultados.write(str(tupla[0])+" "+str(tupla[1])+"\n")
resultados.close() 