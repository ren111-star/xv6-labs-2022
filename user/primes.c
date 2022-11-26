#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char buf[1024];
	
void
child (int p[])
{
  close(p[1]);
  int i;
  if (read(p[0], &i, sizeof(i)) == 0)
  {
    close(p[0]);
    exit(0);
  }
  printf("primes %d\n", i);
  int num = 0;
  int fds_c2gc[2];
  pipe(fds_c2gc);
  int pid = fork();
  if (pid == 0) {
    child(fds_c2gc);
  }
  else
  {
    close(fds_c2gc[0]);
    while (read(p[0], &num, sizeof(num)) > 0) {
      if (num % i != 0) {
        write(fds_c2gc[1], &num, sizeof(num));
      }
    }

    close(fds_c2gc[1]);
    wait(0);
  }

  exit(0);
}

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);
  int pid = fork();
  if (pid > 0) {
    for (int i = 2; i <= 35; i ++ ) {
      write(p[1], &i, sizeof(i));
    }
    close(p[1]);
    wait(0);
  } else{
    child(p);
  }
  exit(0);
}
