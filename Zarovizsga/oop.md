# OOP

A BME VIK Mérnökinformatikus BSc képzésének objektum orientált szoftverfejlesztés tárgyának jegyzete, záróvizsgához.

## Tartalom
<details open>
  <summary></summary>

- [OOP](#oop)
  - [Tartalom](#tartalom)
  - [Kérdések](#kérdések)
  - [Alapfogalmak](#alapfogalmak)
  - [Kapcsolatok](#kapcsolatok)
  - [Tervezési elvek](#tervezési-elvek)
    - [SOLID elvek](#solid-elvek)
      - [Single Responsibility](#single-responsibility)
      - [Open/Closed Principle](#openclosed-principle)
      - [Liskov Substitution Principle](#liskov-substitution-principle)
      - [Interface Segregation Principle](#interface-segregation-principle)
      - [Dependency Inversion Principle](#dependency-inversion-principle)
    - [Egyéb elvek](#egyéb-elvek)
      - [Release Reuse Equivalency Principle](#release-reuse-equivalency-principle)
      - [Common Closure Principle](#common-closure-principle)
      - [Common Reuse Principle](#common-reuse-principle)
      - [Acyclic Dependencies Principle](#acyclic-dependencies-principle)
      - [Stable Dependencies Principle](#stable-dependencies-principle)
      - [Stable Abstractions Principle](#stable-abstractions-principle)
      - [Don’t Repeat Yourself](#dont-repeat-yourself)
      - [Single Choice Principle](#single-choice-principle)
      - [Tell, don’t ask](#tell-dont-ask)
      - [Law of Demeter](#law-of-demeter)
  - [Tervezési minták](#tervezési-minták)
  - [Heurisztikák](#heurisztikák)
  - [Refaktorálás](#refaktorálás)
  - [Clean-code elvek](#clean-code-elvek)
  - [API tervezési elvek](#api-tervezési-elvek)
  - [Elosztott objektumorientáltság](#elosztott-objektumorientáltság)
  - [Konkurens és párhuzamos minták](#konkurens-és-párhuzamos-minták)
  - [Immutable objektumorientáltság](#immutable-objektumorientáltság)

</details>

---

## Kérdések

<details open>
  <summary></summary>

- Tervezés a követelmények változására tekintettel, OO tervezési elvek. Az egyes elvekre: Milyen problémát old meg az adott elv? Mi a megoldás lényege? Miért baj, ha megsértjük? Mikor lehet megsérteni?
  
        valasz

- OO tervezési heurisztikák. Az egyes heurisztikákra: Milyen problémát old meg az adott heurisztika? Mi a megoldás lényege? Miért baj, ha megsértjük? Mikor lehet megsérteni? Hogyan kapcsolódik a refaktorálási mintákhoz és code-smell-ekhez?
  
- Refaktorálás fogalma, szabályai, előnyei és problémái. Milyen refaktorálási minták és code-smell-ek vannak? Hogyan kapcsolódnak egymáshoz? Hogyan kapcsolódnak az OO tervezési heurisztikákhoz?
  
- Clean-code elvek. Az egyes elvekre: Milyen problémát old meg az adott elv? Mi a megoldás lényege? Miért baj, ha megsértjük? Mikor lehet megsérteni?
  
- API tervezési elvek. Az egyes elvekre: Milyen problémát old meg az adott elv? Mi a megoldás lényege? Miért baj, ha megsértjük? Mikor lehet megsérteni?
  
- Elosztott objektumorientáltság. Milyen problémákat vet fel? Milyen megoldási lehetőségek vannak?
  
- Konkurens és párhuzamos minták. Az egyes mintákra: Milyen problémát old meg az adott minta? Mi a megoldás lényege? Hogyan kapcsolódik más mintákhoz?
  
- Immutable objektumorientáltság. Mik a módosíthatóság problémái? Mik a csak olvasható objektumok előnyei és hátrányai? Hogyan kell implementálni egy csak olvasható objektumot leíró osztályt?


</details>

--- 

## Alapfogalmak

Az alábbi fogalmak vázlatosan vannak definiálva. Alapos ismeretük elengedhetetlen a továbbiakban.

<details open>
  <summary></summary>

__Class__: Típus

__Object__: Példány

__Static__: Típushoz (class-hoz) tartozik (pl.: változó vagy függvény)

__Abstraction__: A kontextusban nem fontos részletek elhagyása, a való világ modellezése

__Classification__:  Közös tulajdonság alapján történő csoportosítás

__Encapsulation__:  Egységbezárás, egy osztály adattagjait nem lehet kívülről elérni, csak az erre a célra készített függvényeken keresztül

__Inheritance__:  Leszármazás, a leszármazott osztály tudja használni őse viselkedését, nem az adatait

<p align="center">
    <img src="inheritance.png" width="50"/>
</p>


__Polymorphism__: A hívó felől el van rejtve az objektum típusa, annyi ismert, hogy egy adott osztály leszármazottja

__Visibility__: Láthatóság

__Virtual method__: A virtuális függvények felülírhatóak a leszármazottakban, ezzel módosítva a leszármazottak viselkedését

__Abstract method__: Nem rendelkezik implementációval

__Abstract class__: Olyan osztály amit nem lehet példányosítani. Általában van abstract függvénye

__Interface__: Egy olyan függvényhalmaz amik nincsenek implementálva. Az interface-t megvalósító osztályoknak kell ezeket implementálni. Egyes nyelvekben nincs külön interface, helyette abstract osztályok és függvények (tisztán virtuális függvény) használhatóak

__Interface of a class__: Egy osztály publikus függvényeinek halmaza

__Coupling__: Az összefüggések mértéke. Minél alacsonyabb annál jobb. Az összefüggés azt vonja maga után, hogy ha az egyik rész változik, akkor a másiknak is változnia kell.

__Cohesion__: Annak mértéke, hogy egy adott egységen belül mennyir illenek (logikailag) egymáshoz a részek. Minél magasabb annál jobb

</details>

--- 

## Kapcsolatok

Modulok vagy osztályok között előforduló kapcsolatok.

<details open>
  <summary></summary>

__Dependency__: Két elem függőségét fejezi ki a nyíl irányába (függő felé mutat). Az egyik módosulása maga után vonhatja a másikét

<p align="center">
    <img src="dependency.png" width="200"/>
</p>

__Association__: Gyenge ismeretség a nyíl irányába

<p align="center">
    <img src="association.png" width="200"/>
</p>

__Aggregation__: Két objektum élettartalma között fellépő gyenge kapcsolat. Erősebb mint az Association de gyengébb mint a Composition

<p align="center">
    <img src="aggregation.png" width="200"/>
</p>

__Composition__: Két objektum élettartalma között fellépő erős kapcsolat. Az egyik megszűnése a másik megsemmisítését vnaj maga után

<p align="center">
    <img src="composition.png" width="200"/>
</p>

__Generalization/Inheritance__: Leszármazás. Az ős viselkedését örökli a leszármazott

<p align="center">
    <img src="inheritance2.png" width="200"/>
</p>

__Realization/Implementation__: Megvalósítás

<p align="center">
    <img src="implementation.png" width="200"/>
</p>

</details>

---

## Tervezési elvek

Olyan tervezési irányelvek és minták amik betartása könnyebben fentarthatóvá és továbbfejleszthetővét teszik a kódot.

A folyamatosan változó követelmények lekövetéséhez remek eszköz. 

Egy rosszul tervezett rendszer:
- Nehzen lehet megváltoztatni, mert egy változtatás sok másik részre van hatással (rigidity)
- A változtatás nem várt részekre hat (fragility)
- Az egyes részeket nehezen lehet önállóan újrahasznosítani (immobility)

Megoldás lehet:
- Függőségek csökkentése
- A függőségek a ritkán változó, stabil részekhez kötődjenek

### SOLID elvek

A SOLID öt fontos elvet jelöl, mindegyik betűje egyre utal. Segítenek csökkenteni a függőséget és növelik a kódbázis fenntarthatóságát.

#### Single Responsibility

<details>
  <summary></summary>

"A class should have only one reason to change"

Minden osztálynak pontosan egy felelőssége (feladata) legyen. Ha több van, azt szét kell osztani.

A szétválasztás több szinten történhet. Implementációs szinten ez két külön álló osztályra bontást jelent. Ha ez nem megoldható, akkor lehet interface szinten végezni a szétválasztást, ekkor a megfelelő interface-eket létre kell hozni, amiket aztán megvalósít az osztályunk.

Nem mindig egyértelmű, hogy egy osztály több okból változhat (több felelőssége van). Fontos elv a YAGNI (You Ain’t Gonna Need It), vagyis, hogy ha valami nem fordul elő, arra nem kell tervezni.

</details>

#### Open/Closed Principle

<details>
  <summary></summary>

"Software entities (classes, modules, functions etc.) should
be open for extension, but closed for modification.
"

Egy entitásnak nyíltnak kell lennie a kiegészítésre, de zártnak a módosításra.

Az entitás viselkedését meg lehessen változtatni, hogy ezzel követni tudja a követelményeket.

A kiegészítés ne vonja maga után a már létező forráskód módosulását.

</details>

#### Liskov Substitution Principle

<details>
  <summary></summary>

"Subtypes must be substitutable for their base types"

A leszármazottakat be kell tudni helyettesíteni az őseik helyére, anélkül, hogy ezt a felhasználó észrevenné.

Leszármazás:
- Ami igaz az ősre, az igaz a leszármazottaira is
- Az őse általánosabb a leszármazottnál
- A leszármazott specifkusabb az ősnél
- Bárhol ahol az ős használható, használható a leszármazott

Megsértése típusellenőrzést vonhat maga után és általában az Open/Closed Principle megsértéséhez is vezet.

__Soha ne használjunk leszármazást adat újrahasznosítási céllal! Használjuk a viselkedés újrahasznosítására!__


Függvény Előfeltételek: 
- Feltételei a függvényhívásnak
- pl.: fügvény paramétereinek értékkészlete

Függvény Utófeltételek:
- A függvényhívás után fennálló feltételek
- pl.: fügvény visszatérésének értékkészlete

Osztály Invariánsok (invariants):
- Kényszerek, amiket az osztálynak minden állapotban be kell tartania
- Az osztály saját metódusaival biztosítja őket

Leszármazott függvény előfeltétele nem lehet erősebb őse előfeltételénél és utófeltétele nem lehet gyengébb őse utófeltételénél! Invariánsok erősíthetőek, de nem gyengíthetőek a leszármazottakban!

"Expect no more, provide no less. / Demand no more, promise no less."

A Liskov elv betartása sokszor nem triviális és átfogóbb vizsgálatokat igényelhet.

</details>

#### Interface Segregation Principle

<details>
  <summary></summary>

"Clients should not be forced to depend on methods they
do not use"

Az interface-eket szét kell osztani többm, kisebb és specifikusabb interface-re, hogy a felhasználó tudja csak azt használni, amire tényleg szüksége van.

Ne merüljön fel függőség olyan részekkel, amikre valójában nincs is szükség.

</details>

#### Dependency Inversion Principle

<details>
  <summary></summary>

"Abstractions should not depend on details. Details should
depend on abstractions."

Magas szintű modulok ne függjenek alacsony szintűektől. Különben az alacsony szintű változások magas szintű változtatásokat igényelnek.

Fordítsuk meg interface-ek segítségével a függőség irányát.

Példa a rossz tervezésre:
<p align="center">
    <img src="dipwrong.png" width="100"/>
</p>
Az adatbázis vagy a GUI változtatása a logika módosítását vonja maga után. Megoldás:
<p align="center">
    <img src="dipgood.png" width="250"/>
</p>

</details>



### Egyéb elvek

#### Release Reuse Equivalency Principle

<details>
  <summary></summary>

Az újtafelhasználható elemeket csak akkor szabad használni, ha a készítője kibocsátje, verziószámozza és karbantartja azt. Ezzel biztosítva, hogy minden módosítás és javítás a megfelelő módon jut el a felhasználóhoz, visszafele tartva a kompatibilitást.

</details>

#### Common Closure Principle

<details>
  <summary></summary>

Azok az osztályok amik együtt változnak összetartoznak. Ezt szervezés szintjén is jelezni kell. Ezek az osztályok tartozzanak egy package-be.

</details>

#### Common Reuse Principle

<details>
  <summary></summary>

Azok az osztályok amik nincsenek együtt fölhasználva, külön legyenek csoportosítva. Csak az jusson el a felhasználhoz, amire tényleg szüksége van. 

</details>

#### Acyclic Dependencies Principle

<details>
  <summary></summary>

Package-k között ne legyen körkörös függőség! Mindenféle függőséget próbáljunk minimalizálni.

</details>

#### Stable Dependencies Principle

<details>
  <summary></summary>

A stabil részektől függjenek a kevésbé stabilak és ne fordítva.

</details>

#### Stable Abstractions Principle

<details>
  <summary></summary>

A stabil package-k legyenek abstract-ok. Így könnyebben kiegészíthetőek.

</details>

#### Don’t Repeat Yourself

<details>
  <summary></summary>

Kerüljük az ismétlést és duplikációt. Minden adatnak és tudásnak legyen meg a jól meghatározott helye és felelőse. Ha duplikálnánk valamit gondoljuk végig nem lenne-e jobb kiemelni.

</details>

#### Single Choice Principle

<details>
  <summary></summary>

Ha különböző alternatívák támogatása szükséges, akkor ezt pontosan egy, jól meghatározott helyen tegyük.

</details>

#### Tell, don’t ask

<details>
  <summary></summary>

Egy függvény hívásakor nem a hívó felelőssége a hívott identitás állapotának vizsgálata, hanem a függvényé.

</details>

#### Law of Demeter

<details>
  <summary></summary>

"Don’t talk to strangers!"

Egy objektum függvénye, csupán az alábbi tulajdonú függvényeket hívja:
- Saját objektum egyéb függvényeit
- Saját objektum adattagjainak publikus függvényeit
- A függvény paramétereinek függvényeit
- A függvény által létrehozott objektumok függvényeit

Kerüljük a láncolt függvényhívásokat!

</details>

---

## Tervezési minták

---

## Heurisztikák

---

## Refaktorálás

---

## Clean-code elvek

---

## API tervezési elvek

---

## Elosztott objektumorientáltság

---

## Konkurens és párhuzamos minták

---

## Immutable objektumorientáltság

---