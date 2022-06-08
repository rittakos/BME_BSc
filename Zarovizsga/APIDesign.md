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
- ez néha egyszerű, ha egy szabványt kell implementálni
- de néha nagyon nehéz is tud lenni, ha a követelmények nem tiszták
- éppen ezért érdemes minél több embert megkérdezni, hogy ők miket tartanak
fontosnak
- ezek az emberek lehetnek kollégák, a főnökünk, de leginkább azokat érdemes
megkérdezni, akik majd használni fogják az API-t
- vigyázzunk arra, hogy néha követelmények helyett megoldásokat fogunk kapni,
ezekkel bánjunk óvatosan, mert lehet, hogy létezik jobb megoldás is

### 2. Írjunk use-case-eket
- vagyis, hogy milyen használati eseteket kell az API-nak lefednie
- fontos, hogy ez a lépés előzze meg az implementációt, és az API a felhasználók
tényleges igényét tükrözze, ne pedig az implementáció belső struktúráját
- érdemes egyszerű mintakódokat is írni az egyes use-case-ekhez, hogy lássuk milyen
interfészt várunk el az API-tól
- egyelőre ne törődjünk azzal, hogy ezeket milyen nehéz lesz majd implementálni, a cél
az, hogy könnyű legyen majd használni az API-t
- ezek a kis minta kódok a tesztelésnél és a dokumentáció elkészítésénél is hasznosak
lesznek

### 3. Vegyünk példát hasonló API megoldásokról
- ha van már egy évek óta használt, jól bevált stabil API, akkor érdemes annak a mintáját
követnünk
- egy ilyen API éveken át fejlődött, sok-sok felhasználói visszajelzéssel, nem érdemes
nekünk valami teljesen újat kitalálni
- azért is jó, hogyha hasonlítunk egy meglévő API-ra, mert akkor a mi API-nkat is könnyű
lesz megtanulni, a másik API-val ismerős felhasználók könnyen kiismerik majd magukat
a mi általunk fejlesztett API-ban is
- természetesen, ha a másik API kényelmetlen, netán éppen emiatt írunk egy újat, akkor
nem kell követnünk a másik API által meghatározott szabályokat
- figyeljünk azért arra, hogy egy API nem biztos, hogy teljesen rossz, lehetnek benne jó
ötletek, melyeket érdemes átvenni
- ha a célunk az, hogy egy rossz API-t kiváltsunk egy általunk fejlesztett újabbal, akkor
fontoljuk meg azt, hogy a régebbi API-hoz képest definiálunk újabb, egyszerűbb
dolgokat, de egy ideig visszafele kompatibilisek maradunk, amíg a teljes átállást sikerül
megvalósítani

### 4. Definiáljuk az API-t
- a követelmények és a use-case-ek birtokában definiáljuk az API-t, vagyis adjuk meg a
pontos osztályokat és függvényeket, amelyeket majd használni lehet
- törekedjünk arra, hogy az API kívülről könnyen használható legyen, még akkor is, ha az
implementációja majd trükkös lesz
- írjunk a use-case-ek alapján unit teszteket, ezek segíthetnek abban, hogy az esetleges
hiányosságokat feltárjuk
- később majd jók lesznek arra is, hogy az API implementációját tesztelhessük velük
- ez a lépés abban is segíthet, hogy az implementációs részletek ne szivárogjanak fel az
API felületére
- esetleg néhány beállítást kivezethetünk az API felületére, amelyek segíthetnek a
hatékonyság finomhangolásában, de azért ezekkel is óvatosan bánjunk

### 5. Ellenőriztessük másokkal
- ellenőriztessük az API definícióját főnökünkkel, kollégáinkkal, és a potenciális
felhasználókkal
- gyűjtsünk minél több visszajelzést, legyenek azok pozitívak vagy negatívak, minden
vélemény nagyon hasznos tud lenni
- ehhez azonban fontos az, hogy az API definíciója ne legyen túlságosan hosszú,
lehetőleg férjen rá egy A4-es oldalra
- így az emberek gyorsan áttekinthetik, és nekünk is egyszerűbb karbantartani azt

### 6. Írjunk sok-sok példát
- ha megkaptuk a visszajelzéseket, és néhány iterációs lépés után sikerült kitalálni a
végleges API definíciót, akkor kezdjünk el sok-sok példát írni, hogy hogyan is lehet majd
használni az API-t
- kiindulásként felhasználhatjuk a use-case-eket, és ezek a példák segíthetnek abban is,
hogy az API definícióját a többiek segítségével véglegesítsük
- ahogy az API fejlődik, mindig frissítsük ezeket a példákat
- és fontos az is, hogy mielőbb kezdjük el használni az API-t a saját kódjainkban, mert
nincs annál jobb módszer a hiányosságok kiküszöbölésére, mint hogy a saját főztünket
esszük

### 7. Készüljünk fel a kiterjesztésekre
- az API az idők során fejlődni fog
- egyrészt mi magunk, a fejlesztők is fogunk hozzáadni újabb elemeket az API-nkhoz,
másrészt a felhasználóknak is meg kell adni a lehetőséget, hogy kiterjesszék a
működését
- a kiterjesztés működhet öröklődéssel, delegációval, dependency injection-nel, vagy
egy service provider interfész implementálásával, és az implementáció
beregisztrálásával
- ahhoz, hogy fel tudjunk készülni a megfelelő kiterjeszthetőségre, minden kiterjesztési
lehetőségre legalább 3 példát írjunk saját magunk is
- ezekből látszani fog, hogy az ősben definiált virtuális függvények elegendőek-e ahhoz,
hogy a kiterjesztések széles skáláját biztosíthassák

### 8. Implementáljuk
- ebbe beletartozik az is, hogy jó alaposan teszteljük le az API működését
- figyeljünk arra is, hogy néha úgy keletkezik publikus API, hogy egy belső API-t teszünk
nyilvánossá
- ilyenkor mindenképpen érdemes átnézni az API-t, nehogy valamit hibásan
publikáljunk, mert később aztán azt nagyon nehéz lesz javítani

### 9. Ha kételkedünk, hagyjuk ki
- mielőtt publikálnánk az API-t, meg egyszer alaposan vizsgáljuk meg
- ha bármilyen funkcionalitásban is kételkedünk, inkább hagyjuk ki, vagy váltsuk át belső
API-ra, de bizonytalan dolgot ne adjunk ki a kezünk közül
- hozzáadni mindig tudunk az API-hoz elvenni belőle azonban sosem
- érdemes béta változatokat kiadni, és figyelni a felhasználói visszajelzéseket, de
merjünk nem-et mondani, mert nem járhatunk mindenkinek a kedvében
- készüljünk fel arra is, hogy vétünk majd hibákat, de azokat majd az évek során ki fogjuk
küszöbölni, az API folyamatosan fejlődni fog

### 10. Ne változtassunk rajta
- ha publikáltuk az API-t, már ne változtassunk rajta
- fontos, hogy megőrizzük a visszafele kompatibilitást
- jobbá tehetjük a dokumentációt, megváltoztathatjuk a belső implementációt,
behozhatunk újabb feature-öket, de amit egyszer az API-ból kipublikáltunk, azon már
ne változtassunk
- ha így tennénk, azzal egy csomó másik ember kódját rontanánk el
- valószínűleg nagyon megharagudnának ránk, és nem használnák többet a
könyvtárunkat
- nagyon nagy tehát rajtunk a felelősség, mert az API-t elsőre jól el kell találnunk
- egy kipublikált könyvtárat verziózni is kell, és érdemes követni a szemantikus verziózást

</details>

### Szemantikus verzió
- a szemantikus verzió általában 3 darab számból áll: major, a minor és a patch
verziószámból
- a major, vagyis a fő verziószámot akkor kell növelni, ha az API-ban egy visszafele
inkompatibilis változtatást hajtottunk végre
- ennek nagyon ritkán szabadna csak megtörténnie
- a minor, vagyis az alverzió-számot akkor növeljük, hogyha új verziót adunk az API-hoz,
de az API továbbra is visszafele kompatibilis marad
- az utolsó, patch verziószám akkor növekszik, hogyha a könyvtár API-ján nem
változtatunk, csak a belső implementációban javítottunk valamilyen hibát


