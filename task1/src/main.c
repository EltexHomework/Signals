#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#define print_error(msg) do {perror(msg); \
  exit(EXIT_FAILURE);} while(0)

void handle_sigusr1(int sig_num);

int main(void) {
  struct sigaction handler;
  int result;
  
  /* Initialize sigation struct */
  handler.sa_handler = handle_sigusr1;
  
  /* Set signal handler */
  result = sigaction(SIGUSR1, &handler, NULL);
  if (result != 0)
    print_error("sigaction");
  
  printf("PID: %d\n", getpid());
  /* Wait until signal arrives */
  while (1) {
    sleep(1);
  }

  exit(EXIT_FAILURE);
}

/**
 * handle_sigusr1 - used as handler for SIG_USR1 signal 
 * in sigaction function.
 */
void handle_sigusr1(int sig_num) {
  printf("Signal SIGUSR1 - %d\n", sig_num);
}
