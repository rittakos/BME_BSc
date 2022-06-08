# Clean-code elvek

[Főoldal](oop.md)
<details>
  <summary></summary>

[Fogalmak](terms.md)

[Minták](patterns.md)

[Heurisztikák](heuristics.md)

[Refaktorálás](refactoring.md)

[Clean-code](cleanCode.md)

[API tervezési elvek](APIDesign.md)

[Elosztott objektumorientáltság](distributed.md)

[Konkurens és párhuzamos minták](concurrentParalell.md)

[Immutable objektumorientáltság](immutable.md)

[C++ Idiómák](idioms.md)

</details>


## Tartalom
<details open>
  <summary></summary>

- [Clean-code elvek](#clean-code-elvek)
  - [Tartalom](#tartalom)
  - [Clean Code](#clean-code)
  - [Kifejező nevek írása](#kifejező-nevek-írása)
    - [Az osztálynevek főnév jellegűek legyenek!](#az-osztálynevek-főnév-jellegűek-legyenek)
    - [A függvénynevek ige jellegűek legyenek!](#a-függvénynevek-ige-jellegűek-legyenek)
    - [Használjuk az alkalmazási terület elnevezéseit](#használjuk-az-alkalmazási-terület-elnevezéseit)
    - [Használjunk beszédes neveket!](#használjunk-beszédes-neveket)
    - [Kerüljük a félreinformálást!](#kerüljük-a-félreinformálást)
    - [Használjunk megkülönböztető neveket](#használjunk-megkülönböztető-neveket)
    - [Használjunk kimondható neveket!](#használjunk-kimondható-neveket)
    - [Használjunk kereshető neveket!](#használjunk-kereshető-neveket)
    - [Kerüljük a névkódolást!](#kerüljük-a-névkódolást)
    - [Használunk a hatókörnek megfelelő hosszúságú nevet!](#használunk-a-hatókörnek-megfelelő-hosszúságú-nevet)
    - [Adott dologra mindig ugyanazt a nevet használjuk!](#adott-dologra-mindig-ugyanazt-a-nevet-használjuk)
    - [Biztosítsunk értelmes kontextust a változóknak!](#biztosítsunk-értelmes-kontextust-a-változóknak)
    - [Kerüljük az értelmetlen kontextust!](#kerüljük-az-értelmetlen-kontextust)
  - [Függvényekkel kapcsolatos clean code szabályok](#függvényekkel-kapcsolatos-clean-code-szabályok)
    - [A függvények legyenek rövidek](#a-függvények-legyenek-rövidek)
    - [A blokkok belseje egyetlen sor legyen!](#a-blokkok-belseje-egyetlen-sor-legyen)
    - [Egy függvény egyszerre csak egy dolgot csináljon!](#egy-függvény-egyszerre-csak-egy-dolgot-csináljon)
    - [Egy függvény egyszerre csak egy absztrakciós szinten dolgozzon!](#egy-függvény-egyszerre-csak-egy-absztrakciós-szinten-dolgozzon)
    - [A függvények lépcsőzetesen, az absztrakciós szinteket fokozatosan kibontva kövessék egymást!](#a-függvények-lépcsőzetesen-az-absztrakciós-szinteket-fokozatosan-kibontva-kövessék-egymást)
    - [Kerüljük a mellékhatásokat!](#kerüljük-a-mellékhatásokat)
    - [Válasszuk szét a parancs és a lekérdezés jellegű függvényeket!](#válasszuk-szét-a-parancs-és-a-lekérdezés-jellegű-függvényeket)
  - [Kommentek írása és elhagyása](#kommentek-írása-és-elhagyása)
    - [Kommentek használata](#kommentek-használata)
    - [Motyogás](#motyogás)
    - [Redundáns komment, Félrevezető komment](#redundáns-komment-félrevezető-komment)
    - [Ideges komment](#ideges-komment)
    - [Banner jellegű kommentek](#banner-jellegű-kommentek)
    - [Blokkzáró kommentek](#blokkzáró-kommentek)
    - [Kikommentezett kód](#kikommentezett-kód)
    - [Napló jellegű kommentek](#napló-jellegű-kommentek)
    - [Szerzőt hirdető kommentek](#szerzőt-hirdető-kommentek)
    - [HTML kommentek](#html-kommentek)
    - [Nemlokális információ kommentben](#nemlokális-információ-kommentben)
    - [Túl sok információt tartalmazó komment](#túl-sok-információt-tartalmazó-komment)
    - [Hiányzó kapcsolat kommentben](#hiányzó-kapcsolat-kommentben)
    - [Informatív kommentek](#informatív-kommentek)
    - [Szándék, illetve tervezői döntés magyarázatát tartalmazó komment](#szándék-illetve-tervezői-döntés-magyarázatát-tartalmazó-komment)
    - [Tisztázó kommentek](#tisztázó-kommentek)
    - [Figyelmeztetés a következményre a kommentben](#figyelmeztetés-a-következményre-a-kommentben)
    - [TODO kommentek](#todo-kommentek)
    - [Hangsúlyozó kommentek](#hangsúlyozó-kommentek)
  - [Publikus API dokumentálása](#publikus-api-dokumentálása)
    - [Publikus API dokumentálásának tartalma](#publikus-api-dokumentálásának-tartalma)
  - [Kivételek definiálása és kezelése](#kivételek-definiálása-és-kezelése)
    - [Hibakódok helyett használjunk kivételeket!](#hibakódok-helyett-használjunk-kivételeket)
    - [Biztosítsunk kontextust a kivételhez!](#biztosítsunk-kontextust-a-kivételhez)
    - [Használjunk uchecked (runtime) kivételeket!](#használjunk-uchecked-runtime-kivételeket)
    - [A kivételeket mindig a hívó szemszögéből definiáljuk!](#a-kivételeket-mindig-a-hívó-szemszögéből-definiáljuk)
    - [Ne térjünk vissza null értékkel!](#ne-térjünk-vissza-null-értékkel)
    - [Ne adjunk át paraméterként null értéket!](#ne-adjunk-át-paraméterként-null-értéket)
    - [Bejövő paraméterek ellenőrzése](#bejövő-paraméterek-ellenőrzése)
  - [Objektumok és adatstruktúrák](#objektumok-és-adatstruktúrák)
    - [Procedurális fejlesztés vs objektumorientált fejlesztés választása](#procedurális-fejlesztés-vs-objektumorientált-fejlesztés-választása)

</details>

---

## Clean Code

- kódot többet olvasunk, mint írunk (10:1)
- általános szabályok
- tartsuk mindig tisztán a kódot

Jellemzői:
- könnyű olvasni
- könnyű megérteni
- elegánsan fejezi ki magát
- hatékony
- kevés függőséggel rendelkezik
- minden lehetséges hibát lekezel
- egyetlen dologra fókuszál, és azt jól csinálja
- könnyen továbbfejleszthető

Rossz kód:
- nehéz olvasni
- nehéz megérteni
- nehéz karbantartani
  

## Kifejező nevek írása

### Az osztálynevek főnév jellegűek legyenek!

<details>
  <summary></summary>

- kerüljük az általános neveket (Manager, Data, Processzor, Info)
- minél specifikusabb nevek
- ne legyen ige, kivéve ha a viselkedést szándékosan kiszervezzük([Visitor](patterns.md/#visitor), [Strategy](patterns.md/#strategy))

</details>

### A függvénynevek ige jellegűek legyenek!

<details>
  <summary></summary>

- függvények tevékenységet hajtanak végre
- függvény neve egy ige, vagy főnév-ige kombináció

</details>

### Használjuk az alkalmazási terület elnevezéseit

### Használjunk beszédes neveket!

### Kerüljük a félreinformálást!

### Használjunk megkülönböztető neveket

### Használjunk kimondható neveket!

### Használjunk kereshető neveket!

### Kerüljük a névkódolást!

<details>
  <summary></summary>

- kerülendő a hungarian notation
- ne használjunk prefixeket és suffixeket
- megsérthető ha indokolt

</details>

### Használunk a hatókörnek megfelelő hosszúságú nevet!

### Adott dologra mindig ugyanazt a nevet használjuk!

### Biztosítsunk értelmes kontextust a változóknak!

<details>
  <summary></summary>

- a kontextus biztosítson elég információt ahhoz, hogy a név jelentése egyértelmű legyen

</details>

### Kerüljük az értelmetlen kontextust!

## Függvényekkel kapcsolatos clean code szabályok

### A függvények legyenek rövidek

<details>
  <summary></summary>

-  2-4, max 20 sor

</details>

### A blokkok belseje egyetlen sor legyen!

<details>
  <summary></summary>

-  ha sokkal hosszabb szervezzük ki függvénybe

</details>

### Egy függvény egyszerre csak egy dolgot csináljon!

### Egy függvény egyszerre csak egy absztrakciós szinten dolgozzon!

### A függvények lépcsőzetesen, az absztrakciós szinteket fokozatosan kibontva kövessék egymást!

### Kerüljük a mellékhatásokat!

### Válasszuk szét a parancs és a lekérdezés jellegű függvényeket!

<details>
  <summary></summary>

- csináljon valamit, vagy válaszoljon egy kérdésre

</details>

## Kommentek írása és elhagyása

### Kommentek használata

- kifejezünk olyasmit, amit kódban nem tudunk kifejezni
- hasznosak tudnak lenni, de ha rosszul használjuk félrevezetőek és károsak lehetnek
- egyetlen hiteles információforrás a programkód
- nem kommentekkel kell dokumentálni a kódot, hanem a programkód saját olvashatósága révén dokumentálja magát

### Motyogás

- nem derül ki a komment pontos jelentése
- rossz

### Redundáns komment, Félrevezető komment

- rossz

### Ideges komment

- rossz

### Banner jellegű kommentek

- rossz

### Blokkzáró kommentek

- nem rossz, de ne legyen rájuk szükség

### Kikommentezett kód

- rossz

### Napló jellegű kommentek

- meh, verziókezelés is létezik


### Szerzőt hirdető kommentek

- meh, van rá jobb eszköz (verziókezelés)

### HTML kommentek

- meh

### Nemlokális információ kommentben

- rossz

### Túl sok információt tartalmazó komment

- rossz

### Hiányzó kapcsolat kommentben

- rossz

### Informatív kommentek

- jó, de áltálában meg lehet máshogy oldani

### Szándék, illetve tervezői döntés magyarázatát tartalmazó komment

- jó és javasolt

### Tisztázó kommentek

- jó, de tartsuk karban

### Figyelmeztetés a következményre a kommentben

- jó

### TODO kommentek

- jó, de lehet rá jobb eszköz

### Hangsúlyozó kommentek

- jó

## Publikus API dokumentálása

- nagyon fontos
- kommentezzük a publikus tagokat
- legyen karban tartva

### Publikus API dokumentálásának tartalma
- mit csinál az adott osztály vagy függvény
- melyik paraméter mit jelent
- paraméterek értékkészlete
- függvények előfeltételei is és utófeltételei
- osztály invariánsai
- milyen kivételeket dobálhat
- melyik függvény szálbiztos, és melyik nem
- példakód
- hatékonyság

## Kivételek definiálása és kezelése

### Hibakódok helyett használjunk kivételeket!

- catch blokkok csak hibakezelést tartalmazzanak, az alkalmazáslogika a try blokkokba való

### Biztosítsunk kontextust a kivételhez!

- legyen benne a kivételben, hogy melyik fájlban és hol keletkezett, mi a hiba oka, hogyan lehet elkerülni
- legyen naplózható, és az alapján rekonstruálható

### Használjunk uchecked (runtime) kivételeket!

### A kivételeket mindig a hívó szemszögéből definiáljuk!

### Ne térjünk vissza null értékkel!

- használjuk a [Null object](patterns.md/#null-object) tervezési mintát

### Ne adjunk át paraméterként null értéket!

- kivéve akkor, ha az API explicit megengedi

### Bejövő paraméterek ellenőrzése

## Objektumok és adatstruktúrák

| Procedurális fejlesztés     | Objektumorientált fejlesztés           |
| --------------------------- |:--------------------------------------:|
| a fókuszban az adat áll     | a fókuszban a viselkedés áll           |
| viselkedést függvényekben implementáljuk, paraméterként kapják az adatokat      | adatreprezentáció el van rejtve     |
| könnyű új függvényt hozzáadni anélkül, hogy változtatnánk az adatstruktúrán
 | könnyű megváltoztatni a belső adatreprezentációt anélkül, hogy a külső interfész változna      |
| nehéz megváltoztatni az adatstruktúrát, mert az minden függvényre hatással lehet
| nehéz megváltoztatni a publikus interfészt, mert az egész öröklési hierarchiára, és minden hívóra kihathat|
|stabil, ritkán változó adatstruktúrát kíván|stabil viselkedést kíván, a működés kibővítését leszármazással és delegációval valósítjuk meg|

### Procedurális fejlesztés vs objektumorientált fejlesztés választása

- követelményektől és körülményektől függ, melyiket érdemes választani
- amit az objektumorientált stílusban nehéz megcsinálni, azt a procedurálisban könnyű, és fordítva
- komplex alkalmazás estén keveredhetnek=
- adatbázisok és hálózati kommunikáció esetén az adatok dominálnak
- üzleti logikát érdemes objektumorientált stílusban fejleszteni