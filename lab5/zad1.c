#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

  int fields[2];
  pid_t childPID;
  char str[100];
  char readstr[100];
  
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
    printf ("Odczytana nazwa: %s\n", str);
    
    write(fields[1], str, sizeof(str));
    
    exit(0);
  }
  else{
    close(fields[1]);

    printf ("Wypisanie w procesie dziecka: ");
    read (fields[0], readstr, sizeof(readstr));
    printf ("%s",readstr);

    exit(0);
  }

  return 0;
}
