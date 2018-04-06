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

  //mostrarMatriz(*this);
//std::cout << "multiplicar constante c: " << c << std::endl;
  //std::cout << "_mat size: " << _mat.size() << std::endl;
    for (int i = 0; i <_mat.size(); i++)
    {
      //std::cout << "i, _mat.count(i): " << i << " " <<  _mat.count(i) << std::endl;
        if (_mat.count(i) > 0)
      //  std::cout << "_mat[i].size: " << _mat[i].size() << std::endl;
            for (int j = 0; j < _mat.size(); j++)
            {
    //          std::cout << "_mat size, j: " << _mat[i].size() << " " << j << std::endl;
                if (_mat[i].count(j) > 0){
      //            std::cout << "_mat[i].count(j) size, j: " << _mat[i].size() << " " << j << std::endl;
                  _mat[i][j] = c * _mat[i][j];
        //          std::cout << "c*_mat[i][j]: " << _mat[i][j] <<  std::endl;
                }

            }
    }
//    std::cout << "antes de salir mult cte: " << std::endl;
//    mostrarMatriz(*this);
//    std::cout << "ya mostramos y salimos " << std::endl;
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
                double ij = _mat[i][j] - mult * _mat[k][j];
                //TODO cambiar por epsilon
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

//Esta funcion es para armar la matriz diagonal D, la de "balance"
//TODO testear estas dos
DOK::DOK(DOK& m)
{
  std::cout << "dentro de DOK(m): " << std::endl;
  mostrarMatriz(m);
  std::cout << m._n << std::endl;
    _n = m._n;
    for (int j = 0; j < _n; j++)
    {
        int cj = Cj(j,m);
        if(cj != 0)
        {
            _mat[j][j] = (1 / cj);
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
