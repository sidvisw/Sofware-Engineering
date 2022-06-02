#include <iostream>
using namespace std;

#include "Poly.h"

typedef Poly<int> poly;

void PassTest()
{
    cout << "\n:::PASS TESTS:::" << endl; // ::::PASS TESTS:::

    // Constructors
    poly p1({5, 4});
    poly p2;
    cin >> p2; // Pass the input: 7 -6 2 5
    poly p3(p1);
    cout << "poly p1(2): " << p1 << endl; // poly p1(2): 4x + 5
    cout << "poly p2: " << p2 << endl; // poly p2: 5x^3 + 2x^2 - 6x + 7
    cout << "poly p3(p1): " << p3 << endl; // poly p3(p1): 4x + 5

    // Negation
    cout << "-p2: " << -p2 << endl; // -p2: -5x^3 - 2x^2 + 6x - 7

    // Assignment operator
    p1 = p2;
    cout << "Assignment: p1 = " << p1 << ", p2 = " << p2 << endl; // Assignment: p1 = 5x^3 + 2x^2 - 6x + 7, p2 = 5x^3 + 2x^2 - 6x + 7

    // Binary operations
    cin >> p1; // Pass the input: 5 4 3 2
    cin >> p2; // Pass the input: 1 -1 -2
    p3 = p1 + p2;
    cout << "Additon: p3 = " << p3 << ", p1 = " << p1 << ", p2 = " << p2 << endl; // Additon: p3 = 2x^3 + 1x^2 + 3x + 6, p1 = 2x^3 + 3x^2 + 4x + 5, p2 = -2x^2 - 1x + 1
    p3 = p1 - p2;
    cout << "Subtraction: p3 = " << p3 << ", p1 = " << p1 << ", p2 = " << p2 << endl; // Subtraction: p3 = 2x^3 + 5x^2 + 5x + 4, p1 = 2x^3 + 3x^2 + 4x + 5, p2 = -2x^2 - 1x + 1

    // Evaluate at x = 3 and x = -2
    cout << "p1(3) = " << p1(3) << ", p2(-2) = " << p2(-2) << endl; // p1(3) = 98, p2(-2) = -5
}

void FailTest()
{
    cout << "\n:::FAIL TESTS:::" << endl; // :::FAIL TESTS:::
    try
    {
        vector<int> v;
        cout<<"poly p(v): ";
        poly p(v);
        cout << p << '\n';
    }
    catch (const char *s)
    {
        cout << s << endl;
    } // poly p(v): Empty vector of coefficients given to create Polynomial
}

void MixedTest()
{
    cout << "\n:::MIXED TESTS:::" << endl; // :::MIXED TESTS:::

    poly p1(2), p2(8), p3(5), p4;
    cin >> p1; // Pass this input: 7 -6 2 5
    cin >> p2; // Pass this input: 1 -1 -2
    cin >> p3; // Pass this input: 5 4 3 2

    cout << "p1 = " << p1 << "\np2 = " << p2 << "\np3 = " << p3 << "\np4 = " << p4 << endl;
    // p1 = 5x^3 + 2x^2 - 6x + 7
    // p2 = -2x^2 - 1x + 1
    // p3 = 2x^3 + 3x^2 + 4x + 5
    // p4 = 0

    p4 -= (p2 + p3) - p1;
    cout << "p4 -= (p2+p3) - p1 = " << p4 << endl; // p4 -= (p2+p3) - p1 = 3x^3 + 1x^2 - 9x + 1
}

int main()
{
    PassTest();
    FailTest();
    MixedTest();
    return 0;
}
