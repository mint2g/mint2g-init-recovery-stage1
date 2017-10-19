
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

static int exec_script(const char **argv)
{
    pid_t   pid;
    int     status;

    if (0 == (pid = fork())) {
            if (-1 == execve(argv[0], (char **)argv , NULL)) {
                    perror("child process execve failed [%m]");
                    return -1;
            }
    }

    while (0 == waitpid(pid , &status , WNOHANG)) {
            sleep(1);
    }

    printf("%s WEXITSTATUS %d WIFEXITED %d [status %d]\n",
            argv[0], WEXITSTATUS(status), WIFEXITED(status), status);

    if (1 != WIFEXITED(status) || 0 != WEXITSTATUS(status)) {
            perror("%s failed, halt system");
            return -1;
    }
    return 0;
}

int main() {
	
	const char *script[4] = { "/stage1/busybox", "sh", "/stage1/init.sh", NULL };
	char *init_binary[2] = { "/init", NULL } ;    

	exec_script(script);
    execv( init_binary[0], init_binary );
 }