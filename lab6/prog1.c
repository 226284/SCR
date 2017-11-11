#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#define ROZMIAR 1000 // rozmiar bufora
#define SHM_TESTMEM "/shm_testmem"

int main(){

  char str[100]; // string na nazwy
  char *buf; // bufor pomocniczy
  int size;
  int shmd;
  struct stat st;
  int fd1, fd2;
  pid_t childPID; // PID dziecka

  shmd = shm_open(SHM_TESTMEM, O_RDWR|O_CREAT, 0666);
    if (shmd == -1) {
      perror("Nie udało się utworzyć wspólnej pamięci");
      exit(1);
    }

    /*odpytanie użytkownika o nazwę pliku do odczytu*/
    printf ("Podaj nazwę pliku do odczytu: ");
    scanf ("%s", str);
    
    /*statystyka*/
    stat(str, &st);
    size = st.st_size;
    printf("Liczba bajtów: %d\n",size);
    
    
  if ((childPID = fork()) == -1) // jeśli operacja fork się nie powiodła
  {
    fprintf (stderr, "Fork error\n");
    exit(1);
  }

  if (childPID == 0){ // proces dziecka
    fd2 = shmd;
    close (0);
    dup (fd2);
    execl("/usr/bin/display", "display -update 1", NULL);
    fprintf (stderr, "execl failure\n"); // jeśli błąd display
  }
  
  else{ // proces rodzica

    fd1 = open (str, O_RDONLY, 0);
    ftruncate(shmd, size);
    buf = (char*)mmap(NULL, size, PROT_WRITE|PROT_READ, MAP_SHARED, shmd, 0);
    read (fd1, buf, size); // przepisujemy zawartość
    // write (1, buf, size);
    msync(buf, sizeof(buf), MS_SYNC);

    exit(0);
  }
}
