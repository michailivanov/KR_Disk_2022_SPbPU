#include "Number.h"

void Number::incrementNum()
{
	++m_vec.at(0);
	int i = 0;
	while (i < m_vec.size() - 1 && m_vec.at(i) == CARRIER.Zero())
	{
		++i;
		++m_vec.at(i);
	}

	// in case: 9999 + 1 = 10000
	if (m_vec.at(i) == CARRIER.Zero())
	{
		m_vec.push_back(CARRIER.One());
	}

	if (m_vec.size() > MAX_NUM_OF_DIGHTS)
	{
		throw std::logic_error("OVERFLOW\n");
	}
}

void Number::decrementNum()
{
	//--m_vec.at(0);
	int i = 0;
	bool decrementNext = true;
	while (decrementNext && i < m_vec.size())
	{
		if (m_vec.at(i) == CARRIER.Zero())
		{
			m_vec.at(i) = CARRIER.Max();
		}
		else
		{
			--m_vec.at(i);
			decrementNext = false;
		}

		++i;
	}

	if (i == m_vec.size() && decrementNext)
	{
		m_vec.clear();
		m_vec.push_back(CARRIER.Zero());
	}

	DelUselessBeginZeros();

	if (m_vec.size() > MAX_NUM_OF_DIGHTS)
	{
		throw std::logic_error("OVERFLOW\n");
	}
}

Number::Number() : m_sign(false), m_vec(1, CARRIER.Zero())
{
}

Number::Number(std::string str) : m_sign(false)
{
	if (validateStr(str) == false)
	{
		throw std::logic_error("Invalid number!\n");
	}
	else
	{
		int i = 0;
		int size = str.size();
		if (str.at(0) == '-')
		{
			m_sign = true;
			i = 1;
		}
		for(int j = size - 1; j >= i; j--)
		{
			Digit d = str.at(j);
			m_vec.push_back(str.at(j));
		}
		DelUselessBeginZeros();
	}
}

Number::Number(const std::vector<Digit>& vec, bool sign) : m_vec(vec), m_sign(sign)
{
}

Number::Number(const Element& el, bool sign) : m_sign(sign)
{
	m_vec.push_back(el);
}

Number::Number(const int& i) : m_sign(false)
{
	int num = i;
	if (i < 0)
	{
		m_sign = true;
		num *= -1;
	}
	else if (i == 0)
	{
		m_vec.push_back(CARRIER.Zero());
		return;
	}

	int index;
	int iteration = 0;
	while (num != 0)
	{
		index = num % CARRIER.size();
		m_vec.push_back(CARRIER[index]);
		num = num / CARRIER.size();
		++iteration;
	}
	if (iteration > MAX_NUM_OF_DIGHTS)
	{
		throw std::logic_error("It is impossible to create num using this int, because it will cause overflow!\n");
	}
}

void Number::DelUselessBeginZeros()
{
	while (m_vec.back() == CARRIER.Zero() && m_vec.size() != 1)
	{
		m_vec.pop_back();
	}
}

bool Number::validateStr(std::string str)
{ 
	if (str.size() == 0)
	{
		return false;
	}

	int max_size = MAX_NUM_OF_DIGHTS;
	int index = 0;
	if (str.at(0) == '-')
	{
		++max_size;
		++index;
	}
	
	if (str.size() > max_size) // dights + sign (can be '-')
	{
		return false;
	}
	
	for (; index < str.size(); index++)
	{
		if (!CARRIER.isThere(str.at(index)))
		{
			return false;
		}
	}
	return true;
}

int Number::toInt() const
{
	int res = 0;
	for (int i = 0; i < m_vec.size(); i++)
	{
		res += m_vec.at(i).getID() * pow(CARRIER.size(), i);
	}
	if (m_sign)
	{
		res *= -1;
	}
	return res;
}

void Number::invertSign()
{
	m_sign = 1 - m_sign;
}



bool Number::isZero() const
{
	if (m_vec.size() == 1 && m_vec.at(0) == CARRIER.Zero())
		return true;
	return false;
}

bool Number::operator==(const Number& other) const
{
	if (m_sign != other.m_sign || m_vec.size() != other.m_vec.size())
		return false;
	for (int i = 0; i < m_vec.size(); i++)
	{
		if (m_vec.at(i) != other.m_vec.at(i))
		{
			return false;
		}
	}
	return true;
}

bool Number::operator!=(const Number& other) const
{
	return !(*this == other);
}

bool Number::operator>(const Number& other) const
{
	if (m_vec.size() > other.m_vec.size())
	{
		return true;
	}
	else if (m_vec.size() < other.m_vec.size())
	{
		return false;
	}

	// Then Sizes and Signs are equal 
	for (int i = m_vec.size() - 1; i >= 0; i--)
	{
		if (m_vec.at(i) > other.m_vec.at(i))
		{
			return true;
		}
		else if (m_vec.at(i) < other.m_vec.at(i))
		{
			return false;
		}
	}

	//Then numbers are equal
	return false;
}

bool Number::operator<(const Number& other) const
{
	return !operator>(other);
}

std::ostream& operator<<(std::ostream& os, const Number& n)
{
	if (n.m_sign && !n.isZero())
	{
		os << '-';
	}
	for (int i = n.m_vec.size() - 1; i >= 0; i--)
	{
		os << n.m_vec.at(i);
	}
	return os;
}

Number Number::sum_withSameSign(const Number& other) const
{
	std::vector<Digit> res;

	bool res_sign = m_sign;

	// Pointers big_num and small_num
	const Number* big_num;
	const Number* small_num;
	if (*this > other || *this == other)
	{
		big_num = this;
		small_num = &other;
	}
	else
	{
		big_num = &other;
		small_num = this;
	}

	Digit sumOf2D(CARRIER.Zero());
	Digit carry_buffer(CARRIER.Zero());
	for (int i = 0; i < small_num->m_vec.size(); i++)
	{
		// Previous buffer + sum (and changing buffer to the next val)
		Digit old_buffer(carry_buffer);
		Digit buf(CARRIER.Zero());
		
		sumOf2D = big_num->m_vec.at(i).sum(small_num->m_vec.at(i), carry_buffer);
		sumOf2D = sumOf2D.sum(old_buffer, buf);
		carry_buffer += buf;
		res.push_back(sumOf2D);
	}
	for (int i = small_num->m_vec.size(); i < big_num->m_vec.size(); i++)
	{
		sumOf2D = big_num->m_vec.at(i).sum(carry_buffer, carry_buffer);
		res.push_back(sumOf2D);
	}
	if (carry_buffer != CARRIER.Zero())
	{
		res.push_back(carry_buffer);
	}


	Number RES_return(res, res_sign);
	RES_return.DelUselessBeginZeros();
	if (RES_return.m_vec.size() > MAX_NUM_OF_DIGHTS)
	{
		throw std::logic_error("OVERFLOW!\n");
	}
	return RES_return;
	//return Number(res, big_num->m_sign);
}

Number Number::sub_withSameSign(const Number& other) const
{
	std::vector<Digit> res;

	bool res_sign = m_sign;
	if (*this < other)
	{
		res_sign = 1 - res_sign;
	}

	// Pointers big_num and small_num
	const Number* big_num;
	const Number* small_num;

	if (m_vec.size() > other.m_vec.size())
	{
		big_num = this;
		small_num = &other;
	}
	else if (m_vec.size() == other.m_vec.size())
	{
		if (*this > other || *this == other)
		{
			big_num = this;
			small_num = &other;
		}
		else
		{
			small_num = this;
			big_num = &other;
		}
	}
	else
	{
		big_num = &other;
		small_num = this;
	}

	Digit subOf2D(CARRIER.Zero());
	Digit carry_buffer(CARRIER.Zero());
	for (int i = 0; i < small_num->m_vec.size(); i++)
	{
		// Previous buffer + sub (and changing buffer to the next val)
		Digit old_buffer(carry_buffer);
		Digit buf(CARRIER.Zero());

		subOf2D = big_num->m_vec.at(i).sub(small_num->m_vec.at(i), carry_buffer);
		subOf2D = subOf2D.sub(old_buffer, buf);
		carry_buffer += buf;
		res.push_back(subOf2D);
	}
	for (int i = small_num->m_vec.size(); i < big_num->m_vec.size(); i++)
	{
		subOf2D = big_num->m_vec.at(i).sub(carry_buffer, carry_buffer);
		res.push_back(subOf2D);
	}
	if (carry_buffer != CARRIER.Zero())
	{
		res.push_back(carry_buffer);
	}

	Number RES_return(res, res_sign);
	RES_return.DelUselessBeginZeros();
	if (RES_return.m_vec.size() > MAX_NUM_OF_DIGHTS)
	{
		throw std::logic_error("OVERFLOW!\n");
	}
	return RES_return;
}

void Number::shiftRight()
{
	m_vec.insert(m_vec.begin(), CARRIER.Zero());
}

Number Number::operator+(const Number& other) const
{
	// a + b = (a + b)
	// (-a) + (-b) = - (a + b)
	if (m_sign == other.m_sign)
	{
		return sum_withSameSign(other);
	}
	// a + (-b) = a - b
	else if (m_sign == false && other.m_sign == true)
	{
		Number cpy(other);
		cpy.invertSign();
		return operator-(cpy);
	}
	// (-a) + b = b - a
	else //(m_sign == true && other.m_sign == false)
	{
		Number cpy(*this);
		cpy.invertSign();
		return other.operator-(cpy);
	}
}

Number Number::operator-(const Number& other) const
{
	// (a) - (b) = a - b
	// (-a) - (-b) = b - a
	if (m_sign == other.m_sign)
	{
		return sub_withSameSign(other);
	}
	// (a) - (-b) = a + b
	else if (m_sign == false && other.m_sign == true)
	{
		Number cpy(other);
		cpy.invertSign();
		return operator+(cpy);
	}
	// (-a) - (b) = (-a) + (-b)
	else // (m_sign == true && other.m_sign == false)
	{
		Number cpy(other);
		cpy.invertSign();
		return operator+(cpy);
	}
}

Number Number::operator*(const Number& other) const
{
	Number res;

	Number buf;
	Digit carry_buffer(CARRIER.Zero());
	
	bool res_sign = m_sign != other.m_sign;
	
	for (int i = 0; i < m_vec.size(); i++)
	{
		for (int j = 0; j < other.m_vec.size(); j++)
		{
			//Mul two digits
			Digit mul = m_vec.at(i).mul(other.m_vec.at(j), carry_buffer);

			// Add res to buf
			std::string mul_str = "";
			
			mul_str += carry_buffer.toChar();
			mul_str += mul.toChar();

			// add offset
			for (int k = 0; k < j; k++)
			{
				mul_str.push_back(CARRIER.Zero().getChar());
			}

			buf = buf + Number(mul_str);
		}
		//Add offset to buf
		for (int k = 0; k < i; k++)
		{
			buf.shiftRight();
		}
		res = res + buf;
		buf = Number(); //Zero
	}
	Number RES_return(res.m_vec, res_sign);
	//Number RES_return(res, big_num->m_sign);
	RES_return.DelUselessBeginZeros();
	if (RES_return.m_vec.size() > MAX_NUM_OF_DIGHTS)
	{
		throw std::logic_error("OVERFLOW!\n");
	}
	return RES_return;
	//return Number(res.m_vec, res_sign);
}

Number Number::div(const Number& other, Number& divRemainder, int* iterationCount) const
{
	// if other number is Zero
	if (this->isZero() && other.isZero())
	{
		std::string out;
		std::string maxNum;
		out += "[-";
		for (int i = 0; i < MAX_NUM_OF_DIGHTS; i++)
		{
			maxNum += CARRIER.Max().getChar();
		}
		out += maxNum;
		out += ", ";
		out += maxNum;
		out += "]\n";
		throw std::logic_error(out);
	}
	else if (other.isZero())
	{
		throw std::logic_error("It is impossible to div by Zero!!!\n");
	}

	// Construct sign:
	bool res_sign = false;

	// if this number is Zero
	if (this->isZero())
	{
		divRemainder = Number();
		return Number(); //Zero
	}
	else
	{
		if (this->m_sign != other.m_sign)
		{
			res_sign = true;
		}
	}
	
	// Find div and divRemainder
	Number res;
	if (*this > other)
	{
		int digitCountDiff = m_vec.size() - other.m_vec.size();

		// Form Start Buffer number
		std::string startBufferNumStr;
		if (res_sign)
		{
			startBufferNumStr += '-';
		}
		startBufferNumStr += CARRIER.One().getChar();
		for (int i = 0; i < digitCountDiff - 1; i++)
		{
			startBufferNumStr += CARRIER.Zero().getChar();
		}

		Number buf = Number(startBufferNumStr);
		Number jmp = Number();
		int i = 0;
		do
		{
			res = buf;
			++buf;
			jmp = buf + Number(50);
			if (jmp * other < *this)
			{
				buf = jmp;
			}
			i++;
		} while (buf * other < *this);
		if (iterationCount != nullptr)
		{
			*iterationCount = i;
		}
	}
	else if (*this == other)
	{
		res = Number(CARRIER.One(), false);
	}
	else
	{
		res = Number(CARRIER.Zero(), false);
	}
	

	res.m_sign = res_sign; // set res sign

	// if this (-) / other (+) than we have to change values (Because there is no negative div remainder
	if (this->m_sign == true && other.m_sign == false)
	{
		// Change result of division (Have to be incremented (do not think about sign))
		res.incrementNum();

		// Find Div remainder
		divRemainder = ((res * (-1)) * other) + (*this);
	}
	else
	{ // Find Division remainder for other "normal" cases 
		
		if (res_sign) // res sign is -
		{
			divRemainder = (res * other) - (*this);
		}
		else // res sign is +
		{
			divRemainder = (*this) - (res * other);
		}
		divRemainder.m_sign = false; //set Remainder's sign to +
	}
	return res;
}

void Number::operator++()
{	
	if (*this == Number(CARRIER.One(), true))
	{
		decrementNum();
		m_sign = false;
	}
	else if (m_sign == false) // +
	{
		incrementNum();
	}
	else // -
	{
		decrementNum();
	}
}

void Number::operator--()
{
	if (this->isZero())
	{
		incrementNum();
		m_sign = true;
	}
	else if (m_sign == true) // +
	{
		incrementNum();
	}
	else // -
	{
		decrementNum();
	}
}
