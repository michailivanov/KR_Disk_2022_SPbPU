#pragma once
#include <iostream>
#include "Constants.h"
class Element
{
	char m_c;
	int m_id;
public:
	Element(const char& c, const int& id);
	char getChar() const;
	int getID() const;
	Element operator=(const Element& other);
	bool operator==(const Element& other) const;
	friend std::ostream& operator<<(std::ostream& out, const Element& el);
};
std::ostream& operator<<(std::ostream& out, const Element& el);
