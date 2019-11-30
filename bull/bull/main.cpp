#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <cmath>

using namespace std;

void Digit(int& enterCode, int& numDig, vector<int>& quoV) {
    int quo = 0;
    int rem = 0;
    
    for (int i = numDig-1; i >=1; --i) {
        quo = enterCode/(pow(10, i));
        rem = enterCode - quo * pow(10, i);
        quoV.push_back(quo);
        enterCode = rem;
        if (i == 1) {
            quoV.push_back(enterCode);
        }
    }
}

int main() {
    srand(std::chrono::duration_cast<std::chrono::milliseconds>
          (std::chrono::system_clock::now().time_since_epoch()).count()%2000000000);
    // needed to autograde some test cases in Mimir
    int input = 1;
    
    do {
        cout << "Enter number of digits in code (3, 4 or 5): ";
        cin >> input;
    } while (!((input == 3) || (input == 4) || (input == 5) || (input == 0)));
    
    
    int inputCode= 0;
    int digCode = 0;
    vector<int>inputCodeV;
    int guess = 0;
    
        int countDig = 0;
        do {
            if (input == 0) {
                cout << "Enter code: ";
                cin >> inputCode;
                cout << "Enter number of digits in code: ";
                cin >> digCode;
            } else {
                int sum = 0;
                for (int i = 0; i<input; ++i) {
                    sum = sum + rand()%10 * pow(10, i);
                }
                inputCode = sum;
                digCode = input;
            }
            countDig = 0;
    
            Digit(inputCode, digCode,inputCodeV);
            
            for (int i = 0; i<inputCodeV.size()-1; ++i) {
                for (int j = i+1; j<inputCodeV.size();++j) {
                    if (inputCodeV.at(i) == inputCodeV.at(j)) {
                        ++countDig;
                    }
                }
            }
            if (countDig != 0) {
                inputCodeV.clear();
            }
        } while (countDig != 0);
        
        
        cout << "Number to guess: " << inputCodeV.at(0);
        for (int i = 1; i<inputCodeV.size(); ++i) {
            cout << "-" << inputCodeV.at(i);
        }
        cout << endl;
        
        bool b = 1;
        vector<int>guessV;
        int digCode2 = digCode;
        
        //
        do {
            int bull = 0;
            int cows = 0;
            int count = 0;
            cout << "Enter Guess: ";
            cin >> guess;
            int guess1 = guess;
            
            int leng = 1;
            while (guess>=10) {
                guess/=10;
                ++leng;
            }
            
            if (leng > digCode) {
                cout << "You can only enter " << digCode <<" digits." << endl;
                b = false;
                continue;
            } else {
            
            
            Digit(guess1, digCode2, guessV);
                for (int i = 0; i<guessV.size()-1; ++i) {
                   for (int j = i+1; j<guessV.size();++j) {
                      if (guessV.at(i) == guessV.at(j)) {
                          ++count;
                      }
                   }
                }
            }
            
            if (count != 0) {
                cout << "Each number must be different." << endl;
                b = 0;
                guessV.clear();
                continue;
            } else {
                if (bull!=digCode) {
                    b = 0;
                    for (int i = 0; i<guessV.size(); ++i) {
                        for (int j = 0; j<guessV.size();++j) {
                            if (guessV.at(i) == inputCodeV.at(j)){
                                if (i == j) {
                                    ++bull;
                                } else {
                                    ++cows;
                                }
                            }
                            
                        }
                    }
                    
                    guessV.clear();
                    if (bull==digCode) {
                        b = 1;
                        cout << digCode << " bulls... " << inputCodeV.at(0);
                        for (int i = 1; i<inputCodeV.size(); ++i) {
                            cout << "-" << inputCodeV.at(i);
                        }
                        cout << " is correct!" << endl;
                    } else {
                    cout << bull << " bulls" << endl;
                    cout << cows << " cows" << endl;
                    }
                }
            }
        } while (b == 0);
}

