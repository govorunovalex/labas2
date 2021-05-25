// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_matrix.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (20.04.2015)
//
// Тестирование верхнетреугольной матрицы

#include <iostream>
#include "utmatrix.h"
//---------------------------------------------------------------------------

int main()
{
  TMatrix<int> a(5), b(5), c(5);
  int i, j;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование программ поддержки представления треугольных матриц"
    << endl;
  for (i = 0; i < 5; i++)
    for (j = i; j < 5; j++ )
    {
      a[i][j] =  i * 10 + j;
      b[i][j] = (i * 10 + j) * 100;
    }
  c = a + b;
  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;
  cout << "Matrix c = a + b" << endl << c << endl;

  // їїї. їїїїїїї 2: їїїїїї ї їїїїїїї
  c.saveToFile("c.matrix");
  TMatrix<int> d(5);
  d.loadFromFile("c.matrix");
  if(c==d){
      cout << "save & load were successful!\n";
      }
  else {
      cout << "save & load were NOT successful!\n";
  }
  
  // їїї їїїїїїї 1: їїїїїїїїї їїїїїїї
  TBandMatrix<int> bandmatrix(5, 2);
  // **
  // ***
  //  ***
  //   ***
  //    **
  bandmatrix[0][0]=0;
  bandmatrix[0][1]=0;
  bandmatrix[1][0]=1;
  bandmatrix[1][1]=1;
  bandmatrix[1][2]=1;
  
  // bandmatrix[2][0]=2; // will make throw bc there is no allowed element in 2:0

  bandmatrix[2][1]=2;
  bandmatrix[2][2]=2;
  bandmatrix[2][3]=2;
  bandmatrix[0][0]=0;



  cout << "Band Matrix:\n";
  cout << bandmatrix <<endl;
}
//---------------------------------------------------------------------------
