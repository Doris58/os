Svoj sam program testirala na sljedeći način i dobivala sljedeće ponašanje:

******* TERMINAL 1 *********

doris@doris-VirtualBox:~/os/lab2$ ls
datoteke.c  datoteke.h  lab2.c  Makefile  readme.txt  signali.c  signali.h
doris@doris-VirtualBox:~/os/lab2$ make init
doris@doris-VirtualBox:~/os/lab2$ ls
cijev       datoteke.h  Makefile    readme.txt  signali.h
datoteke.c  lab2.c      obrada.txt  signali.c   status.txt
doris@doris-VirtualBox:~/os/lab2$ cat obrada.txt
1
doris@doris-VirtualBox:~/os/lab2$ cat status.txt
1
doris@doris-VirtualBox:~/os/lab2$ make pokreni
cc -Wall -MMD   -c -o lab2.o lab2.c
cc -Wall -MMD   -c -o signali.o signali.c
cc -Wall -MMD   -c -o datoteke.o datoteke.c
cc -O lab2.o signali.o datoteke.o -lm -lpthread -o lab2

Program je počeo s radom. PID = 18402 .

Upišite prvi broj u konzolu. U status se upisuje 0. 

3
Stvaram nove dretve...

ŽELJENI BROJ MOŽETE UPISIVATI U OVU KONZOLU! 

Dretva koja čita brojeve iz cijevi je počela s radom. 

Dretva koja radi obradu brojeva je počela s radom. 

Tražim zadnji obrađeni broj u datoteci. 
Zadnji broj = 1 . Krećem s radom.                       // u terminal 2: kill -SIGUSR1 18402
Signal SIGUSR1.
Trenutni broj koji se koristi u obradi = 5 . Nastavljamo dalje. // u terminal 2: kill -SIGUSR1 18402
Signal SIGUSR1.
Trenutni broj koji se koristi u obradi = 6 . Nastavljamo dalje. 
2
2                                                                 // u terminal 2: kill -SIGUSR1 18402
Signal SIGUSR1.
Trenutni broj koji se koristi u obradi = 3 . Nastavljamo dalje. 
Signal SIGUSR1.
Trenutni broj koji se koristi u obradi = 5 . Nastavljamo dalje. // u terminal 2: echo 3 > cijev
Broj pročitan iz cijevi: 3 .
Signal SIGUSR1.
Trenutni broj koji se koristi u obradi = 4 . Nastavljamo dalje. 
Signal SIGUSR1.
Trenutni broj koji se koristi u obradi = 5 . Nastavljamo dalje. // u terminal 2: echo 1 > cijev
Broj pročitan iz cijevi: 1 .
Signal SIGUSR1.
Trenutni broj koji se koristi u obradi = 3 . Nastavljamo dalje. 
56
Signal SIGUSR1.
Trenutni broj koji se koristi u obradi = 58 . Nastavljamo dalje.  // u terminal 2: kill -SIGTERM 18402
Primio signal SIGTERM. Pišem zadnji broj u status.txt. 
 Dretva koja obrađuje brojeve završava s radom. 
2
3
-3
Uneseni broj nije > 0. Glavni program prekida svoj rad. 
doris@doris-VirtualBox:~/os/lab2$ cat status.txt
58
doris@doris-VirtualBox:~/os/lab2$ cat obrada.txt
1
4
9
16
25
16
25
36
16
9
16
25
36
49
64
9
9
16
25
9
16
25
16
9
16
25
9
4
9
9
16
3249
3364
3249
3364
doris@doris-VirtualBox:~/os/lab2$ make pokreni

Program je počeo s radom. PID = 18453 .

Upišite prvi broj u konzolu. U status se upisuje 0. 

4
Stvaram nove dretve...

ŽELJENI BROJ MOŽETE UPISIVATI U OVU KONZOLU! 

Dretva koja čita brojeve iz cijevi je počela s radom. 

Dretva koja radi obradu brojeva je počela s radom. 

Tražim zadnji obrađeni broj u datoteci. 
Zadnji broj = 58 . Krećem s radom.
^Cmake: *** [Makefile:26: pokreni] Interrupt

doris@doris-VirtualBox:~/os/lab2$ cat status.txt
0
doris@doris-VirtualBox:~/os/lab2$ cat obrada.txt
1
4
9
16
25
16
25
36
16
9
16
25
36
49
64
9
9
16
25
9
16
25
16
9
16
25
9
4
9
9
16
3249
3364
3249
3364
3481
