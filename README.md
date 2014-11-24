wordfreq
========
C++ Programmierbeispiel


Kurzbeschreibung
----------------
Zum compilieren und testen der Aufgabe wurde zum Zweck der Einfachheit ein Makefile
verwendet. Jede Eingabedatei wird mit einen eigenen Thread wortweise gelesen; Die
Worthäufigkeiten werden in einem gemeinsamen assoziativem Array akkumuliert.

Das mitgelieferte Shellscript "wordfreq-multiproc.sh" soll eine alternative Form
der Parallelisierung mit Prozessen und Unix-Pipes illustrieren.


Build-System
------------
- Compilieren
```
$ make clean && make
```
- Einfacher Testlauf
```
$ make test
```

Abhängigkeiten / Debian(testing) Packete
----------------------------------------
Zum Erstellen des Programmierbeispiels war leider kein Ubuntu System zur Verfügung.
Ich gehe davon aus, dass die Distribution Debian(testing) die entsprechende
Kompatibilität zu Ubuntu aufweist. Folgende Pakete werden zum compilieren benötigt:
- build-essential
- libboost-system-dev
- libboost-program-options-dev
- libboost-thread-dev

--
am 03.07.2014

