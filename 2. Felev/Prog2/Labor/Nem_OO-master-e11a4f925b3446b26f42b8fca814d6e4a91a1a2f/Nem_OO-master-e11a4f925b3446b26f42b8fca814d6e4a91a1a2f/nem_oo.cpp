#include <cstring>
#include <cctype>
#include "nem_oo.h"

/**
 * \file nem_oo_teszt.cpp
 * (UTF-8 kodolasu fajl. Allitsa at a kodolast,
 *  ha a tovabbi kommentek nem olvashatok helyesen!)
 *
 * FELADATOK:
 *  1. Ebben a fájlban valósítsa meg a nem_oo.h állományban deklarált függvényeket!
 *
 * Ügyeljen a helyes névtér használatra!
 *   Tipp: Használja a scope operátort, vagy nyisson névteret!
 */
namespace sajat
{
     int Pow(int a, int n)
     {
         int result = 1;
         for(int idx = 0; idx < n; ++idx)
            result *= a;
         return result;
     }

     int atoi(const char *p, int base)
     {
         int result = 0;
         int length = 0;

         while(p[length] != '\0' && p[length] != ' ')
         {
             if(isdigit(p[length]) && (int)p[length] - 48 < base)
                ++length;
             else
                throw "Z8WK8D";
         }



         for(int idx = 0; idx < length; ++idx)
         {
             //std::cout << '-' << (length - 1) - idx << std::endl;
             result += ((p[idx]-48) * Pow(base, (length - 1) - idx));
         }

         return result;
     }


    char *strcat(const char *p1, const char *p2)
    {
        int length = strlen(p1) + strlen(p2) + 1;

        char* result = new char[length];

        int resultId = 0;

        for(int idx = 0; idx <= (int)strlen(p1); ++idx, ++resultId)
            result[resultId] = p1[idx];

        --resultId;
        for(int idx = 0; idx < (int)strlen(p2); ++idx, ++resultId)
            result[resultId] = p2[idx];

        result[resultId] = 0;
        return result;
    }


    char *unique(char *first, char *last)
    {
		int length = last - first;
		char *result = new char[length];

		int exactLength = 1;
		char prevChar = first[0];
		int resultId = 0;
		result[resultId] = first[0];


		for(int idx = 1; idx < length; ++idx)
		{
			if(first[idx] != prevChar)
			{
				++resultId;
				prevChar = first[idx];
				++exactLength;
				result[resultId] = first[idx];
			}
		}

    for(int idx = 0; idx < exactLength; ++idx)
    {
        first[idx] = result[idx];
    }

    delete[] result;

    last -= (length - exactLength);
    return last;
}
}
