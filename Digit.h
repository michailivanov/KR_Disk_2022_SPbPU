#pragma once
#include "CarrierConstant.h"
#include <iostream>
#include "Element.h"

class Digit
{
	Element m_el;
public:
	int getID() const;
	Digit(const Element&);
	Digit(const char&);
	Digit(const int&);

	char toChar() const;

	Digit operator=(const Digit& other);
	Digit operator+(const Digit& other) const;
	Digit operator-(const Digit& other) const;
	Digit operator*(const Digit& other) const;
	Digit operator/(const Digit& other) const;

	void operator+=(const Digit& other);

	//sum two vals and if there is a carry save it in carry_buffer
	Digit sum(const Digit other, Digit& carry_buffer) const;

	//sub two vals and if there is a carry (this carry is negative) save it in carry_buffer
	Digit sub(const Digit other, Digit& carry_buffer) const;

	//mul two vals and if there is a carry save it in carry_buffer
	Digit mul(const Digit other, Digit& carry_buffer) const;

	//mul two vals and if there is a carry (this carry is negative) save it in carry_buffer
	Digit div(const Digit other, Digit& carry_buffer) const;

	bool operator==(const Digit& other) const;
	bool operator!=(const Digit& other) const;
	bool operator>(const Digit& other) const;
	bool operator<(const Digit& other) const;
	void operator++();
	void operator--();
	Digit operator++(int notUSED);
	Digit operator--(int notUSED);

	friend std::ostream& operator<<(std::ostream& os, const Digit& d);
};
std::ostream& operator<<(std::ostream& os, const Digit& d);


