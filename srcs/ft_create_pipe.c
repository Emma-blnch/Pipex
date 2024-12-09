/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:55 by eblancha          #+#    #+#             */
/*   Updated: 2024/12/09 11:52:25 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	execute_command(t_pipe_args *args, int infile, int outfile)
{
	if (dup2(infile, STDIN_FILENO) == -1)
		perror_exit("dup2 failed for infile\n");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		perror_exit("dup2 failed for outfile\n");
	close(infile);
	close(outfile);
	execve(args->path_cmd, args->cmd, args->envp);
	perror("Error: execve failed");
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
		free(args->cmd);
		exit(127);
	}
	execute_command(args, infile, outfile);
}

int	open_file(char *file, int in_or_out)
{
	int	result;

	if (in_or_out == 0)
		result = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		result = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (result == -1)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
	return (result);
}

void	launch_process(t_pipe_args *args, int infile, int outfile,
				int is_first_cmd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror_exit("Error: Fork creation failed");
	if (pid == 0)
	{
		if (infile < 0 || outfile < 0)
			perror_exit("Error: Invalid file descriptor\n");
		child(args, infile, outfile, is_first_cmd);
	}
}

void	create_pipe(t_pipe_args *args)
{
	int	pipe_fd[2];
	int	infile;
	int	outfile;

	if (pipe(pipe_fd) == -1)
		perror_exit("Error: Pipe creation failed");
	infile = open_file(args->file1, 0);
	launch_process(args, infile, pipe_fd[1], 1);
	close(pipe_fd[1]);
	outfile = open_file(args->file2, 1);
	launch_process(args, pipe_fd[0], outfile, 0);
	close(pipe_fd[0]);
	wait(NULL);
	wait(NULL);
	close(infile);
	close(outfile);
}
