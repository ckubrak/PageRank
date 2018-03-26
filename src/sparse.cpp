#include "sparse.h"

CSR::CSR() {}

std::vector<double> CSR::multiply (std::vector<double>& v)
{
    std::vector<double> res(_n,0.0);

    for (unsigned int i = 0; i < _val.size(); i++)
    {
        if (i == _IA.size() -1 )
            break;
        for (int k = _IA[i]; k < _IA[i+1] ; k++)
        {
            res[i] = res[i] + _val[k]*v[_JA[k]];
        }
    }
    return res;
}

