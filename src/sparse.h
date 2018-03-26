#ifndef SPARCE_H
#define SPARCE_H

#include <vector>
#include <iostream>

typedef std::vector<std::vector <double> > Matriz;
// The CSR format saves on memory only when NNZ < (m (n − 1) − 1) / 2
class CSR
{
public:
    CSR();
    CSR(int n);
    CSR(const CSR&);
    CSR& operator= (const CSR&);
    CSR identity(int n);
    std::vector<double> multiply (std::vector<double>& v);

    const Matriz mostrar(int n);

private:
    std::vector<double> _val;
    std::vector<int> _IA;
    std::vector<int> _JA;
    int _n;
};
#endif
