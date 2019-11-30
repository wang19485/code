# include <iostream>
using namespace std ;

 int main () {
    
     constexpr int val = 1;
    
     switch ( val ) {
             case 1:
             cout << " Pawn " << endl ;
             case 2:
             cout << " Rook " << endl ;
             case 3:
             cout << " Knight " << endl ;
             break ;
             case 4:
             cout << " Bishop " << endl ;
             case 5:
             cout << " Queen " << endl ;
             case 6:
             cout << " King " << endl ;
             break ;
         }
     cout << endl ;
     return 0;
     }
