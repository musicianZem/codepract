#include <iostream>

using namespace std;

class A
{
    private :
        int a;
    protected :
        int b;
    public :
        int c;
        A() {
            a = 1;
            b = 2;
            c = 3;
        }
};

class A_private : private A {
    public :

};

int main() {
}






