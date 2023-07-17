#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include "../libft/headers/libft.h"

char    *get_command_path(char *command, char **envp)
{
    int i;
    char    **path_list;
    while(envp[i])
    {
        if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H')
        {
            path_list = ft_split( envp[i], ':');
            break;
        }
        i++;
    }
    
    i = 0;
    while (path_list[i])
    {
        if (access(ft_strjoin(path_list[i],ft_strjoin("/",command)), X_OK) == 0)
            return(ft_strjoin(path_list[i],ft_strjoin("/",command)));
        i++;
    }

    return (NULL);
}

void    execute_on_string(char *command_path, char *command_options[3], int in_pipe[2], int out_pipe[2], char **env)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        //printf("command_path %s\n command_options0 %s\n command_options1 %s\n command_options2 %s\n", command_path, command_options[0],command_options[1],command_options[2]);
        close(in_pipe[1]);
        close(out_pipe[0]);
        dup2(out_pipe[1], STDOUT_FILENO);
        dup2(in_pipe[0], STDIN_FILENO);
        close(out_pipe[1]);
        close(in_pipe[0]);
        execve(command_path, command_options, env);
    }
}

void    split_cmd_and_options(char *cmd_and_options, char *command, char *options)
{
    int i;

    i = 0;
    while (cmd_and_options[i] != ' ' && cmd_and_options[i])
        i++;
    
    command = malloc((i + 1) * sizeof(char));
    
    while (*cmd_and_options != ' ' && *cmd_and_options)
        *command++ = *cmd_and_options++; 
    *command = 0;
    cmd_and_options++;
    i = 0;
    while (cmd_and_options[i] != 0)
        i++;
       
    options = malloc((i + 1) * sizeof(char));
    while (*cmd_and_options)
        *options++ = *cmd_and_options++;
    *options = 0;
}

char    *get_command(char *cmd_and_options)
{
    char    *command;
    int     i = 0;

    if (!cmd_and_options)
        return (NULL);
    while (cmd_and_options[i] && cmd_and_options[i] != ' ')
        i++;
    command = malloc((i + 1) * sizeof(char));
    i = 0;
    while (cmd_and_options[i] && cmd_and_options[i] != ' ')
    {
        command[i] = cmd_and_options[i];
        i++;
    }
    command[i] = 0;
    
    return (command);
}

void    call_command_on_string(char *cmd_and_options, int in_pipe[2], int out_pipe[2], char **env)
{
    char    *command;
    char    *options;
    char    *command_options[3];
    char    *command_path;

    command = get_command(cmd_and_options);
    command_options[0] = command;
    command_options[1] = NULL;
    command_options[2] = NULL; 
    command_path = get_command_path(command, env);
    
    execute_on_string(command_path, command_options, in_pipe, out_pipe, env);
}

int main(int argc, char **argv, char **envp) {
    int in_pipe[2];
    int out_pipe[2];
    char text[] = "Hello i'm a text from WAOUH SO GOOD\n";
    char *command_and_options = "wc -l";
    char cmd_output[4096];

    int i = 0;
    while (i < sizeof(cmd_output))
        cmd_output[i++] = 0;
    pipe(in_pipe);
    pipe(out_pipe);

    write(in_pipe[1], text, strlen(text));
    close(in_pipe[1]);

    call_command_on_string(command_and_options, in_pipe, out_pipe, envp);

    read(out_pipe[0], cmd_output, sizeof(cmd_output));
    
    // pipe(in_pipe);
    // write(in_pipe[1], cmd_output, strlen(cmd_output));
    // close(in_pipe[1]);
    // execute_on_string(in_pipe, out_pipe);

    // while (i < sizeof(cmd_output))
    //     cmd_output[i++] = 0;
    // read(out_pipe[0], cmd_output, sizeof(cmd_output));

    close(out_pipe[0]);
    close(out_pipe[1]);
    printf("Output:%s", cmd_output);
    return 0;
}


// int main2() {
//     int pipefd[2];
//     pid_t pid;
//     char *wc_options[] = { "wc", NULL };
//     char text[] = "This is the string to be counted by wc. WAOUH SO GOOD\n";

//     pipe(pipefd); // create a pipe
//     pid = fork(); // create a new process

//     if(pid == 0) {
//         printf("child\n");
//         // This is the child process
//         close(pipefd[1]); // close the write end of the pipe in the child
//         dup2(pipefd[0], STDIN_FILENO); // make stdin the read end of the pipe
//         execve("/usr/bin/wc", wc_options, NULL); // replace the child process with wc
//     } else {
//         printf("parent\n");
//         // This is the parent process
//         close(pipefd[0]); // close the read end of the pipe in the parent
//         write(pipefd[1], text, strlen(text)); // write the string to the pipe
//         close(pipefd[1]); // close the write end of the pipe
// 		wait(NULL);
// 		printf("hihihi\n");
// 	}
//     return 0;
// }
/*
void    execute_on_string(int in_pipe[2], int out_pipe[2])
{
    pid_t pid;
    char *wc_options[] = { "echo", NULL };
    
    pid = fork();

    if (pid == 0)
    {
        close(in_pipe[1]);
        close(out_pipe[0]);
        dup2(out_pipe[1], STDOUT_FILENO);
        dup2(in_pipe[0], STDIN_FILENO);
        close(out_pipe[1]);
        close(in_pipe[0]);
        execve("/usr/bin/echo", wc_options, NULL);
    }
}



int main() {
    int in_pipe[2];
    int out_pipe[2];
    char text[] = "Hello i'm a text from \n";
    char cmd_output[4096];

    int i = 0;
    while (i < sizeof(cmd_output))
        cmd_output[i++] = 0;
    pipe(in_pipe);
    pipe(out_pipe);

    write(in_pipe[1], text, strlen(text));
    close(in_pipe[1]);

    execute_on_string(in_pipe, out_pipe);
    read(out_pipe[0], cmd_output, sizeof(cmd_output));

    close(out_pipe[0]);
    close(out_pipe[1]);
    printf("Output length : %lu\n", strlen(cmd_output));
    printf("Output: %s", cmd_output);
    return 0;
}
*/