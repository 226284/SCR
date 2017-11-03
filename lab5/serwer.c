#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define FIFO "/tmp/potok"
#define MESS \
  "Komunikat\n"
#define ROZMIAR 1000 // rozmiar bufora

int main(){

  int potok_fd, fd1, fd2; // potoki
  char str[100]; // string na nazwy
  char buf[ROZMIAR]; // bufor pomocniczy

  potok_fd = open(FIFO, O_WRONLY); // otwarcie potoku w trybie pisania
  
  while (1){
    /*odpytanie użytkownika o nazwę pliku do odczytu*/
    printf ("Podaj nazwę pliku do odczytu: ");
    scanf ("%s", str); 
    
    fd1 = open (str, O_RDONLY, 0); // otwieranie poszczególnych plików
    
    while ((fd2 = read (fd1, buf, ROZMIAR)) > 0){
      write (potok_fd, buf, fd2); // i zapisywanie do potoku
    }
  }
}
