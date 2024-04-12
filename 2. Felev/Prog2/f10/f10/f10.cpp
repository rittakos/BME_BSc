// f10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include "f_10.h"

using std::cout;
using std::endl;
using std::cin;

F10 fv(F10 f, int n) {
	F10 a = f;
	if (n)
		a = fv(f, n - 1);
	return a;
}

int main() {
	F10 a, c;

	cout << a.ident() << endl;
	cout << a.match("xxa asalapja as \n") << endl;
	for (int i = 0; i < 5; i++) {
		F10 b = a;
		cout << b.match(" dolgoznia ") << endl;
	}
	F10 b = a;
	a = a;
	c = b;

	// kicsit nyuzzuk...

	c = fv(c, 100);

	cout << c.getLine();
	return 0;
}

