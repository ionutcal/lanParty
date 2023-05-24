In programul scris, cerintele incercate sunt 1, 2 si 3, iar cerinta 4 este scrisa in comentarii, ce se refera la construirea unui arbore de echipe si afisarea clasamentului cu ultimele 8 echipe in ordine descrescatoare, sub forma unui BST, dar nu sunt utilizate in implementarea finala a programului.


Solutia programului:

Am definit structura `Player` care stocheaza informatii despre un jucator: numele, punctajul.
Am definit structura `Team` care stocheaza informatii despre o echipa: numele echipei, jucatorii echipei, numarul de jucatori, punctajul echipei si referintele catre echipele stanga si dreapta (pentru construirea unui arbore de echipe, dar aceasta functionalitate este comentata in programul final).
Am implementat urmatoarele functii:
 - `removeExtraSpaces` care elimina spatiile suplimentare din fisierul de intrare.
 - `readPlayer` care citeste un jucator din fisierul de intrare si returneaza o structura `Player` cu informatiile corespunzatoare.
 - `readTeam` care citeste o echipa din fisierul de intrare si returneaza o structura `Team` cu informatiile corespunzatoare.
 - `printTeams` care afiseaza numele tuturor echipelor in fisierul de iesire.
 - `removeLowestScoreTeam` care elimina echipa cu cel mai mic punctaj dintr-un vector de echipe.
 - `printMatchQueue` care afiseaza perechile de echipe care se vor intalni intr-o runda in fisierul de iesire.
 - `printWinnersStack` care afiseaza echipele castigatoare ale unei runde in fisierul de iesire.

 In functia `main`, se deschid fisierele de intrare si de iesire. Apoi se apeleaza functiile pentru a citi echipele si jucatorii, se afiseaza echipele, si se initializeaza coada de meciuri cu echipele initiale.
 Intr-un loop while, se parcurg rundele pana cand raman doar 8 echipe.
 In fiecare runda, se afiseaza echipele si se construieste coada de meciuri din echipele ramase.
 Se parcurge coada de meciuri si se determina echipele castigatoare si pierzatoare pentru fiecare meci.
 Echipele pierzatoare sunt eliminate, iar echipele castigatoare sunt adaugate intr-un stiva.
 Se afiseaza echipele castigatoare si echipele eliminate din fiecare runda.
 Se reduce numarul de echipe si se repeta procesul pentru runda urmatoare.
 Dupa ce se termina runda finala, se afiseaza clasamentul final al echipelor si numarul total de runde.
 Fisierele de intrare si de iesire sunt inchise, iar memoria alocata dinamic este eliberata.

Functionalitatile comentate din programul final sunt legate de cerinta 4, ce se refera la construirea unui arbore de echipe si afisarea clasamentului cu ultimele 8 echipe in ordine descrescatoare, sub forma unui BST, dar nu sunt utilizate in implementarea finala a programului.

 !! Programul nu este finalizat, inca sunt multe erori si alte aspecte care nu sunt evidente, dar ce trebuiesc reparate !!
# lanParty
# lanPARTY
# lanParty
