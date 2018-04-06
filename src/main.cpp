#include "sparse.h"
#include <stdlib.h>
#include <chrono>

void normalizarVector(Vector& v);
int main (int argc, char** argv)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    char* archivo = argv[1];
    double p = atof(argv[2]);

    std::ifstream input(archivo);
    std::ofstream output("archivo.out");

    DOK w(archivo);

    // mostrarMatriz(w);
    DOK d(w);

    // mostrarMatriz(d);
    DOK identidad(d.size(),1);

// Hasta aca bien
    w = w.multiplicarMatriz(d);

    // mostrarMatriz(w);

    w.multiplicarConstante(p);

    // mostrarMatriz(w);

    identidad.restarMatrices(w);

    // mostrarMatriz(identidad);
    // mostrarMatriz(identidad);
// testeado hasta aqui: OK

   Vector sol(w.size(),1);

    Vector resultado = identidad.eliminacionGauss(sol);
    mostrarMatriz(identidad);
    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    int timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

    std::cout << timeElapsed;
    normalizarVector(resultado);

    double borrar = 0;
    for (int i =0; i< resultado.size();i++)
    {
        std::cout << std::endl;
        std::cout << resultado[i] << " ";
        borrar += resultado[i];
    }

    std::cout<< "\n" << borrar;


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
