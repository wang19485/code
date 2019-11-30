/* My_matrix.h

Header file for the class My_matrix

Write your name and UIN here

*/

#include <iostream>
#include <exception>
#include <vector>
#include <stdexcept>

using namespace std;
// Definitions of user defined type exceptions 
struct invalid_input : public exception {
  virtual const char* what() const throw()
  { return "Invalid matrix input"; }
};

struct incompatible_matrices : public exception {
  virtual const char* what() const throw()
  { return "Incompatible matrices"; }
};

template <typename T>
class My_matrix{
	
  //member variables
  int n, m;
  //int **ptr;
  vector<vector<T>>data;
  void allocate_memory();  // optional
  
public:	
  //member functions
  My_matrix();  // default constructor
  My_matrix(int n1, int m1); // parameter constructor
  //~My_matrix(); // destructor
  //My_matrix(const My_matrix& mat); // copy constructor
  //My_matrix(My_matrix&& mat);  // move constructor (optional)
  //My_matrix& operator=(const My_matrix& mat); //copy assignment operator
  //My_matrix& operator=(My_matrix&& mat); // move assignment operator (optional)
  T number_of_rows() const;
  T number_of_columns() const;
  //int* operator()(int i) const; // overloaded to access to ith row
  T& operator()(int i, int j); // overloaded to access (i,j) element
  T operator()(int i, int j) const; // overloaded to access (i,j) element
  T elem(int i, int j) const; // overloaded to access (i,j) element
  T& elem(int i, int j); // overloaded to access (i,j) element
};

// see the handout for the description of these operators
template <typename T>
istream& operator>>(istream& in, My_matrix<T>& mat);
template <typename T>
ostream& operator<<(ostream& out, const My_matrix<T>& mat);
template <typename T>
My_matrix<T> operator+(const My_matrix<T>& mat1, const My_matrix<T>& mat2);
template <typename T>
My_matrix<T> operator*(const My_matrix<T>& mat1, const My_matrix<T>& mat2);

template <typename T>
My_matrix<T>::My_matrix(): n(0), m(0){}

//void My_matrix::allocate_memory(){}
template <typename T>
My_matrix<T>::My_matrix(int n1, int m1)
{
    T dta;
    n = n1;
    m = m1;
    //vector<vector<int>>data;
    for (int i = 0; i < n; ++i) {
        vector<T>row;
        for (int j = 0; j < m; ++j) {
            row.push_back(dta);
        }
        data.push_back(row);
    }
}

template <typename T>
T My_matrix<T>::number_of_rows() const
{
    return n;
}

template <typename T>
T My_matrix<T>::number_of_columns() const
{
    return m;
}

template <typename T>
T My_matrix<T>::operator()(int i, int j) const
{
    return data[i][j];
}

template <typename T>
T& My_matrix<T>::operator()(int i, int j)
{
    return data[i][j];
}

template <typename T>
T My_matrix<T>::elem(int i, int j) const
{
    if (i < 0 || i >= n) throw out_of_range("Out of range");
    if (j < 0 || j >= m) throw out_of_range("Out of range");
    return data[i][j];
}

template <typename T>
T& My_matrix<T>::elem(int i, int j)
{
    return data[i][j];
}

template <typename T>
ostream& operator<<(ostream& out, const My_matrix<T>& mat)
{
    for (int i = 0; i < mat.number_of_rows(); i++){
        for (int j = 0; j < mat.number_of_columns(); j++){
            out << mat.elem(i, j) << " ";
        }
        out << endl;
    }
    return out;
}

template <typename T>
istream& operator>>(istream& in, My_matrix<T>& mat)
{
    for (int i = 0; i < mat.number_of_rows(); i++){
        for (int j = 0; j < mat.number_of_columns(); j++) {
            in >> mat.elem(i, j);
        }
    }
    return in;
}

template <typename T>
My_matrix<T> operator+(const My_matrix<T>& mat1, const My_matrix<T>& mat2)
{
    My_matrix<T> matSum(mat1.number_of_rows(),mat1.number_of_columns());
    for (int i = 0; i < mat1.number_of_rows(); ++i){
        for (int j = 0; j < mat1.number_of_columns(); ++j){
            matSum.elem(i, j) = mat1.elem(i, j) + mat2.elem(i, j);
        }
    }
    return matSum;
}

template <typename T>
My_matrix<T> operator*(const My_matrix<T>& mat1, const My_matrix<T>& mat2)
{
    My_matrix<T> matP(mat1.number_of_rows(),mat2.number_of_columns());
    for (int i = 0; i < matP.number_of_rows(); i++){
        for (int j = 0; j < matP.number_of_columns(); j++){
            for (int k = 0; k < mat1.number_of_columns();k++){
                matP(i, j) += mat1(i, k) * mat2(k, j);
            }
        }
    }
    return matP;
}

