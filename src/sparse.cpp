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
    std::cout << "lei: \n";
    std::cout << _n << _m;

    for( std::string line; std::getline( infile, line ); )

    {
        infile >> from >> to;
        //std::cout << "desde: " << from << "\n";
        //std::cout << "hasta: " << to << "\n";
        _mat[to-1][from-1] = 1;
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
        // if(_mat.count(i) != 0)
            for (size_t j=0; j < this->size(); ++j)
            {
                if(_mat[i].count(j))
                    for (size_t k=0; k < this->size(); ++k)
                    {
                        if (m._mat[k].count(j) > 0)
                        {
                            if (C._mat[j].count(j) > 0)
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
            if (_mat[i].count(j) > 0)
            {
                if(m._mat[i].count(j) > 0)
                {
                    _mat[i][j] += m._mat[i][j];
                }
            }
            else
            {
                if( m._mat[i].count(j) > 0)
                {
                    _mat[i][j] = m._mat[i][j];
                }
            }
        }
    }
}


// Vector DOK::operator*(const Vector& x)
// {

//     Vector y(_n);
//     double sum;

//     iter_fila fila;
//     iter_col col;

//     for(fila=_mat.begin(); fila!=_mat.end(); fila++){
//         sum=0;
//         for(col=(*fila).second.begin(); col!=(*fila).second.end(); col++){
//             sum += (*col).second * x[(*col).first];
//         }
//         y[(*fila).first]=sum;
//     }

//     return y;
// }

void DOK::multiplicarConstante(double c)
{

    for (int i = 0; i <size(); i++)
    {
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
    double mult, matij, matkj;
    size_t n; //cantidad total de filas de la matriz
    double eps = 0.001;

    // Se agrega a b en la ultima columna
    // esto aumenta en 1 la dimension de toda la matriz pero en realidad sigue
    // habiendo una fila menos
    n=_n;
    _n++;
// std::cout << "EG filas: " << n << " \n";
    for (int i=0; i < n; i++) //agregar b en la ultima columna
    {
        //    std::cout << fabs(b[i]) << std::endl;
        if (fabs(b[i]) > eps)
        {
            _mat[i][b.size()] = b[i];
        }
    }
// std::cout << "EG. Ya se armo b \n";
    for (int k = 0; k < n-1 ; k++) //filas pivote
    {
        // controlar que el pivote no sea cero
        // por seguridad: la estructura de la matriz nos garantiza que no va a pasar

        if (k%100 == 0)
            std::cout << "fila pivote k: " << k << std::endl;

        for (int i = k+1 ; i < n ; i++) //filas a eliminar
        {
            //  std::cout << "elimin fila i: " << i << std::endl;
            // verificar que en la primera columna de la fila a eliminar no haya cero
            // si ya hubiera cero pasar a eliminar la siguiente fila
            if (_mat[i].count(k) != 0)
            {
                mult = _mat[i][k] / _mat[k][k]; //calcular multiplicador

                    for (iter_col col = _mat[k].begin(); col != _mat[k].end(); col++)
                    {
                        int j = (*col).first;
                        if (j < k)
                            continue;
                        if (_mat[k].count(j) != 0)
                        {
                            matkj=_mat[k][j];
                            if (_mat[i].count(j) == 0)
                            {
                                matij=0;
                            }
                            else
                            {
                                matij=_mat[i][j];
                            }

                            double ij = matij - mult * matkj;
                            if (fabs(ij) < eps)
                            {

                                _mat[i].erase(j);
                            }
                            else
                            {
                                _mat[i][j] = ij;
                            }
                        }
                    }
            } //fin no hay cero en la primera columna de la fila i
        } // fin filas a eliminar
    } // fin filas pivote
    std::cout << "terminamos de triangular " << std::endl;
// mostrarMatriz(*this);

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
        // std::cout << "\n x "<< i << " "<< x[i]<< std::endl;
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


    for (int i = 0; i < _n; i++)
    {
        for (int j = 0; j < _n; j++)
        {
            if (_mat[i].count(j) > 0)
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
            std::cout << vectorDeVectores[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

//Armar la matriz diagonal D, "balance"
DOK::DOK(DOK& m)
{
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
		if(m._mat[i].count(j) > 0)
      Cj += 1;
	}
	return Cj; //Cj son la cantidad de links salientes de la pagina j
}

//Caminante aleatorio:
