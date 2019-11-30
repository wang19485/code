//
//  fun.cpp
//  test
//
//  Created by 王英鉴 on 2018/10/8.
//  Copyright © 2018年 王英鉴. All rights reserved.
//

#include "fun.h"
#include<vector>
#include<string>
#include<iostream>

std::string reverseWords(const std::string & a) {
    std::string a1;
    std::string a2;
    for (int i = 0; i<a.find(" "); ++i) {
        a1.push_back(a.at(i));
    }
    for (int j = 0; j<a1.size()/2; ++j) {
        char tem = a1.at(j);
        a1.at(j) = a1.at(a1.size()-j-1);
        a1.at(a1.size()-j-1) = tem;
    }
    
    for (unsigned long int i = a.find(" ")+1; i<a.size(); ++i) {
        a2.push_back(a.at(i));
    }
    
    for (int i = 0; i < a2.size()/2; ++i) {
        char tem2 = a2.at(i);
        a2.at(i) = a2.at(a2.size()-i-1);
        a2.at(a2.size()-i-1) = tem2;
    }
    
    std::string b = a1 + " " + a2;
    //std::cout << b << std::endl;
    return b;
}
