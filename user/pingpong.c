#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int p[2];
char buf[512];

int
getlen (int n)
{
  int res = 0;
  while (n > 0) {
    n /= 10;
    res ++;
  }
  return res;
}

int
main(int argc, char *argv[])
{
  pipe(p);
  int pid = fork();
  if (pid == 0) {
    // exit(0);
    buf[0] = '<';
    write(1, buf, sizeof buf);    
    read(p[0], buf, sizeof buf);
    close(p[0]);
    write(1, buf, sizeof buf);
    printf(">: received ping\n");
    buf[0] = 'r';
    buf[1] = 'e';
    buf[2] = 'c';
    buf[3] = 'e';
    buf[4] = 'i';
    buf[5] = 'v';
    buf[6] = 'e';
    buf[7] = '\n';
    write(p[1], buf, sizeof buf);

    close(p[1]);
    exit(0);
  } else {
    // wait(0);
    // close(p[0]);
    int length =  getlen(pid);
    int len = length;
    char res[10];
    while (pid > 0) {
      int i = pid % 10;
      res[--len] = i + '0';
      pid /= 10;
    }
    write(p[1], res, length);
    close(p[1]);
    wait(0);
    read(p[0], res, sizeof res);
    write(1, res, sizeof res); 
  }
  exit(0);
}
