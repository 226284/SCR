#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#define int FLAGA=0

void sig_handler(int signo) {
  if (signo == SIGINT){
    printf("found:SIGINT\n");
    exit(0);
  }
  else if (signo == SIGTERM) {
    printf("found:SIGTERM\n");
  }
  else if (signo == SIGUSR1) {
    FLAGA=1;
  }
  else if (signo == SIGALRM) {

  }
}

int main(){
  int j=0;
  
  if (signal(SIGINT, sig_handler) == SIG_ERR) {
    printf("\nNie można złapać SIGINT\n");
  }
  if (signal(SIGTERM, sig_handler) == SIG_ERR) {
    printf("\nNie można złapać SIGTERM\n");
  }
  if (signal(SIGUSR1, sig_handler) == SIG_ERR){
    printf("cs");
  }
  if (signal(SIGALRM, sig_handler) == SIG_ERR) {
  }
  
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = 10000000;

  while (1){
    nanosleep(&ts,NULL);
    printf("SPAM\n");
    if (FLAGA == 1){
      ignore;
      j++;
      if(j == 1000){
	FLAGA == 0)
	}
  }
  
  return 0;
}
    
