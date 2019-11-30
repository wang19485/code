# include <iostream>
# include <stdexcept>
using namespace std ;

 int divide ( int a , int b)
 {
     if (b == 0)
         throw runtime_error (" Divide ␣by␣ Zero ");
         return ( a / b ) ;
     }

 int main ()
 {
     try {
         cout << divide (1.0 , 2.0) << endl ;
         cout << divide (4 , 2) << endl ;
         cout << divide (8 , 0) << endl ;
         cout << divide (8 , 3.0) << endl ;
         } catch ( runtime_error & e ) {
             cerr << e . what () ;
             }
         return 0;
         }
