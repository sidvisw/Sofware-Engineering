#include <iostream>
using namespace std;
#include "Fraction.h"

typedef Fraction<int> fraction;

void PassTest()
{
	cout << ":::PASS TESTS:::" << endl
		 << endl; // :::PASS TESTS:::
	fraction fa(5, 3);
	cout << "fraction fa(5, 3) = " << fa << endl; // fraction fa(5, 3) = 5/3
	fraction fb(7, 9);
	cout << "fraction fb(7, 9) = " << fb << endl; // fraction fb(7, 9) = 7/9
	cout << "fa + fb = " << (fa + fb) << endl;	  // fa + fb = 22/9
}
void FailTest()
{
	cout << ":::FAIL TESTS:::" << endl
		 << endl; // :::FAIL TESTS:::
	try
	{
		cout << "fraction(1, 0): ";
		fraction f1(1, 0);
	}
	catch (const char *s)
	{
		cout << s << endl;
	} // fraction(1, 0): fraction w/ Denominator 0 is undefined
	fraction f1(5, 12), f2(0, 1), f3;
	try
	{
		cout << "Binary Divide: f3 = " << f1 << " / " << f2 << ": ";
		f3 = f1 / f2;
		cout << f3 << endl;
	}
	catch (const char *s)
	{
		cout << s << endl;
	} // Binary Divide: f3 = 5/12 / 0: Divide by 0 is undefined
}
void MixedTest()
{
	cout << ":::MIXED TESTS:::" << endl
		 << endl; // :::MIXED TESTS:::
	fraction f1(2, 3), f2(8), f3(5, 6), f4;
	cout << "f1 = " << f1 << " f2 = " << f2 << " f3 = " << f3 << " f4 = " << f4 << endl;
	// f1 = 2/3 f2 = 8 f3 = 5/6 f4 = 1
	f4 = (f1 + f2) / (f1 - f2) + !f3 - f2 * f3;
	cout << "f4 = (f1 + f2) / (f1 - f2) + !f3 - f2 * f3 = " << f4 << endl;
	// f4 = (f1 + f2) / (f1 - f2) + !f3 - f2 * f3 = -1097/165
}
int main()
{
	PassTest();
	FailTest();
	MixedTest();
	return 0;
}