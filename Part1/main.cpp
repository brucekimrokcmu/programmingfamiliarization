#include <iostream>

using namespace std;

struct A
{
    float data;
};
struct B
{
    A a;
};
struct C
{
    B* b; 
};
struct D
{
    C c;
}; 

int main()
{
    D* d;
    cout << "access struct A member data: ";
    cin >> ((*((*d).c).b).a).data;
    cout << "data is " << ((*((*d).c).b).a).data << endl;

    return 0;

}
