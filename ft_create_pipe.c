/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:55 by eblancha          #+#    #+#             */
/*   Updated: 2024/12/09 10:07:57 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	execute_command(int infile, int outfile, t_pipe_args *args)
{
	if (dup2(infile, STDIN_FILENO) == -1)
		perror_exit("dup2 failed for infile");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		perror_exit("dup2 failed for outfile");
	close(infile);
	close(outfile);
	execve(args->path_cmd, args->cmd, args->envp);
	write(STDERR_FILENO, args->cmd[0], ft_strlen(args->cmd[0]));
    write(STDERR_FILENO, ": command not found\n", 20);
    exit(127);
}

void	child(t_pipe_args *args, int infile, int outfile, int is_first_cmd)
{
	if (is_first_cmd)
	{
		args->path_cmd = args->path_cmd1;
		args->cmd = args->cmd1;
	}
	else
	{
		args->path_cmd = args->path_cmd2;
		args->cmd = args->cmd2;
	}
	if (!args->path_cmd)
	{
		write(STDERR_FILENO, args->cmd[0], ft_strlen(args->cmd[0]));
 		write(STDERR_FILENO, ": command not found\n", 20);
 		exit(127);
	}
	execute_command(args, infile, outfile);
}

int	open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (ret == -1)
		exit(0);
	return (ret);
}

void	create_pipe(t_pipe_args *args)
{
	int	pipe_fd[2];
	int	pid;
	int	infile;
	int	outfile;

	if (piped(pipe_fd) == -1)
		perror_exit("Error: Pipe creation failed");
	pid = fork();
	if (pid == -1)
		perror_exit("Error: Fork creation failed");
	if (pid == 0)
	{
		infile = open_file(args->file1, 0);
		close(pipe_fd[0]);
		child(args, infile, pipe_fd[1], 1);
	}
	pid = fork();
	if (pid == -1)
		perror_exit("Error: Fork creation failed");
	if (pid == 0)
	{
		outfile = open_file(args->file2, 1);
		close(pipe_fd[1]);
		child(args, outfile, pipe_fd[0], 0);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait(NULL);
	wait(NULL);
}
