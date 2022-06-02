#include <iostream>
using namespace std;
#include "Int.h"

typedef Int_<int, 4> Int;

void PassTest()
{
    cout << "\n:::PASS TESTS:::" << endl; // :::PASS TESTS:::

    // Constructors
    Int f1_(5);
    Int f2_(f1_);
    cout<<Int(-18)<<endl;
    cout << "Int f1_(5) = " << f1_ << endl;  // Int f1_(5) = 5
    cout << "Int f2_(f1) = " << f2_ << endl; // Int f2_(f1) = 5

    // Fit to size
    Int f(9), f1(2), f2(-3), f4(-8), f5(-12);
    cout << "Fit to size: Int f(9) = " << f << ", f1(12) = " << f1 << ", f2(-3) = " << f2 << ", f4(-8) = " << f4 << ", f5(-12) = " << f5 << '\n';
    // Fit to size: Int f(9) = -7, f1(12) = 2, f2(-3) = -3, f4(-8) = -8, f5(-12) = 4

    // Negation
    Int f6(-8), f7(5);
    f6 = -f6;
    f7 = -f7;
    cout << "Negate: f6(-8) = " << f6 << ", f7(5) = " << f7 << '\n'; // Negate: f6(-8) = -8, f7(5) = -5

    // Assignment operator
    f2 = f1;
    cout << "Assignment: f2 = " << f2 << ", f1 = " << f1 << endl; // Assignment: f2 = 2, f1 = 2

    // Binary operations
    f1 = Int(7);
    f2 = Int(-5);
    Int f3;
    f3 = f1 + f2;
    cout << "Addition: f3 = " << f3 << ", f1 = " << f1 << ", f2 = " << f2 << endl; // Addition: f3 = 2, f1 = 7, f2 = -5
    f3 = f1 - f2;
    cout << "Subtraction: f3 = " << f3 << ", f1 = " << f1 << ", f2 = " << f2 << endl; // Subtraction: f3 = -4, f1 = 7, f2 = -5
    f3 = f1 * f2;
    cout << "Multiply: f3 = " << f3 << ", f1 = " << f1 << ", f2 = " << f2 << endl; // Multiply: f3 = -19, f1 = 7, f2 = -5
    f3 = f1 / f2;
    cout << "Divide: f3 = " << f3 << ", f1 = " << f1 << ", f2 = " << f2 << endl; // Divide: f3 = -1, f1 = 7, f2 = -5
    f3 = f1 % f2;
    cout << "Modulo: f3 = " << f3 << ", f1 = " << f1 << ", f2 = " << f2 << endl; // Modulo: f3 = 2, f1 = 7, f2 = -5
}

void FailTest()
{
    cout << "\n:::FAIL TESTS:::" << endl; // :::FAIL TESTS:::

    try
    {
        Int i1(2), i2;
        cout << "Division: i1/i2 " << i1 / i2 << "\n";
    }
    catch (const char *s)
    {
        cout << s << endl;
    } // Division: i1/i2 Divide by 0 is undefined
}

void MixedTest()
{
    cout << "\n:::MIXED TESTS:::" << endl; // :::MIXED TESTS:::

    Int i1(2), i2(8), i3(-4), i4(-11);
    cout << "i1 = " << i1 << " i2 = " << i2 << " i3 = " << i3 << " i4 = " << i4 << endl; // i1 = 2 i2 = -8 i3 = -4 i4 = 5

    Int i5;
    i5 = (i1 + i2) / (i3 - i4) * i1 + i2 - i3;
    cout << "i5 = (i1+i2)/(i3-i4) * i1 + i2 - i3 = " << i5 << endl; // i5 = (i1+i2)/(i3-i4) * i1 + i2 - i3 = -4
}

int main()
{
    PassTest();
    FailTest();
    MixedTest();
    return 0;
}
