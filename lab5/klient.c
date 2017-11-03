#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define FIFO "/tmp/potok"
#define ROZMIAR 1000 // rozmiar bufora

int main(){

  int potok_fd, licz;
  char buf[ROZMIAR];
  
  potok_fd = open(FIFO, O_RDONLY); // otwarcie potoku w trybie czytania
  
  while ((licz = read (potok_fd, buf, ROZMIAR)) > 0){
    write (1, buf, licz); // wpisywanie otrzymanych danych ze strumienia 
  } // na standardowe wyjście
}
