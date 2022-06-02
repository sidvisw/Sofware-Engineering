#ifndef INT_H
#define INT_H
using namespace std;

template <typename T = int, unsigned int N = 4>
class Int_
{		  // an N-bits integer class with underlying type T
	T v_; // actual value in underlying type T
public:
	static const Int_<T, N> MaxInt; // maximum value of Int_
	static const Int_<T, N> MinInt; // minimum value of Int_

	// Constructors

	// Default constructor
	Int_() : v_(0)
	{
		if (N == 0)
		{
			throw "N cannot be 0";
		}
		if (N > sizeof(T) * 8)
		{
			throw "N cannot be greater than sizeof(T)*8";
		}
	}

	// Constructor from underlying type T
	Int_(T v) : v_(v)
	{
		if (N == 0)
		{
			throw "N cannot be 0";
		}
		if (N > sizeof(T) * 8)
		{
			throw "N cannot be greater than sizeof(T)*8";
		}
		if (v_ > MaxInt.v_)
		{
			v_ = MinInt.v_ + v_ - MaxInt.v_ - 1;
		}
		if (v_ < MinInt.v_)
		{
			v_ = MaxInt.v_ + v_ - MinInt.v_ + 1;
		}
	}

	// Copy constructor
	Int_(const Int_<T, N> &i) : v_(i.v_) {}

	// Destructor
	~Int_() {}

	// Unary operations

	// Function for preserve(sign)
	// Parameter: None
	// Return: Preserve(sign) of the current Int_
	Int_<T, N> operator+() const
	{
		return Int_<T, N>(this->v_);
	}

	// Function for Negation
	// Parameters: None
	// Returns: A new Int_ with the negated value of the current Int_
	Int_<T, N> operator-() const
	{
		Int_<T, N> temp;
		if (v_ == MinInt.v_)
			temp.v_ = MinInt.v_;
		else
			temp.v_ = -v_;
		return temp;
	}

	// Function for postfix increment
	// Parameters: None
	// Returns: A new Int_ with the incremented value of the current Int_
	Int_<T, N> operator++(int)
	{
		Int_<T, N> temp;
		temp.v_ = v_;
		if (v_ == MaxInt.v_)
			v_ = MinInt.v_;
		else
			v_++;
		return temp;
	}

	// Function for prefix increment
	// Parameters: None
	// Returns: A new Int_ with the incremented value of the current Int_
	Int_<T, N> &operator++()
	{
		if (v_ == MaxInt.v_)
			v_ = MinInt.v_;
		else
			v_++;
		return *this;
	}

	// Binary operations

	// Function for Addition
	// Parameters: An Int_ to be added to the current Int_
	// Returns: A new Int_ with the sum of the current Int_ and the parameter
	Int_<T, N> operator+(const Int_<T, N> &i) const
	{
		Int_<T, N> temp;
		temp.v_ = v_ + i.v_;
		while (temp.v_ > MaxInt.v_)
		{
			temp.v_ = MinInt.v_ + temp.v_ - MaxInt.v_ - 1;
		}
		while (temp.v_ < MinInt.v_)
		{
			temp.v_ = MaxInt.v_ + temp.v_ - MinInt.v_ + 1;
		}
		return temp;
	}

	// Function for Subtraction
	// Parameters: An Int_ to be subtracted from the current Int_
	// Returns: A new Int_ with the difference of the current Int_ and the parameter
	Int_<T, N> operator-(const Int_<T, N> &i) const
	{
		Int_<T, N> temp;
		temp = *this + (-i);
		return temp;
	}

	// Function for Multiplication
	// Parameters: An Int_ to be multiplied with the current Int_
	// Returns: A new Int_ with the product of the current Int_ and the parameter
	Int_<T, N> operator*(const Int_<T, N> &i) const
	{
		Int_<T, N> temp;
		temp.v_ = v_ * i.v_;
		while (temp.v_ > MaxInt.v_)
		{
			temp.v_ = MinInt.v_ + temp.v_ - MaxInt.v_ - 1;
		}
		while (temp.v_ < MinInt.v_)
		{
			temp.v_ = MaxInt.v_ + temp.v_ - MinInt.v_ + 1;
		}
		return temp;
	}

	// Function for Division
	// Parameters: An Int_ to be divided by the current Int_
	// Returns: A new Int_ with the quotient of the current Int_ and the parameter
	Int_<T, N> operator/(const Int_<T, N> &i) const
	{
		if(i.v_ == 0)
			throw "Divide by 0 is undefined";
		Int_<T, N> temp;
		temp.v_ = v_ / i.v_;
		while (temp.v_ > MaxInt.v_)
		{
			temp.v_ = MinInt.v_ + temp.v_ - MaxInt.v_ - 1;
		}
		while (temp.v_ < MinInt.v_)
		{
			temp.v_ = MaxInt.v_ + temp.v_ - MinInt.v_ + 1;
		}
		return temp;
	}

	// Function for Modulus
	// Parameters: An Int_ to be modulus by the current Int_
	// Returns: A new Int_ with the modulus of the current Int_ and the parameter
	Int_<T, N> operator%(const Int_<T, N> &i) const
	{
		Int_<T, N> temp;
		temp.v_ = v_ % i.v_;
		while (temp.v_ > MaxInt.v_)
		{
			temp.v_ = MinInt.v_ + temp.v_ - MaxInt.v_ - 1;
		}
		while (temp.v_ < MinInt.v_)
		{
			temp.v_ = MaxInt.v_ + temp.v_ - MinInt.v_ + 1;
		}
		return temp;
	}

	// Assignment operator

	// Function for Assignment
	// Parameters: An Int_ to be assigned to the current Int_
	// Returns: A new Int_ with the assigned value of the parameter
	Int_<T, N> &operator=(const Int_<T, N> &i)
	{
		v_ = i.v_;
		return *this;
	}

	// Function for Addition Assignment
	// Parameters: An Int_ to be added to the current Int_
	// Returns: A new Int_ with the sum of the current Int_ and the parameter
	Int_<T, N> &operator+=(const Int_<T, N> &i)
	{
		*this=*this+i;
		return *this;
	}

	// Function for Subtraction Assignment
	// Parameters: An Int_ to be subtracted from the current Int_
	// Returns: A new Int_ with the difference of the current Int_ and the parameter
	Int_<T, N> &operator-=(const Int_<T, N> &i)
	{
		*this=*this-i;
		return *this;
	}

	// Function for Multiplication Assignment
	// Parameters: An Int_ to be multiplied with the current Int_
	// Returns: A new Int_ with the product of the current Int_ and the parameter
	Int_<T, N> &operator*=(const Int_<T, N> &i)
	{
		*this=*this*i;
		return *this;
	}

	// Function for Division Assignment
	// Parameters: An Int_ to be divided by the current Int_
	// Returns: A new Int_ with the quotient of the current Int_ and the parameter
	Int_<T, N> &operator/=(const Int_<T, N> &i)
	{
		*this=*this/i;
		return *this;
	}

	// Function for Modulus Assignment
	// Parameters: An Int_ to be modulus by the current Int_
	// Returns: A new Int_ with the modulus of the current Int_ and the parameter
	Int_<T, N> &operator%=(const Int_<T, N> &i)
	{
		*this=*this%i;
		return *this;
	}

	// Relational operators

	// Function for Less Than
	// Parameters: An Int_ to be compared with the current Int_
	// Returns: A boolean value indicating whether the current Int_ is less than the parameter
	bool operator<(const Int_<T, N> &i) const
	{
		return v_ < i.v_;
	}

	// Function for Less Than or Equal
	// Parameters: An Int_ to be compared with the current Int_
	// Returns: A boolean value indicating whether the current Int_ is less than or equal to the parameter
	bool operator<=(const Int_<T, N> &i) const
	{
		return v_ <= i.v_;
	}

	// Function for Greater Than
	// Parameters: An Int_ to be compared with the current Int_
	// Returns: A boolean value indicating whether the current Int_ is greater than the parameter
	bool operator>(const Int_<T, N> &i) const
	{
		return v_ > i.v_;
	}

	// Function for Greater Than or Equal
	// Parameters: An Int_ to be compared with the current Int_
	// Returns: A boolean value indicating whether the current Int_ is greater than or equal to the parameter
	bool operator>=(const Int_<T, N> &i) const
	{
		return v_ >= i.v_;
	}

	// Function for Equality
	// Parameters: An Int_ to be compared with the current Int_
	// Returns: A boolean value indicating whether the current Int_ is equal to the parameter
	bool operator==(const Int_<T, N> &i) const
	{
		return v_ == i.v_;
	}

	// Function for Inequality
	// Parameters: An Int_ to be compared with the current Int_
	// Returns: A boolean value indicating whether the current Int_ is not equal to the parameter
	bool operator!=(const Int_<T, N> &i) const
	{
		return v_ != i.v_;
	}

	// IO operators

	// Function for Output
	// Parameters: An ostream to be used for output, and an Int_ to be output
	// Returns: An ostream with the current Int_
	friend ostream &operator<<(std::ostream &os, const Int_<T, N> &i)
	{
		os << i.v_;
		return os;
	}

	// Function for Input
	// Parameters: An istream to be used for input, and an Int_ to be input
	// Returns: An istream with the current Int_
	friend istream &operator>>(std::istream &is, Int_<T, N> &i)
	{
		is >> i.v_;
		return is;
	}
};

template <typename T, unsigned int N>
const Int_<T, N> Int_<T, N>::MaxInt = Int_<T, N>((1 << (N - 1)) - 1);

template <typename T, unsigned int N>
const Int_<T, N> Int_<T, N>::MinInt = Int_<T, N>(-(1 << (N - 1)));

#endif