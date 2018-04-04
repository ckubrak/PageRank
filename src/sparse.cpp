#include "sparse.h"
DOK::DOK(size_t n)
{
    _n = n;
}

Vector DOK::operator*(const Vector& x)
{

    Vector y(_n);
    double sum;

    iter_fila fila;
    iter_col col;

    for(fila=_mat.begin(); fila!=_mat.end(); fila++){
        sum=0;
        for(col=(*fila).second.begin(); col!=(*fila).second.end(); col++){
            sum += (*col).second * x[(*col).first];
        }
        y[(*fila).first]=sum;
    }

    return y;
}

DOK& DOK::operator*(const double c)
{
    for (int i = 0; i <_mat.size(); i++)
    {
        if (_mat.count(i) > 0)
            for (int j = 0; j < _mat[i].size(); j++)
            {
                _mat[i][j] = c * _mat[i][j];
            }
    }
}

//TODO si sobra tiempo ver si puedo hacerlo con iteradores
Vector DOK::eliminacionGauss(Vector& b)
{
    double mult;

    // Agrego a b en la ultima columna
    _n++;
    for (int i=0; i < b.size(); i++)
    {
        if (b[i] != 0)
        {
            _mat[i][b.size()] = b[i];
        }
    }

    for (int k = 0; k < _n; k++)
    {
        for (int i = k+1 ; i < _n + 1; i++)
        {
            if (_mat.count(i) == 0 || _mat[i].count(k) == 0)
                {
                    break;
                }
            else
            {
               mult = _mat[i][k] / _mat[k][k];

            }
            for (int j = k ; j < _n + 1  ;j++)
            {
                double ij = _mat[i][j] - _mat[i][j] - mult * _mat[k][j];
                if (ij == 0)
                {
                    _mat[i].erase(j);
                }
                else
                {
                    _mat[i][j] = ij;
                }
            }

        }
    }

    return resolverSistema();
}

Vector DOK::resolverSistema()
{
    // TODO discutir esto (Si no le agrego 1 a _n no lo podria printear pero no es necesario para la entrega)

    int n = _n - 1;
    Vector x(n,0);

    x[n-1] = _mat[n-1][n] / _mat[n-1][n-1];

    double sum = 0;
    for (int i = n-2; i >= 0 ; i-- )
    {
        for (int j = i + 1; j <= n-1; j++)
        {
            sum += _mat[i][j]*x[j];
        }
        x[i]=(_mat[i][n]-sum)/_mat[i][i];
    }
    return x;
}

DOK::DOK(const char* input)
{
    int m,from,to;
    std::ifstream infile(input);
    std::string line;
    int i =0; //Para contar las lineas
    infile >> _n;
    infile >> m;
    for( std::string line; std::getline( infile, line ); )
    {
            infile >> from >> to;
            _mat[from][to] = 1;
    }

}

// Testing only
// TODO borrar antes de entregar matrizCompleta
std::vector<Vector> DOK::matrizCompleta()
{
    std::vector<Vector> res(_n);
    std::vector<double> ceros(_n,0.0);
    // Creo una matriz nula
    for (int i = 0; i < _n; i++)
    {
        res[i] = ceros;
    }

    iter_fila fila;
    iter_col col;

    for (int i = 0; i < _n; i++)
    {
        for (int j = 0; j < _n; j++)
        {
            if (_mat.count(i) > 0 && _mat[i].count(j) > 0)
                res[i][j] += _mat[i][j];
        }
    }

    return res;
}

// TODO borrar antes de entregar mostrarMatriz
void mostrarMatriz(DOK& dok)
{
    std::vector<Vector> vectorDeVectores = dok.matrizCompleta();
    for (int i = 0; i < vectorDeVectores[0].size(); i++)
    {
        for (int j = 0; j < vectorDeVectores[0].size(); j++)
        {
            std::cout << vectorDeVectores[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
