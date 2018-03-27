#ifndef SPARCE_H
#define SPARCE_H

#include <vector>
#include <iostream>

typedef std::vector<double > Vector;
// The CSR format saves on memory only when NNZ < (m (n − 1) − 1) / 2
class CSR
{
public:
    CSR();
    CSR(int n);
    CSR(std::vector<double> val, std::vector<int> IA, std::vector<int> JA, int n);
    CSR(const CSR&);
    CSR& operator= (const CSR&);
    std::vector<double> multiply (std::vector<double>& v);

private:
    std::vector<double> _val;
    std::vector<int> _IA;
    std::vector<int> _JA;
    int _n;
};
#endif
