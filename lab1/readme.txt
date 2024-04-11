Svoj sam program testirala na sljedeći način i dobivala sljedeće ponašanje:

******* TERMINAL 1 *********

doris@doris-VirtualBox:~/os/lab1$ ls
lab1.c  Makefile  readme.txt
doris@doris-VirtualBox:~/os/lab1$ make init
doris@doris-VirtualBox:~/os/lab1$ ls
lab1.c  Makefile  obrada.txt  readme.txt  status.txt
doris@doris-VirtualBox:~/os/lab1$ cat obrada.txt
1
doris@doris-VirtualBox:~/os/lab1$ cat status.txt
1
doris@doris-VirtualBox:~/os/lab1$ make pokreni
cc lab1.c -Wall -O -lm -o lab1
Zadnji broj = 1 . Krećem s radom. PID = 26560 

**********************************************
NAKON PAR SEKUNDI :
**********************************************

******* TERMINAL 2 *********

doris@doris-VirtualBox:~$ kill -SIGUSR1 26560

**********************************************
ODMAH :
**********************************************

******* TERMINAL 1 *********

Signal SIGUSR1.
Trenutni broj koji se koristi u obradi = 6

**********************************************
NAKON NEKOLIKO SEKUNDI :
**********************************************

******* TERMINAL 2 *********

doris@doris-VirtualBox:~$ kill -SIGUSR1 26560

**********************************************
ODMAH :
**********************************************

******* TERMINAL 1 *********

Signal SIGUSR1.
Trenutni broj koji se koristi u obradi = 10

**********************************************
NAKON PAR SEKUNDI :  pritišćem  Ctr + c
**********************************************

^Cmake: *** [Makefile:20: pokreni] Interrupt

doris@doris-VirtualBox:~/os/lab1$ cat obrada.txt
1
4
9
16
25
36
49
64
81
100
121
144
169
196
225
256
289
doris@doris-VirtualBox:~/os/lab1$ cat status.txt
0
doris@doris-VirtualBox:~/os/lab1$ make pokreni
Program je bio prekinut. Tražim broj. 
Zadnji broj = 17 . Krećem s radom. PID = 26599 

**********************************************
NAKON PAR SEKUNDI :
**********************************************

******* TERMINAL 2 *********

doris@doris-VirtualBox:~$ kill -SIGTERM 26599

**********************************************
ODMAH :
**********************************************

******* TERMINAL 1 *********

Primio signal SIGTERM. Pišem zadnji broj u status.txt i završavam s radom. 
make: *** [Makefile:20: pokreni] Error 1
doris@doris-VirtualBox:~/os/lab1$ cat status.txt
21
doris@doris-VirtualBox:~/os/lab1$ cat obrada.txt
1
4
9
16
25
36
49
64
81
100
121
144
169
196
225
256
289
324
361
400
441
doris@doris-VirtualBox:~/os/lab1$ make obrisi
rm -rf lab1 status.txt obrada.txt
doris@doris-VirtualBox:~/os/lab1$ ls
lab1.c  Makefile  readme.txt




