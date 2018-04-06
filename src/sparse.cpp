#include "sparse.h"
DOK::DOK(size_t n)
{
    _n = n;
    _m = 0;
}

DOK::DOK(const char* input)
{
    int from,to;
    std::ifstream infile(input);
    std::string line;
    infile >> _n;
    infile >> _m;
    for( std::string line; std::getline( infile, line ); )
    {
        infile >> from >> to;
        _mat[from-1][to-1] = 1;
        _m++;
    }

}

DOK::DOK(size_t n, double val)
{
    _n = n;
    for (int i = 0; i < _n; i++)
    {
        _mat[i][i] = val;
        _m ++;
    }
}

DOK DOK::multiplicarMatriz(DOK &m)
{
    DOK C(this->_n);
    for (size_t i=0; i < this->size(); ++i)
        if(_mat.count(i) != 0)
            for (size_t j=0; j < this->size(); ++j)
            {
                if(_mat[i].count(j))
                    for (size_t k=0; k < this->size(); ++k)
                    {
                        if (m._mat.count(k) > 0 && m._mat[k].count(j) > 0)
                        {
                            if (C._mat.count(i) > 0 && C._mat[j].count(j) > 0)
                                C._mat[i][j] += this->_mat[i][k] * m._mat[k][j];
                            else
                                C._mat[i][j] = this->_mat[i][k] * m._mat[k][j];
                        }
                    }
            }
    return C;
}
void DOK::restarMatrices(DOK& m)
{
    m.multiplicarConstante(-1.0);
    sumarMatrices(m);
}
void DOK::sumarMatrices(DOK& m)
{
    for (int i = 0; i < _n; i++)
    {
        for (int j = 0; j < _n; j++)
        {
            if (_mat.count(i) > 0 && _mat[i].count(j) > 0)
            {
                if(m._mat.count(i) > 0 && m._mat[i].count(j) > 0)
                {
                    _mat[i][j] += m._mat[i][j];
                }
            }
            else
            {
                if(m._mat.count(i) > 0 && m._mat[i].count(j) > 0)
                {
                    _mat[i][j] = m._mat[i][j];
                }
            }
        }
    }
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

void DOK::multiplicarConstante(double c)
{

    for (int i = 0; i <size(); i++)
    {
        if (_mat.count(i) > 0)
            for (int j = 0; j < size(); j++)
            {
                if (_mat[i].count(j) > 0){
                    _mat[i][j] = c * _mat[i][j];
                }

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

    for (int k = 0; k < b.size() ; k++)
    {
        for (int i = k+1 ; i < _n ; i++)
        {
            if (_mat.count(i) == 0 || _mat[i].count(k) == 0)
                {
                    break;
                }
            else
            {
               mult = _mat[i][k] / _mat[k][k];

            }
            for (int j = k ; j < _n;j++)
            {
                double ij = _mat[i][j] - mult * _mat[k][j];
                //TODO cambiar por epsilon
                if (std::fabs(ij) < 0.0001)
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

    int n = n-2;
    Vector x(_n-1,0.0);
    for (int i = _n-2; i >= 0; i--)
    {
        x[i] = _mat[i][_n-1];
        // std::cout << "\n xi: "<< x[i]<< std::endl;

        for(int j = i+1; j <= _n-2; j++)
        {
            x[i] = x[i] - _mat[i][j]*x[j];
        }
        x[i] = x[i]/_mat[i][i];
        std::cout << "\n x "<< i << " "<< x[i]<< std::endl;
    }
    // int n = _n - 2;
    // Vector x(n-1,0);

    // x[n] = _mat[n-1][n] / _mat[n][n];
    // int n = _n - 1;

    // Vector x(n,0);
    // for (int i = 1; i >= 1; i++)
    // {
    //     x[i] = _mat[i][_n-1];
    //     // std ::cout <<x[i];
    // }
    // x[n] = _mat[n][n+1] / _mat[n][n];
    // std::cout << x[n-1] << "\n\n\n";
    // for (int i = n-1; i >= 1 ; i-- )
    // {
    //     double sum = 0;
    //     for (int j = i + 1; j <= n; j++)
    //     {
    //             sum += _mat[i][j]*x[j];
    //     }
    //     x[i]=(_mat[i][n+1]-sum)/_mat[i][i];
    //     std::cout << "n: " << n << std::endl;
    //     std::cout << "i: " << i << std::endl;
    //     std::cout << "_mat[i][n]: " << _mat[i][n]<< std::endl;
    //     std::cout << x[i] << std::endl;
    // }
    return x;
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
            std::cout << vectorDeVectores[i][j] << "     ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

//Esta funcion es para armar la matriz diagonal D, la de "balance"
//TODO testear estas dos
DOK::DOK(DOK& m)
{
  // std::cout << "dentro de DOK(m): " << std::endl;
  // mostrarMatriz(m);
  // std::cout << m._n << std::endl;
    _n = m._n;
    for (int j = 0; j < _n; j++)
    {
        int cj = Cj(j,m);
        if(cj != 0)
        {
            _mat[j][j] = (1.0 / double(cj));
        }
    }
}

int DOK::Cj(int j, DOK& m){
	int Cj = 0;
	for (int i = 0; i < _n; i++) //i son filas, j es la columna fija
	{
		if(m._mat.count(i) > 0 && m._mat[i].count(j) > 0)
		{
			//Cj += m._mat[i][j];
      Cj += 1;
		}
	}
	return Cj; //Cj son la cantidad de links salientes de la pagina j
}

//Caminante aleatorio:
