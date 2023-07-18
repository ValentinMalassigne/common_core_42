#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include "../libft/headers/libft.h"

void    execute_on_file(char *command_path, char *command_options[4], int out_pipe[2], char **env)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        close(out_pipe[0]);
        dup2(out_pipe[1], STDOUT_FILENO);
        close(out_pipe[1]);
        execve(command_path, command_options, env);
    }
}

void    execute_on_string(char *command_path, char *command_options[3], int in_pipe[2], int out_pipe[2], char **env)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        close(in_pipe[1]);
        close(out_pipe[0]);
        dup2(out_pipe[1], STDOUT_FILENO);
        dup2(in_pipe[0], STDIN_FILENO);
        close(out_pipe[1]);
        close(in_pipe[0]);
        execve(command_path, command_options, env);
    }
}

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

char    *get_options(char *cmd_and_options)
{
    char    *options;
    int     i = 0;

    if (!cmd_and_options)
        return (NULL);
    while (*cmd_and_options && *cmd_and_options != ' ')
        cmd_and_options++;

    while (cmd_and_options[i] && cmd_and_options[i] != ' ')
        i++;
    if (i == 0)
        return (NULL);
    options = malloc((i +1) * sizeof(char));
    i = 0;
    while (cmd_and_options[i] && cmd_and_options[i] != ' ')
    {
        options[i] = cmd_and_options[i];
        i++;
    }
    options[i] = 0;
    return (options);
}

char    *get_command(char *cmd_and_options)
{
    char    *command;
    int     i = 0;

    if (!cmd_and_options)
        return (NULL);
    while (cmd_and_options[i] && cmd_and_options[i] != ' ')
        i++;
    if (i == 0)
        return (NULL);
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
    options = get_options(cmd_and_options);
    command_options[0] = command;
    if (options)
        command_options[1] = options;
    else
        command_options[1] = NULL;
    command_options[2] = NULL; 
    command_path = get_command_path(command, env);
    
    execute_on_string(command_path, command_options, in_pipe, out_pipe, env);
}

char    **setup_command_options(char *command_options[4], char *options, char *command, char *file_name)
{
    command_options[0] = command;
    if (options)
    {
        command_options[1] = options;
        command_options[2] = file_name; 
    }
    else
    {
        command_options[1] = file_name; 
        command_options[2] = NULL; 
    }
    command_options[3] = NULL;

    return (command_options);
}

void    call_command_on_file(char *cmd_and_options, char *file_name, int out_pipe[2], char **env)
{
    char    *command;
    char    *options;
    char    *command_options[4];
    char    *command_path;

    if (access(file_name, R_OK) != 0)
    {
        printf("Todo implement infile error\n");
        return ;
    }
    command = get_command(cmd_and_options);
    if (!command)
    {
        printf("TODO implement cmd = NULL\n");
        return ;
    }
    options = get_options(cmd_and_options);
    setup_command_options(command_options, options, command, file_name);
    command_path = get_command_path(command, env);
    if (!command_path)
    {
        printf("Todo implement command_path error\n");
        return ;
    }
    execute_on_file(command_path, command_options, out_pipe, env);
}

int main(int argc, char **argv, char **envp) {
    int in_pipe[2];
    int out_pipe[2];
    char cmd_output[4096];
    int i = 0;

    while (i < sizeof(cmd_output))
        cmd_output[i++] = 0;

    if(pipe(out_pipe) == -1)
    {
        printf("TODO pipe creation failure\n");
        return (-1);
    }

    call_command_on_file(argv[2], argv[1], out_pipe, envp);

    read(out_pipe[0], cmd_output, sizeof(cmd_output));

    close(out_pipe[0]);
    close(out_pipe[1]);
    printf("Output:%s\n", cmd_output);
    return (0);
}

// int main(int argc, char **argv, char **envp) {
//     int in_pipe[2];
//     int out_pipe[2];
//     char text[] = "Hello i'm a text from WAOUH SO GOOD\n";
//     char *command_and_options = "wc -l";
//     char cmd_output[4096];

//     int i = 0;
//     while (i < sizeof(cmd_output))
//         cmd_output[i++] = 0;
//     pipe(in_pipe);
//     pipe(out_pipe);

//     write(in_pipe[1], text, strlen(text));
//     close(in_pipe[1]);
    

//     call_command_on_string(command_and_options, in_pipe, out_pipe, envp);
//     read(out_pipe[0], cmd_output, sizeof(cmd_output));

//     close(in_pipe[0]);
//     close(out_pipe[0]);
//     close(out_pipe[1]);
//     printf("Output:%s", cmd_output);
//     return 0;
// }
