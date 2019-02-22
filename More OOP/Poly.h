#ifndef POLY_HEADER
#define POLY_HEADER
#include<iostream>
#include<algorithm>



template<class Type>
class Poly
{
public:
	class Iterator
	{
	public:
		Iterator( Type*type)
		{
			ptrCoeff = type;
		}
	public:
		Iterator& operator++()
		{
			++ptrCoeff;
			return *this;
		}

		Iterator operator++(int)const
		{
			Iterator temp(*this);
			operator++;
			return temp;
		}

		Iterator& operator--()
		{
			--ptrCoeff;
			return *this;
		}

		Iterator operator--(int)const
		{
			Iterator temp(*this);
			operator--;
			return temp;
		}

		bool operator==(const Iterator&other)const
		{
			return ptrCoeff == other.ptrCoeff;
		}
		
		bool operator<(const Iterator&other)const
		{
			return ptrCoeff < other.ptrCoeff;
		}

		bool operator>(const Iterator&other)const
		{
			return ptrCoeff >other.ptrCoeff;
		}
		bool operator<=(const Iterator&other)const
		{
			return !(*this > other);
		}
		bool operator>=(const Iterator&other)const
		{
			return !(*this < other);
		}
		bool operator!=(const Iterator&other)const
		{
			return !(*this == other);
		}
		Iterator operator-(int how)const
		{
			return Iterator(ptrCoeff - how);
		}
		Iterator operator+(int how)const
		{
			return Iterator(ptrCoeff + how);
		}
		Type& operator*()const
		{
			return *ptrCoeff;
		}

		Type* operator->()const
		{
			return ptrCoeff;
		}

	private:
		Type* ptrCoeff;
	};

	Iterator begin()
	{
		return Iterator(coeff);
	}
	Iterator end()
	{
		return Iterator(coeff + size);
	}
public:
	/*потребителят подава степента на полинома която иска -> N+1 степен и какъв да
	е коефициента пред най-високата степен, другите коефициенти се инициализират с 0
	хвърля се изключение ако се подаде 0 за степен или за коефициент
	!!!опитал съм се да поддържам винаги пред най-високата степен да има ненулев коефициент
	поради,което работа с чисто нулеви полиноми не се предполага да се поддържа от външния свят
	изключение прави оператори - ,/ и %,където може да се получи 0 като резултат и оператора за индексиране,който
	не пречи-на външния свят да си сложи коеф.0
	*/

	Poly(size_t degree, size_t coeff_biggest_deg);
	Poly(const Poly&other);
	Poly& operator=(const Poly&other);
	~Poly();
	
	bool operator==(const Poly &other)const;
	bool operator!=(const Poly&other)const;
	bool operator<(const Poly&other)const;
	bool operator<=(const Poly&other)const;
	bool operator>(const Poly&other)const;
	bool operator >= (const Poly&other)const;


	Poly& operator+=(const Poly&other);
	const Poly operator+(const Poly&other)const;

	Poly& operator-= (const Poly&other);
	const Poly operator- (const Poly&other);

	Poly& operator*=(const Poly&other);
	const Poly operator*(const Poly&other)const;

	Poly& operator*=(const Type&t);
	const Poly operator*(const Type&t)const;


	Poly& operator/=(const Poly&other);
	const Poly operator/(const Poly&other)const;
	Poly& operator/=(const Type&t);
	const Poly operator/(const Type&t)const;

	Poly& operator%=(const Poly&other);
	const Poly operator%(const Poly&other)const;

	Type& operator[](size_t pos);
	const Type operator[](size_t pos) const;

	Type operator()(const Type& t)const;
	Type operator()(const Type& t1, const Type& t2)const;

	Poly& operator++();
	const Poly operator++(int);

	Poly& operator--();
	const Poly operator--(int);

	template<class U>
	friend std::ostream& operator<< (std::ostream&os, const Poly<U>&other);

	template<class U>
	friend std::istream& operator>> (std::istream&, Poly<U>&r);

	operator int()const ; 
	operator bool()const;

private:
	void resize(size_t newSize);
	void clean(Type*& data);
	void copyFrom(const Poly&other);
	void setData(size_t size);
	void setSize(size_t size);
	void allToZero(size_t size);
	void find_Q_R(Poly&q, Poly&r, const Poly&other);
	bool isZero()const;
	size_t findHowZero(const Poly&other);
private:
	Type*coeff;
	size_t size;//степента на полинома - size-1
};

template<class Type>
inline std::ostream& operator<< (std::ostream&os, const Poly<Type>&other)
{
	if (other.size == 0)
	{
		std::cout << 0;
		return os;
	}
	os << other.coeff[0];
	for (size_t i = 1; i <other.size - 1; ++i)
	{
		if (other.coeff[i] == 0)
			continue;
		if (other.coeff[i] > 0)
			os << "+" << other.coeff[i] << "*" << "x^" << i;
		else
			os << other.coeff[i] << "*" << "x^" << i;
	}
	if (other.coeff[other.size - 1] > 0)
		os << "+" << other.coeff[other.size - 1] << "*" << "x^" << other.size - 1 << "\n" << "\n";
	else if (other.coeff[other.size - 1] < 0)
		os << other.coeff[other.size - 1] << "*" << "x^" << other.size - 1 << "\n" << "\n";
	else
		os << "\n" << "\n";

	return os;
}

template<class Type>
inline std::istream& operator>> (std::istream& ifs, Poly<Type>& r) 
{

	for (size_t i = 0; ifs.get() != '\n' && ifs.good(); ++i)
	{
		ifs.unget();
		ifs >> r[i];
	}
	return ifs;
}

#include"Poly.hpp"

#endif
