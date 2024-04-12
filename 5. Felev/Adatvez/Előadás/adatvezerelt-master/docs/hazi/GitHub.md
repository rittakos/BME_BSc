# Feladatok beadása (GitHub)

A feladatok beadásához a GitHub platformot használjuk. Minden házi beadása egy-egy GitHub repository-ban történik, melyet a feladatleírásban található linken keresztül kapsz meg. A házi feladatainak megoldását ezen repository-ban kell elkészítened, és ide kell feltöltened. A kész megoldás beadása a repository-ba való feltöltés után egy un. _pull request_ formájában történik, amelyet a gyakorlatvezetődhöz rendelsz.

!!! important "FONTOS"
    Az itt leírt formai előírások betartása elvárás. A nem ilyen formában beadott megoldásokat nem értékeljük.

## Rövidített verzió

Alább részletesen bemutatjuk a beadás menetét. Itt egy rövid összefoglaló az áttekintéshez, illetve a helyes beadás ellenőrzéséhez.

1. A munkádat a házi leírásban található linken keresztül létrehozott GitHub repository-ban kell elkészítsd.

1. A megoldáshoz készíts egy külön ágat, ne a _master_-en dolgozz. Erre az ágra akárhány kommitot tehetsz. Mindenképpen pushold a megoldást.

1. A beadást egy pull request jelzi, amely pull request-et a gyakorlatvezetődhöz kell rendelned.

1. Ha az eredménnyel vagy értékeléssel kapcsolatban kérdésed van, pull request kommentben kérdezhetsz. A gyakorlatvezető értesítéséhez használd a `@név` címzést a komment szövegében.

## A munka elkezdése: git checkout

1. [Regisztrálj](https://github.com/join) egy GitHub accountot, ha még nincs.

1. A feladat beadásához tartozó linket nyisd meg. Ez minden feladathoz más lesz, a feladat leírásában találod.

1. Ha kéri, adj engedélyt a _GitHub Classroom_ alkalmazásnak, hogy használja az account adataidat.

    ![Authorize GitHub classroom](images/github/github-authorize-classroom.png)

1. Látni fogsz egy oldalt, ahol elfogadhatod a feladatot ("Accept the ... assignment"). Kattints a gombra.

    ![Accept assignment](images/github/github-accept-assignment.png)

1. Várd meg, amíg elkészül a repository. A repository linkjét itt kapod meg.

    !!! note "Megjegyzés"
        A repository privát lesz, azaz az senki nem látja, csak te, és az oktatók.

    ![Repository created](images/github/github-repository-create-success.png)

1. Nyisd meg a repository-t a webes felületen a linkre kattintva. Ezt az URL-t írd fel, vagy mentsd el.

    ![Repository webes felülete](images/github/github-repository-webpage.png)

1. Klónozd le a repository-t. Ehhez szükséges lesz a repository címére, amit a repository webes felületén a _Clone or download_ alatt találsz.

    A git repository kezeléséhez tetszőleges klienst használhatsz. Ha nincs kedvenced még, akkor legegyszerűbb a [GitHub Desktop](https://desktop.github.com/). Ebben az alkalmazásban közvetlenül tudod listázni a repository-kat GitHub-ról, vagy használhatod az URL-t is a klónozáshoz.

    ![GitHub Desktop repository clone](images/github/github-desktop-clone.png)

    Ha konzolt használnál, az alábbi parancs klónozza a repository-t (ha a `git` parancs elérhető): `git clone <repository link>`

1. Ha sikerült a klónozás, **MÉG NE KEZDJ EL DOLGOZNI!** A megoldást _ne_ a repository `master` ágán készítsd el. Hozz létre egy új ágat (branch) `megoldas` néven.

    GitHub Desktop-ban a _Branch_ menüben teheted ezt meg.

    ![GitHub Desktop create branch](images/github/github-desktop-new-branch.png)

    Ha konzolt használsz, az új ág elkészíthető ezzel a paranccsal: `git checkout -b megoldas`

1. Ezen a megoldás ágon dolgozva készítsd el a beadandókat. Akárhányszor kommitolhatsz és pusholhatsz.

    !!! warning "Kommit név ellenőrzése"
        Mielőtt a git repository-val dolgozol, ellenőrízd, hogy a megfelelő névvel és email címmel kommitolsz-e. Ezt a következő command line paranccsal tudod megtenni.

        ```bash
        git config user.name
        git config user.email
        ```

        Ha ez nem megfelelő lenne, akkor add ki az alábbi parancsokat a git repository mappájában. Ezzel az adott repository-ra fogod beállítani a kívánt nevet és email címet. (Érdemes olyan email címet, megadni ami a github useretekhez van rendelve)

        ```bash
        git config user.name "John Doe"
        git config user.email "john@doe.org"
        ```

        Ha nem akarod minden repository-re külön állítani a fentieket, akkor érdemes lehet a globálisan vizsgálni és felülírni a `--global` kapcsolóval.

    GitHub Desktop-ban így tudsz kommitolni. Mindig ellenőrizd, hogy jó ágon vagy-e. Első alkalommal a _megoldas_ ág csak helyben létezik, ezért publikálni kell: _Publish this branch_.

    ![GitHub Desktop push branch](images/github/github-desktop-commit-to-branch.png)

    A további kommitoknál is mindig ellenőrizd a megfelelő ágat. Ha egy kommit még nincs felöltve, azt a _Push origin_ gombbal teheted meg. A kis szám a gombon jelzi, hogy hány, még nem pusholt kommit van.

    ![GitHub Desktop commit and push](images/github/github-desktop-push-commit.png)

    Ha konzolt használsz, akkor az alábbi parancsokat használd (feltéve, hogy a jó ágon vagy):

    ```bash
    # Ellenőrizd az ágat, és hogy milyen fájlok módosultak
    git status

    # Minden változtatást előkészít kommitolásra
    git add .

    # Kommit
    git commit -m "f1"

    # Push első alkalommal az új ág publikálásához
    git push --set-upstream origin megoldas

    # Push a továbbiakban, amikor az ág már nem új
    git push
    ```

## A megoldás beadása

1. Ha végeztél a megoldással, ellenőrizd a GitHub webes felületén, hogy mindent feltöltöttél-e. Ehhez a webes felületen váltanod kell az ágak között.

    ![GitHub web switch branch](images/github/github-switch-branch-webpage.png)

    !!! warning "Feltöltés a webes felületen"
        Azt javasoljuk, hogy ne használd a GitHub fájl feltöltés funkcióját. Ha valami hiányzik, a helyi git repository-ban pótold, és kommitold majd pushold.

1. Ha tényleg kész vagy, akkor nyiss egy _pull request_-et.

    !!! important "Minek a pull request?"
        Ez a _pull request_ fogja össze a megoldásodat, és annak "végeredményét" mutatja. Így a gyakorlatvezetőnek nem az egyes kommitjaidat vagy fájljaidat kell néznie, hanem csak a releváns, változott részeket látja egyben. A _pull request_ jelenti a feladatod beadását is, így ez a lépés **nem hagyható ki**.

    A _pull request_ nyitásához a GitHub webes felületére kell menj. Itt, ha nem rég pusholtál, a GitHub fel is ajánlja a pull request létrehozását.

    ![GitHub create pull request](images/github/github-create-pull-request-1.png)

    A _pull request_-et a fenti menüben is létrehozhatod. Fontos, hogy a megfelelő brancheket válaszd ki: `master`-be megy a `megoldas` ág.

    ![GitHub create pull request](images/github/github-create-pull-request-2.png)

    Ha minden rendben sikerült, a menüben fent látod a kis "1" számot a _Pull request_ elem mellett, jelezve, hogy van egy nyitott pull request. **DE MÉG NEM VÉGEZTÉL!**

    ![GitHub create pull request](images/github/github-create-pull-request-4.png)

1. A _pull request_ hatására le fog futni egy értékelés. Ennek eredményét a pull request alatt kommentben fogod látni.

    Ez az értékelés minden házi esetében más lesz. A programodat minden esetben lefuttatjuk, és előzetes pontszámot is kapsz.

    ![GitHub create pull request](images/github/github-pull-request-eval-result.png)

     Ha a kiértékelés eredményével kapcsolatban több információra van szükséged, mint amit itt látsz, a _GitHub Actions_ webes felülete segítségül szolgálhat. Erről [itt](GitHub-Actions.md) találsz egy rövid ismertetőt.

1. Ha nem vagy megelégedve a munkáddal, akkor még javíthatsz rajta. Ehhez kommitolj és pusholj újra. Ha továbbra is a megfelelő ágon dolgozol, akkor a _pull request_ újból le fogja futtatni a kiértékelést. Arra kérünk, hogy **MAXIMUM 5 alkalommal** futtasd le a kiértékelést!

    !!! tip "Megoldás javítása kiértékelés nélkül"
        Ha úgy látod, hogy a megoldásodat még javítani akarod, és nem szeretnéd, hogy mindig lefusson az értékelés, akkor állítsd át a pull request-et a webes felületen **draft** állapotra.

        ![GitHub create pull request](images/github/github-convert-pr-to-draft.png)

        Ezzel az állapottal jelzed, hogy még dolgozol. Kommitolj és pusholj. Ilyenkor nem fog futni kiértékelés. Ha végeztél, akkor vissza **kell** állítanod a pull request-et: menj a PR aljára és kattints a "Ready for review" gombra. Ennek hatására visszaáll a PR és le fog futni az automata értékelés.

        ![GitHub create pull request](images/github/github-draft-pr-ready.png)

    !!! info "Maximum 5"
        A maximum 5 alkalomba nem számoljuk bele az esetlegesen megszakadt, vagy tranziens hiba miatt sikertelen futtatásokat. Ha viszont figyelmetlenségből, vagy szándékosan túlléped az ötöt, akkor pontlevonással szankcionálunk. Arra kérünk, hogy beadás előtt **teszteld a megoldásod**, ne a GitHub platformot "dolgoztasd" magad helyett!

1. **VÉGEZETÜL**, ha kész vagy, a _pull request_-et rendeld a **gyakorlatvezetődhöz**. Ez a lépés feltétlenül fontos, ez jelzi a beadást.

    ![GitHub create pull request](images/github/github-create-pull-request-3.png)

    !!! error "Pull request nélkül"
        Ha nincs pull request-ed, vagy nincs a gyakorlatvezetőhöz rendelve, akkor úgy tekintjük, hogy még nem vagy készen, és nem adtad be a megoldást.

    !!! success "Végeztél"
        Miután a gyakorlatvezetőhöz rendelted a pull request-et, már **ne módosíts** semmin. A gyakorlatvezető értékelni fogja a munkádat, és a pull request lezárásával kommentben jelzi a végeredményt.

## Kapott eredménnyel kapcsolatban kérdés vagy reklamáció

Ha a feladatok értékelésével vagy az eredménnyel kapcsolatban kérdést tennél fel, vagy reklamálnál, használd a Pull Request kommentelési lehetőségét erre. Annak érdekében, hogy a gyakorlatvezető biztosan értesüljön a kérdésről használd a `@név` [mention](https://help.github.com/en/github/writing-on-github/basic-writing-and-formatting-syntax#mentioning-people-and-teams) funkciót a **gyakorlatvezetőd** megnevezéséhez. Erről automatikusan kapni fog egy email értesítést.

![GitHub PR kérdés](images/github/github-question-in-pr.png)

!!! warning "Reklamáció csak indoklással"
    Ha nem értesz egyet az értékeléssel, a bizonyítás téged terhel, azaz alá kell támasztanod a reklamációd (pl. annak leírásával, hogyan tesztelted a megoldásod, és mi bizonyítja a helyességét).
