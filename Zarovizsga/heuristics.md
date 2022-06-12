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

[C++ Idiómák](idioms.md)

</details>

## Tartalom
<details open>
  <summary></summary>

- [Heurisztikák](#heurisztikák)
  - [Tartalom](#tartalom)
  - [Heurisztikák szigorúsága](#heurisztikák-szigorúsága)
  - [Osztályok tervezésével kapcsolatos heurisztikák](#osztályok-tervezésével-kapcsolatos-heurisztikák)
    - [Az attribútumok mindig legyenek privátok!](#az-attribútumok-mindig-legyenek-privátok)
    - [Ne használjuk másik osztály nempublikus tagjait!](#ne-használjuk-másik-osztály-nempublikus-tagjait)
    - [Minimalizáljuk a publikus metódusok számát!](#minimalizáljuk-a-publikus-metódusok-számát)
    - [Implementáljuk a sztenderd metódusokat!](#implementáljuk-a-sztenderd-metódusokat)
    - [Egy osztály ne függjön az őt használó osztályoktól, beleértve a leszármazottjait is!](#egy-osztály-ne-függjön-az-őt-használó-osztályoktól-beleértve-a-leszármazottjait-is)
    - [Egy osztály csak egy absztrakcióval rendelkezzen!](#egy-osztály-csak-egy-absztrakcióval-rendelkezzen)
    - [Az összetartozó adatot és viselkedést tartsuk egy helyen, tehát egy osztályban!](#az-összetartozó-adatot-és-viselkedést-tartsuk-egy-helyen-tehát-egy-osztályban)
    - [A metódusok használjanak minél több attribútumot és metódust a saját osztályukból!](#a-metódusok-használjanak-minél-több-attribútumot-és-metódust-a-saját-osztályukból)
    - [A viselkedést modellezük, ne a szerepeket!](#a-viselkedést-modellezük-ne-a-szerepeket)
  - [Felelősségek kiosztásával kapcsolatos heurisztikák](#felelősségek-kiosztásával-kapcsolatos-heurisztikák)
    - [A felelősségeket egyenletesen osszuk szét!](#a-felelősségeket-egyenletesen-osszuk-szét)
    - [Kerüljük az isten-osztályokat!](#kerüljük-az-isten-osztályokat)
    - [Kerüljük a csak adattárolásra használt osztályokat!](#kerüljük-a-csak-adattárolásra-használt-osztályokat)
    - [Kerüljük azokat az osztályokat, amelyeknek függvényeknek kellene lenniük!](#kerüljük-azokat-az-osztályokat-amelyeknek-függvényeknek-kellene-lenniük)
    - [Modellezzük a valódi világ működését!](#modellezzük-a-valódi-világ-működését)
    - [Modellezzünk a megfelelő absztrakciós szinten!](#modellezzünk-a-megfelelő-absztrakciós-szinten)
    - [Modellezésnél maradjunk a rendszer határain beül!](#modellezésnél-maradjunk-a-rendszer-határain-beül)
    - [Mindig a nézet függjön a modelltől, sosem a modell a nézettől!](#mindig-a-nézet-függjön-a-modelltől-sosem-a-modell-a-nézettől)
  - [Asszociációkkal kapcsolatos heurisztikák](#asszociációkkal-kapcsolatos-heurisztikák)
    - [Túl sok asszociáció problémája](#túl-sok-asszociáció-problémája)
    - [Minimalizáljuk az együttműködő osztályok számát!](#minimalizáljuk-az-együttműködő-osztályok-számát)
    - [Minimalizáljuk az együttműködő osztályok között használt metódusok számát!](#minimalizáljuk-az-együttműködő-osztályok-között-használt-metódusok-számát)
    - [Osszuk szét a felelősségeket a tartalmazás mentén!](#osszuk-szét-a-felelősségeket-a-tartalmazás-mentén)
    - [Asszociáció helyett preferáljuk a tartalmazást!](#asszociáció-helyett-preferáljuk-a-tartalmazást)
    - [A tartalmazó objektum ne csak egyszerűen tartalmazza, hanem használja is a tartalmazott objektumokat!](#a-tartalmazó-objektum-ne-csak-egyszerűen-tartalmazza-hanem-használja-is-a-tartalmazott-objektumokat)
    - [A tartalmazott objektum ne használja a tartalmazó objektumot!](#a-tartalmazott-objektum-ne-használja-a-tartalmazó-objektumot)
    - [A tartalmazott objektumok ne beszélgessenek egymással közvetlenül!](#a-tartalmazott-objektumok-ne-beszélgessenek-egymással-közvetlenül)
  - [Öröklődéssel kapcsolatos heurisztikák](#öröklődéssel-kapcsolatos-heurisztikák)
    - [Az öröklődés célja mindig a viselkedés újrahasznosítása!](#az-öröklődés-célja-mindig-a-viselkedés-újrahasznosítása)
    - [Az öröklés helyett preferáljuk a tartalmazást!](#az-öröklés-helyett-preferáljuk-a-tartalmazást)
    - [A közös viselkedéssel nem rendelkező közös adat tartalmazás relációban legyen!](#a-közös-viselkedéssel-nem-rendelkező-közös-adat-tartalmazás-relációban-legyen)
    - [A közös viselkedéssel rendelkező közös adat az ősosztályban legyen definiálva!](#a-közös-viselkedéssel-rendelkező-közös-adat-az-ősosztályban-legyen-definiálva)
    - [A közös viselkedés és közös adat minél magasabban legyen az öröklési hierarchiában!](#a-közös-viselkedés-és-közös-adat-minél-magasabban-legyen-az-öröklési-hierarchiában)
    - [Közös interfészt csak akkor valósítsunk meg, ha a viselkedés is közös!](#közös-interfészt-csak-akkor-valósítsunk-meg-ha-a-viselkedés-is-közös)
    - [Egy osztály ne függjön a saját  leszármazottjaitól!](#egy-osztály-ne-függjön-a-saját--leszármazottjaitól)
    - [Protected láthatóságot csak metódusoknál használjunk, az attribútumok mindig privátak legyenek!](#protected-láthatóságot-csak-metódusoknál-használjunk-az-attribútumok-mindig-privátak-legyenek)
    - [Az öröklődési hierarchia legyen mély, de legfeljebb hét szintű!](#az-öröklődési-hierarchia-legyen-mély-de-legfeljebb-hét-szintű)
    - [Az absztrakt osztályok és interfészek az öröklési hierarchia gyökerében legyenek!](#az-absztrakt-osztályok-és-interfészek-az-öröklési-hierarchia-gyökerében-legyenek)
    - [Az öröklési hierarchia gyökerében absztrakt osztályok vagy interfészek legyenek!](#az-öröklési-hierarchia-gyökerében-absztrakt-osztályok-vagy-interfészek-legyenek)
    - [Soha ne vizsgáljuk egy objektum típusát, használjunk helyette polimorfizmust!](#soha-ne-vizsgáljuk-egy-objektum-típusát-használjunk-helyette-polimorfizmust)
    - [Soha ne kódoljuk a típust enum vagy int értékekbe, használjunk helyette polimorfizmust!](#soha-ne-kódoljuk-a-típust-enum-vagy-int-értékekbe-használjunk-helyette-polimorfizmust)
    - [Ne készítsünk függvényeket a típusok, illetve a képességek megkülönböztetésére, használjunk helyettük polimorfizmust!](#ne-készítsünk-függvényeket-a-típusok-illetve-a-képességek-megkülönböztetésére-használjunk-helyettük-polimorfizmust)
    - [Ne keverjük össze a leszármazottakat az objektumokkal! Vigyázzunk azokkal a leszármazottakkal, amelyekből csak egyetlen példányt hozunk létre!](#ne-keverjük-össze-a-leszármazottakat-az-objektumokkal-vigyázzunk-azokkal-a-leszármazottakkal-amelyekből-csak-egyetlen-példányt-hozunk-létre)
    - [A statikus szemantikát és kényszereket a modell struktúrájába építsük be! (ha kevés a helyes kombináció)](#a-statikus-szemantikát-és-kényszereket-a-modell-struktúrájába-építsük-be-ha-kevés-a-helyes-kombináció)
    - [A statikus szemantikát és kényszereket a konstruktorba építsük be! (ha túl sok a helyes kombináció)](#a-statikus-szemantikát-és-kényszereket-a-konstruktorba-építsük-be-ha-túl-sok-a-helyes-kombináció)
    - [A dinamikus szemantikát és kényszereket viselkedésként implementáljuk!](#a-dinamikus-szemantikát-és-kényszereket-viselkedésként-implementáljuk)
    - [A gyakran változó dinamikus szemantikát és kényszereket külső viselkedésként implementáljuk!](#a-gyakran-változó-dinamikus-szemantikát-és-kényszereket-külső-viselkedésként-implementáljuk)
    - [Az opcionális elemeket tartalmazásként implementáljuk, ne öröklődéssel!](#az-opcionális-elemeket-tartalmazásként-implementáljuk-ne-öröklődéssel)
    - [Ne keverjük össze a statikus és dinamikus kényszereket!](#ne-keverjük-össze-a-statikus-és-dinamikus-kényszereket)
    - [Ha reflection-ra van szükségünk modellezzünk osztályokat, ne objektumokat!](#ha-reflection-ra-van-szükségünk-modellezzünk-osztályokat-ne-objektumokat)
    - [Ha az ős működését üres implementációval írjuk felül, akkor hibás az öröklési hierarchia!](#ha-az-ős-működését-üres-implementációval-írjuk-felül-akkor-hibás-az-öröklési-hierarchia)
    - [Törekedjünk újrahasznosítható API írására, ne csak újrahasznosítható osztályokéra!](#törekedjünk-újrahasznosítható-api-írására-ne-csak-újrahasznosítható-osztályokéra)
    - [Ha többszörös öröklődésre van szükségünk, gondoljuk át még egyszer a terveket!](#ha-többszörös-öröklődésre-van-szükségünk-gondoljuk-át-még-egyszer-a-terveket)

</details>

---

## Heurisztikák szigorúsága

- nem lehet mindig 100%-osan betartani
- egyes heurisztikák ellent is mondhatnak egymásnak
- irányelvek
- okkal és ésszel 

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

### Egy osztály ne függjön az őt használó osztályoktól, beleértve a leszármazottjait is!

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

Megoldás lehet [Push](patterns.md/#push-modell) vagy [Pull](patterns.md/#pull-modell) modell.

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

<details>
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


### A közös viselkedéssel nem rendelkező közös adat tartalmazás relációban legyen!

<details>
  <summary></summary>

Megsértése feleslekes adatokat ad osztályoknak.

</details>


### A közös viselkedéssel rendelkező közös adat az ősosztályban legyen definiálva!

<details>
  <summary></summary>

Különben sérülhet a [DRY](principles.md/#dont-repeat-yourself).

Megsérthető:
- ha többszörös öröklésre van szükségünk, de a programnyelv ezt nem támogatja

</details>


### A közös viselkedés és közös adat minél magasabban legyen az öröklési hierarchiában!

<details>
  <summary></summary>

Különben sérülhet a [DRY](principles.md/#dont-repeat-yourself).

</details>


### Közös interfészt csak akkor valósítsunk meg, ha a viselkedés is közös!

<details>
  <summary></summary>

Egy interfészt nem csak függvény szignatúrákat ír elő, hanem azt is meghatározza, hogy melyik függvénynek mi az elvárt viselkedése.

Ha csak formailag azonosak interface-ek akkor különüljenek el.

[Duck Typing](terms.md/#duck-typing)
</details>


### Egy osztály ne függjön a saját  leszármazottjaitól!

<details>
  <summary></summary>

[Lásd.](#egy-osztály-ne-függjön-az-őt-használó-osztályoktól-beleértve-a-leszármazottjait-is)

Megsértése sérti:
- [OCP](principles.md/#openclosed-principle): új leszármazott bevezetésekor módosul az ős is

Megoldás:
- [polimorfizmus](terms.md/#alapfogalmak)

</details>

### Protected láthatóságot csak metódusoknál használjunk, az attribútumok mindig privátak legyenek!

<details>
  <summary></summary>

[Lásd.](#az-attribútumok-mindig-legyenek-privátok)

Megsértése sérti:
- leszármazott elronthatja az örökölt viselkedést ([Liskov elv](principles.md/#liskov-substitotional-principle))

Megoldás:
- kezeljük őket protected metódusokkal (ha muszály)

</details>

### Az öröklődési hierarchia legyen mély, de legfeljebb hét szintű!

<details>
  <summary></summary>

Megsértése sérti:
- átláthatatlanná teszi a kódot (7 is sok)

</details>

### Az absztrakt osztályok és interfészek az öröklési hierarchia gyökerében legyenek!

<details>
  <summary></summary>

[Lásd.](#egy-osztály-ne-függjön-az-őt-használó-osztályoktól-beleértve-a-leszármazottjait-is)

Megsértése sérti:
- Lentebb egyre kevésbé van értelmük (levélben semmi)

Megsérthető:
- bizonyos könyvtáraknál

</details>


### Az öröklési hierarchia gyökerében absztrakt osztályok vagy interfészek legyenek!

<details>
  <summary></summary>

Megsértése sérti:
- konkrét osztályból később absztrakt osztályt készíteni sokkal nehezebb, mint fordítva

Megsérthető:
- ha egy konkrét osztály biztosan nem fog megváltozni

</details>

### Soha ne vizsgáljuk egy objektum típusát, használjunk helyette polimorfizmust!

<details>
  <summary></summary>

Megsértése sérti:
- típusellenőrzés történik ami sérti a [OCP](principles.md/#openclosed-principle)-t

Megoldás:
- polimorfizmus

Megsérthető:
- okkal és ésszel
- egyes mintáknál

</details>

### Soha ne kódoljuk a típust enum vagy int értékekbe, használjunk helyette polimorfizmust!

<details>
  <summary></summary>

Megsértése sérti:
- [OCP](principles.md/#openclosed-principle) sérül

Megoldás:
- [polimorfizmus](terms.md/#alapfogalmak)

</details>

### Ne készítsünk függvényeket a típusok, illetve a képességek megkülönböztetésére, használjunk helyettük polimorfizmust!

<details>
  <summary></summary>

Megsértése sérti:
- [OCP](principles.md/#openclosed-principle) sérül
- [TDA](principles.md/#tell-dont-ask) sérül

Megoldás:
- [polimorfizmus](terms.md/#alapfogalmak)

</details>

### Ne keverjük össze a leszármazottakat az objektumokkal! Vigyázzunk azokkal a leszármazottakkal, amelyekből csak egyetlen példányt hozunk létre!

<details>
  <summary></summary>

Megsértésekor:
- lehet, hogy nincs szükség a leszármazott osztályokra

Megoldás:
- leszármazottak megszűntetése

</details>

### A statikus szemantikát és kényszereket a modell struktúrájába építsük be! (ha kevés a helyes kombináció)

<details>
  <summary></summary>

</details>

### A statikus szemantikát és kényszereket a konstruktorba építsük be! (ha túl sok a helyes kombináció)

<details>
  <summary></summary>

</details>

### A dinamikus szemantikát és kényszereket viselkedésként implementáljuk!

<details>
  <summary></summary>

</details>

### A gyakran változó dinamikus szemantikát és kényszereket külső viselkedésként implementáljuk!

<details>
  <summary></summary>

</details>

### Az opcionális elemeket tartalmazásként implementáljuk, ne öröklődéssel!

<details>
  <summary></summary>

</details>

### Ne keverjük össze a statikus és dinamikus kényszereket!

<details>
  <summary></summary>

- a statikus kényszereket a modell struktúrájában vagy a konstruktorokban implementájuk
- a dinamikus kényszereket pedig a viselkedésben, tehát a metódusokban

</details>

### Ha reflection-ra van szükségünk modellezzünk osztályokat, ne objektumokat!

<details>
  <summary></summary>
Megsértésekor:
- nem a megfelelő absztrakciós szinten modellezünk
- objektumokat próbálunk meg modellezni ahelyett, hogy osztályokat terveznénk

Megsérthető:
- mentés és visszatöltés

</details>

### Ha az ős működését üres implementációval írjuk felül, akkor hibás az öröklési hierarchia!

<details>
  <summary></summary>

Megsértésekor:
- sérül a [Liskov elv](principles.md/#liskov-substitution-principle)

Megoldás:
- öröklési hierarchia módosítása
  
</details>

### Törekedjünk újrahasznosítható API írására, ne csak újrahasznosítható osztályokéra!

<details>
  <summary></summary>

Megsértésekor:
- nehéz az API-t változtatni, ami miatt fontos az alaposság

</details>

### Ha többszörös öröklődésre van szükségünk, gondoljuk át még egyszer a terveket!

<details>
  <summary></summary>

Megsértésekor:
- sok nyelvben nem támogatott
- rossz öröklés vagy hierarchia

Megsérthető:
- okkal és ésszel

</details>