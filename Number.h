#pragma once
#include <vector>
#include "Digit.h"
#include <string>

class Number;

// Pointer to operations(+ - * /) in Number class
typedef  Number(Number::* OperationPtr)(const Number& other) const;

class Number
{
	bool m_sign;
	// vector of digits in number, from lower rank to bigger
	std::vector<Digit> m_vec;
	
	// I don't think about sign in this function
	void incrementNum(); 

	// I don't think about sign in this function
	void decrementNum(); 
public:
	// default number is 'zero'
	Number();

	// Construct using string (from higher rank to lower)
	Number(std::string str);
	Number(const std::vector<Digit>& vec, bool sign);

	// Construct num out of one digit
	Number(const Element& el, bool sign);

	// Construct using equivalent integer
	Number(const int& i);

	// Del useless dights (Zeros at the begining of Number Ex.: 000065 -> 65)
	void DelUselessBeginZeros();

	// Check that string can be a number (return true), if false
	// throw some exeptions
	static bool validateStr(std::string str);

	int toInt() const;

	void invertSign();

	// Sign of Both num have to be the same
	Number sum_withSameSign(const Number& other) const;
	Number sub_withSameSign(const Number& other) const;

	void shiftRight();
	
	Number operator+(const Number& other) const;
	Number operator-(const Number& other) const;
	Number operator*(const Number& other) const;
	Number div(const Number& other, Number& divRemainder, int* iterationCount = nullptr) const;

	void operator++();
	void operator--();

	bool isZero() const;

	// Sign does not count in these compare functions
	bool operator==(const Number& other) const;
	bool operator!=(const Number& other) const;
	bool operator>(const Number& other) const;
	bool operator<(const Number& other) const;
	

	friend std::ostream& operator<<(std::ostream& os, const Number& n);
};

std::ostream& operator<<(std::ostream& os, const Number& n);
