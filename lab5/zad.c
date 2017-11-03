#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define ROZMIAR 1024 //rozmiar bufora

int main(){

  int fields[2]; // potok
  int fd1, fd2, fdin;
  pid_t childPID; // PID dziecka
  char str[100]; // string do nazwy obrazu
  char buf[ROZMIAR]; // bufor pomocniczy

  /*odpytanie użytkownika o nazwę pliku do odczytu*/
  printf ("Podaj nazwę pliku do odczytu: ");
  scanf ("%s", str);
  fd1 = open (str, O_RDONLY, 0); // otwarcie pliku i przekazanie na strumień we
  
  pipe(fields); // stworzenie potoku

  if ((childPID = fork()) == -1) // jeśli operacja fork się nie powiodła
  {
    fprintf (stderr, "Fork error\n");
    exit(1);
  }

  if (childPID == 0){ // proces dziecka
    close(0); // zamykamy wejście
    dup(fields[0]); // wstawiamy w jeo miejsce wejście strumienia
    close(fields[1]); // zamykamy drugi koniec strumienia - nie jest potrzebny
    
    execl("/usr/bin/display", "display", NULL); // uruchomienie display 
    fprintf (stderr, "execl failure\n"); // jeśli błąd display
    
    exit(0);
  }
  
  else{ // proces rodzica
    close(1); // zamykamy wyjście
    dup(fields[1]); // w jego miejsce wstawiamy drugi koniec potoku
    close (fields[0]); // zamykamy niepotrzebny potok
    
    while ((fdin = read (fd1, buf, ROZMIAR)) > 0){ // przepisujemy zawartość
      //printf ("%s", buf);
      write (fields[1], buf, fdin); // wpisywanie na wyjście, przemieści dane
      // na wejście procesu dziecka
    }
    
    exit(0);
  }

  return 0;
}
