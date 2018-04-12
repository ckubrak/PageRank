from random import randint
import sys
import os
import subprocess
import time
import pylab as pl
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
res = []



for proba in [0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.99]:

    crearMatriz(n,m)

    archivo = os.path.join("tests/", "test_" + str(n) + "_" + str(m) + ".txt")
    tiempos = []
    archivoRes = "proba/proba"+str(n)+"_"+str(m)+"_"+str(proba)+".txt"
    subprocess.call(["./../build/tp", archivo, str(proba),archivoRes])

    fh = open(archivoRes)
    for line in fh:
        tiempos.append(float(line))
    promedio = sum(tiempos)/float(len(tiempos))
    os.remove(archivo)
    os.remove(archivoRes)
    os.remove(archivo + ".outi")

    res.append((promedio,proba))

resultados = open("resultados/proba"+str(n)+"_"+str(m)+"_.txt","w") 
for tupla in res:
    resultados.write(str(tupla[0])+" "+str(tupla[1])+"\n")
resultados.close() 