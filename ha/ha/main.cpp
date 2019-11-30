//
//  main.cpp
//  ha
//
//  Created by 王英鉴 on 2019/2/27.
//  Copyright © 2019 王英鉴. All rights reserved.
//

#include <iostream>
using namespace std;

void nonTailRecur(int n)
{
    if (n > 0) {
        nonTailRecur(n-1);
        cout << n << " ";
        nonTailRecur(n-1);
    } else cout << endl;
}
int main() {
    nonTailRecur(4);
    return 0;
}
