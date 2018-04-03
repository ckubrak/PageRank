#include <gtest/gtest.h>
#include "../src/sparse.h"
#include <chrono>


TEST(DOK_MatrizXVector, Nula)
{
    Vector nulo(100,0.0);
    Vector dos(100,2.0);
    Vector noNulo;
    for (int i=0; i<100;i++)
        noNulo.push_back(i);

    DOK nula(100);
    EXPECT_EQ(nula*nulo,nulo);
    EXPECT_EQ(nula*dos,nulo);
    EXPECT_EQ(nula*noNulo,nulo);
}

TEST(DOK_MatrizXVector, identidad)
{
    Vector nulo(100,0.0);
    Vector dos(100,2.0);
    Vector noNulo;
    for (int i=0; i<100;i++)
        noNulo.push_back(i);

    DOK identidad(100);
    for (int i =0; i<100;i++)
    {
            identidad(i,i) = 1;
    }

    EXPECT_EQ(identidad*nulo,nulo);
    EXPECT_EQ(identidad*dos,dos);
    EXPECT_EQ(identidad*noNulo,noNulo);
}

TEST(DOK_MatrizXVector, identidadGigante)
{
    Vector nulo(100000,0.0);
    Vector dos(100000,2.0);
    Vector noNulo;
    for (int i=0; i<100000;i++)
        noNulo.push_back(i);

    DOK identidad(100000);
    for (int i =0; i<100000;i++)
    {
        identidad(i,i) = 1;
    }

    EXPECT_EQ(identidad*nulo,nulo);
    EXPECT_EQ(identidad*dos,dos);
    EXPECT_EQ(identidad*noNulo,noNulo);
}


TEST(DOK_Gauss, Identidad_Unos)
{
    DOK identidad(10);
    for (int i =0; i<10;i++)
    {
        identidad(i,i) = 1;
    }
    Vector unos(10,1.0);


    EXPECT_EQ(identidad.eliminacionGauss(unos),unos);
    mostrarMatriz(identidad);

}



TEST(DOK_Gauss, Identidad_No_Unos)
{
    DOK identidad(10);
    for (int i =0; i<10;i++)
    {
        identidad(i,i) = 1;
    }

    Vector noUnos(10,0.0);
    for (int i =0; i<10;i++)
    {
        noUnos[i] = i+1;
    }

    EXPECT_EQ(identidad.eliminacionGauss(noUnos),noUnos);
    mostrarMatriz(identidad);

}

TEST(DOK_Velocidad, Gauss150x150)
{
    DOK identidad(150);
    for (int i =0; i<150;i++)
    {
        identidad(i,i) = 1;
    }

    Vector noUnos(150,0.0);
    for (int i =0; i<150;i++)
    {
        noUnos[i] = i+1;
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    EXPECT_EQ(identidad.eliminacionGauss(noUnos),noUnos);

    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    int timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

    EXPECT_LT(timeElapsed/1000000,2); //Puede fallar segun la computadora. A mi (Cristian) me pasa
}

TEST(DOK_Construccion, txt15)
{
    DOK contruir("../tests_tp1/tests_tp1/test_30_segundos.txt");
    // mostrarMatriz(contruir);
}
