#ifndef FRACTION_H
#define FRACTION_H
#include <string>
using namespace std;

// Function for finding floor of a number
// Parameter: Number to be floored
// Return: Floor of the number
template <class T=int>
T floor(T a)
{
	if(a>=T(0))
		return a;
	else
		return a-1;
}

// Function for finding absolute value of a number
// Parameter: Number to be found absolute value
// Return: Absolute value of the number
template <class T=int>
T abs(T a)
{
	if(a>=T(0))
		return a;
	else
		return -a;
}

// Function to find the greatest common divisor of two numbers
// Parameters: two numbers
// Returns: greatest common divisor of the two numbers
template <class T=int>
T GCD(T a, T b)
{
	T c;
	while (b != T(0))
	{
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

// Function to find the least common multiple of two numbers
// Parameters: two numbers
// Returns: least common multiple of the two numbers
template <class T=int>
T LCM(T a, T b)
{
	return (a * b) / GCD(a, b);
}

template <typename T = int>
class Fraction
{		  // Implicit assertion for proper fraction: gcd(|n_|, d_) = 1
	T n_; // numerator
	T d_; // denominator

public:
	// Constructors
	Fraction(T n, T d) : n_(n), d_(d)
	{
		if (d_ == 0)
		{
			throw "fraction w/ Denominator 0 is undefined";
		}
		T g = GCD(abs(n_), d_);
		n_ /= g;
		d_ /= g;
	}
	Fraction(T n) : n_(n), d_(1) {}
	Fraction() : n_(0), d_(1) {}

	// Copy constructor
	Fraction(const Fraction &f) : n_(f.n_), d_(f.d_) {}

	// Destructor
	~Fraction() {}

	// Unary operators

	// Function to preseve(sign) the fraction
	// Parameters: none
	// Returns: Preseved(sign) fraction
	Fraction operator+() const
	{
		return Fraction<T>(n_, d_);
	}

	// Function to negate the fraction
	// Parameters: none
	// Returns: Negated fraction
	Fraction operator-() const
	{
		return Fraction<T>(-n_, d_);
	}

	// Function to find the componendo of the fraction
	// Parameters: none
	// Returns: Componendo of the fraction
	Fraction operator++()
	{
		n_ += d_;
		return *this;
	}

	// Function to find the dividendo of the fraction
	// Parameters: none
	// Returns: Dividendo of the fraction
	Fraction operator--()
	{
		n_ -= d_;
		return *this;
	}

	// Function to find the reciprocal of the fraction
	// Parameters: none
	// Returns: Reciprocal of the fraction
	Fraction operator!() const
	{
		if (n_ == 0)
		{
			throw "fraction w/ Numerator 0 cannot be reciprocated";
		}
		return Fraction<T>(d_, n_);
	}

	// Binary operators

	// Function to add two fractions
	// Parameters: Fraction to be added
	// Returns: Sum of the two fractions
	Fraction operator+(const Fraction &f) const
	{
		return Fraction<T>(n_ * (LCM(d_, f.d_) / d_) + f.n_ * (LCM(d_, f.d_) / f.d_), LCM(d_, f.d_));
	}
	friend Fraction operator+(const Fraction &f,const T &n)
	{
		return Fraction<T>(f.n_ + n * (f.d_), f.d_);
	}
	friend Fraction operator+(const T &n,const Fraction &f)
	{
		return Fraction<T>(f.n_ + n * (f.d_), f.d_);
	}

	// Function to subtract two fractions
	// Parameters: Fraction to be subtracted
	// Returns: Difference of the two fractions
	Fraction operator-(const Fraction &f) const
	{
		return Fraction<T>(*this + (-f));
	}
	friend Fraction operator-(const Fraction &f,const T &n)
	{
		return Fraction<T>(f.n_ - n * (f.d_), f.d_);
	}
	friend Fraction operator-(const T &n,const Fraction &f)
	{
		return Fraction<T>(n * (f.d_) - f.n_, f.d_);
	}

	// Function to multiply two fractions
	// Parameters: Fraction to be multiplied
	// Returns: Product of the two fractions
	Fraction operator*(const Fraction &f) const
	{
		return Fraction<T>(n_ * f.n_, d_ * f.d_);
	}
	friend Fraction operator*(const Fraction &f,const T &n)
	{
		return Fraction<T>(f.n_ * n, f.d_);
	}
	friend Fraction operator*(const T &n,const Fraction &f)
	{
		return Fraction<T>(f.n_ * n, f.d_);
	}

	// Function to divide two fractions
	// Parameters: Fraction to be divided
	// Returns: Quotient of the two fractions
	Fraction operator/(const Fraction &f) const
	{
		if (f.n_ == 0)
		{
			throw "Divide by 0 is undefined";
		}
		return Fraction<T>(n_ * f.d_, d_ * f.n_);
	}
	friend Fraction operator/(const Fraction &f,const T &n)
	{
		if (n == 0)
		{
			throw "Divide by 0 is undefined";
		}
		return Fraction<T>(f.n_, f.d_ * n);
	}
	friend Fraction operator/(const T &n,const Fraction &f)
	{
		if (f.n_ == 0)
		{
			throw "Divide by 0 is undefined";
		}
		return Fraction<T>(n * f.d_, f.n_);
	}

	// Function to modulo two fractions
	// Parameters: Fraction to be modulo
	// Returns: Modulo of the two fractions
	Fraction operator%(const Fraction &f) const
	{
		if (f.n_ == 0)
		{
			throw "Divide by 0 is undefined";
		}
		return Fraction<T>(*this - floor(n_ * f.d_/ d_ * f.n_) * f);
	}
	friend Fraction operator%(const Fraction &f,const T &n)
	{
		if (n == 0)
		{
			throw "Divide by 0 is undefined";
		}
		return Fraction<T>(f%Fraction<T>(n));
	}
	friend Fraction operator%(const T &n,const Fraction &f)
	{
		if (f.n_ == 0)
		{
			throw "Divide by 0 is undefined";
		}
		return Fraction<T>(Fraction<T>(n)%f);
	}

	// Assignment operators

	// Function to assign a fraction to another fraction
	// Parameters: Fraction to be assigned
	// Returns: Assigned fraction
	Fraction &operator=(const Fraction &f)
	{
		n_ = f.n_;
		d_ = f.d_;
		return *this;
	}

	// Function to add a fraction to another fraction and assign it to the first fraction
	// Parameters: Fraction to be added
	// Returns: Assigned fraction
	Fraction &operator+=(const Fraction &f)
	{
		*this = *this + f;
		return *this;
	}

	// Function to subtract a fraction from another fraction and assign it to the first fraction
	// Parameters: Fraction to be subtracted
	// Returns: Assigned fraction
	Fraction &operator-=(const Fraction &f)
	{
		*this = *this - f;
		return *this;
	}

	// Function to multiply a fraction with another fraction and assign it to the first fraction
	// Parameters: Fraction to be multiplied
	// Returns: Assigned fraction
	Fraction &operator*=(const Fraction &f)
	{
		*this = *this * f;
		return *this;
	}

	// Function to divide a fraction by another fraction and assign it to the first fraction
	// Parameters: Fraction to be divided
	// Returns: Assigned fraction
	Fraction &operator/=(const Fraction &f)
	{
		*this = *this / f;
		return *this;
	}

	// Function to modulo a fraction by another fraction and assign it to the first fraction
	// Parameters: Fraction to be modulo
	// Returns: Assigned fraction
	Fraction &operator%=(const Fraction &f)
	{
		*this = *this % f;
		return *this;
	}

	// Relational operators

	// Function to check if one fraction is less than another
	// Parameters: Fraction to be compared
	// Returns: True if the first fraction is less than the second, false otherwise
	bool operator<(const Fraction &f) const
	{
		return n_ * f.d_ < d_ * f.n_;
	}

	// Function to check if one fraction is less than or equal to another
	// Parameters: Fraction to be compared
	// Returns: True if the first fraction is less than or equal to the second, false otherwise
	bool operator<=(const Fraction &f) const
	{
		return n_ * f.d_ <= d_ * f.n_;
	}

	// Function to check if one fraction is greater than another
	// Parameters: Fraction to be compared
	// Returns: True if the first fraction is greater than the second, false otherwise
	bool operator>(const Fraction &f) const
	{
		return n_ * f.d_ > d_ * f.n_;
	}

	// Function to check if one fraction is greater than or equal to another
	// Parameters: Fraction to be compared
	// Returns: True if the first fraction is greater than or equal to the second, false otherwise
	bool operator>=(const Fraction &f) const
	{
		return n_ * f.d_ >= d_ * f.n_;
	}

	// Function to check if one fraction is equal to another
	// Parameters: Fraction to be compared
	// Returns: True if the first fraction is equal to the second, false otherwise
	bool operator==(const Fraction &f) const
	{
		return n_ * f.d_ == d_ * f.n_;
	}

	// Function to check if one fraction is not equal to another
	// Parameters: Fraction to be compared
	// Returns: True if the first fraction is not equal to the second, false otherwise
	bool operator!=(const Fraction &f) const
	{
		return n_ * f.d_ != d_ * f.n_;
	}

	// IO operators

	// Parameter: output stream, fraction to be output
	// Return: reference to the output stream
	template <class U>
	friend ostream &operator<<(std::ostream &os, const Fraction<U> &f)
	{
		if(f.d_ == 1)
		{
			os << f.n_;
		}
		else
		{
			os << f.n_ << "/" << f.d_;
		}
		return os;
	}

	// Parameter: input stream, fraction to be input
	// Return: reference to the input stream
	template <class U>
	friend istream &operator>>(std::istream &is, Fraction<U> &f)
	{
		string s;
		is >> s;
		if(s.find('/') != string::npos)
		{
			f.n_ = atoi(s.substr(0, s.find('/')).c_str());
			f.d_ = atoi(s.substr(s.find('/') + 1, s.length() - s.find('/') - 1).c_str());
		}
		else
		{
			f.n_ = atoi(s.c_str());
			f.d_ = 1;
		}
		return is;
	}
}; // T is an integral type like int, char, short, long, etc.

#endif