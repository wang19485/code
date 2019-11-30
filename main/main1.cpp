#include <iostream>
#include <string>
using namespace std;
int main()
{
    string firstName;
    string lastName;
    int birthYear;
    int heightFeet;
    int heightInch;
    int age;
    double heightCm;
    
    cout << "First name:";
    cin >> firstName;
    cout << " Last name:";
    cin >> lastName;
    cout << " Birth year:";
    cin >> birthYear;
    cout << " Height in feet (do not include inches):";
    cin >> heightFeet;
    cout << " Height in inches (do not include feet): ";
    cin >> heightInch;
    
    age = 2018 - birthYear;
    heightCm = (12 * heightFeet + heightInch) * 2.54;
    
    cout << "\nHello " << firstName << " " << lastName << "." << endl;
    cout << "You are " << age << " years old in 2018." << endl;
    cout << "Your height is " << heightCm << " cm." << endl;
    cout << "You grew an average of " << (heightCm - 51) / age << " cm per year (assuming you were 51 cm at birth)." << endl;
}
