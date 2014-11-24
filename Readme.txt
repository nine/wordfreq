*** Szenario ***

Für einen Kunden wird ein kleines, einfaches Utility benötigt. Das 
Consolen-Programm soll mehrere als Parameter angegebene Textdatein einlesen, 
die einzelnen Wörter herausfiltern und für jedes Wort die Anzahl der 
Vorkommnisse zählen. Das Ergebnis ist in Form einer einfachen Tabelle mit zwei 
Spalten auszugegeben. Die erste Spalte enthält die gefundenen Wörter, die 
zweite Spalte die Anzahl der Vorkommnisse. Eine Sortierung oder Filterung der 
Ergebnisse ist nicht notwendig.
Es werden vom Kunden größere Dateien (~100MB) verarbeitet, daher sollte die
Verarbeitung der einzelnen Dateien parallelisiert werden. Weiters sollten die
häufigsten Fehlerfälle (File nicht vorhanden usw.) abgefangen werden.
Die Trennung in Wörter erfolgt einzig aufgrund von Whitespaces (Space,
LF, CR, ...), auf die Behandlung von Satzzeichen muss nicht eingegangen werden.

Siehe Datei Sample.txt für eine Beispieldatei.

Die folgende Datei

1:1 Adam Seth Enos
1:2 Cainan Adam Seth Iared

sollte folgende Tabelle als Ergebnis ausgeben:

Wort   Anzahl
1:1         1
Adam        2
Seth        2
Enos        1
1:2         1
Cainan      1
Iared       1
