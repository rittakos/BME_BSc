Rittgasszer Ákos    Z8WK8D

A progrma alapjaként, a laborfeladat alapját használtam.
A TextureQuadGeometry osztályt használtam, a téglalaphoz. 
Itt, az osztályon belül úgy módosítottam a vertexbuffer mátrixát, hogy rendesen nézzen ki a figura.
A texturát ráraktam a téglalapra, úgy hogy egyszerre a tksztúra 64-ed része van rajta, 
mivel a 8x8 kis kép van. A laboron elkészített vertex shadert használtam kisebb módosításokkal.
Hozzáadam egy vec2 uniform változót, ami azt mondja meg melyi képét akarom megjeleníteni a textúrának.
A képek közötti váltáshoz, ezt a uniform változót módosítom. Amikor azt akarom elérni, hpgy űgy tűnjön,
mintha mozogna az ember, akkor a textura eltolása mellett, magát, a téglalapot is eltolom.
Ehhez a sebességet úgy kísérleteztem ki, hogy jól nézzen ki. A futó(r) és gyalogos(w) mód között az 
r és w gombokkal lehet váltani. Ezek után pedig a jobbra és balra nyilakkal lehet a figurát mozgatni.
A szebb hatásért még lelassítottam a mozgást, úgy, hogy csak minden 5. gombnyomásra mozog 
(így tűnt a legszebbnek).
