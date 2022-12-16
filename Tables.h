#pragma once
#include "Element.h"

class Tables
{
	std::vector<std::vector<Element>> addTable;
	std::vector<std::vector<Element>> mulTable;
	std::vector<std::vector<Element>> c_addTable;
	std::vector<std::vector<Element>> c_mulTable;

	void initializeAddTables(const std::vector<char>& carrier);
	void initializeMulTables(const std::vector<char>& carrier);

	//void initializeMulTables();
	void printTable(std::ostream& os, const int& index) const;

	// return element from 'local carrier' (using 0 row of addTable)
	Element getCarrierEl(const int& id) const;

	// return size from 'local carrier' (using 0 row of addTable)
	int getSizeOfCarrier() const;

public:
	Tables(const std::vector<char>& carrier);
	int findElementInRow(const std::vector<std::vector<Element>>& table, const int& rowID, const Element& e) const;
	Element sum(const Element& e1, const Element& e2) const;
	Element reverse_sum(const Element& e1, const Element& e2) const;
	Element mul(const Element& e1, const Element& e2) const;
	Element reverse_mul(const Element& e1, const Element& e2) const;
	Element carry_sum(const Element& e1, const Element& e2) const;
	Element carry_mul(const Element& e1, const Element& e2) const;

	friend std::ostream& operator<<(std::ostream& os, const Tables& t);
};

std::ostream& operator<<(std::ostream& os, const Tables& t);

