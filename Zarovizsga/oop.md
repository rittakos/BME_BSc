# OOP

A BME VIK Mérnökinformatikus BSc képzésének objektum orientált szoftverfejlesztés tárgyának jegyzete, záróvizsgához.

## Tartalom
1. [Alapfogalmak](#alapfogalmak)
2. [Kapcsolatok](#kapcsolatok)
3. [Tervezési elvek](#tervezesi-elvek)
   1. [SOLID elvek](#SOLID-elvek)
      1. [Single Responsibility](#single-responsibility)
   2. [Egyéb elvek](#egyeb-elvek)
4. [xxx](#xxx)

---

## Alapfogalmak <a name="alapfogalmak" />

Az alábbi fogalmak vázlatosan vannak definiálva. Alapos ismeretük elengedhetetlen a továbbiakban.

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


--- 

## Kapcsolatok <a name="kapcsolatok" />

Modulok vagy osztályok között előforduló kapcsolatok.

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

---

## Tervezési elvek <a name="tervezesi-elvek" />

Olyan tervezési irányelvek és minták amik betartása könnyebben fentarthatóvá és továbbfejleszthetővét teszik a kódot.

### SOLID elvek <a name="SOLID-elvek" />

#### Single Responsibility <a name="single-responsibility" />

### Egyéb elvek <a name="egyeb-elvek" />

---