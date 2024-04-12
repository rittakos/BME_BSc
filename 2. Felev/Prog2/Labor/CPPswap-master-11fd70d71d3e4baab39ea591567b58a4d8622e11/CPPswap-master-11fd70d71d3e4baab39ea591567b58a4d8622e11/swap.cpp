/**
 * \file swap.cpp
 */
#include "swap.h"

 /**
 * swap
 * Két bool adat felcserélése
 * @param a - egyik adat
 * @param b - másik adat
 */
void swap(bool& a, bool& b)
{
	bool temp = a;
	a = b;
	b = temp;
}

/**
* swap
* Két int adat felcserélése
* @param a - egyik adat
* @param b - másik adat
*/
void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

/**
* swap
* Két char adat felcserélése
* @param a - egyik adat
* @param b - másik adat
*/
void swap(char& a, char& b)
{
	char temp = a;
	a = b;
	b = temp;
}
/**
* swap
* Két double adat felcserélése
* @param a - egyik adat
* @param b - másik adat
*/
void swap(double& a, double& b)
{
	double temp = a;
	a = b;
	b = temp;
}
/**
* swap
* Két const char* adat (pointer) felcserélése
* @param a - egyik pointer
* @param b - másik pointer
*/
void swap(const char*& a, const char*& b)  /// Figyelje meg a ref. típus jelölését
{
	const char* temp = a;
	a = b;
	b = temp;
}
