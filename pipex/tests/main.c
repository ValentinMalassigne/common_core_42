#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 4096

char	*ft_strjoin_gnl(char *s1, const char *s2)
{
	char	*res;
	size_t	i;

	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		*s1 = 0;
	}
	if (!s1 || !s2)
		return (NULL);
	res = malloc((strlen((const char *)s1) + strlen(s2) + 1)
			* sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	while (*s2)
		res[i++] = *s2++;
	res[i] = 0;
	free(s1);
	return (res);
}
#include <sys/wait.h>
int main3() {
   pid_t pid = fork();
    if (pid == 0) {
        char    *test1 = malloc(1);
        printf("Child process\n");
        char *args[] = {"ls", "-l", NULL};
        char *env[] = {NULL};
        execve("/bin/ls", args, env);
        printf("This line will not be executed\n");
    } else if (pid > 0) {
        char    *test2 = malloc(10);
        printf("Parent process\n");
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        }
        pid_t pid = fork();
        if (pid == 0) {
            char    *test3 = malloc(100);
            printf("Child process2\n");
            char *args[] = {"ls", "-l", NULL};
            char *env[] = {NULL};
            execve("/bin/ls", args, env);
            printf("This line will not be executed\n");
        }
        char    *test4 = malloc(1000);
        printf("Parent process2\n");
        
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Child process2 exited with status: %d\n", WEXITSTATUS(status));
        }
    } else {
        printf("Fork failed\n");
    }


    return 0;
}

//des leaks mais on les voit pas !!!!!!
int main()
{
    pid_t pid = fork();
    int     status;
    if (pid == 0)
    {
        char *test = malloc(100);
        char *args[] = {"ls", "-l", NULL};
        char *env[] = {NULL};
        execve("/bin/ls", args, env);
    }
    else
        waitpid(pid, &status, 0);
    return (0);
}

//Des leaks mais on peut les voir :)
int main2()
{
    pid_t pid = fork();
    pid_t pid2;
    int     status;
    if (pid == 0)
    {
        char *test = malloc(100);
        pid2 = fork();
        if (pid2 == 0)
        {
            char *args[] = {"ls", "-l", NULL};
            char *env[] = {NULL};
            execve("/bin/ls", args, env);
        }
        else   
            waitpid(pid2, &status, 0);
    }
    else
        waitpid(pid, &status, 0);
    return (0);
}
