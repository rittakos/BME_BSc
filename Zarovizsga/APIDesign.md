# API tervezési elvek

[Főoldal](oop.md)
<details>
  <summary></summary>

[Fogalmak](terms.md)

[Minták](patterns.md)

[Elvek](principles.md)

[Heurisztikák](heuristics.md)

[Refaktorálás](refactoring.md)

[Clean-code](cleanCode.md)

[Elosztott objektumorientáltság](distributed.md)

[Konkurens és párhuzamos minták](concurrentParalell.md)

[Immutable objektumorientáltság](immutable.md)

[C++ Idiómák](idioms.md)

</details>

## Tartalom
<details open>
  <summary></summary>

- [API tervezési elvek](#api-tervezési-elvek)
  - [Tartalom](#tartalom)
  - [API](#api)
  - [Jó API tulajdonságai](#jó-api-tulajdonságai)
    - [Könnyű megtanulni, és memorizálni](#könnyű-megtanulni-és-memorizálni)
    - [Olvasható kódhoz vezet](#olvasható-kódhoz-vezet)
    - [Nehéz rosszul használni](#nehéz-rosszul-használni)
    - [Könnyű kiterjeszteni](#könnyű-kiterjeszteni)
    - [Teljes, vagyis lefedi az összes felhasználói igényt](#teljes-vagyis-lefedi-az-összes-felhasználói-igényt)
    - [Jól dokumentált](#jól-dokumentált)
  - [API fejlesztés folyamata](#api-fejlesztés-folyamata)
    - [1. Gyűjtsük össze a követelményeket](#1-gyűjtsük-össze-a-követelményeket)
    - [2. Írjunk use-case-eket](#2-írjunk-use-case-eket)
    - [3. Vegyünk példát hasonló API megoldásokról](#3-vegyünk-példát-hasonló-api-megoldásokról)
    - [4. Definiáljuk az API-t](#4-definiáljuk-az-api-t)
    - [5. Ellenőriztessük másokkal](#5-ellenőriztessük-másokkal)
    - [6. Írjunk sok-sok példát](#6-írjunk-sok-sok-példát)
    - [7. Készüljünk fel a kiterjesztésekre](#7-készüljünk-fel-a-kiterjesztésekre)
    - [8. Implementáljuk](#8-implementáljuk)
    - [9. Ha kételkedünk, hagyjuk ki](#9-ha-kételkedünk-hagyjuk-ki)
    - [10. Ne változtassunk rajta](#10-ne-változtassunk-rajta)
    - [Szemantikus verzió](#szemantikus-verzió)
  - [API tervezési elvek](#api-tervezési-elvek-1)
    - [Válasszunk magától értetődő neveket és szignatúrákat!](#válasszunk-magától-értetődő-neveket-és-szignatúrákat)
    - [Válasszunk egyfajta nevet az összetartozó dolgokra](#válasszunk-egyfajta-nevet-az-összetartozó-dolgokra)
    - [Kerüljük a hamis konzisztenciát](#kerüljük-a-hamis-konzisztenciát)
    - [Kerüljük a rövidítéseket](#kerüljük-a-rövidítéseket)
    - [Általános nevek helyett használjunk specifikus neveket](#általános-nevek-helyett-használjunk-specifikus-neveket)
    - [Használjuk a helyi terminológiát](#használjuk-a-helyi-terminológiát)
    - [Ne legyünk az alattunk lévő API elnevezésinek foglyai](#ne-legyünk-az-alattunk-lévő-api-elnevezésinek-foglyai)
    - [Válasszunk megfelelő alapértelmezett értékeket és működést](#válasszunk-megfelelő-alapértelmezett-értékeket-és-működést)
    - [Az API-t ne tegyük túlságosan okossá](#az-api-t-ne-tegyük-túlságosan-okossá)
    - [Gondoljunk az API tervezési döntéseink teljesítménybeli következményeire](#gondoljunk-az-api-tervezési-döntéseink-teljesítménybeli-következményeire)
    - [Minimalizáljuk a módosíthatóságot](#minimalizáljuk-a-módosíthatóságot)
    - [Vagy öröklésre tervezzünk, és dokumentáljuk is, vagy tiltsuk meg az öröklődést](#vagy-öröklésre-tervezzünk-és-dokumentáljuk-is-vagy-tiltsuk-meg-az-öröklődést)
    - [Legyünk óvatosak, ha virtuális API-t definiálunk](#legyünk-óvatosak-ha-virtuális-api-t-definiálunk)
    - [Egy GUI-hoz készülő API tulajdonságokra épüljön](#egy-gui-hoz-készülő-api-tulajdonságokra-épüljön)
    - [Próbáljuk meg előre látni a testreszabhatósági lehetőségeket](#próbáljuk-meg-előre-látni-a-testreszabhatósági-lehetőségeket)
    - [Kerüljük a hosszú paraméterlistákat](#kerüljük-a-hosszú-paraméterlistákat)
    - [Használjunk kényelmi függvényeket](#használjunk-kényelmi-függvényeket)
    - [Induljunk el 3 sorból](#induljunk-el-3-sorból)
    - [A mágia rendben van, a számok nem](#a-mágia-rendben-van-a-számok-nem)
    - [Jelezzük a hibát, amilyen hamar csak lehet](#jelezzük-a-hibát-amilyen-hamar-csak-lehet)
    - [Ne használjunk checked exception-öket](#ne-használjunk-checked-exception-öket)
    - [A kivétel jelezze, hogyan lehet őt elkerülni](#a-kivétel-jelezze-hogyan-lehet-őt-elkerülni)
    - [Vigyázzunk a függvények túlterhelésével](#vigyázzunk-a-függvények-túlterhelésével)
    - [Teszteljük ki a belét is](#teszteljük-ki-a-belét-is)
    - [Dokumentáljuk az API-t](#dokumentáljuk-az-api-t)

</details>

---

## API

- Application Programming Interface
- függvények és osztályok gyűjteménye, melyet egy felhasznált könyvtár publikál
- az API nehéz változtatni
- legyen jól átgondolt és stabil

## Jó API tulajdonságai

### Könnyű megtanulni, és memorizálni

### Olvasható kódhoz vezet

### Nehéz rosszul használni

### Könnyű kiterjeszteni

### Teljes, vagyis lefedi az összes felhasználói igényt

### Jól dokumentált
- [Lásd.](cleanCode.md/#publikus-API-dokumentálásának-tartalma)

## API fejlesztés folyamata 

1. Gyűjtsük össze a követelményeket
2. Írjunk use-case-eket
3. Vegyünk példát hasonló API megoldásokról
4. Definiáljuk az API-t
5. Ellenőriztessük másokkal
6. Írjunk sok-sok példát
7. Készüljünk fel a kiterjesztésekre
8. Implementáljuk
9. Ha kételkedünk, hagyjuk ki
10. Ne változtassunk rajta

Részletesebben:

<details>
  <summary></summary>

### 1. Gyűjtsük össze a követelményeket

- legyen minél átfogóbb és pontosabb

### 2. Írjunk use-case-eket

- használati esetek, amiket lefed az API
- felhasználói igényeken alapuljon
- egyszerű mintakódokkal ki lehet egészíteni
- cél az, hogy könnyű legyen használni az API-t

### 3. Vegyünk példát hasonló API megoldásokról

- használjuk amiről tudjuk, hogy jó
- tanuljunk más API-k hibáiból

### 4. Definiáljuk az API-t

- adjuk meg a pontos osztályokat és függvényeket, amiket használni lehet
- kívülről könnyen használható legyen
- unit tesztek, test driven development

### 5. Ellenőriztessük másokkal

- visszajelzések

### 6. Írjunk sok-sok példát

### 7. Készüljünk fel a kiterjesztésekre

- az API fejlődni fog
- kiterjesztés működhet öröklődéssel, delegációval, dependency injection-nel, vagy egy service provider interfész implementálásával, és az implementáció beregisztrálásával

### 8. Implementáljuk

- tesztelés is

### 9. Ha kételkedünk, hagyjuk ki

### 10. Ne változtassunk rajta

- visszafele kompatibilitás
- verziózni is kell, érdemes követni a [szemantikus verziózást](#szemantikus-verzió)

</details>

### Szemantikus verzió

- 3 darab számból áll: major, a minor és a patch verziószámból
- major verziószámot akkor kell növelni, ha egy visszafele inkompatibilis változtatást hajtottunk végre, minél ritkábban
- a minor verziószámot akkor növeljük, ha új verziót adunk az API-hoz, kompatibilitás nem sérül
- patch verziószám akkor növekszik, ha a könyvtár API-ján nem változtatunk, csak a belső implementációban javítottunk


## API tervezési elvek

<details open>
  <summary></summary>


### Válasszunk magától értetődő neveket és szignatúrákat!
- Lásd [clean code](cleanCode.md/#Kifejező-nevek-írása)

### Válasszunk egyfajta nevet az összetartozó dolgokra

### Kerüljük a hamis konzisztenciát

### Kerüljük a rövidítéseket

### Általános nevek helyett használjunk specifikus neveket

### Használjuk a helyi terminológiát

### Ne legyünk az alattunk lévő API elnevezésinek foglyai

### Válasszunk megfelelő alapértelmezett értékeket és működést

### Az API-t ne tegyük túlságosan okossá
- ne legyenek olyan rejtett mellékhatások, amelyekre a kliens nem számít

### Gondoljunk az API tervezési döntéseink teljesítménybeli következményeire

### Minimalizáljuk a módosíthatóságot

### Vagy öröklésre tervezzünk, és dokumentáljuk is, vagy tiltsuk meg az öröklődést

### Legyünk óvatosak, ha virtuális API-t definiálunk

### Egy GUI-hoz készülő API tulajdonságokra épüljön

### Próbáljuk meg előre látni a testreszabhatósági lehetőségeket
- property-ken, és egyéb kiterjesztési lehetőségeken keresztül tudjuk finomhangolni a könyvtárunk viselkedését
- limitáljuk a lehetséges opciók számát

### Kerüljük a hosszú paraméterlistákat

### Használjunk kényelmi függvényeket

### Induljunk el 3 sorból
- inicializálás
- alapvető konfiguráció
- afuttatás

### A mágia rendben van, a számok nem

### Jelezzük a hibát, amilyen hamar csak lehet
- fordítási időben ha lehet

### Ne használjunk checked exception-öket

### A kivétel jelezze, hogyan lehet őt elkerülni

### Vigyázzunk a függvények túlterhelésével

### Teszteljük ki a belét is
- unit tesztek
- regressziós tesztek 
- use-case-eket,
- tesztek a szélső értékekre


### Dokumentáljuk az API-t

- dokumentáció nélküli szinte lehetetlen használni

<details/>

