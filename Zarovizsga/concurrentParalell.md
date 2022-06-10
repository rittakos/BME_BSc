# Konkurens és párhuzamos minták

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

[Immutable objektumorientáltság](immutable.md)

[C++ Idiómák](idioms.md)

</details>

## Tartalom
<details open>
  <summary></summary>

- [Konkurens és párhuzamos minták](#konkurens-és-párhuzamos-minták)
  - [Tartalom](#tartalom)
  - [A konkurencia és az elosztott rendszerek problémái](#a-konkurencia-és-az-elosztott-rendszerek-problémái)
    - [A konkurens programozás előfordulása](#a-konkurens-programozás-előfordulása)
    - [A konkurens programozás problémái](#a-konkurens-programozás-problémái)
    - [Elosztott rendszerek problémái](#elosztott-rendszerek-problémái)
  - [Szinkronizációs minták](#szinkronizációs-minták)
  - [Kontextus minták](#kontextus-minták)
  - [Kérés- és eseménykezelési minták](#kérés--és-eseménykezelési-minták)
  - [Konkurencia minták](#konkurencia-minták)
    - [Active object](#active-object)
    - [Half-sync/half-async](#half-synchalf-async)
    - [Half-sync/half-async - async->sync](#half-synchalf-async---async-sync)
    - [Half-sync/half-async - sync->async](#half-synchalf-async---sync-async)
    - [Leader-followers](#leader-followers)
    - [Scheduler](#scheduler)
  - [Kapcsolat a minták között](#kapcsolat-a-minták-között)

</details>

---

## A konkurencia és az elosztott rendszerek problémái

A konkurens és elosztott minták abban segítenek, hogy ezeket korrekt módon tudjuk megoldani.

<details>
  <summary></summary>


### A konkurens programozás előfordulása

Problémái abból erednek, hogy több szál próbál egy módosítható közös állapothoz egyszerre hozzáférni.

### A konkurens programozás problémái

Konkurens programozás esetben versenyhelyzet van a szálak között, felülírhatják egymás értékeit, így valamilyen módon szinkronizálni kell közöttük. Vigyázni kell, nehogy a szálak dead-lock-ba kerüljenek, és el kell kerülni, hogy egyes szálakat kiéheztessünk. Ezen kívül tovább nehezít, hogy nem lehet pontosan reprodukálni.

### Elosztott rendszerek problémái

Problémát okoz a heterogenitás, vagyis, hogy a szerver és kliens különböző programnyelveken is készülhet. Meg kell oldani a transzparenciát, hogy lehetőleg a kliens ne tudjon róla, hogy éppen
egy lokális, vagy egy távoli objektummal kommunikál. A kérések feldolgozása történhet szinkron és aszinkron módon is. Memória menedzsment problémák is felmerülhetnek, hogy kinek kell lefoglalnia, és kinek kell felszabadítania egy adott objektumot. Felmerülhetnek versenyhelyzetek. Fel készülni, és reagálni kell tudni a hálózati hibákra.

</details>

## Szinkronizációs minták

Szálak közötti szinkronizációra nyújtanak megoldást.

<details>


</details>


## Kontextus minták

<details>
  <summary>## Kontextus minták</summary>



</details>

## Kérés- és eseménykezelési minták

<details>
  <summary></summary>



</details>

## Konkurencia minták

A konkurencia minták a többszálú feldolgozásról szólnak.

<details>
  <summary></summary>

### Active object
- célja a függvény meghívásának és a függvény lefutásának szétcsatolása
- a kliens és a szerver külön szálon futnak
- amikor a kliens a Proxy objektumot meghívja, a Proxy létrehozza a Future-t, ami később az eredményt szolgáltatja a kliensnek, és létrehoz egy Task-ot, ami később a háttérben a függvény végrehajtásáért fog felelni

<p align="center">
    <img src="ConcurrentparalellImages/activeobject.png" />
</p>

### Half-sync/half-async
- a szinkron és az aszinkron végrehajtást szétcsatolja egymástól
- a szétcsatolás egy task-okat tartalmazó soron keresztül történik

### Half-sync/half-async - async->sync
- egy aszinkron kliens hív szinkron szervert
- aszinkron módon érkeznek feladatok, és szinkron módon dolgozzuk őket fel
- szerver objektumokból több is lehet, ezek külön szálakon futnak
<p align="center">
    <img src="ConcurrentparalellImages/hsas.png" />
</p>
- működése:
  <p align="center">
    <img src="ConcurrentparalellImages/hsas2.png" />
</p>

### Half-sync/half-async - sync->async
- egy szinkron kliens hív aszinkron szervert
- egy darab szinkron szál generálja a feladatokat, berakja őket egy feladatsorba, és az aszinkron feldolgozók ezekből válogatnak
<p align="center">
    <img src="ConcurrentparalellImages/hssa.png" />
</p>
- működése:
<p align="center">
    <img src="ConcurrentparalellImages/hssa2.png" />
</p>

### Leader-followers
- egy nagyon egyszerű ütemezést valósít meg
- van egy készletünk a szálakból, amelyek közül egy a Leader, a többiek a followers
- a follower szálak arra várnak, hogy egyszer majd leader-ek lehessenek
- sorra érkeznek a feladatok, és mindig a vezető szál kapja a következőt
- ilyenkor a vezető szál a követő szálak közül egyet előléptet vezetővé, ő pedig elkezd dolgozni a feladaton, és amikor végzett, ő is követővé válik

### Scheduler
- okos ütemezést valósít meg
- folyamatosan érkeznek be a feladatok
- az ütemező több szálat kezel egyszerre és algoritmus alapján ezeknek osztja ki a feladatokat

</details>


## Kapcsolat a minták között

<p align="center">
    <img src="ConcurrentparalellImages/kapcsolatok.png" />
</p>
