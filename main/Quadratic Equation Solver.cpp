//
//  Quadratic Equation Solver.cpp
//  main
//
//  Created by Yingjian Wang on 2018/9/6.
//  Copyright © 2018 Yingjian Wang. All rights reserved.
//
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    double a;
    double b;
    double c;
    double x;
    double x1;
    double x2;
    double delta;
    double xInt;
    double xd;
    
    cin >> a;
    cin >> b;
    cin >> c;
    if ((b < 0) && (c < 0)) {
        cout << a << "x^2" << " - " << -b << "x" << " - " << -c << " = 0" << endl;
    }
    else if ((b < 0) && (c > 0)) {
        cout << a << "x^2" << " - " << -b << "x" << " + " << c << " = 0" << endl;
    }
    else if ((b > 0) && (c < 0)) {
        cout << a << "x^2" << " + " << b << "x" << " - " << -c << " = 0" << endl;
    }
    else if ((b >= 0) && (c >= 0)) {
        cout << a << "x^2" << " + " << b << "x" << " + " << c << " = 0" << endl;
    }
    
    delta = pow(b,2) - 4 * a * c;
    
    if ((a==0) && (b==0)) {
        if (c < 0) {
            cout << a << "x^2" << " + " << b << "x" << " - " << -c << " = 0" << endl;
        }
        cout << "Unable to determine root(s)." << endl;
        
    } else {
          if (a == 0) {
               x = -c / b;
               cout << "x = " << x << endl;
          }
          else if (delta > 0) {
               x1 = (-b + sqrt(delta)) / (2 * a);
               x2 = (-b - sqrt(delta)) / (2 * a);
              cout << "x = " << x2 << "\n" << "x = " << x1 << endl;
          }
          else if (delta == 0) {
              x = (-b + sqrt(delta)) / (2 * a);
              cout << "x = " << x << endl;
          }
          else {
               xInt = -b/(2 * a);
               xd = sqrt(-delta) / (2 * a);
              if (xd > 0) {
              cout << "x = " << xInt << " - " << xd << "i" << endl;
              cout << "x = " << xInt << " + " << xd << "i" << endl;
              }
              else {
                  cout << "x = " << xInt << " + " << -xd<< "i" << endl;
                  cout << "x = " << xInt << " - " << -xd << "i" << endl;
              }
          }
    }
}

