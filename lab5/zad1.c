#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

  int fields[2];
  pid_t childPID;
  char str[100];
  char readstr[100];
  FILE *pic;
  FILE *new;
  
  pipe(fields);

  if ((childPID = fork()) == -1)
  {
    fprintf (stderr, "Fork error\n");
    exit(1);
  }

  if (childPID == 0){
    close(fields[0]);
    
    /*odpytanie użytkownika o nazwę pliku do odczytu*/
    printf ("Podaj nazwę pliku do odczytu: ");
    scanf ("%s", str);
    //printf ("Odczytana nazwa: %s\n", str);

    pic = fopen (str, "r");
    
    /* wysyłanie obrazka do procesu potomnego*/
    write(fields[1], pic, sizeof(pic));

    fclose(pic);
    
    exit(0);
  }
  else{
    close(fields[1]);
    close(0);
    dup(fields[0]);
    
    execl("/usr/bin/display", "display", NULL);
    fprintf (stderr, "execl failure\n");
    exit(0);
  }

  return 0;
}
