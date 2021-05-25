// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>
#include <fstream>
using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
    if(s<0 || si<0 || s>MAX_VECTOR_SIZE) throw std::logic_error("negative value!");

    pVector = new ValType[s];
    Size = s;
    StartIndex = si;
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
    pVector = new ValType[v.Size];
    Size = v.Size;
    StartIndex = v.StartIndex;
    for(int i=0; i<Size; ++i){
        pVector[i]=v.pVector[i];
    }
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
    delete[] pVector;
    pVector = NULL;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
    pos-=StartIndex;
    if(pos<0 || pos>=Size) throw std::logic_error("negative value!");

    return pVector[pos];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
    bool result = true;
    if(Size!=v.Size){
        result = false;
    }
    else {
        for(int i=0; i<Size; ++i){
            if(pVector[i]!=v.pVector[i]){
                result = false;
                break;
            }
        }
    }
    return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
    return !(v == *this);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
    if(this!=&v){
        if(Size!=v.Size){
            delete[] pVector;
            pVector = new ValType[v.Size];
        }
        Size = v.Size;
        StartIndex = v.StartIndex;
        for(int i=0; i<Size; ++i){
            pVector[i] = v.pVector[i];
        }
    }
    
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{

    TVector<ValType> result(*this);
    for(int i=0; i<Size; ++i){
        result.pVector[i]+=val;
    }
    return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{

    TVector<ValType> result(*this);
    for(int i=0; i<Size; ++i){
        result.pVector[i]-=val;
    }
    return result;

} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{

    TVector<ValType> result(*this);
    for(int i=0; i<Size; ++i){
        result.pVector[i]*=val;
    }
    return result;

} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
    if(Size != v.Size) throw std::logic_error("negative value!");
    TVector<ValType> result(*this);

    for(int i=0; i<Size; ++i){
        result.pVector[i]+=v.pVector[i];
    }

    return result;

} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
    if(Size != v.Size) throw std::logic_error("negative value!");
    TVector<ValType> result(*this);

    for(int i=0; i<Size; ++i){
        result.pVector[i]-=v.pVector[i];
    }

    return result;

} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
    if(Size != v.Size) throw std::logic_error("negative value!");
    ValType result=0;
    
    for(int i=0; i<Size; ++i){
        result += pVector[i] * v.pVector[i];
    }

    return result;
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
 using TVector<TVector<ValType> >::pVector;
 using TVector<TVector<ValType> >::Size;       // размер вектора
 using TVector<TVector<ValType> >::StartIndex; // индекс первого элемента вектора

public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  bool saveToFile(const string& filename);
  bool loadFromFile(const string& filename);
  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++){
        in >> mt.pVector[i];
    }
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++){
        for(int j=0; j<i; ++j){
            out <<' ';
        }
        out << mt.pVector[i] << endl;
    }
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
    if(s<0 || s>MAX_MATRIX_SIZE) throw std::logic_error("wrong size!");
    for(int i=0; i<s; i++){
        pVector[i] = TVector<ValType>(s-i,i);
    }
    // ####### s=7
    //  ######
    //   #####
    //    ####
    //     ###
    //      ##
    //       #
    //
    //
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
    bool result = true;

    for(int i=0; i<Size; ++i){
        if(pVector[i] != mt.pVector[i]){
            result = false;
            break;
        }
    }

    return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
    return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
    if(this != &mt)
    {
        if(Size != mt.Size){
            delete[] pVector;
            pVector = new TVector<ValType>[mt.Size];
        }
        Size = mt.Size;
        StartIndex = mt.StartIndex;
        for(int i=0; i<Size; i++){
            pVector[i] = mt.pVector[i];
        }
    }
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
    if(Size != mt.Size) throw std::logic_error("not equal matrixes!");
    TMatrix<ValType> result(*this);

    for(int i=0; i<Size; i++){
            result.pVector[i] = result.pVector[i] + mt.pVector[i];
    }
    
    return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
    if(Size != mt.Size) throw std::logic_error("not equal matrixes!");
    TMatrix<ValType> result(*this);

    for(int i=0; i<Size; i++){
            result.pVector[i] = result.pVector[i] - mt.pVector[i];
    }
    
    return result;

} /*-------------------------------------------------------------------------*/

// Доп. задание 2: сохранение и загрузка из файла

template <class ValType>
bool  TMatrix<ValType>::saveToFile(const string& filename){
    ofstream file(filename);
    if(!file.is_open()){
        cout << "Error during write to disk!\n";
        return false;
    }

    file << *this << endl;
    return true;

}

template <class ValType>
bool  TMatrix<ValType>::loadFromFile(const string& filename){
    ifstream file(filename);
    if(!file.is_open()){
        cout << "Error during reading from disk!\n";
        return false;
    }

    file >> *this;
    return true;
}


//  Доп. Задание 1
// Ленточная матрица
template <class ValType>
class TBandMatrix : public TVector<TVector<ValType> >
{
 using TVector<TVector<ValType> >::pVector;
 using TVector<TVector<ValType> >::Size;       // размер вектора
 using TVector<TVector<ValType> >::StartIndex; // индекс первого элемента вектора

public:
  TBandMatrix(int s = 10, int b=1);                           
  TBandMatrix(const TBandMatrix &mt);                    // копирование
  TBandMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TBandMatrix &mt) const;      // сравнение
  bool operator!=(const TBandMatrix &mt) const;      // сравнение
  TBandMatrix& operator= (const TBandMatrix &mt);        // присваивание
  TBandMatrix  operator+ (const TBandMatrix &mt);        // сложение
  TBandMatrix  operator- (const TBandMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TBandMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++){
        in >> mt.pVector[i];
    }
    return in;
  }

  friend ostream& operator<<(ostream &out, const TBandMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++){
        for(int j=0;j<i; ++j) out << ' ';
          out <<mt.pVector[i] << endl;
    }
    return out;
  }
};

template <class ValType>
TBandMatrix<ValType>::TBandMatrix(int s, int b): TVector<TVector<ValType> >(s)
{
    if(s<0 || s>MAX_MATRIX_SIZE|| b>s || b<=0) throw std::logic_error("wrong size!");
    pVector[0]=TVector<ValType>(b);
    for(int i=1; i<s-1; i++){
        pVector[i] = TVector<ValType>(b+1,i-1);
    }
    pVector[s-1]=TVector<ValType>(b);
    // s =9, b=2
    // 012345678
    //0**        
    //1***       
    //2 ***       
    //3  ***     
    //4   ***     
    //5    ***    
    //6     ***   
    //7      ***  
    //8       **

} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TBandMatrix<ValType>::TBandMatrix(const TBandMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TBandMatrix<ValType>::TBandMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TBandMatrix<ValType>::operator==(const TBandMatrix<ValType> &mt) const
{
    bool result = true;

    for(int i=0; i<Size; ++i){
        if(pVector[i] != mt.pVector[i]){
            result = false;
            break;
        }
    }

    return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TBandMatrix<ValType>::operator!=(const TBandMatrix<ValType> &mt) const
{
    return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TBandMatrix<ValType>& TBandMatrix<ValType>::operator=(const TBandMatrix<ValType> &mt)
{
    if(this != &mt)
    {
        if(Size != mt.Size){
            delete[] pVector;
            pVector = new TVector<ValType>[mt.Size];
        }
        Size = mt.Size;
        StartIndex = mt.StartIndex;
        for(int i=0; i<Size; i++){
            pVector[i] = mt.pVector[i];
        }
    }
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TBandMatrix<ValType> TBandMatrix<ValType>::operator+(const TBandMatrix<ValType> &mt)
{
    if(Size != mt.Size) throw std::logic_error("not equal matrixes!");
    TBandMatrix<ValType> result(*this);

    for(int i=0; i<Size; i++){
            result.pVector[i] = result.pVector[i] + mt.pVector[i];
    }
    
    return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TBandMatrix<ValType> TBandMatrix<ValType>::operator-(const TBandMatrix<ValType> &mt)
{
    if(Size != mt.Size) throw std::logic_error("not equal matrixes!");
    TBandMatrix<ValType> result(*this);

    for(int i=0; i<Size; i++){
            result.pVector[i] = result.pVector[i] - mt.pVector[i];
    }
    
    return result;

} /*-------------------------------------------------------------------------*/


// TVector О3 Л2 П4 С6
// TBandMatrix О2 Л2 П3 С3
#endif
