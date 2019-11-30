/* 
Implementation of the clas My_matrix
*/

/*#include "My_matrixVector.h"
#include <stdexcept>
#include <vector>

My_matrixVector::My_matrixVector(): n(0), m(0){}

void My_matrixVector::allocate_memory(){}

My_matrixVector::My_matrixVector(int n1, int m1)
{
    //int dta = 0;
    n = n1;
    m = m1;
    //vector<vector<int>>data;
    for (int i = 0; i < n; ++i) {
        vector<int>row;
        for (int j = 0; j < m; ++j) {
            row.push_back(0);
        }
        data.push_back(row);
    }
}*/

/*My_matrix::My_matrix(const My_matrix& mat)
{
    n = mat.n;
    m = mat.m;
    vector<vector<int>>data;
    for (int i = 0; i < n; ++i) {
        vector<int>row;
        for (int j = 0; j < m; ++j) {
            row.push_back(0);
        }
        data.push_back(row);
    }
    for (int i = 0; i < mat.number_of_rows(); i++){
        for (int j = 0; j < mat.number_of_columns(); j++){
            data[i][j] = mat.elem(i, j);
        }
    }
}*/

// move constructor (optional)
/*My_matrix::My_matrix(My_matrix&& mat)
{
    n = mat.n;
    m = mat.m;
    vector<vector<int>>data;
    for (int i = 0; i < n; ++i) {
        vector<int>row;
        for (int j = 0; j < m; ++j) {
            row.push_back(0);
        }
        data.push_back(row);
    }
    for (int i = 0; i < mat.number_of_rows(); i++){
        for (int j = 0; j < mat.number_of_columns(); j++){
            data[i][j] = mat.elem(i, j);
        }
    }
}*/

/*My_matrix::~My_matrix()
{
    for (int i = 0; i < n; i++){
        delete[] ptr[i];
    }
    delete[] ptr;
}*/

/*My_matrix& My_matrix::operator=(const My_matrix& mat)
{
    if (this == &mat){return *this;}
    
    n = mat.n;
    m = mat.m;
    vector<vector<int>>data;
    for (int i = 0; i < n; ++i) {
        vector<int>row;
        for (int j = 0; j < m; ++j) {
            row.push_back(0);
        }
        data.push_back(row);
    }
    for (int i = 0; i < mat.number_of_rows(); i++){
        for (int j = 0; j < mat.number_of_columns(); j++){
            data[i][j] = mat.elem(i, j);
        }
    }
    
    return *this;
}*/

// move assignment operator (optional)
/*My_matrix& My_matrix::operator=(My_matrix&& mat)
{
    if (this == &mat){return *this;}
    
    n = mat.n;
    m = mat.m;
    vector<vector<int>>data;
    for (int i = 0; i < n; ++i) {
        vector<int>row;
        for (int j = 0; j < m; ++j) {
            row.push_back(0);
        }
        data.push_back(row);
    }
    for (int i = 0; i < mat.number_of_rows(); i++){
        for (int j = 0; j < mat.number_of_columns(); j++){
            data[i][j] = mat.elem(i, j);
        }
    }
    
    return *this;
}*/

/*int My_matrixVector::number_of_rows() const
{
    return n;
}

int My_matrixVector::number_of_columns() const
{
    return m;
}*/

/*int* My_matrix::operator()(int i) const
{
    return ptr[i];
}*/

/*int My_matrixVector::operator()(int i, int j) const
{
    return data[i][j];
}

int& My_matrixVector::operator()(int i, int j)
{
    return data[i][j];
}

int My_matrixVector::elem(int i, int j) const
{
  if (i < 0 || i >= n) throw out_of_range("Out of range");
  if (j < 0 || j >= m) throw out_of_range("Out of range");
  return data[i][j];
}

int& My_matrixVector::elem(int i, int j)
{
    return data[i][j];
}

ostream& operator<<(ostream& out, const My_matrixVector& mat)
{
    for (int i = 0; i < mat.number_of_rows(); i++){
        for (int j = 0; j < mat.number_of_columns(); j++){
            out << mat.elem(i, j) << " ";
        }
        out << endl;
    }
    return out;
}

istream& operator>>(istream& in, My_matrixVector& mat)
{
    int dta = 0;
    for (int i = 0; i < mat.number_of_rows(); i++){
        for (int j = 0; j < mat.number_of_columns(); j++) {
            in >> dta;
            mat.elem(i, j) = dta;
        }
    }
    return in;
}

My_matrixVector operator+(const My_matrixVector& mat1, const My_matrixVector& mat2)
{
    My_matrixVector matSum(mat1.number_of_rows(),mat1.number_of_columns());
    for (int i = 0; i < mat1.number_of_rows(); ++i){
        for (int j = 0; j < mat1.number_of_columns(); ++j){
            matSum.elem(i, j) = mat1.elem(i, j) + mat2.elem(i, j);
        }
    }
    return matSum;
}

My_matrixVector operator*(const My_matrixVector& mat1, const My_matrixVector& mat2)
{
    My_matrixVector matP(mat1.number_of_rows(),mat2.number_of_columns());
    for (int i = 0; i < matP.number_of_rows(); i++){
        for (int j = 0; j < matP.number_of_columns(); j++){
            for (int k = 0; k < mat1.number_of_columns();k++){
                matP(i, j) += mat1(i, k) * mat2(k, j);
            }
        }
    }
    return matP;
}*/
