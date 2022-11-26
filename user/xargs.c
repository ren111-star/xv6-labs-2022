#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void child(int p[], char* method) {
    if (!method) {
        method = "echo";
    }
    char buf[512];
    close(p[1]);
    int len;
    while ((len = read(p[0], buf, sizeof buf)) > 0) {
        char* argv[3];
        argv[0] = method;
        argv[1] = buf;
        argv[2] = 0;
        exec(method, argv);
        fprintf(2, "exec error\n");
    }
    exit(0);
}

int main (int argc, char *argv[])
{
    while (1)
    {
        int p[2];
        pipe(p);
        int pid = fork();
        if (pid > 0)
        {
            char buf[512];
            int len = read(0, buf, sizeof buf);
            write(p[1], buf, len - 1);
            close(p[1]);
            wait(0);
        }
        else {
            child(p, argv[1]);
        }
        
    }

    exit(0);
}