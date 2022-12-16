#include "Tables.h"

void Tables::initializeAddTables(const std::vector<char>& s)
{
	int size = s.size();
	int index;

	addTable.reserve(size);
	c_addTable.reserve(size);

	for (int i = 0; i < size; i++) //num of rows
	{
		std::vector<Element> row;
		std::vector<Element> carryRow;
		
		row.reserve(size);
		carryRow.reserve(size);

		for (int j = 0; j < size; j++)
		{

			//add sum of two symbols into row
			// (i + j) % size -- index of element in carrier vector
			// s.at((i + j) % size)) -- result of sum of two symbols (Small Arithmetic)
			index = (i + j) % size;
			row.push_back(Element(s[index], index));

			// Add carry result into carryRow
			// std::round() -- rounds down to the nearest integer
			// std::round((i + j) / size) 
			index = int(round((i + j) / size));
			carryRow.push_back(Element(s[index], index));
		}
		addTable.push_back(row);
		c_addTable.push_back(carryRow);
	}
}

void Tables::initializeMulTables(const std::vector<char>& s)
{

	int size = s.size();
	int index;

	mulTable.reserve(size);
	c_mulTable.reserve(size);

	for (int i = 0; i < size; i++) //num of rows
	{
		std::vector<Element> row;
		std::vector<Element> carryRow;

		row.reserve(size);
		carryRow.reserve(size);

		for (int j = 0; j < size; j++)
		{

			//add sum of two symbols into row
			// (i * j) % size -- index of element in carrier vector
			// s.at((i * j) % size)) -- result of sum of two symbols (Small Arithmetic)
			index = (i * j) % size;
			row.push_back(Element(s[index], index));

			// Add carry result into carryRow
			// std::round() -- rounds down to the nearest integer
			// std::round((i * j) / size) 
			index = int(round((i * j) / size));
			carryRow.push_back(Element(s[index], index));

		}
		mulTable.push_back(row);
		c_mulTable.push_back(carryRow);
	}
}

void Tables::printTable(std::ostream& out, const int& index) const
{
	const std::vector<std::vector<Element>>* table;

	// Row of Titles
	if (index < 2)
	{
		if (index == 0)
		{
			out << "+ ";
			table = &addTable;
		}
		else
		{
			out << "& ";
			table = &c_addTable;
		}
	}
	else
	{
		if (index == 2)
		{
			out << "* ";
			table = &mulTable;
		}
		else
		{
			out << "^ ";
			table = &c_mulTable;
		}
	}

	for (int i = 0; i < getSizeOfCarrier(); i++)
	{
		out << getCarrierEl(i) << ' ';
	}
	out << '\n';

	// Other rows
	int i = 0;
	for (int i = 0; i < getSizeOfCarrier(); i++)
	{
		out << getCarrierEl(i) << ' ';
		for (int j = 0; j < table->size(); j++)
		{
			out << table->at(i).at(j) << ' ';
		}
		/*for (Element el : table->at(i))
		{
			out << *el << ' ';
		}*/
		out << '\n';
	}
}

Element Tables::getCarrierEl(const int& id) const
{
	return addTable.at(0).at(id);
}

int Tables::getSizeOfCarrier() const
{
	return addTable.at(0).size();
}

Tables::Tables(const std::vector<char>& carrier)
{
	initializeAddTables(carrier);
	initializeMulTables(carrier);
}

int Tables::findElementInRow(const std::vector<std::vector<Element>>& table, const int& rowID, const Element& findEl) const
{
	int id = 0;
	for (Element el : table.at(rowID))
	{
		if (el == findEl)
		{
			return id;
		}
		++id;
	}
	throw std::logic_error("There is no such element in table!");
}

Element Tables::sum(const Element& e1, const Element& e2) const
{
	return addTable.at(e1.getID()).at(e2.getID());
}

Element Tables::reverse_sum(const Element& e1, const Element& e2) const
{
	// e1 = res + e2 ==> res = e1 - e2
	int resID = findElementInRow(addTable, e2.getID(), e1);
	return getCarrierEl(resID);
}

Element Tables::mul(const Element& e1, const Element& e2) const
{
	return mulTable.at(e1.getID()).at(e2.getID());
}

Element Tables::reverse_mul(const Element& e1, const Element& e2) const
{
	// e1 = res * e2 ==> res = e1 / e2
	int resID = findElementInRow(mulTable, e2.getID(), e1);
	return getCarrierEl(resID);
}

Element Tables::carry_sum(const Element& e1, const Element& e2) const
{
	return c_addTable.at(e1.getID()).at(e2.getID());
}

Element Tables::carry_mul(const Element& e1, const Element& e2) const
{
	return c_mulTable.at(e1.getID()).at(e2.getID());
}

std::ostream& operator<<(std::ostream& os, const Tables& t)
{
	os << "\nTABLES----------------------------\n";
	os << "------------------\n";
	for (int i = 0; i < 4; i++)
	{
		t.printTable(os, i);
		os << "------------------\n";
	}
	os << "----------------------------------\n";
	return os;
	
}