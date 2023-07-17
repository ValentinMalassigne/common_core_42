/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 07:09:31 by vmalassi          #+#    #+#             */
/*   Updated: 2023/07/17 10:06:03 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

/*
The goal :
./pipex file1 cmd1 cmd2 file2
==
< file1 cmd1 | cmd2 > file2
*/

#define die(e) do { fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE); } while (0);

void	run_command_on_file(int link[2], char *command, char *file, char **env)
{
	pid_t pid;
	if ((pid = fork()) == -1){
		die("fork");
	}
	if (pid == 0)
	{
		dup2 (link[1], STDOUT_FILENO);
		close(link[0]);
		char *args[] = {ft_strjoin("/bin/", command), file, NULL};
		execve(args[0], args, env);
		die("execl");
	}
}

void	run_command_on_stdin(int link[2], char *command,char *content, char **env)
{
	pid_t pid;
	if ((pid = fork()) == -1){
		die("fork");
	}
	if(pid == 0) {
        // This is the child process
        close(link[1]); // close the write end of the pipe in the child
        dup2(link[0], STDIN_FILENO); // make stdin the read end of the pipe
        char *args[] = {command, NULL};
		execve(ft_strjoin("/bin/", command), args, env); // replace the child process with wc
		die("execl");
    } else {

        // This is the parent process
        close(link[0]); // close the read end of the pipe in the parent
        write(link[1], content, ft_strlen(content)); // write the string to the pipe
        close(link[1]); // close the write end of the pipe
    }

}

int main(int argc, char **argv, char **env)
{
	if (argc == 5)
	{
		char cmd_output[4096];

		int link[2];
		if (pipe(link) == -1){
			die("pipe");
		}
		run_command_on_file(link, argv[2], argv[1], env);

		read(link[0], cmd_output, sizeof(cmd_output));
		
		cmd_output[sizeof(cmd_output)- 1] = 0;
		ft_printf("length : %d\n", ft_strlen(cmd_output));
		run_command_on_stdin(link, argv[3],cmd_output, env);
		close(link[1]);

		ft_printf("Output: %s\n", cmd_output);
	}
	else
	{
		ft_printf("Wrong number of parameters\n");
	}
	return (0);
}
