# Vedés

[Előadás](vedes.pptx)

## Bevezető: 1.dia

A feladatom egy játékmotor készítése volt aminek OpenGL könyvtár képezi az alapját

## Feladat: 2.dia

Legelső lépésként meg lett határozva egy részletesebb specifikáció és irány a feladathoz. Ez úgy lett kialakítva, hogy elsőként egy minimális funkcionalitású, de használható könyvtár legyen létrehozva, úgy, hogy minél könnyebben lehessen továbbfejleszteni. Cél, hogy a motor és a demo játék minél jobban elkülönüljön egymástól. A labirintust támogató funkciók úgy lettek kialakítva, hogy egy általános, működő megoldást használjunk, de azt lehessen testreszabni.

## Tervezés: 3.dia

A tervezés során elsosorban objektum orientált tervezési elvekre és tervezési mintákra támaszkodtam. Ezek garantálták, hogy fenntartható, könnyen módosítható program készüljön el. A projekt generálásának megoldása azért volt fontos, hogy platform és fejlesztőkörnyezet függtelen lehessen a projekt, valamint jól működjön a verziókezelő rendszer. A felhasznált könyvtárak összeillesztéséhez meg kellett tervezni azok interface-eit, hogy minél kevesebb probléma merüljön fel. Ez azért is volt fontos, hogy könnyebben ki lehessen cserélni vagy továbbfejleszteni ezeket a könyvtárakat. Meg kellet határozni, hogy miként oszlanak szét a felelősségek, ez a fejlesztés, hibajavítás és módosítások esetén is nagyon fontos.
A hibák felderítéséhez fontosak a tesztek és egy jól működő logolási rendszer. Itt készült pár unit teszt a független logikai részekhez, valmint demo-k a használt könyvtárakhoz és magához a motorhoz is.

## Implementáció: 4.dia

Az implementáció, a tervezés alapján történt. Először egy váz készült el, ami játék és motor kapcsolatának logikáját határozta meg. Ezek után el lettek készítve a szükséges interface-ek. Az interface-ek azért fontosak, hogy a mögöttük levő logika változása, minél függetlenebb legyen a többi kódrésztől. Implementálásra kerültek a központi logikai elemek, például a játék fő ciklusa. Ekkor lettek integrálva a külső könyvtárak is, amik el lettek rejtve interface-ek mögé, hogy cseréjük minél egyszerűbb legyen. A funkciók ezután lettek lefejlesztve, mindegyik a skeletonban meghatározott helyén. A funkciók fejlesztésével párhuzamosan volt fejlesztve a játék is. Ez egy tesztként funkcionált, ami mindig nyomon követte a motor fejlődését. A könnyebb használatért több default beállítás, algoritmus és érték is meg lett határozva. Ilyen például egy labirintus generló algorimtus, a alapértelmezett inputok vagy a textúrázott téglalap.

## Végeredmény: 5.dia

A végeredmény magában foglalja az elkészült motor könyvtárat és egy demo alkalmazást ami megmutattja a használatát. A motor képes egy beépített algoritmussal legenerálni egy útvesztőt, de van lehetőség saját algoritmus implementálására is. Ezen kívül vannak beépített grafikus objektumok, amiket létre lehet hozni, de újak létrehozásához is biztosít eszközöket a motor. A motornban van egy beépített input kezelő rendszer, amit azonban tetszőleges lehet módosítani. Motor szinten lehet objektumok közötti ütközést detektálni és annak hatását szimulálni. Természetesen rengeteg módon lehet továbbfejleszteni a motort, mind funkciók mind kényelmi eszközök terén.

## Kérdések: 6.dia

Két megválaszolandó kérdés merült fel a bírálat során. Az egyik az osztályok részletesebb bemutatását kérte, kitérve arra, hogy hogyan lehet új shadert, textúrát és geometriát készíteni. A másik kérdés a labirintus generáló algoritmusra irányult.


## Labirintus: 7.dia
 
Az algoritmus a Kruskal algoritmus módosított változata. Ennek lényege, hogy egy súlyozott gráfban keresi a legkisebb súlyú feszítőfát. Ez annyban módosul, hogy a gráf nem súlyoztt, hanem véletlenszerűen választjuk ki az éleket. A megoldás menete, hogy választunk egy élet, amiről megnézzük, hogy a két vége között van-e már ut, ha nincs bevesszük az élet a megoldásba, ha van eldobjuk. A labirintus úgy van megfeleltetve egy gráfnak, hogy a mezők élek az utak pedig a csúcsok. Kezdetben a szomszédos csúcsok között van él. A végeredményben szereplő élek helyén lesznek utak, ahonnan pedig elvettük az éleket ott falak lesznek.

A megoldás a start mezőből indított mélységi kereséssek adható meg.

<details>
  <summary>Lépések</summary>

1. Létrehozzuk a labirintust, egy n*m mátrix amelyiknek minden cellája tudja:
	- koordinátáját a mátrixban
	- melyik irányban helyezkedik el tőle fal
	- a megoldási útvonal része-e
	- a megoldás során volt-e már vizsgálva
	- a generálás során volt-e már vizsgálva
2. Létrehozunk egy stack tipusú tárolót a generáláshoz és egyet a megoldáshoz. A generáláshoz használt stackbe beletesszük a kiindulási cellát.
3. A generálás egy rekurzív algoritmus, aminek végfeltétele, hogy az összes mező meg lett vizsgálva, ekkor true értékkel tér vissza
4. A generálás egy iterációjában a következő lépések hajtódnak végre
	1. Az aktuális mező, ami a stack tipusú tároló legfelső eleme
	2. Összegyűjtjük az aktuális mező szomszédai közül azokat, amik még nem voltak vizsgálva
	3. Ha nincs szomszéd, akkor zsákutcába jutottunk és visszalépünk. Visszatérünk false-al és kiszedjük a stack tetejéről az aktuális elemet
	4. Ha van szomszéd, akkor kiválasztunk egyet véletlenszerűen
	5. A kiválasztott szomszéd és az aktuális elem között út lesz, azok a mezők között fal van ahol nincs út
	6. A kiválsztott szomszédot berakjuk a stack tetejére
	7. Újra meghívjuk a generáló algoritmust
5. Megoldó algoritmus a generálóhoz hasonlóan rekurzió és egy stack tároló segítségével bejárja a labirintust, amíg el nem jut a célmezőhöz
6. A generáló algoritmus tökéletes labirintust készít, vagyis bárhonann bárhova el lehet jutni

<details/>

## Osztályok részletesebb leírása: 8.dia

Új grafikus objektum létrehozásához használható, a Renderer APIban létrehozott shader és textura osztály. Ezek meghívják a megfelelő platform megfelelő függvényeit. Ezen kívül az új objektumért felelős osztálynak a GameObject-ből kell leszármaznia. Az más geometria leírásához nem készültek el a wrapper osztályok, ezeket OpenGL parancsokkal lehet megoldani.

Az osztályok négy nagyobb egységbe sorolhatóak be. Ezek a Motor, a játék, a labirintus és a platform függő kódok.

## 9. dia

A játék logikájáért és megjelenéséért felelős osztályok a motor beli osztályok leszármazottjai. Ezeken kívül a játék még használhatja RendererAPI-t, a labirintust és új parancsot rendelhet bemenetkehez. A GraphicsProfram leszármazott LabyrinthGame példányosításával jön létre a játék.

A labirintusért felelős rész áll egy osztályból aminek példányosításával létrehozható egy labirintus. Ez használ egy data, egy generáló és egy megjelenítő osztályt. A megjelenítő osztály platform függő és ő hozza létre az ütköző objektumokat is.

A platform függő rész a motorbeli interface-ek konkrét megvalósításait tartalmazza. Ilyen a rendererAPI-t megvalósító OpenGL Renderer API, a Window osztály és részben a TexturedRectangle osztály, ami tartalmaz olyan OpenGL hívásokat, amikhez még nem készült wrapper. Az inputok windows-os kezelése is itt valósul meg.

A motor leginkább alaplogikákat és interface-eket tartalmaz. Ilyen a fő ciklus, ami frissíti az adatszerkezeteket és kirajzolja amit kell. A inputok általános kezelése is itt történik. A GameObject minden olyan objektum őse, amit szeretnénk használni a játékhoz.