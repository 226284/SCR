#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#define POSIX_SOURCE
#define SHM_TESTMEM "/shm_testmem"
#define MODES 0666

struct shared_struct {
  int client_wrote;
  char text[BUFSIZ];
};

int main(){
  struct shared_struct *shared_mem;
  int shmd, shared_size;
  char str[100]; // string na nazwy
  int size;
  struct stat st;
  
  /*odpytanie użytkownika o nazwę pliku do odczytu*/
  printf ("Podaj nazwę pliku do odczytu: ");
  scanf ("%s", str); 
  
  /*statystyka*/
  stat(str, &st);
  size = st.st_size;
  printf("Liczba bajtów: %d\n",size);
  
  // na wszelki wypadek
  printf("Probuje usunac istniejacy obszar wspolny...\n");
  if(shm_unlink(SHM_TESTMEM) < 0)
    perror("nie moge usunac obszaru pamieci");
  else printf("Obszar pamieci wspolnej usuniety.\n");

  shmd = shm_open(SHM_TESTMEM, O_RDWR|O_CREAT, MODES);
  if (shmd == -1) {
    perror("shm_open padlo");
    exit(errno);
  }
  shared_size = sizeof(struct shared_struct);
  ftruncate(shmd, shared_size);
  shared_mem = (struct shared_struct *)
    mmap(NULL,shared_size,PROT_READ|PROT_WRITE,MAP_SHARED,shmd,0);
  srand((unsigned int)getpid());
  shared_mem->client_wrote = 0;
  do {
    printf("Czekam na dane ...\n");
    sleep( rand() % 4 );
    /* troche czekamy */
    if (shared_mem->client_wrote) {
      printf("Otrzymalem: \"%s\"\n", shared_mem->text);
      sleep( rand() % 4 );      /* znow troche poczekajmy */
      shared_mem->client_wrote = 0;
    }
  }
  while (strncmp(shared_mem->text, "koniec", 6) != 0);
  munmap((char *)shared_mem, shared_size);
  return 0;
}
