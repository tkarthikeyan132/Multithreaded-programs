# The Carbird Fury game

## **Description:**
 This Project is done as a part of the OS course. It is a simple game created using ncurses.h library of C on the *LINUX* OS.

## **Make sure to install ncurses Library**

Command:
For Debian/Ubuntu Linux
sudo apt-get install libncurses5-dev libncursesw5-dev

## **Execution method:**
To execute the `main_experiment.c`
  * `cd` into the project directory and run
    > `make`
  * Then run
    > `./exp`

## **In Case above execution method doesn't work**
To compile the code:
gcc -o exp main_experiment.c -lncurses -lpthread
./exp
