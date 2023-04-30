# Proiect PA 2023 - CrazyHouse Chess Bot
__Nume echipă: Daudecrapastiva__

__Membri:__
* Șerban Andrei-Teodor, 324CC
* Pințoiu Alina-Diana, 324CC
* Dascălu Ștefan-Teodor, 324CC
* Petracovici Tudor, 324CC

__Limbaj__: C++

## Instrucțiuni de compilare

```
make build # construiește binarul Main
make run # rulează engine-ul care se conectează la xboard
make clean # șterge toate binarele și fișierele de debug
```

## Structura proiectului
Proiectul constă în crearea unui bot de șah care să joace varianta [CrazyHouse](https://www.chess.com/article/view/crazyhouse-chess).

Acesta folosește platforma [Xboard](https://www.gnu.org/software/xboard/) și este construit pentru sisteme Linux/GNU.

### Etapa 1
Pentru prima etapă, scopul nostru a fost să avem un bot care răspunde cu mișcări aleatorii dar valide. Pentru acest lucru am folosit scheletul de cod oferit de echipa PA, deci singurele funcții pe care a trebuit să le completăm sunt `recordMove()`, care înregistrează într-o reprezentare internă a engine-ului fiecare mișcare făcută pe tabla de șah, și `calculateNextMove()`, care trimite o mișcare validă în funcție de cum i s-a modificat reprezentarea internă a mișcărilor.
#### Reprezentare internă a tablei de șah
Am creat clasa `Pis` (`Piece` era luat de enumerația din schelet lmao), unde ținem minte informații adiționale despre fiecare piesă de pe tablă în parte, în afară de tipul piesei, cum ar fi flaguri logice utile pentru mișcări cum ar fi en passant sau rocadă.

Clasa `Bot` din schelet primește ca și câmp intern un tablou bidimensional de 8X8 de obiecte de tip `Pis`, numit `chessBoard`, reprezentând tabla de șah, iar în constructorul clasei se inițializează tabla de șah așa cum este ea la începutul oricărui meci de șah.

Metoda `recordMove()` parsează mișcarea primită de la xboard în coordonate ale matricei `chessBoard` și actualizează matricea astfel încat mutarea să fie efectuată, cu promoție sau drop in, acolo unde mișcarea specifică acest lucru. În fișierul `out.txt`, folosit pentru debugging, se actualizează, dupa fiecare mișcare, o vizualizare simplă a matricei interne pe care o folosește botul, precum și un text care anunță dacă botul se află în șah sau nu, care folosește metoda `isCheck()` a botului.

Metoda `isCheck()` primește ca parametru reprezentarea internă a tablei de șah (deoarece uneori este nevoie de o copie a acesteia pentru a verifica mișcări valide, altfel nu era nevoie de parametru și se putea folosi doar câmpul clasei) și iterează prin ea până găsește poziția pe care se află regele. După aceea, verifică fiecare linie, coloană și diagonală care are regele în mijloc pentru piese inamice ce pot amenința regele. Dacă se găsește o piesă a botului sau o piesă a inamicului, dar care nu poate amenința pe direcția respectivă, se verifică următoarea direcție, altfel dacă se găsește o piesă a inamicului ce poate amenința pe direcția aceea înainte de oricare altă piesă, se returnează true. Întâi se verifică dacă este amenințat pe direcția verticală și orizontală, după aceea se verifică diagonalele, iar după aceea pionii sunt tratați separat, în funcție de culoare, deoarece reprezentarea internă a tablei are întotdeauna jucătorul negru în partea superioară și la final sunt tratate cele 8 poziții ale cailor.
#### Alegerea următoarei mișcări
Ideea generală a alegerii mișcării pe care să o trimită botul la orice mișcare trimisă de oponent constă în construirea unui vector `allMoves` unde sunt trecute toate mișcările valide pe care le poate face botul conform reprezentării în `chessBoard` la momentul respectiv. Acest vector se construiește în metoda `calculateNextMove`, care la final returnează, folosind funcția `rand()`, un element aleator din vector ca mișcare de trimis către xboard. Pentru a aduna în `allMoves` toate mișcările valide, metoda apelează, pentru fiecare tip de piesă în parte, metode de forma `get*Move`, unde * = {Pawn, Knight, Rook, Bishop, Queen, King, Castle, DropIn}.
### Etapa 2
TODO
## Abordare algoritmică
### Etapa 1
TODO
### Etapa 2
TODO
## Responsabilitățile membrilor
Gândirea generală a soluției a fost un efort comun, dar fiecare membru al echipei a depus efort particular în următoarele:

* Ștefan și Tudor - implementare cod
* Diana - testare
* Andrei - scriere documentație
## Surse
TODO