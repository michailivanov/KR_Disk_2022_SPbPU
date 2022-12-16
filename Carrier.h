#pragma once
#include "Constants.h"
#include "Element.h"
#include "Tables.h"
class Carrier
{
	std::vector<Element> m_vec;
	Tables m_tables;
public:
	Carrier(const std::vector<char>& s);
	Element One() const;
	Element Zero() const;
	Element Max() const;
	Element operator[](const int& id) const;
	Element operator[](const char& c) const;
	int size() const;
	Tables getTables() const;

	bool isThere(const char& c) const;

	friend std::ostream& operator<<(std::ostream& out, const Carrier& s);
};

std::ostream& operator<<(std::ostream& out, const Carrier& s);