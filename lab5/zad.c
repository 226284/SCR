#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

  int i = 0;
  int fields[2];
  pid_t childPID;
  char str[100];
  FILE *pic;
  char buf[1000000];
  
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
    while (fgets(buf, sizeof(buf), pic)){
      //printf ("%s", buf);
      write(fields[1], buf, sizeof(buf));
    }
    
    fclose(pic);
    
    exit(0);
  }
  else{
    close(fields[1]);
    
    while (!feof(stdin)){
      read(fields[0], buf, sizeof(buf));
      printf("%s", buf);
      i++;
    }
    
    execl("/usr/bin/display", "display", NULL);
    fprintf (stderr, "execl failure\n");
    exit(0);
  }

  return 0;
}
