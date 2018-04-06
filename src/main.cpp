#include "sparse.h"
#include <stdlib.h>
#include <chrono>

int main (int argc, char** argv)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    char* archivo = argv[1];
    int p = atoi(argv[2]);

    std::ifstream input(archivo);
    std::ofstream output("archivo.out");

    DOK w(archivo);
    std::cout << "w levantado" << std::endl;
    // mostrarMatriz(w);

    w.multiplicarConstante(p);
    std::cout << "p.W"<< std::endl;;
    // mostrarMatriz(w);

    DOK d(w);
    std::cout << "d"<< std::endl;;
    // mostrarMatriz(d);

    DOK identidad(d.size(),1);
    std::cout << "id"<< std::endl;;

    // mostrarMatriz(d);
    w.multiplicarMatriz(d);
    std::cout << "WxD"<< std::endl;;
    identidad.restarMatrices(w);

    std::cout << "restarMatrices"<< std::endl;;
    Vector sol(w.size(),1);

    Vector resultado = identidad.eliminacionGauss(sol);

    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    int timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

    std::cout << timeElapsed/1000000 << std::endl;
    for (int i =0; i< w.size();i++)
    {
        std::cout << resultado[i] << " ";
    }


    return 0;
}
