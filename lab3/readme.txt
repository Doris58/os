Svoj sam program testirala na sljedeći način i dobivala sljedeće ponašanje:

******* TERMINAL 1 *********

doris@doris-VirtualBox:~/os/lab3$ make obrisi
rm -rf lab3.o signali.o datoteke.o lab3.d signali.d datoteke.d lab3 status.txt obrada.txt cijev
doris@doris-VirtualBox:~/os/lab3$ make init
doris@doris-VirtualBox:~/os/lab3$ cat obrada.txt
1
doris@doris-VirtualBox:~/os/lab3$ make pokreni
cc -Wall -MMD   -c -o lab3.o lab3.c
cc -Wall -MMD   -c -o signali.o signali.c
cc -Wall -MMD   -c -o datoteke.o datoteke.c
cc -O lab3.o signali.o datoteke.o -lm -lpthread -o lab3

Program je počeo s radom. PID = 18293 .

Upišite prvi broj u konzolu. U status se upisuje 0. 

3
Stvaram nove dretve...

ŽELJENI BROJ ZA OBRADU MOŽETE UPISIVATI U OVU KONZOLU! 

Dretva koja kontrolira broj radnih dretvi je počela s radom. 

Želim da bude 3 radnih dretvi.

Dretva 2 traži zadnji obrađeni broj u datoteci. 
Dretva 2: zadnji broj = 1 . Krećem s radom.
Dretva koja čita brojeve iz cijevi je počela s radom. 

Želim da bude 9 radnih dretvi.

Želim da bude 7 radnih dretvi.

Dretva 8  koja radi obradu brojeva prestaje s radom. 

Želim da bude 9 radnih dretvi.

2                                              // UPIS BROJA U KONZOLU!
Želim da bude 2 radnih dretvi.

Dretva 8  koja radi obradu brojeva prestaje s radom. 

Dretva 2  koja radi obradu brojeva prestaje s radom. 

Dretva 7  koja radi obradu brojeva prestaje s radom. 

Dretva 9  koja radi obradu brojeva prestaje s radom. 

Dretva 5  koja radi obradu brojeva prestaje s radom. 

Dretva 3  koja radi obradu brojeva prestaje s radom. 

Dretva 6  koja radi obradu brojeva prestaje s radom. 

Želim da bude 4 radnih dretvi.

2                                              // UPIS BROJA U KONZOLU!
Želim da bude 10 radnih dretvi.

Želim da bude 8 radnih dretvi.

Dretva 10  koja radi obradu brojeva prestaje s radom. 

Dretva 2  koja radi obradu brojeva prestaje s radom. 

Želim da bude 2 radnih dretvi.

Dretva 3  koja radi obradu brojeva prestaje s radom. 

Dretva 6  koja radi obradu brojeva prestaje s radom. 

Dretva 5  koja radi obradu brojeva prestaje s radom. 

Dretva 11  koja radi obradu brojeva prestaje s radom. 

Dretva 7  koja radi obradu brojeva prestaje s radom. 

Dretva 8  koja radi obradu brojeva prestaje s radom. 

Želim da bude 5 radnih dretvi.

Želim da bude 2 radnih dretvi.

Dretva 4  koja radi obradu brojeva prestaje s radom. 

Želim da bude 1 radnih dretvi.

Dretva 9  koja radi obradu brojeva prestaje s radom. 

Dretva 2  koja radi obradu brojeva prestaje s radom. 

Dretva 5  koja radi obradu brojeva prestaje s radom. 

Želim da bude 4 radnih dretvi.

Želim da bude 7 radnih dretvi.
                                                            // u terminal 2: kill -SIGTERM 18293
Primio signal SIGTERM. Pišem zadnji broj u status.txt. 
 Dretve koje obrađuju brojeve završavaju s radom. 
-5                                                          // UPIS BROJA U KONZOLU!
Uneseni broj nije > 0. Glavni program prekida svoj rad. 
doris@doris-VirtualBox:~/os/lab3$ cat obrada.txt
1
16
9
4
25
36
49
64
81
100
121
144
169
361
400
441
324
256
225
289
196
484
529
729
676
625
841
784
576
900
961
4
9
36
16
25
49
4
36
49
64
81
100
121
25
16
9
225
196
169
144
256
289
324
361
441
484
625
400
576
529
676
729
900
841
784
961
1024
1225
1296
1156
1089
1369
1521
1444
1600
1681
1764
2116
1936
1849
2025
2209
2304
doris@doris-VirtualBox:~/os/lab3$ cat status.txt
49
doris@doris-VirtualBox:~/os/lab3$ make pokreni

Program je počeo s radom. PID = 18379 .

Upišite prvi broj u konzolu. U status se upisuje 0. 

3
Stvaram nove dretve...

ŽELJENI BROJ ZA OBRADU MOŽETE UPISIVATI U OVU KONZOLU! 

Dretva koja kontrolira broj radnih dretvi je počela s radom. 

Želim da bude 3 radnih dretvi.

Dretva koja čita brojeve iz cijevi je počela s radom. 

Dretva 4 traži zadnji obrađeni broj u datoteci. 
Dretva 4: zadnji broj = 48 . Krećem s radom.
Želim da bude 10 radnih dretvi.

Želim da bude 7 radnih dretvi.

2
Dretva 2  koja radi obradu brojeva prestaje s radom. 

Želim da bude 9 radnih dretvi.

^Cmake: *** [Makefile:26: pokreni] Interrupt

doris@doris-VirtualBox:~/os/lab3$ cat obrada.txt
1
16
9
4
25
36
49
64
81
100
121
144
169
361
400
441
324
256
225
289
196
484
529
729
676
625
841
784
576
900
961
4
9
36
16
25
49
4
36
49
64
81
100
121
25
16
9
225
196
169
144
256
289
324
361
441
484
625
400
576
529
676
729
900
841
784
961
1024
1225
1296
1156
1089
1369
1521
1444
1600
1681
1764
2116
1936
1849
2025
2209
2304
2601
2500
2401
2704
3025
2916
3364
3481
3600
3721
3136
3249
2809
3844
4225
4096
4356
4489
4624
3969
4761
4900
5041
doris@doris-VirtualBox:~/os/lab3$ ls
cijev       datoteke.d  datoteke.o  lab3.c  lab3.o    obrada.txt  signali.c  signali.h  status.txt
datoteke.c  datoteke.h  lab3        lab3.d  Makefile  readme.txt  signali.d  signali.o
doris@doris-VirtualBox:~/os/lab3$ make obrisi
rm -rf lab3.o signali.o datoteke.o lab3.d signali.d datoteke.d lab3 status.txt obrada.txt cijev

