# Tervezési Minták

[Főoldal](#oop.md)
<details open>
  <summary></summary>

[Fogalmak](terms.md)

[Elvek](principles.md)

[Heurisztikák](heuristics.md)

[Refaktorálás](refactoring.md)

[Clean-code](cleanCode.md)

[API tervezési elvek](APIDesign.md)

[Elosztott objektumorientáltság](distributed.md)

[Konkurens és párhuzamos minták](concurrentParalell.md)

[Immutable objektumorientáltság](immutable.md)

</details>

## Tartalom
<details open>
  <summary></summary>

- [Tervezési Minták](#tervezési-minták)
  - [Tartalom](#tartalom)
  - [Composite](#composite)
  - [Observer](#observer)
  - [Singleton](#singleton)
  - [Strategy](#strategy)
  - [Proxy](#proxy)
  - [Abstract Factory](#abstract-factory)
  - [Factory Method](#factory-method)
  - [Adpater](#adpater)
  - [Memento](#memento)
  - [Visitor](#visitor)

</details>

---

## Composite

<details>
  <summary></summary>

Cél:
- Rész-egész viszonyban lévő objektumokat fastruktórába rendez
- A kliensek számára lehetővé teszi, hogy az egyszerű és összetett(kompozit) objektumokat egységesen kezelje egy interface-en keresztül

Példa: Olyan grafikus alkalmazás, amely lehetővé teszi összetett grafikus objektumok létrehozását

</details>

## Observer

<details>
  <summary></summary>

Cél:
- Egy objektum állapotának megváltozásáról értesít más objektumokat
- Nincsen függőség, maguk az osztályok között (csak az observer-ekkel)

Példa: MVC vagy Document-View

Működés: Egy osztály eltárolja azokat az Observer-eket (interface), amiket értesíteni kell. Ezek értesítésére késpes az osztály. A különböző observer-ek ismerik a megfelelő adatszerkezeti osztályokat és le tudják kérni valamint módosítani azokat.

</details>

## Singleton

<details>
  <summary></summary>

Cél:
- Biztosítja, hogy egy osztályból 1 példány legyen, és azt globálisan el lehessen érni

Magyarázat:

```
class Singleton
{ 
private:
    static Singleton* instance; 
 protected:   
    Singleton() { } 

public: 
    Singleton(Singleton &other) = delete;
    void operator=(const Singleton &) = delete;
    static Singleton *GetInstance();

    void doSomething() {}
 }

Singleton* Singleton::instance= nullptr;

Singleton *Singleton::GetInstance(c) 
{ 
    if(instance == nullptr)
    { 
        instance = new Singleton(); 
    } 
    return instance; 
}
```

```
Singleton* instance = Singleton::GetInstance();
instance->doSomething();
```

</details>

## Strategy

<details>
  <summary></summary>

Cél: 
- Algoritmusok egységbe zárása, egyszerűen ki lehessen őket cserélni

Példa:

</details>

## Proxy

<details>
  <summary></summary>

Cél:
- Objektum helyett egy transzparens helyettesítő objektumot használ, mely szabályozza a hozzáférést

Példa: Jogosultságok korlátozása, erőforrás igényes műveletek csak akkor legyenek végrehajtva ha muszály

Magyarázat: A Proxy és az Objektum közös őssel rendelkezik, amit ismer a cliens. A cliens a proxy függvényein keresztül módosítja (akár törli és létrehozza) és lekérdezi a valódi objektumot

</details>

## Abstract Factory

<details>
  <summary></summary>

Cél:
- Interfészt biztosít ahhoz, hogy egymással összefüggő objektumok családjait hozzuk létre konkrét osztály specifikálása nélkül
- Létrehozás egy interfészen keresztül történik, nem függ a létrehozott objektumok konkrét típusától.



Példa: 
- Ablakos rendszerek, GUI vezérlőelemek

</details>

## Factory Method

<details>
  <summary></summary>

Cél:
- Interfészt definiál objektum létrehozására, de a leszármazott osztályra hagyja a konkrét osztály eldöntését

</details>

## Adpater

<details>
  <summary></summary>

Cél:
- Osztály interfészét olyanná változtatja, amilyet a kliens vár
- Lehetővé teszi egyébként inkompatibilis osztályok együttműködését

Object Adapter: Megoldás delegációval

Class Adapter: Megoldás leszármazással

</details>

## Memento

<details>
  <summary></summary>

Cél: 
- Egységbezárás megsértése nélkül a külvilág számára elérhetővé tenni az objektum belső állapotát
- Célszrű elmenti az objektun állapotát Undo parancshoz

Egy memento objektum készül az aktuális állapotból

</details>

## Visitor

<details>
  <summary></summary>

Cél: 
- h

</details>