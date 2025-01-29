/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:55 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/29 13:55:13 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_pipex.h"

void	execute_command(t_pipe_args *args, int infile, int outfile)
{
	if (dup2(infile, STDIN_FILENO) == -1)
		perror_exit("Error: dup2 failed for infile");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		perror_exit("Error: dup2 failed for outfile");
	close(args->pipe_fd[0]);
	close(args->pipe_fd[1]);
	close(infile);
	close(outfile);
	if (execve(args->path_cmd, args->cmd, args->envp) == -1)
	{
		perror("Error: execve failed");
		if (errno == EACCES)
			args->exit_code = 126;
		else
			args->exit_code = 127;
		exit(args->exit_code);
	}
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
		close(args->pipe_fd[1]);
		close(args->pipe_fd[0]);
		close(infile);
		close(outfile);
		free_args(args);
		exit(127);
	}
	execute_command(args, infile, outfile);
}

int	open_file(char *file, int in_or_out, t_pipe_args *args)
{
	int	result;

	if (in_or_out == INFILE)
		result = open(file, O_RDONLY);
	else if (in_or_out == OUTFILE)
		result = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		result = -1;
	if (result == -1)
	{
		//perror(file);
		close(args->pipe_fd[1]);
		close(args->pipe_fd[0]);
		free_args(args);
	}
	return (result);
}

void	launch_process(t_pipe_args *args, int infile, int outfile,
				int is_first_cmd)
{
	int	pid;

	if (infile < 0)
	{
		perror(args->file1);
		exit(0);
	}
	if (outfile < 0)
	{
		perror(args->file2);
		exit(1);
	}
	pid = fork();
	if (pid == -1)
		perror_exit("Error: Fork creation failed");
	if (pid == 0)
		child(args, infile, outfile, is_first_cmd);
	if (is_first_cmd)
		close(infile);
	else
		close(outfile);
}

void	create_pipe(t_pipe_args *args)
{
	int	infile;
	int	outfile;

	if (pipe(args->pipe_fd) == -1)
		perror_exit("Error: Pipe creation failed");
	infile = open_file(args->file1, INFILE, args);
	launch_process(args, infile, args->pipe_fd[1], 1);
	close(args->pipe_fd[1]);
	outfile = open_file(args->file2, OUTFILE, args);
	launch_process(args, args->pipe_fd[0], outfile, 0);
	close(args->pipe_fd[0]);
	close(infile);
	close(outfile);
}
