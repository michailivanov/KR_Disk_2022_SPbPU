#include "Carrier.h"

Carrier::Carrier(const std::vector<char>& s) : m_tables(s)
{
	m_vec.reserve(s.size());
	int i = 0;
	for (const char& c : s)
	{
		m_vec.push_back(Element(c, i));
		++i;
	}
}

Element Carrier::One() const
{
	return m_vec.at(1);
}

Element Carrier::Zero() const
{
	return m_vec.front();
}

Element Carrier::Max() const
{
	return m_vec.back();
}

Element Carrier::operator[](const int& id) const
{
	if (id >= 0 && id < m_vec.size())
	{
		return m_vec.at(id);
	}

	throw std::logic_error("Element id is invalid!\n");
	
}

Element Carrier::operator[](const char& c) const
{
	for (const Element& el : m_vec)
	{
		if (el.getChar() == c)
		{
			return el;
		}
	}
	throw std::logic_error("There is no such el in Carrier!\n");
}

int Carrier::size() const
{
	return m_vec.size();
}

Tables Carrier::getTables() const
{
	return m_tables;
}

bool Carrier::isThere(const char& c) const
{
	for (const Element& el : m_vec)
	{
		if (el.getChar() == c)
		{
			return true;
		}
	}
	return false;
}

//const Element* Carrier::getElementPtr(const int& id) const
//{
//	if (id >= 0 && id < m_vec.size())
//	{
//		return &(m_vec.at(id));
//	}
//	throw std::logic_error("Element id is invalid!\n");
//}
//
//const Element* Carrier::getElementPtr(const char& c) const
//{
//	for (const Element& el : m_vec)
//	{
//		if (el.getChar() == c)
//		{
//			return &el;
//		}
//	}
//	throw std::logic_error("There is no such el in Carrier!\n");
//}


std::ostream& operator<<(std::ostream& out, const Carrier& s)
{
	for (int i = 0; i < s.size(); i++)
	{
		out << s.m_vec[i] << ' ';
	}
	//out << '\n';

	return out;
	
}