#include"Poly.h"
template<class Type>
void test1()
{
	Poly<Type> p1(6, 10);
	p1[0] = 2;
	p1[1] = 3;
	p1[2] = 0;
	p1[3] = 2;

	std::cout << "New Poly\nP1=" << p1;

	Poly<Type>p2(p1);
	std::cout << "New Poly\nP2=" << p2;

	p1 += p2;
	std::cout << "P1+=P2:\nP1=" << p1;

	p1 = p1 + p2;
	std::cout << "P1=P1+P2:\n" << p1;

	Poly<Type>p3(p1);
	std::cout << "New Poly:P3:\n" << p3;

	p3 *= 2;
	std::cout << "P3 *= 2:\n" << p3;
	//p3 = p3 * 2;
	//std::cout<<p3;

	p3 /= 4;
	std::cout << "P3 /= 4:\n" << p3;

	//p3 = p3 /= 4;
	//std::cout << p3;

	Poly<Type>p4 = p3;
	std::cout << "New Poly:P4:\n" << p4;

	p4 -= p3;
	std::cout << "P4-=P3:\n" << p4;

	p4 += p2;
	std::cout << "P4+=P2:\n" << p4;

	p4 = (p4 - p1) * (Type)2;
	std::cout << "P4=(P4-P1)*2:\n" << p4;

	Poly<Type>p5 = p4 - p2;
	std::cout << "New poly P5=P4-P2:\n" << p5;

	p5 = p4*p1;
	std::cout << "P5=P4*P1:\n" << p5;

	p5 *= p1;
	std::cout << "P5*=P1:\n" << p5;


	
	Poly<Type>p6 = p4 / p2;
	std::cout << "New poly P6=P4/P2:\n" << p6;
	
	p6 = p4%p2;
	std::cout << "P6=P4%P2\n" << p6;
	std::cout << "Is P6 a zero!" << (bool)p6 << "\n";

	Poly <Type>p7(7, 8);
	p7[2] = 8;
	p7[4] = 3;
	std::cout << "New poly P7:\n" << p7;
	std::cout << p1;
	p7 %= p1;
	std::cout << "P7%=P1:\n" << p7;
	
}


template<class Type>
void test2()
{
	std::cout << "DEMONSTRATING THE OTHER OPERATOR!:\n";
	Poly<Type> p1(6, 6);
	p1[0] = 2;
	p1[1] = 3;
	p1[2] = 0;
	p1[3] = 2;

	std::cout << "New poly P1:\n" << p1;
	std::cout << "P1(3):" << p1(3) << "\n";
	std::cout << "Integral - [-2,4]:" << p1(2, 4)<<"\n";

	Poly<Type> p2 = p1 * (Type)5;
	std::cout << "P2=P1*5\n" << p2;

	std::cout << "P2(4):" << p2(4) << "\n";
	std::cout << "Integral - [-10,7]:" << p2(1, 7) << "\n";

	Poly<Type> p3 = ++p2;

	std::cout << "New Poly-P3=++p2:\n" << p3;


	std::cout << "New Poly-P3=p2++:\n";
	p3 =p2++;
	std::cout << "P2 is NOW:\n" << p2;

	Poly<Type>p4(4, 10);
	p4[0] = 10;
	p4[1] = 4;
	p4[2] = 6;

	std::cout << "New poly P4:\n" << p4;

	p3 = --p4;
	std::cout << "P3=--P4:\n" << p3;

	std::cout << "P4=P3--:\n";
	p4 = p3--;
	std::cout << "P3 is NOW:\n" << p3;

	Poly<Type>p5(5, 10);

	std::cout << "The coeff under the biggest degree is already fixed- 10!\n";
	std::cout << "New polynom P1:Enter the coeff with spaces and enter when you ready!\n";
	std::cin >> p5;

	std::cout << p5;
	std::cout << "Deg of P1:" << int(p5) << "\n";

	std::cout << "Is P1 a 0" << bool(p5) << "\n";

	std::cout<<"P5==P4:" << (p5 == p4)<<"\n";
	std::cout << "P5>P4:" << (p5 > p4) << "\n";
	std::cout << "P5<P4:" << (p5 < p4) << "\n";
	std::cout << "P5<=P4:" << (p5 <= p4) << "\n";
	std::cout << "P5>=P4:" << (p5 >= p4) << "\n";

}

template<class Type>
void test3()
{
	typedef Poly<int>::Iterator Iter;
	Poly<int>p(4, 10);

	for (Iter it = p.begin(); it != p.end(); ++it)
		std::cout << *it << "\n";


	for (Iter it = p.end()-1; it >= p.begin(); --it)
		std::cout << *it << "\n";

}

int main()
{
	try
	{
		//при size_t е възможно да има превъртане на данните
		//ползвателят трябва да съобрази това
		test1<double>();
		test1<size_t>();
		test1<int>();

		test2<double>();
		test2<int>();
		test2<size_t>();

		test3<double>();
		test3<int>();
		test3<size_t>();


	}
	catch (const std::exception&e)
	{
		std::cout<<e.what();
	}

	return 0;
}