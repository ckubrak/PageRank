#include "sparse.h"
#include <stdlib.h>
#include <chrono>

void normalizarVector(Vector& v);
int main (int argc, char** argv)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    char* archivo = argv[1];
    double p = atof(argv[2]);
//std::cout << "p: "<< p << std::endl;;
    std::ifstream input(archivo);
    std::ofstream output("archivo.out");

    DOK w(archivo);
    std::cout << "w levantado" << std::endl;

    mostrarMatriz(w);

  std::cout << "antes de llamar a DOK d(w) "<< std::endl;;
    DOK d(w);
    std::cout << "d"<< std::endl;;
     mostrarMatriz(d);

       std::cout << "antes de llamar a multiplicarConstante "<< std::endl;;
     w.multiplicarConstante(p);
     std::cout << "p.W" << std::endl;
     mostrarMatriz(w);


    DOK identidad(d.size(),1);
    std::cout << "id"<< std::endl;;

     mostrarMatriz(d);
    w.multiplicarMatriz(d);
    std::cout << "WxD"<< std::endl;;
    identidad.restarMatrices(w);

    std::cout << "restarMatrices"<< std::endl;;

mostrarMatriz(identidad);
// testeado hasta aqui: OK

    Vector sol(w.size(),1);

    Vector resultado = identidad.eliminacionGauss(sol);

    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    int timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

    std::cout << timeElapsed/1000000 << std::endl;

    normalizarVector(resultado);

    for (int i =0; i< resultado.size();i++)
    {
        std::cout << resultado[i] << " ";
    }


    return 0;
}

void normalizarVector(Vector& v)
{
    double total = 0;
    for (int i = 0; i< v.size(); i++)
    {
        total += v[i];
    }
    for (int i = 0; i< v.size(); i++)
    {
        v[i] /= total;
    }
}
