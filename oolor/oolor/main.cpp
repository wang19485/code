#include <iostream>
using namespace std;

class Color {
    /* Public */
public:
    void cout_rgb (void) { cout << "Color Values: (" << R << ',' << G <<
        ',' << B << ')' << endl;}
    int get_R () {
        return R;
    }
    int get_G () {
        return G;
    }
    int get_B () {
        return B;
    }
    void set_R (int r) {
        R = r;
    }
    void set_G (int g) {
        G = g;
    }
    void set_B (int b) {
        B = b;
    }
    /* Private */
private:
    int R = 255;
    int G = 255;
    int B = 255;
};

int main()
{
    Color color;
    color.cout_rgb();
    cout << "color.R = " << color.get_R() << endl;
    cout << "color.G = " << color.get_G() << endl;
    cout << "color.B = " << color.get_B() << endl;
    cout << "Please enter integer values for R, G, and B: ";
    int R, G, B;
    cin >> R >> G >> B;
    try {
        if (R > 255 || R < 0 || G > 255 || G < 0 || B > 255 || B < 0) {
            throw runtime_error("the value is out of range");
        }
    } catch (runtime_error& e) {
        cerr << e.what() << endl;
        exit(1);
    }
    color.set_R(R); color.set_G(G); color.set_B(B);
    color.cout_rgb();

}
