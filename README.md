# Akustischer Abstandssensor

**Erstellt im Wahlkurs Elektronik am Gymnasium Mering**

## Komponenten für dieses Projekt

1. Arduino
2. Ultraschallsensor
3. Aktiv-Lautsprecher

## Funktion des Projekts

Bei diesem Sketch wird der Abstand bis zum nächsten Objekt gemessen und dann, genau wie bei einem Auto, ein akustisches Signal ausgegeben.
Jenachdem wie nah ein Objekt ist verändert sich das akustische Signal:
- Umso näher ein Objekt ist umso schneller Piepst das Signal
- Ab einem sehr nahem Abstand wird ein konstanter Dauerton ausgegeben

## Anwendungsmöglichkeiten im Alltag

- Diese Art von Akustischen Sensoren wird oft in Autos verwendet. In so gut wie jedem Auto heutzutage befinden sich Abstandsmesser, welche den Abstand zu Objekten runderhum um das Auto messen. Wenn das Auto zu nah an ein solches Objekt heranfährt, gibt es ein akustisches Warnsignal. Der Fahrer wird also unterstützt, um ihm das Einparken oder andere Aktionen zu erleichtern.

## Technische Umsetung

- An einen Arduino werden einem Ultraschallsensor und einem Aktiv-Lautsprecher angeschlossen
- Nun misst der Arduino in sehr kurzen Zeitabständen den Abstand zu einem vor ihm liegendem Objekt mithilfe des Ultraschallsensors
- Der Arduino berechnet mithilfe diesem Abstand welches Akustische Signal er ausgeben soll: 
  - Bei einem Abstand bis zu 23cm wird kein Signal ausgegeben
  - Bei einem Abstand von 23cm bis ca. 7cm wird ein variierendes Piepen ausgegeben
  - Ab einem Abstand von ca 7cm wird ein konstanter Dauerton ausgegeben

### Berechnung des Piepabstandes

1. Um ein Piep Geräusch zu erzeugen, muss der Lautsprecher des Arduinos immer für eine bestimmte Zeit angeschaltet und darauf für eine bestimmte Zeit ausgeschaltet sein
2. Also muss ein Zeitabstand zwischen dem Anschalten und Ausschalten in abhängigkeit des Abstandes `x` berechnet werden
3. Die Dauer des Piepsignals ist also 2 mal der Zeitabstand zwischen An- und Ausschalten des Lautsprechers
4. Diese wird in diesem Projekt mit einer Geraden der Form `y = m * x + t` berechnet, indiesem Fall mit der Geraden `f(x) = 31 * x - 218`
5. Um nun den Zeitabstand zu bekommen wird die Dauer des Signals geteilt durch 2 gerechnet 
```c++
puls = (31 * entfernung - 218) / 2; 
```
6. Nun wird überprüft ob dieser Zeitabstand kleiner wie Null ist und wenn dies zutrifft auf 0 gesetzt
```c++
if(puls < 0) {
  puls = 0;
}
```
7. - Wenn nun der Zeitabstand größer wie 30ms ist, wird ein Piepston ausgegeben, indem der Lautsprecher aktiviert wird und nach dem berechnetem Zeitabstand wieder deaktiviert wird. Darauf folgt eine kurze Pause, auch in der länge des Zeitabstandes, damit das konstante Piepen ereicht wird, welches ja durch Lautsprecher an für `z` Sekunden und Lautsprecher aus für `z` Sekunden erzeugt wird
```c++
if(puls >= 30) {
		  
  digitalWrite(piezo, HIGH);
  delay(puls);
  digitalWrite(piezo, LOW);
  delay(puls);
  return;

}
```
  - Wenn der Zeitabstand kleiner wie 30ms ist, wird der Lautsprecher einfach nur Eingeschaltet, unabhängig von dem berechnetem Zeitabstand. Das ist also das Warnsignal wenn ein Objekt zu nah ist 
