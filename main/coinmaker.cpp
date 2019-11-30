//
//  coinmaker.cpp
//  main
//
//  Created by 王英鉴 on 2018/9/11.
//  Copyright © 2018年 王英鉴. All rights reserved.
//

#include "coinmaker.hpp"
#include<cmath>
#include<string>
using namespace std;
int main() {
    double userInput;
    int pennyNumber;
    int nickelNumber;
    int dimeNumber;
    int quarterNumber;
    int makeCents;
    int remainDer1;
    int remainDer2;
    int remainDer3;
    int totalNumber;
    cout << "Enter dollar amount: ";
    cin >> userInput;
    makeCents = userInput * 100;
    quarterNumber = makeCents / 25;
    remainDer1 = makeCents % 25;
    dimeNumber = remainDer1 / 10;
    remainDer2 = remainDer1 % 10;
    nickelNumber = remainDer2 / 5;
    remainDer3 = remainDer2 % 5;
    pennyNumber = remainDer3;
    totalNumber = pennyNumber + nickelNumber + dimeNumber + quarterNumber;
    cout << "Amount requested: $" << userInput<<endl;
    cout << "Quarters: " << quarterNumber << endl;
    cout << "Dimes: " << dimeNumber << endl;
    cout << "Nickels: " << nickelNumber << endl;
    cout << "Pennies: " << pennyNumber << endl<<endl;
    cout << "Total coins used: " << totalNumber << endl;
    
}
