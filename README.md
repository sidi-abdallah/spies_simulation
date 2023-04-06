# "License to kill" project 

# Authors : 
## Mohamed El-Mokhtar SIDI-ABDALLAH
## Youssef AGHZERE
## Colin HARTVICK
## Mohamed CHERGUI
## Ayoub ED-DAHMANY  




## Introduction 
The aim of this project is to implement all the knowledge acquired in lectures and practical exercises on operating systems, 
in order to create a multiprocess application around the world of espionage. Specifically, we used various interprocess
communication mechanisms (signals, pipes, message queues, and shared memory), threads, as well as synchronization techniques
such as semaphores and/or mutexes, and eventually file locks.

The project was developed in the course of two months, and was carried out in teams of five using an agile project management approach.

## Context
In this project, we aimed to create a simulation consisting of distinct processes that implement the information retrieval 
of a foreign espionage network. This network comprises of spy agents responsible for collecting sensitive information from 
companies located in the city, and a case officer responsible for gathering and transmitting the collected information to 
their superiors. Furthermore, the simulation also depicts the counterintelligence officer's efforts to thwart this espionage network.

The simulation consists of 2016 rounds, equivalent to two weeks, with each round representing 10 fictitious minutes. 
The duration of each round varies from 0.1 to 1 second, depending on the desired animation speed. The simulation begins
on a Monday at 0:00 hours.

## interaction between programs (processus)
The simulator consists of at least 7 distinct programs that interact with each other and share resources.

##### The "spy_simulation" : 
Manages the city and the information about the characters that populate it. 
To do this, it creates a shared memory containing data structures for managing the city, its surveillance network,
and the characters' status. Additionally, it handles communication with other processes via named pipes, signals, etc.

#####The "citizen_manager" :
Manages all threads associated with the city's citizens and also accesses all or part of the shared memory.
The "enemy_spy_network" program manages the spy network consisting of threads associated with source agents and the handling officer. 
It also accesses all or part of the shared memory.

##### The "counterintelligence_officer" :
Manages the functioning of the counter-espionage officer and also accesses all or part of the shared memory.

##### The "enemy_country" :
Receives encrypted messages from the spy network and continuously displays them on a teleprinter,
except for any "misleading" messages it has also received. Communication between the spy network program and "enemy_country" 
is established via a unique message queue.

##### The "timer" : 
Periodically indicates the end of a turn to "spy_simulation". The actual duration of a turn is transmitted during its launch, 
and except in case of spy network dissolution, a signal is sent to all other ongoing processes after 2016 turns. This program can also access all 
or part of the shared memory.

##### The "monitor" : 
Allows monitoring of the simulation via a textual interface.


## Install the program

Run the following commands :
> make distclean //To make sure there are no stains left

> make

## Run the program
In different terminals, run the following command in the same order :
> ./bin/spy_simulation

> ./bin/citizen_manager

> ./bin/enemy_spy_simulation

> ./bin/counterintelligence_officer

> ./bin/timer

> ./bin/monitor


