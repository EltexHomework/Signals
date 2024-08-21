#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

#define print_error(msg) do {perror(msg); \
  exit(EXIT_FAILURE);} while(0)

int main(void) {
  int result;
  int sig_num;
  sigset_t set;
  
  /* Initialize sigset_t object */
  sigemptyset(&set);
  sigaddset(&set, SIGUSR1);
  
  /* Add SIGUSR1 to blocked signals */
  result = sigprocmask(SIG_BLOCK, &set, NULL);
  if (result != 0)
    print_error("sigprocmask");
  
  printf("PID: %d\n", getpid());
  /* Wait for SIGUSR1 signals */
  while (1) {
    sigwait(&set, &sig_num);
    printf("Signal - %d\n", sig_num);
  }

  exit(EXIT_SUCCESS);
}
