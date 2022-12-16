#include "Digit.h"

//Digit::Digit(const char& c) : m_c(c)
//{
//}

int Digit::getID() const
{
	return m_el.getID();
}

Digit::Digit(const Element& el) : m_el(el)
{
}

Digit::Digit(const char& c) : m_el(CARRIER[c])
{
}

Digit::Digit(const int& i) : m_el(CARRIER[i])
{
}

char Digit::toChar() const
{
	return m_el.getChar();
}

Digit Digit::operator+(const Digit& other) const
{
	return CARRIER.getTables().sum(this->m_el, other.m_el);
}

Digit Digit::operator-(const Digit& other) const
{
	return CARRIER.getTables().reverse_sum(this->m_el, other.m_el);
}

Digit Digit::operator*(const Digit& other) const
{
	return CARRIER.getTables().mul(this->m_el, other.m_el);
}

Digit Digit::operator/(const Digit& other) const
{
	return CARRIER.getTables().reverse_mul(this->m_el, other.m_el);
}

void Digit::operator+=(const Digit& other)
{
	*this = *this + other;
}

Digit Digit::sum(const Digit other, Digit& carry_buffer) const
{
	carry_buffer = CARRIER.getTables().carry_sum(this->m_el, other.m_el);
	return *this + other;
}

Digit Digit::sub(const Digit other, Digit& carry_buffer) const
{
	carry_buffer = CARRIER.getTables().carry_sum((*this - other).m_el, other.m_el);
	return *this - other;
}

Digit Digit::mul(const Digit other, Digit& carry_buffer) const
{
	carry_buffer = CARRIER.getTables().carry_mul(this->m_el, other.m_el);
	return (*this) * (other);
}

Digit Digit::div(const Digit other, Digit& carry_buffer) const
{
	carry_buffer = CARRIER.getTables().carry_mul((*this / other).m_el, other.m_el);
	return *this / other;
}

void Digit::operator++()
{
	int id = m_el.getID() + 1;
	if (id == CARRIER.size())
	{
		id = 0;
	}
	m_el = CARRIER[id];
}

void Digit::operator--()
{
	int id = m_el.getID() - 1;
	if (id == -1)
	{
		id = CARRIER.size() - 1;
	}
	m_el = CARRIER[id];
}



Digit Digit::operator=(const Digit& other)
{
	m_el = other.m_el;
	return *this;
}

bool Digit::operator==(const Digit& other) const
{
	if (m_el == other.m_el)
		return true;
	return false;
}

bool Digit::operator!=(const Digit& other) const
{
	if (m_el == other.m_el)
		return false;
	return true;
}

bool Digit::operator>(const Digit& other) const
{
	return (m_el.getID() - other.m_el.getID()) > 0;;
}

bool Digit::operator<(const Digit& other) const
{
	return (m_el.getID() - other.m_el.getID()) < 0;;
}

Digit Digit::operator++(int notUSED)
{
	operator++();
	return *this;
}

Digit Digit::operator--(int notUSED)
{
	operator--();
	return *this;
}



std::ostream& operator<<(std::ostream& os, const Digit& d)
{
	os << d.m_el.getChar();
	return os;
}