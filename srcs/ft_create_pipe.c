/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:55 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/06 10:16:48 by eblancha         ###   ########.fr       */
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

	if (args->is_heredoc && in_or_out == INFILE)
		return (args->pipe_fd[0]);
	if (in_or_out == INFILE)
		result = open(file, O_RDONLY);
	else if (in_or_out == OUTFILE)
	{
		if (args->is_heredoc)
			result = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			result = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
		result = -1;
	if (result == -1)
	{
		perror(file);
		close(args->pipe_fd[1]);
		close(args->pipe_fd[0]);
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
			perror_exit("Error: Invalid file descriptor");
		child(args, infile, outfile, is_first_cmd);
	}
	if (is_first_cmd)
		close(infile);
	else
		close(outfile);
}

void	create_pipe(t_pipe_args *args)
{
	int	infile;
	int	outfile;

	if (args->is_heredoc)
	{
		handle_here_doc(args, args->limiter);
		infile = args->pipe_fd[0];
	}
	else
		infile = open_file(args->file1, INFILE, args);
	if (pipe(args->pipe_fd) == -1)
		perror_exit("Error: Pipe creation failed");
	launch_process(args, infile, args->pipe_fd[1], 1);
	close(args->pipe_fd[1]);
	outfile = open_file(args->file2, OUTFILE, args);
	if (outfile < 0)
	{
		args->exit_code = 1;
		return ;
	}
	launch_process(args, args->pipe_fd[0], outfile, 0);
	close(args->pipe_fd[0]);
	close(infile);
	close(outfile);
}
