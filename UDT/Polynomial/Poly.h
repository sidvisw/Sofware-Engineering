#ifndef POLY_H
#define POLY_H
#include <vector>
#include <cmath>
using namespace std;

// Function for finding a^b
// Parameters: a, b
// Returns: a^b
template<typename T = int>
T pow(T a,size_t b)
{
	if(b==0)
		return T(1);
	else if(b==1)
		return a;
	T num=a*a;
	if(b%2==0)
		return pow(num,b/2);
	else
		return a*pow(num,(b-1)/2);
}

template <typename T = int> // Type of Coefficients and value
class Poly
{					  // a polynomial of type T
	vector<T> coeff_; // coefficients
	size_t deg_;	  // deg_ = coeff_.size()-1
public:
	// Constructors

	// Default constructor
	Poly() : coeff_({T(0)}), deg_(0) {}

	// Single coefficient constructor
	Poly(T c) : coeff_({c}), deg_(0) {}

	// Constructor from vector of coefficients
	Poly(const vector<T> &coeff) : coeff_(coeff), deg_(coeff.size() - 1)
	{
		if (coeff.size() == 0)
		{
			throw "Empty vector of coefficients given to create Polynomial";
		}
		// Remove trailing zeros
		while (deg_ > 0 && coeff_[deg_] == T(0))
		{
			coeff_.pop_back();
			deg_--;
		}
	}

	// Copy constructor
	Poly(const Poly &p) : coeff_(p.coeff_), deg_(p.deg_) {}

	// Destructor
	~Poly() {}

	// Unary operations

	// Function for preserving(sign) a polynomial
	// Parameter: None
	// Return: Preserve(sign) of the current polynomial
	Poly operator+() const
	{
		return Poly(coeff_);
	}

	// Function for negating a polynomial
	// Parameter: None
	// Return: Negated polynomial
	Poly operator-() const
	{
		vector<T> temp;
		for (size_t i = 0; i <= deg_; i++)
		{
			temp.push_back(-coeff_[i]);
		}
		return Poly(temp);
	}

	// Binary operations

	// Function for adding two polynomials
	// Parameter: Polynomial p to be added
	// Return: Sum of the current polynomial and p
	Poly operator+(const Poly &p) const
	{
		vector<T> temp1 = coeff_;
		vector<T> temp2 = p.coeff_;
		if (deg_ > p.deg_)
		{
			for (size_t i = p.deg_ + 1; i <= deg_; i++)
			{
				temp2.push_back(T(0));
			}
		}
		else
		{
			for (size_t i = deg_ + 1; i <= p.deg_; i++)
			{
				temp1.push_back(T(0));
			}
		}
		for (size_t i = 0; i <= max(deg_, p.deg_); i++)
		{
			temp1[i] += temp2[i];
		}
		// Remove trailing zeros
		while (temp1.size() > 0 && temp1[temp1.size() - 1] == T(0))
		{
			temp1.pop_back();
		}
		return Poly(temp1);
	}

	// Function for subtracting two polynomials
	// Parameter: Polynomial p to be subtracted
	// Return: Difference of the current polynomial and p
	Poly operator-(const Poly &p) const
	{
		return *this + (-p);
	}

	// Arithmetic operations

	// Function for assigning a polynomial to the current polynomial
	// Parameter: Polynomial p to be assigned
	// Return: Current polynomial
	Poly &operator=(const Poly &p)
	{
		coeff_ = p.coeff_;
		deg_ = p.deg_;
		return *this;
	}

	// Function for adding a polynomial to the current polynomial and assigning the result to the current polynomial
	// Parameter: Polynomial p to be added
	// Return: Current polynomial
	Poly &operator+=(const Poly &p)
	{
		*this = *this + p;
		return *this;
	}

	// Function for subtracting a polynomial from the current polynomial and assigning the result to the current polynomial
	// Parameter: Polynomial p to be subtracted
	// Return: Current polynomial
	Poly &operator-=(const Poly &p)
	{
		*this = *this - p;
		return *this;
	}

	// Evaluation Operation
	// Function for evaluating a polynomial at a value
	// Parameter: Value at which the polynomial is to be evaluated
	// Return: Value of the polynomial at the given value
	T operator()(T x) const
	{
		T y = T(0);
		for (size_t i = 0; i <= deg_; i++)
		{
			y += coeff_[i] * pow(x, i);
		}
		return y;
	}

	// IO Operations

	// Function for printing a polynomial
	// Parameter: An ostream object, and the polynomial to be printed
	// Return: The ostream object
	friend ostream &operator<<(ostream &os, const Poly &p)
	{
		if (p.deg_ == 0)
		{
			os << p.coeff_[0];
		}
		else
		{
			if (p.deg_ > 1)
			{
				os << p.coeff_[p.deg_] << "x^" << p.deg_;
			}
			for (size_t i = p.deg_ - 1; i > 1; i--)
			{
				if (p.coeff_[i] != T(0))
				{
					if (p.coeff_[i] >= T(0))
					{
						os << " + " << p.coeff_[i] << "x^" << i;
					}
					else
					{
						os << " - " << -p.coeff_[i] << "x^" << i;
					}
				}
			}
			if (p.coeff_[1] != T(0))
			{
				if (p.deg_ == 1)
				{
					os << p.coeff_[1] << "x";
				}
				else if (p.coeff_[1] >= T(0))
				{
					os << " + " << p.coeff_[1] << "x";
				}
				else
				{
					os << " - " << -p.coeff_[1] << "x";
				}
			}
			if (p.coeff_[0] != T(0))
			{
				if (p.deg_ == 0)
				{
					os << p.coeff_[0];
				}
				else if (p.coeff_[0] >= T(0))
				{
					os << " + " << p.coeff_[0];
				}
				else
				{
					os << " - " << -p.coeff_[0];
				}
			}
		}
		return os;
	}

	// Function for reading a polynomial
	// Parameter: An istream object, and the polynomial to be read
	// Return: The istream object
	friend istream &operator>>(istream &is, Poly &p)
	{
		vector<T> coeff;
		string s;
		getline(is, s);
		T num=T(0);
		size_t i=0;
		while(i<s.length()){
			if(s[i]=='-'){
				num=T(0);
				i++;
				while(s[i]!=' '&&i<s.length()){
					num=num*T(10)+T(s[i]-'0');
					i++;
				}
				coeff.push_back(-num);
				i++;
			}
			else{
				num=T(0);
				while(s[i]!=' '&&i<s.length()){
					num=num*T(10)+T(s[i]-'0');
					i++;
				}
				coeff.push_back(num);
				i++;
			}
		}
		p=Poly(coeff);
		return is;
	}
};

#endif