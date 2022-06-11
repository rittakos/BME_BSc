# Immutable objektumorientáltság

[Főoldal](oop.md)
<details>
  <summary></summary>

[Fogalmak](terms.md)

[Minták](patterns.md)

[Elvek](principles.md)

[Heurisztikák](heuristics.md)

[Refaktorálás](refactoring.md)

[Clean-code](cleanCode.md)

[API tervezési elvek](APIDesign.md)

[Elosztott objektumorientáltság](distributed.md)

[Konkurens és párhuzamos minták](concurrentParalell.md)

[C++ Idiómák](idioms.md)

</details>

## Tartalom
<details open>
  <summary></summary>

- [Immutable objektumorientáltság](#immutable-objektumorientáltság)
  - [Tartalom](#tartalom)
  - [Immutable objektumok](#immutable-objektumok)
  - [Mutable és Immutable implementációk összehasonlítása](#mutable-és-immutable-implementációk-összehasonlítása)
    - [Mutable lista tömbbel implementálva: List<T>](#mutable-lista-tömbbel-implementálva-listt)
    - [Immutable lista tömbbel implementálva](#immutable-lista-tömbbel-implementálva)
    - [Immutable lista bináris fával: ImmutableList<T>](#immutable-lista-bináris-fával-immutablelistt)
  - [Problémák a módosíthatósággal](#problémák-a-módosíthatósággal)
    - [Readonly/final](#readonlyfinal)
    - [Módosítható érték átadása paraméterként](#módosítható-érték-átadása-paraméterként)
    - [Módosítható értékkel való visszatérés](#módosítható-értékkel-való-visszatérés)
    - [Többszálú elérés](#többszálú-elérés)
    - [Változó identitás](#változó-identitás)
    - [Hiba esetén korrupt belső állapot](#hiba-esetén-korrupt-belső-állapot)
    - [Időbeli csatolás](#időbeli-csatolás)
  - [Immutable objektumok előnyei](#immutable-objektumok-előnyei)
  - [Immutable objektumok implementálása](#immutable-objektumok-implementálása)
  - [Immutable objektumok hátrányai](#immutable-objektumok-hátrányai)
  - [Immutable gyűjtemények .NET-ben](#immutable-gyűjtemények-net-ben)
  - [Immutable vs. mutable gyűjtemények](#immutable-vs-mutable-gyűjtemények)
    - [Immutable vs. mutable gyűjtemények komplexitása](#immutable-vs-mutable-gyűjtemények-komplexitása)
    - [Immutability vs. mutability tanulság](#immutability-vs-mutability-tanulság)

</details>

---

## Immutable objektumok
Egy objektumot akkor nevezünk immutable-nek, ha az állapotát a létrehozás után már nem tudjuk módosítani. 

Előnye:
- szálbiztosak
  
Használata:
- módosítás helyett egy új immutable objektumot kell létre hozni, lemásolva a régit


## Mutable és Immutable implementációk összehasonlítása

<details>
  <summary></summary>

### Mutable lista tömbbel implementálva: List<T>
- az elemeket tároló tömb nagyobb, mint ahány elem ténylegesen van
- amikor ez betelik, akkor megduplázzuk a méretét, átmásoljuk, és így már lesz hely
- átlagosan új elem hozzáadás időigénye konstans
- adott indexű elem lekérése konstans idejű
- a beszúrás és törlés lineáris
  
### Immutable lista tömbbel implementálva
- a tömböt egyesével növelgjük és másoljuk
- elem hozzáadása lineáris idejű
- a többi művelet komplexitása nem változik
- rosszabb megoldás
  
### Immutable lista bináris fával: ImmutableList<T>
- elem hozzáadása a fának a bővítését jelenti
- elem hozzáadása logaritmikus komplexitásúvá
- az indexelés logaritmikus
- beszúrás és törlés logaritmikus válik,
- nem rossz, olykor jobb lehet

</details>

## Problémák a módosíthatósággal 

<details>
  <summary></summary>

### Readonly/final
- nem garantálják azt, hogy az objektum csak olvasható, csak hogy az objektumra mutató referencia nem módosítható

### Módosítható érték átadása paraméterként
- semmi nem garantálja azt, hogy a függvény, amit meghívtunk, nem fogja elrontani a paraméterként beadott objektum állapotát

### Módosítható értékkel való visszatérés
- a külvilág bármikor belenyúlhat és elronthatja a mi állapotunkat
- másolatot adhatunk vissza

### Többszálú elérés
- egyszerre módosításnál probléma merül fel

### Változó identitás
- változik az objektumok identitása, ugyanis az objektumok hash-kódja belső állapothoz kötött

### Hiba esetén korrupt belső állapot
-a belső állapot inkonzisztensé válhat kivétel keletkezése során

### Időbeli csatolás
- nem mindegy, hogy melyik függvényt melyik függvény után hívunk, mert a hívások más sorrendben történő intézésének más lesz az eredménye

</details>


## Immutable objektumok előnyei

- könnyű létrehozni, tesztelni és használni
- szálbiztos
- nincs szükség klónozásra és copy-konstuktorra
- mellékhatásmentesség
- identitás nem változik
- könnyű cache-elni
- nincs korrupt állapot
- megelőzhetők a null-referenciák
- elkerülhető az időbeli csatolás

## Immutable objektumok implementálása

Az immutable objektum implementálása hosszabb mutable verziójuknál.

[C++ példa.](ImmutableCodes/immutable.cpp)
Ki lehet egészíteni egy [Builderrel](patterns.md/#builder), a kényelmesebb használathoz.


## Immutable objektumok hátrányai 

- túl sok kód
- kényelmetlen szintaxis
- nem lehet körkörös referencia
- változásokkal kapcsolatos hátrányok

## Immutable gyűjtemények .NET-ben 

Struktúra típusú gyűjtemény:
- ImmutableArray<T>
  
Osztály típusú gyűjtemény:
- ImmutableStack<T>
- ImmutableQueue<T>
- ImmutableList<T>
- ImmutableHashSet<T>
- ImmutableSortedSet<T>
- ImmutableDictionary<K, V>
- ImmutableSortedDictionary<K, V>

## Immutable vs. mutable gyűjtemények

Az immutable gyűjtemények hatékonyabbak is tudnak lenni, mint a módosítható változataik.


<details>
  <summary></summary>

### Immutable vs. mutable gyűjtemények komplexitása 

<p align="center">
    <img src="ImmutableImages/vs.png" />
</p>

### Immutability vs. mutability tanulság

- használjunk immutable objektumokat amikor csak lehet
- módosítható objektumok akkor előnyösek, hogyha sok, és gyakori változtatásra van szükség
- módosítható objektumokat nehezebb többszálú környezetben biztonságosan használni

</details>