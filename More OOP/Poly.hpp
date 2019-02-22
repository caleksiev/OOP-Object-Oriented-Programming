#include "Poly.h"
#pragma once

template<class Type>
inline Poly<Type>::Poly(size_t degree, size_t coeff_biggest_deg):coeff(nullptr),size(0)
{
	if (!degree ||!coeff_biggest_deg)
		throw std::invalid_argument("0 argument pass on Poly CTOR!\n");
	setData(degree);
	allToZero(degree);
	setSize(degree);
	coeff[size - 1] = coeff_biggest_deg;
}

template<class Type>
inline Poly<Type>::Poly(const Poly<Type> & other):coeff(nullptr),size(0)
{
	copyFrom(other);
}

template<class Type>
inline Poly<Type> & Poly<Type>::operator=(const Poly<Type> & other)
{
	if (this != &other)
	{ 
	//само ако успее копирането изчистваме данните,ако възникне изключение this->обекта остава непроменен
		Type*oldCoeff = coeff;
		copyFrom(other);
		clean(oldCoeff);	
	}
	return *this;
}

template<class Type>
inline Poly<Type>::~Poly()
{
	clean(coeff);
}

template<class Type>
inline bool Poly<Type>::operator==(const Poly<Type> & other) const
{
	//ако са от различни степени със сигурност съществуват аргументи за които полиномите не са ==
	if (size != other.size)
		return false;
	//в противен случай гледаме дали коф. им съвпадат
	for (size_t i = 0; i < size; ++i)
	{
		if (coeff[i] != other.coeff[i])
			return false;
	}
	return true;
}


//спецификация при дробни числа - приближена точност 
template<>
inline bool Poly<double>::operator==(const Poly<double> & other)const
{
	//ако са от различни степени със сигуност съшесвуват аргументи за които полиномите не са ==
	if (size != other.size)
		return false;
	//в противен случай гледаме дали коф. им съвпадат
	for (size_t i = 0; i < size; ++i)
	{
		if ((abs(coeff[i] - other.coeff[i]) > 0.00001))
			return false;
	}
	return true;
}

template<class Type>
inline bool Poly<Type>::operator!=(const Poly<Type> & other) const
{
	return !(*this == other);
}


template<class Type>
inline bool Poly<Type>::operator<(const Poly<Type> & other) const
{
	if (size < other.size)
		return true;
	return false;
}


template<class Type>
inline bool Poly<Type>::operator>(const Poly<Type> & other)const
{
	if (size > other.size)
		return true;
	return false;
}

template<class Type>
inline bool Poly<Type>::operator<=(const Poly<Type> & other)const
{
	return !(*this > other);
}


template<class Type>
inline bool Poly<Type>::operator>=(const Poly<Type> & other)const
{
	return!(*this < other);
}

template<class Type>
inline Poly<Type> & Poly<Type>::operator+=(const Poly<Type> & other)
{
	if (other.size > size)
		resize(other.size);

	for (size_t i = 0; i < size; ++i)
		coeff[i] += other.coeff[i];

	return *this;
}

template<class Type>
inline const Poly<Type> Poly<Type>::operator+(const Poly<Type> & other) const
{
	return Poly(*this) += other;
}

template<class Type>
inline Poly<Type> & Poly<Type>::operator-=(const Poly <Type>& other)
{
	if (other.size > size)
		resize(other.size);

	for (size_t i = 0; i < size; ++i)
		coeff[i] -= other.coeff[i];

	return *this;
}

template<class Type>
inline const Poly<Type> Poly<Type>::operator-(const Poly<Type> & other)
{
	Poly temp(*this);
	temp -= other;
	return temp;
}

template<class Type>
inline Poly<Type> & Poly<Type>::operator*=(const Poly<Type> & other)
{
	Poly temp(size + other.size-1,1);
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < other.size; j++)
			temp.coeff[i + j] += coeff[i] * other.coeff[j];
	}
	*this = temp;
	return *this;
}

template<class Type>
inline const  Poly<Type> Poly<Type>::operator*(const Poly<Type> & other)const
{
	Poly temp(*this);
	temp *= other;
	return temp;
}
template<class Type>
inline Poly<Type> & Poly<Type>::operator*=(const Type & t)
{
	if (!t)
		throw std::invalid_argument("NULL POLY!\n");
	for (size_t i = 0; i < size; ++i)
		coeff[i] *= t;
	return *this;
}

template<class Type>
inline const Poly<Type> Poly<Type>::operator*(const Type & t)const
{
	return Poly(*this)*=t;
}

template<class Type>
inline Poly<Type> & Poly<Type>::operator/=(const Poly<Type> & other)
{

	if (other.size > size|| !other.size || !size)
		return *this;
	Poly q((size - other.size) + 1,1);//делителя
	Poly r(size,1);//остатъка

	//малко е глупаво,ама върши работа
	r.coeff[r.size - 1] = 0;
	q.coeff[q.size - 1] = 0;

	//намираме съответия остатък и частно
	find_Q_R(q, r,other);
	size_t  cntQ = findHowZero(q);
	//ако полинома,съдържащ частното не е точно от първоначалната степен се преоразмерява
	if (cntQ)
		q.resize(q.size - cntQ);
	*this = q;
	return *this;
	
}

template<class Type>
inline const Poly<Type> Poly<Type>::operator/(const Poly<Type> & other) const
{
	return Poly(*this) /= other;
}

template<class Type>
inline Poly<Type> & Poly<Type>::operator/=(const Type & t)
{
	if (t == 0)
		throw std::invalid_argument("DEVISION ON !0!");
	for (size_t i = 0; i < size; ++i)
		coeff[i] /= t;

	return *this;
}

template<class Type>
inline const  Poly<Type> Poly<Type>::operator/(const Type & t)const
{
	return Poly(*this) /= t;
}

template<class Type>
inline Poly<Type> & Poly<Type>::operator%=(const Poly<Type> & other)
{

	if (other.size > size || !other.size || !size)
		return *this;
	Poly q((size - other.size) + 1,1);//делителя
	Poly r(size,1);//остатъка
	r.coeff[r.size - 1] = 0;
	q.coeff[q.size - 1] = 0;

	find_Q_R(q, r, other);
	size_t cntR = findHowZero(r);
	//ако полинома,съдържащ остатъка не е точно от първоначалната степен се преоразмерява
	if (cntR)
		r.resize(r.size - cntR);
	*this = r;
	return *this;
}

template<class Type>
inline const Poly<Type> Poly<Type>::operator%(const Poly<Type> & other) const
{
	return Poly(*this) %= other;
}

template<class Type>
inline Type & Poly<Type>::operator[](size_t pos)
{
	if (pos >= size)
	{
		resize(pos + 1);
	}
	if (pos == size - 1)
	{
		if (!coeff[pos])
			return coeff[pos];//няма какво да се направи по накъкъв начин коеф е 0
		else
		{
		Type pos = coeff[size - 1];
		resize(size + 1);
		coeff[size - 1] = pos;
		}
	}
	return coeff[pos];
}

template<class Type>
inline const Type Poly<Type>::operator[](size_t pos) const
{
	if(pos>=size)
		throw std::out_of_range("invalid index");
	return coeff[pos];
}

template<class Type>
inline Type Poly<Type>::operator()(const Type&  t) const
{
	Type res = 0;
	for (size_t i = 0; i < size; ++i)
	{
		size_t how = i;
		Type deg = 1;
		while (how)
		{
			deg *= t;
			--how;
		}
		res += coeff[i] * deg;
	}
	return res;
}

template<class Type>
Type pow(const Type&what, size_t deg)
{
	Type res = 1;
	while (deg)
	{
		res *= what;
		--deg;
	}
	return res;
}
template<class Type>
inline Type Poly<Type>::operator()( const Type& t1,  const Type& t2) const
{
	if (t1 > t2)
		throw std::invalid_argument("Invalid Inteval!\n");
	Type res = 0;
	for (size_t i = 0; i < size; ++i)
	{
		size_t deg = i + 1;
		Type a = pow(t1, deg);
		Type b = pow(t2, deg);
		res += coeff[i] * ((b / deg) - (a / deg));
	}
	return res;
}

template<class Type>
inline Poly<Type> & Poly<Type>::operator++()
{
	Poly temp(size + 1,1);
	for (size_t i = 1; i < size; ++i)
	{
		temp.coeff[i] = coeff[i - 1] / i;
	}
	*this = temp;
	return *this;
}

template<class Type>
inline const Poly<Type> Poly<Type>::operator++(int)
{
	Poly temp(*this);
	operator++();
	return temp;
}

template<class Type>
inline Poly<Type> & Poly<Type>::operator--()
{
	Poly temp(size - 1,1);
	for (size_t i = 0; i < size-1; ++i)
	{
		temp.coeff[i] = coeff[i + 1] * (i+1);
	}
	*this = temp;
	return *this;
}

template<class Type>
inline const Poly<Type> Poly<Type>::operator--(int)
{
	Poly temp(*this);
	operator--();
	return temp;
}

template<class Type>
inline Poly<Type>::operator int()const
{
	return size - 1;
}

template<class Type>
inline Poly<Type>::operator bool() const
{
	return isZero();
}
template<class Type>
inline void Poly<Type>::resize(size_t newSize)
{
	size = std::min(size, newSize);
	Type*oldData = coeff;
	coeff = new Type[newSize];
	allToZero(newSize);
	//ако кофециентите са стандартните вградени типове няма да имаме проблем
	//в противен случай при оператор = може да възникне грешка
	try
	{
		for (size_t i = 0; i < size; ++i)
			coeff[i] = oldData[i];

		for (size_t i = size; i < newSize; ++i)
			coeff[i] = 0;
	}
	catch (...)
	{
		clean(coeff);
		coeff = oldData;
		throw;
	}
	delete[]oldData;
	setSize(newSize);
}

template<class Type>
inline void Poly<Type>::clean(Type*& data)
{
	delete[]data;
	data = nullptr;
}

template<class Type>
inline void Poly<Type>::copyFrom(const Poly<Type> & other)
{
	setData(other.size);
	
	allToZero(other.size);//приемам,че при оператор= за нестандартните типове няма да има грешка
	setSize(other.size);


	//ако кофециентите са стандартните вградени типове няма да имаме проблем
	//в противен случай при оператор = може да възникне грешка
	try
	{
		for (size_t i = 0; i < size; ++i)
			coeff[i] = other.coeff[i];
	}
	catch (...)
	{
		setSize(0);
		clean(coeff);
		throw;
	}
}

template<class Type>
inline void Poly<Type>::setData(size_t size)
{
	coeff = new Type[size];
}

template<class Type>
inline void Poly<Type>::setSize(size_t size)
{
	this->size = size;
}

template<class Type>
inline void::Poly<Type>::allToZero(size_t size)
{
	for (size_t i = 0; i < size; ++i)
		coeff[i] = 0;
}

template<class Type>
inline void Poly<Type>::find_Q_R(Poly<Type> & q, Poly<Type>& r,const Poly&other)
{
	for (int i = size - other.size; i >= 0; --i)
	{
		if (!other.coeff[other.size - 1])
			throw std::invalid_argument("The coeff under the dеvisor biggest degree is 0!\n");
		q.coeff[i] = coeff[i+(other.size - 1)] / other.coeff[other.size - 1];
		for (int j = other.size - 1; j >= 0; --j)
			coeff[i + j] = coeff[i + j] - (other.coeff[j] * q.coeff[i]);
	}
	for (int j = other.size - 1; j >= 0; --j)
		r.coeff[j] = coeff[j];
	std::cout << r;
}

template<class Type>
inline bool Poly<Type>::isZero() const
{
	for (size_t i = 0; i < size; ++i)
	{
		if (coeff[i] < 0.0001)
			return true;
	}
	return false;
}

template<class Type>
inline size_t Poly<Type>::findHowZero(const Poly & other)
{
	size_t cnt = 0;
	bool  findNeNulev = false;
	for (int i = other.size-1; i>=0; --i)
	{
		if (!other.coeff[i])
			++cnt;
		else
			break;
	}
	return cnt;
}

