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

archivoRes = open("resultados/resultados"+str(n)+"_"+str(mFinal)+"_"+str(proba)+ "_.txt", "w") 
for m in range(saltos,mFinal,saltos):
    crearMatriz(n,m)
    archivo = os.path.join("tests/", "test_" + str(n) + "_" + str(m) + ".txt")
    tiempos = []
    for x in range (1,30):
        start_time = time.time()    
        subprocess.call(["./../build/tp", archivo, proba])
        elapsed = time.time() - start_time
        tiempos.append(elapsed)


    promedio = sum(tiempos)/float(len(tiempos))
    print(elapsed)
    os.remove(archivo)
    os.remove(archivo + ".outi")

    sparsity = 1-( m / (n**2))
    archivoRes.write(str(promedio) + " " + str(sparsity) + "\n")

archivoRes.close() 


    # res.append((promedio,sparsity))

# print (res)
# plt.scatter(*zip(*res))
# plt.xlabel('x')
# plt.ylabel('y')
# plt.show()

    
