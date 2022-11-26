#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main (int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(2, "Usage: stop num...\n");
    exit(1);
  }
  else if (argc > 2) {
    fprintf(2, "Usage: stop num over ...\n");
    exit(1);    
  }
  int n;
  n = atoi(argv[1]);
  sleep(n);
  write(1, "sleep end\n", 10);
  exit(0);
}
