#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

char digit_to_char(int);

int main (int argc, char *argv[])
{
    // (1) read decimal value from user
    cout << "Enter a decimal value : ";
    int dval;
    cin >> dval;
    
    // (2a) read base to convert decimal value to from user
    cout << "Enter a base (2-16) : ";
    int base;
    cin >> base;
    while (base > 16 || base < 2) {
        cout << "Enter a base (2-16) : ";
        cin >> base;
    }
    // (2b) continue to prompt user for base while (base < 2 || base > 16)
    
    cout << "\nBase-10 value : " << dval << '\n';
    string cval;
    // (3) perform conversion
    //string cval; // store result in a string
    // ... while some condition (remember, we continue to take mod base and subsequently divide dval by base until we reach zero...), pushing back the mod int value encoded as a character to string...
    /* Remember, we are storing the result in a string opposed to vector<int> because base some bases use characters as digits.  You can convert a digit (i.e., 0-9) to a character by calling the digit_to_char() function; for instance, if int i = 1 contains the digit that you'd like to convert (in this case, 1), writing the expression char c = digit_to_char(i) would initialize c with the character '1'.  You could then push_back c to cval (i.e., cval.push_back(c);)... When using a base larger then 10, A encodes 10 (so push back 'A' if you find a remainder of 10), B encodes 11, C encodes 12, D encodes 13, E encodes 14, and F encodes 15.  Therefore, we can convert digits int val 0-9 to 0-9 char val and store in string; if 10, 11, 12, 13, 14, or 15, we can store A, B, C, D, E, or F in that string respectively (instead of 10,...,15).  */
    
    // (4) reverse result stored in string
    // ... use for loop to do this...
    
    // (5) Print result...
    int result;
    int remain;

    result = dval;
    while (result != 0) {
        remain = result%base;
        result = result/base;
        if (remain<10) {
            char c = digit_to_char(remain);
            cval.push_back(c);
        } else {
            switch (remain) {
                case 10:
                    cval.push_back('A');
                    break;
                case 11:
                    cval.push_back('B');
                    break;
                case 12:
                    cval.push_back('C');
                    break;
                case 13:
                    cval.push_back('D');
                    break;
                case 14:
                    cval.push_back('E');
                    break;
                case 15:
                    cval.push_back('F');
                default:
                    break;
            }
        }
    }
    int tem;
    for (int i=0; i<cval.size()/2; ++i) {
         tem = cval.at(i);
         cval.at(i) = cval.at(cval.size() - 1 -i);
         cval.at(cval.size()-1-i) = tem;
    }
    
    if (cval.size() == 0)
        cout << "Base-" << base << " value : " << 0 << endl;
    else
        cout << "Base-" << base << " value : " << cval << endl;
    cout << "Digits required : " << cval.size() << endl;
    
    return 0;
}

char digit_to_char(int i)
{
    stringstream ss;
    ss << i; char c; ss >> c;
    return c;
}
