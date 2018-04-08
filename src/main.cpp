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

std::cout << "llama constructor : \n";
    DOK w(archivo);


std::cout << " W \n\n";
    //mostrarMatriz(w);
    DOK d(w);

    // mostrarMatriz(d);
    DOK identidad(d.size(),1);

// Hasta aca bien
    w = w.multiplicarMatriz(d);

std::cout << " WD \n\n";
    //mostrarMatriz(w);

    w.multiplicarConstante(p);

std::cout << " pWD \n\n";
    //mostrarMatriz(w);

    identidad.restarMatrices(w);
std::cout << " I-pWD \n\n";
//    mostrarMatriz(identidad);
    // mostrarMatriz(identidad);
// testeado hasta aqui: OK


   Vector sol(w.size(),1);

    Vector resultado = identidad.eliminacionGauss(sol);

    std::cout << " triangulada \n\n";
    // mostrarMatriz(identidad);

    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    int timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

    std::cout << timeElapsed/1000000 << std::endl;

// std::cout << "vector resultado sin normalizar: \n";
// std::cout << "resultado.size() :" << resultado.size() << std::endl;
//     for (int i =0; i< resultado.size();i++)
//     {
//         std::cout << i << " " << resultado[i] << std::endl;
//     }



    normalizarVector(resultado);
    std::cout <<"vector normalizado: "<<std::endl;
    std::cout << timeElapsed/1000000;
    // for (int i =0; i< resultado.size();i++)
    // {
    //     std::cout << std::endl;
    //     std::cout << resultado[i] << " ";
    // }



    return 0;
}

void normalizarVector(Vector& v)
{
    double total = 0;
  // std::cout << "\n\n\ntamaño vector " << v.size()<< std::endl;
    for (int i = 0; i< v.size(); i++)
    {
      // std::cout << "i, v[i]: " << i << " " << v[i]<< "      ";
      total += v[i];
      // std::cout << "total: " << total << std::endl;
    }
    for (int i = 0; i< v.size(); i++)
    {
        v[i] /= total;
    }
}
