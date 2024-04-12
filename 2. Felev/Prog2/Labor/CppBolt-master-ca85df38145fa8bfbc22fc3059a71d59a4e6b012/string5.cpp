/**
 *
 * \file string5.cpp
 *
 * Itt kell megvalósítania a hiányzó tagfüggvényeket.
 * Segítségül megadtuk a C++ nem OO eszközeinek felhasználásával készített String-kezelő
 * függvényke neveit.
 *
 * Ha valamit INLINE-ként valósít meg, akkor annak a string5.h-ba kell kerülnie,
 * akár kívül akár osztályon belül definiálja. (Az inline függvényeknek minden
 * fordítási egységben elérhetőknek kell lenniük)
 * *
 * A teszteléskor ne felejtse el beállítani a string5.h állományban az ELKESZULT makrót.
 *
 */

#ifdef _MSC_VER
// MSC ne adjon figyelmeztető üzenetet a C sztringkezelő függvényeire
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>             // Kiíratáshoz
#include <cstring>              // Sztringműveletekhez

#include "memtrace.h"           // a standard headerek után kell lennie
#include "string5.h"


/// Konstruktorok: egy char karakterből (createString)
String::String(char ch)
    {
        this->len = 1;
        this->pData = new char[this->len + 1];
        this->pData[0] = ch;
        this->pData[1] = '\0';
    }


///                egy nullával lezárt char sorozatból (createString)
String::String (const char* str)
    {
        this->len = strlen(str);
        this->pData = new char[this->len + 1];
        strcpy(this->pData, str);
        this->pData[this->len] = '\0';
    }

/// Másoló konstruktor: String-ből készít (createString)
String::String(const String& str)
{
    this->len = str.len;
    this->pData = new char[this->len + 1];
    strcpy(this->pData, str.pData);

}




/// Destruktor (disposeString)

String::~String()
{
    delete[] this->pData;
}


/// operator=

String& String::operator=(const String& str)
{
    if(this == &str)
        return *this;

    delete[] this->pData;
    this->len = str.len;
    this->pData = new char[this->len + 1];
    strcpy(this->pData, str.c_str());

    return *this;
}

/// [] operátorok: egy megadott indexű elem REFERENCIÁJÁVAL térnek vissza (charAtString)
/// indexhiba esetén const char * kivételt dob!

char String::operator[](int idx) const
{
    if(idx < 0 || idx >= (int)this->len)
        throw "String: túlindexelés";

    return this->pData[idx];
}

char& String::operator[](int idx)
{
    if(idx < 0 || idx >= (int)this->len)
        throw "String: túlindexelés";

    return this->pData[idx];
}

/// + operátorok:
///                 String-hez jobbról karaktert ad (addString)
String String::operator+(const char ch)
{

    String result;
    delete[] result.pData;
    result.len = this->size() + 1;
    result.pData = new char[result.len + 1];
    strcpy(result.pData, this->pData);
    result[result.len - 1] = ch;
    result.pData[result.len] = '\0';

    return result;
}
///                 String-hez String-et ad (addString)
String String::operator+(String str)
{
    String result;
    delete[] result.pData;
    result.len = this->size() + str.size();
    result.pData = new char[result.len + 1];
    strcpy(result.pData, this->pData);
    strcat(result.pData, str.pData);

    return result;
}

String String::operator+(const String str) const
{
    String result;
    delete[] result.pData;
    result.len = this->size() + str.size();
    result.pData = new char[result.len + 1];
    strcpy(result.pData, this->pData);
    strcat(result.pData, str.pData);

    return result;
}

String operator+(char ch, String str)
{

    size_t l = 1 + str.size();
    char* st = new char[l + 1];
    st[0] = ch;
    st[1] = '\0';
    strcat(st, str.c_str());

    String result(st);
    delete[] st;
    return result;
}

/// << operator, ami kiír az ostream-re

std::ostream& operator<<(std::ostream& os, String&  str)
{
    os << str.c_str();
    return os;
}

/// >> operátor, ami beolvas az istream-ről egy szót
