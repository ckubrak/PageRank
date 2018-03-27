#include <gtest/gtest.h>
#include "../src/sparse.h"


TEST(MatrizXVector, Nula)
{
    std::vector<double> val = {};
    std::vector<int> IA = {};
    std::vector<int> JA = {};
    CSR nula(val,IA,IA,100);

    Vector nulo(100,0.0);
    Vector dos(100,2.0);
    Vector noNulo;
    for (int i=0; i<100;i++)
        noNulo.push_back(i);

    EXPECT_EQ(nula.multiply(nulo),nulo);
    EXPECT_EQ(nula.multiply(dos),nulo);
    EXPECT_EQ(nula.multiply(noNulo),nulo);
}


TEST(MatrizXVector, NoNula)
{
    std::vector<double> val = {5,8,3,6};
    std::vector<int> IA = {0,0,2,3,4};
    std::vector<int> JA = {0,1,2,1};
    CSR ejemploWiki(val,IA,JA,4);

    Vector nulo(4,0.0);

    EXPECT_EQ(ejemploWiki.multiply(nulo),nulo);

    Vector unos(4,1.0);
    Vector res = {0,13,3,6};
    EXPECT_EQ(ejemploWiki.multiply(unos),res);
}
