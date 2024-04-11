#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

typedef struct
{
    double x;
    double y;
    double z;

}vector;

void addition (int &a, int &b)
{
    a=a+b;
}

void addition (double &a, double &b)
{
    a=a+b;
}

void addition (vector &a, vector &b)
{
    a.x= a.x + b.x;
    a.y=a.y + b.y;
    a.z=a.z+b.z;
}

void multiply (int &a, int &b)
{
    a=a*b;
}

void multiply (double &a, double &b)
{
    a=a*b;
}
void multiply (vector &a, vector &b)
{
    a.x= a.y*b.z-a.z*b.y;
    a.y=-a.z*b.x-a.x*b.z;
    a.z=a.x*b.y-a.y*b.x;

}
int main ()
{
    string s;
    cout <<"If you want to work with ints write:int"<<endl;
    cout <<"If you want to work with floats write: floats "<<endl;
    cout <<"If you want to work with 3dvector write: vectors"<<endl;
    if (!(cin >> s))
    {
        cerr << "cant read"<<endl;
        return -1;

    }
    if (s=="int")
    {
        int a, b, i;
        char k;
        cout <<"Choose a, b to calculate"<<endl;
        cin >> a;
        while((cin >> b) )
        {
            cout<<"choose + or * "<< endl;
            cin >> k;
            if (k=='+')
            {
                addition(a, b);
            }
            else if (k=='*')
            {
                multiply(a, b);
            }
            else
            {
                cerr <<"incorrect sign"<< endl;
                return -2;
            }
            cout<<"Result is "<< a <<endl;
            cout << "if you want to continue enter 1, if you want to stop enter any other number" << endl;
            if (!(cin >> i) || i!=1)
            {
                cout << "Programm stopped running" << endl;
                return 0;
            }
            cout<<"Enter b" <<endl;
        }
    }
    if (s=="float")
    {
        double a, b;
        int i;
        char k;
        cout <<"Choose a, b to calculate"<<endl;
        cin >>a;
        while((cin >> b))
        {
            cout<<"choose + or * "<< endl;
            cin >> k;
            if (k=='+')
            {
                addition(a, b);
            }
            else if (k=='*')
            {
                multiply(a, b);
            }
            else
            {
                cerr <<"incorrect sign"<< endl;
                return -2;
            }
            cout<<"Result is "<< a <<endl;
            cout << "if you want to continue enter 1, if you want to stop enter any other number" << endl;
            if (!(cin >> i) || i!=1)
            {
                cout << "Programm stopped running" << endl;
                return 0;
            }
            cout<<"Enter b" <<endl;
        }
    }
     if (s=="vectors")
    {
        vector a, b;
        int i;
        char k;
        cout <<"Choose a, b to calculate"<<endl;
        cin >> a.x >> a.y >> a.z;
        while ((cin >> b.x >> b.y >> b.z))
        {
            cout<<"choose + or * "<< endl;
            cin >>k;
            if (k== '+')
            {
                addition(a, b);
            }
            else if (k== '*' )
            {
                multiply(a, b);
            }
            else
            {
                cerr <<"incorrect sign"<< endl;
                return -2;
            };
            cout<<"Result is ("<< a.x << " ; "<< a.y <<" ; " << a.z << ")" << endl;
            cout << "if you want to continue enter 1, if you want to stop enter any other number" << endl;
            if (!(cin >>  i) || i!=1)
            {
                cout << "Programm stopped running" << endl;
                return 0;
            }
            cout<<"Enter b" <<endl;
        }
    }
    cerr << "incorrect input" << endl;
    return 1;
}