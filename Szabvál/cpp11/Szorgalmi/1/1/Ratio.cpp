#include <iostream>

class Ratio /* rational number */
{       
public:
	Ratio(int num, int den);
	int num() const { return num_; }
	int den() const { return den_; }

	operator double();

private:
	int num_;       /* numerator */
	int den_;       /* denominator */
};

Ratio::Ratio(int num, int den) {
	/* Euclidean: gcd -> a */
	int a = num, b = den, t;
	while (b != 0)
		t = a % b, a = b, b = t;
	num_ = num / a;
	den_ = den / a;
}

Ratio operator+(Ratio r1, Ratio r2) {
	return Ratio(
		r1.num() * r2.den() + r2.num() * r1.den(),
		r1.den() * r2.den());
}

Ratio operator+(Ratio& rat)
{
	Ratio r(rat.num(), rat.den());
	rat = r;
	return rat;
}

std::ostream& operator<<(std::ostream& os, Ratio r) {
	os << r.num() << '/' << r.den();
	return os;
}

Ratio operator-(Ratio& rat)
{
	Ratio r(rat.num() * -1, rat.den());
	rat = r;
	return rat;
}

Ratio operator-(Ratio r1, Ratio r2)
{
	return r1 + (-r2);
}

Ratio operator+=(Ratio& rat1, Ratio rat2)
{
	rat1 = rat1 + rat2;
	return rat1;
}

Ratio operator-=(Ratio& rat1, Ratio rat2)
{
	rat1 = rat1 - rat2;
	return rat1;
}

Ratio operator*(Ratio r1, Ratio r2)
{
	return Ratio(
		r1.num() * r2.num(),
		r1.den() * r2.den());
}

Ratio operator*=(Ratio& rat1, Ratio rat2)
{
	rat1 = rat1 * rat2;
	return rat1;
}

Ratio operator/(Ratio r1, Ratio r2)
{
	return Ratio(
		r1.num() * r2.den(),
		r1.den() * r2.num());
}

Ratio operator/=(Ratio& rat1, Ratio rat2)
{
	rat1 = rat1 / rat2;
	return rat1;
}

std::istream& operator>>(std::istream& is, Ratio& rat)
{
	int num;
	int den;

	char slash;
	is >> num >> slash >> den;
	Ratio r(num, den);

	rat = r;
	return is;
}

Ratio::operator double()
{
	return (double)this->num_ / (double)this->den_;
}

void test()
{
	Ratio r1(1, 2);
	Ratio r2(2, 8);

	//operator+
	Ratio r3 = r1 + r2;
	std::cout << r1 << '+' << r2 << '=' << r3 << '\n';

	//operator+=
	Ratio r4(1, 2);
	r4 += r2;
	std::cout << r4 << '\n';

	//operator-
	-r1;
	std::cout << r1 << '\n';
	-r1;

	//operator-
	std::cout << r1 - r2 << '\n';

	//operator-=
	Ratio r5 = Ratio(1, 1);
	r5 -= r2;
	std::cout << r5 << '\n';

	//operator*
	std::cout << r1 * r1 << '\n';

	//operator*=
	Ratio r6 = Ratio(1, 2);
	r6 *= r1;
	std::cout << r6 << '\n';

	//operator/
	std::cout << r1 / r2 << '\n';

	//operator/=
	Ratio r7 = Ratio(1, 2);
	r7 /= r2;
	std::cout << r7 << '\n';

	//operator>>
	Ratio r8(1, 1);
	std::cin >> r8;
	std::cout << r8 << '\n';

	//operator(double)
	Ratio r9(1, 3);
	std::cout << (double)r9;
}

int main()
{
	//test();
}