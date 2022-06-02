#include <iostream>
#include "Fraction/Fraction.h"
#include "Int/Int.h"
#include "Polynomial/Poly.h"
using namespace std;

typedef Fraction<int> fraction;
typedef Int_<int, 4> Int;
typedef Poly<int> poly;

typedef Fraction<Int> FracInt;
typedef Poly<Int> PolyInt;
typedef Poly<FracInt> PolyFracInt;

void Test1()
{
    cout<<":::Test 1: Fraction and Int:::\n"; // :::Test 1: Fraction and Int:::

    // Constructors
    FracInt fi1(Int(2), Int(-7)), fi2(Int(-18), Int(5));
    cout << "FracInt fi1(Int(2), Int(-5)) = " << fi1 << '\n'; // FracInt fi1(Int(2), Int(-5)) = -2/7
    cout << "FracInt fi2(Int(-18), Int(3)) = " << fi2 << '\n'; // FracInt fi2(Int(-18), Int(3)) = -2/5

    // Binary Arithmetic:
    cout << "fi1 + fi2 = " << fi1 + fi2 << '\n'; // fi1 + fi2 = 0
    cout << "fi1 - fi2 = " << fi1 - fi2 << '\n'; // fi1 - fi2 = 0
    cout << "fi1 * fi2 = " << fi1 * fi2 << '\n'; // fi1 * fi2 = 4/3
    cout << "fi1 / fi2 = " << fi1 / fi2 << '\n'; // fi1 / fi2 = 3
    cout << "fi1 % fi2 = " << fi1 % fi2 << '\n'; // fi1 % fi2 = -2/7

    // Componedo and Dividendo operations:
    cout << "++fi1 = " << ++fi1 << '\n'; // ++fi1 = 5/7
    cout << "--fi2 = " << --fi2 << '\n'; // --fi2 = -7/5

    // Relation Operators:
    cout << "fi1 > fi2 = " << ((fi1 > fi2) ? "true\n" : "false\n"); // fi1 > fi2 = false
    cout << "fi1 == fi2 = " << ((fi1 == fi2) ? "true\n" : "false\n"); // fi1 == fi2 = false
}

void Test2()
{
    cout<<"\n:::Test 2: Polynomial and Int:::\n"; // :::Test 2: Polynomial and Int:::

    PolyInt pi1, pi2;
    cin >> pi1; // Pass the input: 2 -9 12 3
    cin >> pi2; // Pass the input: 4 -2 11 8 -7 -23

    // Output Operator:
    cout << "PolyInt pi1 = " << pi1 << '\n'; // PolyInt pi1 = 3x^3 - 4x^2 + 7x + 2
    cout << "PolyInt pi2 = " << pi2 << '\n'; // PolyInt pi2 = -7x^5 - 7x^4 - -8x^3 - 5x^2 - 2x + 4

    // Binary Arithmetic:
    cout << "pi1 + pi2 = " << pi1 + pi2 << '\n'; // pi1 + pi2 = -7x^5 - 7x^4 - 5x^3 + 7x^2 + 5x + 6
    cout << "pi1 - pi2 = " << pi1 - pi2 << '\n'; // pi1 - pi2 = 7x^5 + 7x^4 - 5x^3 + 1x^2 - 7x - 2

    // Evaluate:
    cout<< "Evaluate pi2 at (x = 3) = " << pi2(3) << '\n'; // Evaluate pi2 at (x = 3) = -3
}

void Test3()
{
    cout<<"\n:::Test 3: Polynomial and Fraction and Int:::\n"; // :::Test 3: Polynomial and Fraction and Int:::

    PolyFracInt pfi1, pfi2;
    cin >> pfi1; // Pass the input: 2 8 -11 4 17 2 -9
    cin >> pfi2; // Pass the input: 3 6 -2 1 8 -4 -2 0 4

    // Output Operator:
    cout << "PolyFracInt pfi1(2) = " << pfi1 << endl; // PolyFracInt pfi1(2) = 7x^6 + 2x^5 + 1x^4 + 4x^3 + 5x^2 - -8x + 2
    cout << "PolyFracInt pfi2(3) = " << pfi2 << endl; // PolyFracInt pfi2(3) = 4x^8 - 2x^6 - 4x^5 - -8x^4 + 1x^3 - 2x^2 + 6x + 3

    // Binary Arithmetic:
    cout << "pfi1 + pfi2 = " << pfi1 + pfi2 << endl; // pfi1 + pfi2 = 4x^8 + 5x^6 - 2x^5 - 7x^4 + 5x^3 + 3x^2 - 2x + 5

    // Evaluate at a value:
    cout << "Evaluate pfi2 at (x = 2) = " << pfi2(FracInt(2)) << endl; // Evaluate pfi2 at (x = 2) = -1
}

int main()
{
    Test1();
    Test2();
    Test3();
    return 0;
}