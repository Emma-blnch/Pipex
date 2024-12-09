/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:42:09 by eblancha          #+#    #+#             */
/*   Updated: 2024/12/09 09:18:23 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	execute_command(int infile, int outfile, t_pipe_args *args)
{
	if (dup2(infile, STDIN_FILENO) == -1)
		perror_exit("dup2 failed");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		perror_exit("Error: dup2 output_fd failed\n");
	close(infile);
	close(outfile);
	execve(args->path_cmd, args->cmd, args->envp);
	perror_exit("Error: execve failed");
}

void	child_process_1(t_pipe_args *args, int pipe_fd[2])
{
	int	infile;

	args->path_cmd = args->path_cmd1;
	args->cmd = args->cmd1;
	if (!args->path_cmd)
		perror_exit("Error: command not found");
	infile = open(args->file1, O_RDONLY);
	if (infile == -1)
		perror_exit("Error: cannot open file1");
	close(pipe_fd[0]);
	execute_command(infile, pipe_fd[1], args);
}

void	child_process_2(t_pipe_args *args, int pipe_fd[2])
{
	int	outfile;

	args->path_cmd = args->path_cmd2;
	args->cmd = args->cmd2;
	if (!args->path_cmd)
		perror_exit("Error: command not found");
	outfile = open(args->file2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile == -1)
	{
		write(STDERR_FILENO, args->file2, ft_strlen(args->file2));
		perror(" ");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[1]);
	execute_command(pipe_fd[0], outfile, args);
}

void	create_pipe(t_pipe_args *args)
{
	int	pipe_fd[2];
	int	pid1;
	int	pid2;

	if (pipe(pipe_fd) == -1)
		perror_exit("Error: Pipe creation failed");
	pid1 = fork();
	if (pid1 == -1)
		perror_exit("Error: Fork creation failed");
	if (pid1 == 0)
		child_process_1(args, pipe_fd);
	pid2 = fork();
	if (pid2 == -1)
		perror_exit("Error: Fork creation failed");
	if (pid2 == 0)
		child_process_2(args, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait(NULL);
	wait(NULL);
}
