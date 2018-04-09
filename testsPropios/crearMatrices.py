from random import randint
import spam
import sys

def crearMatriz(n,m):
    file = open("test_" + str(n) + "_" + str(m) + ".txt"  ,"w")
    file.write(str(n) + "\n" + str(m) + "\n")
    for x in range(1,m):
        desde = randint(1,m)
        to = randint(1,m)
        while(to == desde):
            to = randint(1,m)
        file.write(str(desde) + " " + str(to) + "\n")
n = int(sys.argv[1])
mFinal = int(sys.argv[2])
saltos = int(sys.argv[3])
for m in range(saltos,mFinal,saltos):
    crearMatriz(n,m)