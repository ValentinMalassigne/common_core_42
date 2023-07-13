#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child process\n");
        sleep(2);
        printf("Child process exiting\n");
        return 0;
    } else if (pid > 0) {
        printf("Parent process\n");
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        }
    } else {
        printf("Fork failed\n");
    }
    return 0;
}
