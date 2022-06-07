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
    - [Parallel inheritance hierarchies (párhuzamos öröklődési hierarchiák)](#parallel-inheritance-hierarchies-párhuzamos-öröklődési-hierarchiák)
    - [Lazy class (lusta osztály)](#lazy-class-lusta-osztály)
    - [Speculative generality (spekulatív általánosság)](#speculative-generality-spekulatív-általánosság)
    - [Temporary Field (ideiglenes mező)](#temporary-field-ideiglenes-mező)
    - [Message chains](#message-chains)
    - [Middle man](#middle-man)
    - [Inappropiate intimacy](#inappropiate-intimacy)
    - [Alternative classes with different interfaces](#alternative-classes-with-different-interfaces)
    - [Incomplete library class](#incomplete-library-class)
    - [Data class](#data-class)
    - [Refused bequest (elutasított örökség)](#refused-bequest-elutasított-örökség)
    - [Comments](#comments)
    - [Downcasting](#downcasting)
  - [Refaktorálási technikák](#refaktorálási-technikák)
    - [Extract method](#extract-method)
    - [Inline method](#inline-method)
    - [Inline temporary](#inline-temporary)
    - [Replace temporary with query](#replace-temporary-with-query)
    - [Introduce explaining variable](#introduce-explaining-variable)
    - [Split temporary variable](#split-temporary-variable)
    - [Remove assignments to parameters](#remove-assignments-to-parameters)
    - [Replace method with method object](#replace-method-with-method-object)
    - [Substitute algorithm](#substitute-algorithm)
    - [Move method](#move-method)
    - [Move field](#move-field)
    - [Extract class](#extract-class)
    - [Inline class](#inline-class)
    - [Hide delegate](#hide-delegate)
    - [Remove middle man](#remove-middle-man)
    - [Introduce foreign method](#introduce-foreign-method)
    - [Introduce local extension](#introduce-local-extension)
    - [Self encapsulate field](#self-encapsulate-field)
    - [Replace data value with object](#replace-data-value-with-object)
    - [Change value to reference](#change-value-to-reference)
    - [Change reference to value](#change-reference-to-value)
    - [Replace array with object](#replace-array-with-object)
    - [Duplicate observed data](#duplicate-observed-data)
    - [Change unidirectional association to bidirectional](#change-unidirectional-association-to-bidirectional)
    - [Change bidirectional association to unidirectional](#change-bidirectional-association-to-unidirectional)
    - [Replace magic numbers with symbolic constant](#replace-magic-numbers-with-symbolic-constant)
    - [Encapsulate field](#encapsulate-field)
    - [Encapsulate collection](#encapsulate-collection)
    - [Replace record with data class](#replace-record-with-data-class)
    - [Replace type code with class](#replace-type-code-with-class)
    - [Replace type code with subclasses](#replace-type-code-with-subclasses)
    - [Replace type code with state/strategy](#replace-type-code-with-statestrategy)
    - [Replace subclass with fields](#replace-subclass-with-fields)
    - [Decompose conditional](#decompose-conditional)
    - [Consolidate conditional expression](#consolidate-conditional-expression)
    - [Consolidate duplicate conditional fragments](#consolidate-duplicate-conditional-fragments)
    - [Remove control flag](#remove-control-flag)
    - [Replace nested conditional with guard clauses](#replace-nested-conditional-with-guard-clauses)
    - [Replace conditional with polymorphism](#replace-conditional-with-polymorphism)
    - [Introduce null object](#introduce-null-object)
    - [Introduce assertion](#introduce-assertion)
    - [Rename method](#rename-method)
    - [Add parameter](#add-parameter)
    - [Remove parameter](#remove-parameter)
    - [Separate query from modifier](#separate-query-from-modifier)
    - [Parameterize method](#parameterize-method)
    - [Replace parameter with explicit methods](#replace-parameter-with-explicit-methods)
    - [Preserve whole object](#preserve-whole-object)
    - [Replace parameter with method](#replace-parameter-with-method)
    - [Introduce parameter object](#introduce-parameter-object)
    - [Remove setting method](#remove-setting-method)
    - [Hide method](#hide-method)
    - [Replace constructor with factory method](#replace-constructor-with-factory-method)
    - [Encapsulate downcast](#encapsulate-downcast)
    - [Replace error code with exception](#replace-error-code-with-exception)
    - [Replace exception with test](#replace-exception-with-test)
    - [Pull up field](#pull-up-field)
    - [Pull up method](#pull-up-method)
    - [Pull up constructor body](#pull-up-constructor-body)
    - [Push down method](#push-down-method)
    - [Push down field](#push-down-field)
    - [Extract subclass](#extract-subclass)
    - [Extract superclass](#extract-superclass)
    - [Extract interface](#extract-interface)
    - [Collapse hierarchy](#collapse-hierarchy)
    - [Form template method](#form-template-method)
    - [Replace inheritance with delegation](#replace-inheritance-with-delegation)
    - [Replace delegation with inheritance](#replace-delegation-with-inheritance)
    - [Tease apart inheritance](#tease-apart-inheritance)
    - [Convert procedural design to objects](#convert-procedural-design-to-objects)
    - [Separate domain from presentation](#separate-domain-from-presentation)
    - [Extract hierarchy](#extract-hierarchy)

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
- [null object](patterns.md/#null-object) elv



### Parallel inheritance hierarchies (párhuzamos öröklődési hierarchiák)

Probléma:
- Ha egy osztályból új leszármazott készül, akkor egy másikból is kell leszármazottat készíteni
- Nehezen módosítható
- [Shotgun Surgery](#shotgun-surgery) speciális esete

Megoldás:
- összevonás



### Lazy class (lusta osztály)

Probléma:
- osztály túl kevés dolgot csinál
- nics rá szükség

Megoldás:
- elimináljuk



### Speculative generality (spekulatív általánosság)

Utal:
- [YAGNI](principles.md/#yagni) lehet sérül

Probléma:
- osztály feleslegesen túl nehézsúlyú
- felesleges munka a karbantartása

Megoldás:
- eliminálni a felesleges tudást



### Temporary Field (ideiglenes mező)

Utal:
- alacsony kohézió

Probléma:
- attribútum csak bizonyos esetekben van használva
- globális változók
- Nehezen módosítható

Megoldás:
- kiszervezés



### Message chains

Utal:
- [Demeter törvény](principles.md/#law-of-demeter) sérül

Probléma:
- hosszú metódushívási láncok
- nem kívánt függőség

Megoldás:
- delegálni a következő hívásnak, ha sok ilyen van inkább sérüljön



### Middle man

Probléma:
- osztály túl sokat delegál egy másik osztály felé
- felesleges az osztály

Megoldás:
- felelősség és delegálás újragondolása




### Inappropiate intimacy

Utal:
- [ne használjuk másik osztály nempublikus tagjait](#ne-használjuk-másik-osztály-nempublikus-tagjait) sérül
- felelősségek rossz kiosztása

Probléma:
- másik osztály privát tagjainak közvetlen elérése

Megoldás:
- felelősségek újragondolása


### Alternative classes with different interfaces

Probléma:
- ugyanarra a feladatra különböző interfészű osztályok

Megoldás:
- közös interface
- [bridge](patterns.md/#bridge) minta



### Incomplete library class

Probléma:
- felhasznált könyvtárbeli osztályt nem tudunk módosítani
- hiányzik, valemi nekünk kellő funkcionalitás

Megoldás:
- csomagoljuk be egy saját osztályba és egészítsük ki



### Data class

Utal:
- nem oo tervezés
- [isten osztály](principles.md/#kerüljük-az-isten-osztályokat) létezése

Probléma:
- osztály csak adatot tárol

Megoldás:
- átmozgatni másik osztályba
- kiegészíteni funkcionalitással



### Refused bequest (elutasított örökség)

Utal:
- [Liskov elv](principles.md/#liskov-substitution-principle) sérülhet
- öröklés nem a viselkedést hasznosítja újra

Probléma:
- leszármazottnak nincsen szüksége az ős viselkedésére

Megoldás:
- öröklődés helyett delegálás



### Comments

Utal:
- rossz tervezés és refaktorálás hiánya
- [clean code](cleanCode.md)

Probléma:
- sok magyarázó komment
- a kód túl bonyolult

Megoldás:
- delegálni a következő hívásnak, ha sok ilyen van inkább sérüljön
- [clean code kommentezés](cleanCode.md)



### Downcasting

Utal:
- [TDA](principles.md/#tell-dont-ask) sérül
- [OCP](principles.md/#openclosed-principle) sérül

Probléma:
- típusfüggő kód

Megoldás:
- polimorfizmus



## Refaktorálási technikák

### Extract method
- függvényt készítünk a kód egy részéből
- csökkenthető a kódduplikáció


### Inline method
- a függvény törzsét beépítjük a hívó oldalon
- felesleges delegáció megszűntetése


### Inline temporary
- egyszer használt ideiglenes változó értékének behelyettesítése a használat helyén


### Replace temporary with query
- egy ideiglenes változó helyett függvényt vezet be


### Introduce explaining variable
- egy bonyolultabb kifejezést helyettesít egy olvashatóbb nevű változóval


### Split temporary variable
- ha egy ideiglenes változót több különböző célra is felhasználunk
- válasszuk szét a célokat, és adjunk különböző neveket a változóknak


### Remove assignments to parameters
- ideiglenes változót vezetünk be ahelyett, hogy a paraméternek adnánk értéket


### Replace method with method object
- metódusból osztályt készítünk, ahol a lokális változókból mezők lesznek
- függvényben definiált algoritmust kiszervezzük egy osztályba


### Substitute algorithm
- algoritmust lecseréljük egy tisztább változatra


### Move method
- egy metódust egy másik osztályba mozgatunk át


### Move field
- egy mezőt egy másik osztályba mozgatunk át


### Extract class
- egy osztály néhány metódusából és mezőjéből egy másik osztályt képzünk


### Inline class
- egy osztály metódusait és mezőit beépítjük egy másik osztályba


### Hide delegate
- egy távoli objektumhoz intézett hívást delegációval helyettesítünk


### Remove middle man
- a delegációt egy direkt hívásra cseréljük le


### Introduce foreign method
- a kliens osztályban új metódust készítünk, ahol a szerver paraméter
- a kliensben olyan funkciót tudunk adni a szerverhez, amelyet a szerver alapból nem támogat


### Introduce local extension
- kibővíti a szerver működését, úgy hogy egy új leszármazottat hoz létre


### Self encapsulate field
- egy mezőt getter-setter metódusokba, vagy property-be csomagolunk


### Replace data value with object
- primitív adatokat tároló változók helyett osztályt vezet be


### Change value to reference
- értékegyenlőség helyett referencia-egyenlőséget vezet be
- [Flyweight](patterns.md/#flyweight) tervezési minta


### Change reference to value
- referencia-egyenlőség helyett értékegyenlőséget vezet be


### Replace array with object
- ha egy tömböt használunk arra, hogy összetartozó elemeket csoportosítsunk, akkor ezt a tömböt cseréljük le egy osztályra, az osztály mezői a tömb egyes elemei lesznek


### Duplicate observed data
- GUI-ban ne tároljunk olyan adatokat, amelyek a modell számára fontosak, helyette válasszuk szét a modell és a GUI réteget
- GUI függjön a modelltől, és ne fordítva


### Change unidirectional association to bidirectional
- asszociáció átjárhatóságát változtatja meg
- egyirányú asszociációt kétirányúra vált


### Change bidirectional association to unidirectional
- asszociáció átjárhatóságát változtatja meg
- kétirányú asszociációt egyirányúra vált


### Replace magic numbers with symbolic constant
- kódban szétszórt számok és string literálok helyett nevesített konstansokat használjunk


### Encapsulate field
- nem privát attribútumból privátot készítünk
- a hozzáférést getter-setter metódusokkal, vagy property-vel oldjuk meg


### Encapsulate collection
- egy gyűjtemény típusú attribútumot rejtünk el
- kifelé csak olvasható, módosítására saját függvényeket publikálunk


### Replace record with data class
- ha egy nem oo nyelven írt könyvtárhoz kell csatlakoznunk, ilyenkor a rekordok reprezentálására adatosztályokat használunk


### Replace type code with class
- a típusok egész számként vagy enum-ként való kódolása helyett különböző osztályokat használjunk


### Replace type code with subclasses
- a típusok egész számként vagy enum-ként való kódolása helyett különböző osztályokat használjunk, öröklődést és polimorfizmust is használ


### Replace type code with state/strategy
- a típusok egész számként vagy enum-ként való kódolása helyett különböző osztályokat használjunk
- ha az öröklődés valamilyen ok miatt nem működik, akkor ennek segítségével az objektum dinamikus viselkedését szervezzük ki a [state](patterns.md/#state) vagy a [strategy](patterns.md/#strategy) tervezési minta segítségével


### Replace subclass with fields
- ha a leszármazottak nem adnak hozzá viselkedést az őshöz
- az egyes leszármazottak csak állapotban különböznek, helyettük az ős is példányosítható lenne
- felesleges a leszármazottakat külön típusként definiálni


### Decompose conditional
- elágazások különböző ágait önálló függvényekként reprezentáljuk


### Consolidate conditional expression
- ha ugyanaz a feltétel többször egymás után szerepel, akkor a kódot írjuk át úgy, hogy azt csak egyszer kelljen kiértékelni és tesztelni


### Consolidate duplicate conditional fragments
- ha ugyanaz a részkifejezés többször egymás után szerepel, akkor akódot írjuk át úgy, hogy azt csak egyszer kelljen kiértékelni és tesztelni


### Remove control flag
- kilépést jelző változót cseréljünk le egy break vagy return utasításra


### Replace nested conditional with guard clauses
- egymásba ágyazott feltételek helyett if-ek, vagy if-else-k sorozatát kapjuk


### Replace conditional with polymorphism
- a típus-ellenőrzéseket polimorfizmussal helyettesítjük


### Introduce null object
- ne null értékeket tároljunk, hanem használjuk a [null object](patterns.md/#null-object) tervezési mintát
- nem kell folyton a null értékeket vizsgálni


### Introduce assertion
- egy feltételezett állapotra egy feltételellenőrzést helyezünk el, amely debug módban kivételt dob, ha a feltétel sérül, így fejlesztés közben ad egy plusz ellenőrzést


### Rename method
- a függvényt átnevezzük, az új név jobban tükrözze a függvény célját


### Add parameter
- új paramétert adunk a függvényhez, hogy több információt tudjunk átadni neki


### Remove parameter
- nem használt paramétert törlünk


### Separate query from modifier
- két metódust készítünk, az egyik csak lekérdezésre, a másik csak módosításra való


### Parameterize method
- két nagyon hasonló függvényt kombinálunk össze eggyé, új paraméterek bevezetésével


### Replace parameter with explicit methods
- egy metódus felosztása több, kevesebb paraméterű metódusra


### Preserve whole object
- teljes objektumra adunk tovább referenciát, nem az objektum egyes részeit adjuk tovább


### Replace parameter with method
- nem metódushívás eredményét adjuk tovább, hanem hagyjuk, hogy a hívást a függvény végezze el


### Introduce parameter object
- sok csoportosuló paramétert helyettesíti egy önálló osztállyal


### Remove setting method
- az attribútumok értékét a konstruktorokban állítjuk be, settereket nem biztosítunk


### Hide method
- ha egy osztály egy publikus függvényét senki sem használja, akkor tegyük ezt priváttá


### Replace constructor with [factory method](patterns.md/#factory-method)
- ha egy objektum létrehozása és inicializálása bonyolultabb annál, mint egy konstruktor-hívás


### Encapsulate downcast
- ha egy metódus eredményét a klienseknek folyton át kell kasztolniuk, akkor ezt a típuskasztolást tegyük át a metódusba, és a metódus térjen vissza a helyes típussal


### Replace error code with exception
- hibakódok, és speciális értékek helyett használjunk kivételeket


### Replace exception with test
- kivételek elkapása helyett ellenőrizzük, hogy a paraméterek helyesek-e

### Pull up field
- leszármazottakban lévő közös attribútomokat a közös ősbe visszük


### Pull up method
- leszármazottakban lévő közös metódusokat a közös ősbe visszük


### Pull up constructor body
- leszármazottak konstruktorainak közös részeit viszik a közös ős konstruktorába


### Push down method
- olyan metódust, amely a leszármazottak csak egy részére érvényes, lejjebb viszünk az öröklési hierarchiában


### Push down field
- olyan mezőt, amely a leszármazottak csak egy részére érvényes, lejjebb viszünk az öröklési hierarchiában


### Extract subclass
- azokat a viselkedéseket, amelyek csak a leszármazottak egy részére érvényesek egy önálló leszármazottba szervezzük ki, és az eredeti leszármazottak tőle fognak leszármazni


### Extract superclass
- ha néhány leszármazott közös viselkedéssel rendelkezik, akkor ezt a viselkedést egy önálló közös ősbe lehet kiszervezni


### Extract interface
- ha több osztály publikus interfészében vannak közös részek, akkor a közös halmaz kiszervezhető


### Collapse hierarchy
- ha egy osztály nem sok mindent ad hozzá az ős viselkedéséhez, akkor összevonjuk őket


### Form template method
- ha néhány leszármazott hasonló metódusokat tartalmaz hasonló lépésekkel azonos sorrendben, akkor a [template method](patterns.md/#template-method) tervezési mintával vigyük őket az ősbe


### Replace inheritance with delegation
- ha egy leszármazottnak nem mindenre van szüksége, amit megörököl, akkor öröklődés helyett használjunk delegációt


### Replace delegation with inheritance
- ha egy osztály többnyire csak delegál egy hasonló interfészű másik osztályhoz, akkor a delegálást kiválthatjuk egy örökléssel


### Tease apart inheritance
- ha egy öröklési hierarchia két dolgot csinál egyszerre, akkor vágjuk szét két különálló öröklési hierarchiára


### Convert procedural design to objects
- adatosztályokhoz felelősségeket, metódusokat rendelünk


### Separate domain from presentation
- az üzleti logikát vegyük ki a GUI-ból


### Extract hierarchy
- egy bonyolult osztály darabolunk fel egy komplett öröklési hierarchiára
- a speciális eseteket az egyes leszármazottak kezeljék