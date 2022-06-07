# Refaktorálás

[Főoldal](oop.md)
<details>
  <summary></summary>

[Fogalmak](terms.md)

[Minták](patterns.md)

[Elvek](principles.md)

[Heurisztikák](heuristics.md)

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

- [Refaktorálás](#refaktorálás)
  - [Tartalom](#tartalom)
  - [Refaktorálás](#refaktorálás-1)
  - [Code Smell](#code-smell)
    - [Duplikált kód](#duplikált-kód)
    - [Hosszú metódus](#hosszú-metódus)
    - [Hosszú paraméter lista](#hosszú-paraméter-lista)
    - [Nagy osztály](#nagy-osztály)
    - [Divergent change](#divergent-change)
    - [Shotgun surgery](#shotgun-surgery)
    - [Feature envy](#feature-envy)
    - [Data clups (adatcsomósodás)](#data-clups-adatcsomósodás)
    - [Primitive obsession (primitív típusokhoz való ragaszkodás)](#primitive-obsession-primitív-típusokhoz-való-ragaszkodás)
    - [Switch statements](#switch-statements)
    - [Nagy osztály](#nagy-osztály-1)
    - [Nagy osztály](#nagy-osztály-2)
    - [Nagy osztály](#nagy-osztály-3)
    - [Nagy osztály](#nagy-osztály-4)
    - [Nagy osztály](#nagy-osztály-5)

</details>

---

## Refaktorálás

Egy működő kódot alakítunk át ekvivalens lépésekkel, úgy, hogy a működése ne változzon, de a kód olvashatósága és minősége javuljon.

Mikor és miért?
- új funkció a jelenlegi állapotban nehezen, vagy nem megvalósítható
- hibajavítást/keresést segíti elő
- mert (ha) megtehetjük
- gyorsítja a jövőbeli fejlesztéseket
- a program minősége folyamatosan romlik, ezt hivatott ellensúlyozni

Szabályok:
- teszteljünk átfogóan előtte és utána
- haladjunk kis lépésenként, de legyünk bátrak

Menete:
1. sikeres tesztelés
2. refaktor
3. újból sikeres tesztelés
4. ismétlés a kívánt eredmény eléréséig


## Code Smell

Olyan tünet, ami valamilyen tervezései hibát, elv vagy heurisztika sérülését jelzi.

Refaktorálást igényel.

### Duplikált kód

Utal:
- [TDA](principles.md/#tell-dont-ask) lehet sérül
- [DRY](principles.md/#dont-repeat-yourself) biztos sérül

Probléma:
- Lásd, [DRY](principles.md/#dont-repeat-yourself)

Megoldás:
- kiemelés


### Hosszú metódus

Utal:
- [SRP](principles.md/#single-responsibility) lehet sérül

Probléma:
- Nehezen érthető
- Nehezen módosítható

Megoldás:
- szétvágni kisebb egységekre
- új objektum bevezetése


### Hosszú paraméter lista

Probléma:
- kb 3-nál több paraméter
- Nehezen érthető
- Nehezen tesztelhető

Megoldás:
- szétvágni kisebb függvényekre
- új objektum bevezetése több paraméter helyett



### Nagy osztály

Utal:
- [SRP](principles.md/#single-responsibility) sérül
- [isten osztály](heuristics.md/#kerüljük-az-isten-osztályokat)ra utal
- [ISP](principles.md/#interface-segregation-principle) sérül

Probléma:
- Nehezen érthető
- Nehezen módosítható

Megoldás:
- szétvágni kisebb osztályokra
- [ISP](principles.md/#interface-segregation-principle)


### Divergent change

Probléma:
- Felhasznált technológiánként más és más osztályt kell használnunk
- Nehezen módosítható

Megoldás:
- a technológiák közös részét egy közös stabil absztrakt csomagba kiszervezzük
- [Bridge](patterns.md/#bridge) tervezési minta



### Shotgun surgery

Utal:
- [DRY](principles.md/#dont-repeat-yourself) lehet sérül

Probléma:
- Egy változtatás sok más osztályban apró változtatásokat indukál
- Nehezen módosítható

Megoldás:
- összeszedés egy helyre, akár erőforrásba kiszervezni



### Feature envy

Utal:
- rosszul vannak kiosztva a felelősségek
- [SRP](principles.md/#single-responsibility) lehet sérül

Probléma:
- egy osztály túlságosan érdeklődik egy másik iránt, vagyis túl sok függvényt hív a másikból
- túl magas csatolás

Megoldás:
- bizonyos részek áthelyezése a hívóba



### Data clups (adatcsomósodás)

Probléma:
- Ugyanaz a paramétercsoport ismétlődik több metódushíváson keresztül
- Nehezen módosítható

Megoldás:
- emeljük ki a paramétereket egy osztályba, ha valóban összetartoznak



### Primitive obsession (primitív típusokhoz való ragaszkodás)

Utal:
- nem oop elveket követtünk

Probléma:
- adatok primitív típusokban vannak tárolva osztályok helyett
- Nehezen bővíthető

Megoldás:
- hozzunk létre osztályokat



### Switch statements

Utal:
- [DRY](principles.md/#dont-repeat-yourself) lehet sérül
- Rossz felelősség kiosztás

Probléma:
- túlságosan sok a feltételes elágazás
- Nehezen módosítható

Megoldás:
- [polimorfizmus](terms.md/#alapfogalmak)
- [null object](principles.md/#null-object) elv



### Nagy osztály

Utal:
- [SRP](principles.md/#single-responsibility) lehet sérül

Probléma:
- Nehezen érthető
- Nehezen módosítható

Megoldás:
- szétvágni kisebb egységekre
- új objektum bevezetése



### Nagy osztály

Utal:
- [SRP](principles.md/#single-responsibility) lehet sérül

Probléma:
- Nehezen érthető
- Nehezen módosítható

Megoldás:
- szétvágni kisebb egységekre
- új objektum bevezetése



### Nagy osztály

Utal:
- [SRP](principles.md/#single-responsibility) lehet sérül

Probléma:
- Nehezen érthető
- Nehezen módosítható

Megoldás:
- szétvágni kisebb egységekre
- új objektum bevezetése



### Nagy osztály

Utal:
- [SRP](principles.md/#single-responsibility) lehet sérül

Probléma:
- Nehezen érthető
- Nehezen módosítható

Megoldás:
- szétvágni kisebb egységekre
- új objektum bevezetése



### Nagy osztály

Utal:
- [SRP](principles.md/#single-responsibility) lehet sérül

Probléma:
- Nehezen érthető
- Nehezen módosítható

Megoldás:
- szétvágni kisebb egységekre
- új objektum bevezetése