#include "sparse.h"
#include <stdlib.h>
#include <chrono>

void normalizarVector(Vector& v);
void escribir(Vector& v, double p, char* archivo );

int main (int argc, char** argv)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    char* archivo = argv[1];
    std::string out = argv[1];
    //TODO cambiar a .out a la hora de entregar
    out += ".outi";

    double p = atof(argv[2]);

    std::ifstream input(archivo);

    DOK w(archivo);
    DOK d(w);
    DOK identidad(d.size(),1);

    w = w.multiplicarMatriz(d);
    w.multiplicarConstante(p);

    identidad.restarMatrices(w);

    Vector sol(w.size(),1);
    Vector resultado = identidad.eliminacionGauss(sol);

    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    int timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

    std::cout << timeElapsed/1000000 << std::endl;

    normalizarVector(resultado);

    std::ofstream output(out);
    output << p <<"\n";
    for (int i =0; i< resultado.size();i++)
    {
        output << resultado[i] << "\n";
    }
    output.close();

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
