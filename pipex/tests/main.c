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

int main() {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Fork a child process
    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process: Write data to the pipe
        close(pipe_fd[0]); // Close the read end of the pipe

        // Redirect stdout to the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);

        // Execute a command (replace "your_command" with the actual command)
        execlp("ls", "ls", NULL);

        // If execlp fails
        perror("execlp failed");
        return 1;
    } else {
        // Parent process: Read data from the pipe
        close(pipe_fd[1]); // Close the write end of the pipe

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read = 1;
        size_t total_bytes_read = 0;
        char    *res = NULL;

        while (bytes_read > 0) {
            bytes_read = read(pipe_fd[0], buffer, 3);
            total_bytes_read += bytes_read;
            
            res = ft_strjoin_gnl(res, buffer);
            memset(buffer, 0, bytes_read);
        }

        if (bytes_read == -1) {
            perror("Read error");
            return 1;
        }
        printf("res : %s",res);
        printf("Total bytes read: %zu\n", total_bytes_read);
    }

    return 0;
}
