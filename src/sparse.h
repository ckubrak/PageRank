#ifndef SPARCE_H
#define SPARCE_H

#include <vector>
#include <iostream>
#include <map>
#include <iterator>
#include <fstream>

typedef std::vector<double > Vector;

class DOK
{
public:
    typedef std::map<size_t, std::map<size_t , double> > matriz;
    typedef matriz::iterator iter_fila;

    typedef std::map<size_t, double> columnas;
    typedef columnas::iterator iter_col;

    DOK (size_t n);
    DOK(const char* input);

    Vector eliminacionGauss (Vector& b);
    Vector operator*(const Vector& x);

    DOK& operator*(const double c);
    double& operator()(size_t i, size_t j)
    {
        return _mat[i][j];
    }

    std::vector<Vector> matrizCompleta();

private:
    matriz _mat;
    size_t _n;

    Vector resolverSistema();
};


void mostrarMatriz(DOK&);
#endif
