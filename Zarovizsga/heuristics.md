# Heurisztikák

[Főoldal](oop.md)
<details>
  <summary></summary>

[Fogalmak](terms.md)

[Minták](patterns.md)

[Elvek](principles.md)

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

- [Heurisztikák](#heurisztikák)
  - [Tartalom](#tartalom)
  

</details>

---

## Osztályok tervezésével kapcsolatos heurisztikák

### Az attribútumok mindig legyenek privátok!

<details>
  <summary></summary>

Megsértése nem kívánt függőségeket és invalid belső állapot eredményezhet. Megsértheti a [DRY](principles.md/#dont-repeat-yourself) elvet.

Használjunk privát attribútumokat public és protected függvényekkel.

Megsérthető:
- Statikus, konstans attribútumok

</details>

### Ne használjuk másik osztály nempublikus tagjait!

<details>
  <summary></summary>

Használjunk a publikus függvényeket.

Megsérthető:
- Keretrendszer, könyvtár készítése
- Tesztelés

</details>

### Minimalizáljuk a publikus metódusok számát!

<details>
  <summary></summary>

Megsértése nehezen használhatóvá teszi az osztályt. Csak arra legyen publikus függvény amire kell.

Ne sértsük meg!

</details>

### Implementáljuk a sztenderd metódusokat!

<details>
  <summary></summary>

Megszegése nehezíti a fejlesztést és tesztelést. Ha valakinek kell, és rosszul implementálja az baj.

Ilyen pl.:
- C#: ToString(), Equals(), GetHashCode()
- Java: toString(), equals(), hashCode()
- C++: másolókonstruktor, operator=, operator==, operator<< to an ostream

Megsérthető:
- Ha valamelyiket nem szeretnénk támogatni, de ekkor ezt jelezzük

</details>

### Egy osztály ne függjön az őt használó osztályoktól, beleértve a leszármazottjait
is!

<details>
  <summary></summary>

Megsértése körökörös függést eredményez. Nem kívánt függőségekhez vezet. Sérti az [OCP](principles.md/#openclosed-principle) és [ADP](principles.md/#acyclic-dependencies-principle) elveket.

Megoldható [ISP](principles.md/#interface-segregation-principle) vagy [DIP](principles.md/#dependency-inversion-principle) segítésgével.

Ne sértsük meg!

</details>

### Egy osztály csak egy absztrakcióval rendelkezzen!

<details>
  <summary></summary>

Megsértése túl sok felelősséget eredményez, sérti a [SRP](principles.md/#single-responsibility) elvet.

Megoldható az osztályok szétdarabolásával, vagy a [ISP](principles.md/#interface-segregation-principle) segítségével.

Megsérthető:
- [Visitor](patterns.md/#visitor), [Strategy](patterns.md/#strategy) minta

</details>

### Az összetartozó adatot és viselkedést tartsuk egy helyen, tehát egy osztályban!

<details>
  <summary></summary>

Megsértése nem kívánt függőségeket és nem kívánt módosításokat eredményezhet.

Megsérthető:
- Kizárólag adatcseréle való osztályok
- [Visitor](patterns.md/#visitor), [Strategy](patterns.md/#strategy) minta

</details>

### A metódusok használjanak minél több attribútumot és metódust a saját osztályukból!

<details>
  <summary></summary>

Megsértése sérti a [SRP](principles.md/#single-responsibility) elvet.

Megsérthető:
- adabázis-leképezés, hálózati kommunikáció
- [Utility osztályok](terms.md/#alapfogalmak)

</details>

### A viselkedést modellezük, ne a szerepeket!

<details>
  <summary></summary>

Ha a leszármazottak nem adnak hozzá viselkedést az ősosztályhoz, akkor ne az osztály leszármazottjaiként, hanem annak példányaiként modellezzük őket.

</details>


## Felelősségek kiosztásával kapcsolatos heurisztikák

### A felelősségeket egyenletesen osszuk szét!

<details>
  <summary></summary>

Megsértése sérti a [SRP](principles.md/#single-responsibility) elvet és isten osztály keletkezhet.

Ne sértsük meg!

</details>

### Kerüljük az isten-osztályokat!

<details>
  <summary></summary>

Megsértése esetén sok adattároló osztály van és az isten osztály irányít mindenkit. Sérti a [SRP](principles.md/#single-responsibility) elvet.

Ne sértsük meg!

</details>

### Kerüljük a csak adattárolásra használt osztályokat!

<details>
  <summary></summary>

Megsértése sérti a [TDA](principles.md/#tell-dont-ask) elvet, mivel nincs ezeknek az osztályoknak felelőssége és más osztályok manipulálják.

Megsérthető:
- adabázis-leképezés, hálózati kommunikáció

</details>

### Kerüljük azokat az osztályokat, amelyeknek függvényeknek kellene lenniük!

<details>
  <summary></summary>

Megsértése esetén külön helyen van a visekedés és az adat.

Megsérthető:
- [Visitor](patterns.md/#visitor), [Strategy](patterns.md/#strategy) minta

</details>

### Modellezzük a valódi világ működését!

<details>
  <summary></summary>

Működő, logikus példán alapul így egyszerűbb a modellezés. Mindenki könnyebben értelmezi a modellt.

Megsérthető:
- Indokolt esetben

</details>

### Modellezzünk a megfelelő absztrakciós szinten!

<details>
  <summary></summary>

Vegyünk fel olyan ügynököket,
melyek megkönnyítik a modellezést, és elimináljuk azokat az osztályokat, melyeknek
nincs értelmes hozzáadott értéke.


</details>

### Modellezésnél maradjunk a rendszer határain beül!

<details>
  <summary></summary>

Legyenek egyértelmű határok.

Megsértése sérti a [YAGNI](principles.md/#yagni) elvet. Fölöslegesen bonyolítja a modellt és fölösleges munkát eredményez.

</details>

### Mindig a nézet függjön a modelltől, sosem a modell a nézettől!

<details>
  <summary></summary>

Megsértése estén a gyakran változó nézet vagy új nézet bevezetése a modell változtatását igényli.

Megoldás lehet [Push](patterns.md/push-modell) vagy [Pull](patterns.md/pull-modell) modell.

</details>


## Asszociációkkal kapcsolatos heurisztikák

### Túl sok asszociáció problémája

<details>
  <summary></summary>

- túl sok a keresztfüggőség
- úgy néz ki program felépítése, mint egy spagetti: bármelyik komponenst is fogjuk meg, jön vele az összes többi 
- nem lehet a komponenseket önállóan újrahasznosítani


</details>

### Minimalizáljuk az együttműködő osztályok számát!

<details>
  <summary></summary>

Ha túl sok osztály működik együtt, túl sok közöttük a keresztfüggőség, túl nagy a csatolás

</details>

### Minimalizáljuk az együttműködő osztályok között használt metódusok számát!

<details>
  <summary></summary>

Minél több különböző metódust hívnak egymás között az együttműködő osztályok, annál erősebb közöttük a csatolás.

Megsértése sérti a [TDA](principles.md/#tell-dont-ask) és [DRY](principles.md/#dont-repeat-yourself) elveket.

</details>

### Osszuk szét a felelősségeket a tartalmazás mentén!

<details>
  <summary></summary>

Ne a tartalmazó osztály csináljon mindent, hanem a tartalmazott komponensek viselkedéséből jöjjön ki a tartalmazó osztály működése.

A tartalmazó osztályok fekete-dobozok legyenek.


Megsértése sérti a [Demeter törvényt](principles.md/#law-of-demeter).

</details>

### Asszociáció helyett preferáljuk a tartalmazást!

<details>
  <summary></summary>

Az osztály külső használói tudhatnak az asszociációban lévő objektumokról, függhetnek
tőlük, ezt kerüljük.

Megsérthető:
- ha nem lehetséges a tartalmazás, pl.: kör
- ha a belső objektumok kívülről, másoknak is látniuk kell


</details>

### A tartalmazó objektum ne csak egyszerűen tartalmazza, hanem használja is a tartalmazott objektumokat!

<details>
  <summary></summary>

Megsértése sérti a [Demeter törvényt](principles.md/#law-of-demeter).

[Facade](patterns.md/#facade-minta) tervezési minta.

Megsérthető:
- gyüjtemény osztályok

</details>

### A tartalmazott objektum ne használja a tartalmazó objektumot!

<details>
  <summary></summary>

Megsértése kör függést eredményez. A tartalmazott objektum nem használható külön.

Megsérthető:
- adabázis-leképezés, hálózati kommunikáció
- [Utility osztályok](terms.md/#alapfogalmak)

</details>

### A tartalmazott objektumok ne beszélgessenek egymással közvetlenül!

details>
  <summary></summary>

Megsértése felesleges függőségeket okoz.

[Mediátor](patterns.md/#mediátor-minta) tervezési minta.

</details>


## Öröklődéssel kapcsolatos heurisztikák

### Az öröklődés célja mindig a viselkedés újrahasznosítása!

<details>
  <summary></summary>

Megsértése sérti a [Liskov](principles.md/#liskov-substitution-principle) elvet.

Ne sértsük meg!

</details>

### Az öröklés helyett preferáljuk a tartalmazást!

<details>
  <summary></summary>

Adatok újrahasznosítására mindig a tartalmazás való. Ha nem akarjuk az ős minden viselkedését használni fölösleges a leszármazás.

Viselkedést nem csak örökléssel lehet hozzáadni egy osztályhoz, hanem delegálással is,
ezt csinálja a [Dekorátor](patterns.md/#dekorátor-minta) tervezési minta.

</details>

c