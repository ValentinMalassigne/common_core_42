#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char *wc_args[] = { "wc", NULL };
    char text[] = "This is the string to be counted by wc.\n";

    pipe(pipefd); // create a pipe
    pid = fork(); // create a new process

    if(pid == 0) {
		printf("Child\n");
        // This is the child process
        close(pipefd[1]); // close the write end of the pipe in the child
        dup2(pipefd[0], STDIN_FILENO); // make stdin the read end of the pipe
        execve("/usr/bin/wc", wc_args, NULL); // replace the child process with wc
    } else {
		printf("Parent\n");
        // This is the parent process
        close(pipefd[0]); // close the read end of the pipe in the parent
        write(pipefd[1], text, strlen(text)); // write the string to the pipe
        close(pipefd[1]); // close the write end of the pipe
    }

    return 0;
}
