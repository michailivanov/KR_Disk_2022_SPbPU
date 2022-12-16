#include "Element.h"

Element::Element(const char& c, const int& id) : m_c(c), m_id(id)
{
}

char Element::getChar() const
{
	return m_c;
}

int Element::getID() const
{
	return m_id;
}

Element Element::operator=(const Element& other)
{
	m_c = other.m_c;
	m_id = other.m_id;
	return *this;
}

bool Element::operator==(const Element& other) const
{
	return m_c == other.m_c && m_id == other.m_id;
}



std::ostream& operator<<(std::ostream& out, const Element& el)
{
	out << el.m_c;
	return out;
}