// main.cpp
// Tests all functionality of the class My_matrix class.

#include <iostream>
#include <fstream>
#include "My_matrix.h"
#include <stdexcept>

int main(){
    //int argc, char** argv
  
  // Some test cases are expected to throw an exception.
  // Add more try and catch blocks as necessary for your code
  // to finish execution.
    
  try{
    
    // Test 1
    // * Create an object of type My_matrix, called m1, using constructor
    // * Initialize m1 in main (by assigning numbers to matrix elements)
    // * Display m1 on the screen using the operator <<
      cout << "input row and column: " << endl;
      int a = 0;
      int b = 0;
      cin >> a >> b;
      My_matrix m1(a,b); // constructor called
      cout << "Enter matrix elements: " << endl;
      cin >> m1;
      cout << endl;
      cout << "m1: " << endl;
      cout << m1 << endl;
      
    // Test 2
    // * Create an object of type My_matrix, called m2, using (default)
    //   constructor
    // * Open an input file containing a matrix (row by row)
    // * Initialize m2 by reading from the input file using
    //   the operator >>
    // * Open an output file (can be empty)
    // * Write m2 to the output file using the operator <<
      
      ifstream inf;
      inf.open("input.txt");
      int n = 0;
      int m = 0;
      inf >> n >> m;
      My_matrix m2(n,m);
      inf >> m2;
      inf.close();
      ofstream outf;
      outf.open("result.txt");
      outf << m2;
      outf.close();
      // Test 3
    // * Use the copy constructor to make a copy of m1 called m3
    // * Apply the copy assignment to m1 called m4
    // * Display m3 and m4 on the screen using the operator <<
      
      My_matrix m3 = m1; // copy constructor called
      My_matrix m4;
      m4 = m1; // copy assignment operator called
      cout << "m3: " << endl << m3 << endl << "m4: " << endl << m4 << endl;
      
    // Test 4
    // * Test the matrix multiplication operator (operator*)
    // * Apply the multiplication operator to valid and invalid cases
    // * Display the resulting matrix and its number of rows and columns
      int nn5 = 0; // number of row of matrix m5
      int mm5 = 0; // number of column of matrix m5
      cout << "m5 row and column: ";
      cin >> nn5 >> mm5;
      My_matrix m5(nn5,mm5);
      cout << "Input matrix m5: " << endl;
      cin >> m5;
      
      int nn6 = 0; // number of row of matrix m6
      int mm6 = 0; // number of column of matrix m6
      cout << "m6 row and column: ";
      cin >> nn6 >> mm6;
      My_matrix m6(nn6,mm6);
      cout << "Input matrix m6: " << endl;
      cin >> m6;
      
      if (mm5 != nn6) {
          throw out_of_range("invalid.");
      }
      cout << "Number of row: " << nn5 << endl;
      cout << "Number of column: " << mm6 << endl;
       cout << "Product results: " << endl;
      cout << m5 * m6 << endl;
      
    // Test 5
    // * Test the matrix addition operator (operator+)
    // * Apply the multiplication operator to valid and invalid cases
    // * Display the resulting matrix and its number of rows and columns
    
      int nn7 = 0; // number of row of matrix m7
      int mm7 = 0; // number of column of matrix m7
      cout << "m7 row and column: ";
      cin >> nn7 >> mm7;
      My_matrix m7(nn7,mm7);
      cout << "Input matrix m7: " << endl;
      cin >> m7;
      
      int nn8 = 0; // number of row of matrix m8
      int mm8 = 0; // number of column of matrix m8
      cout << "m8 row and column: ";
      cin >> nn8 >> mm8;
      My_matrix m8(nn8,mm8);
      cout << "Input matrix m8: " << endl;
      cin >> m8;
      
      if (nn7 != nn8 || mm7 != mm8 ) {
          throw out_of_range("invalid.");
      }
       
      cout << "Number of row: " << nn7 << endl;
      cout << "Number of column: " << mm8 << endl;
      cout << "Addition results: " << endl;
      cout << m7 + m8 << endl;
      
  } catch(exception &error){
    cerr << "Error: " << error.what() << endl;
  }
}
