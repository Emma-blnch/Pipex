/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_pipe_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:55 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/26 16:54:09 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_pipex_bonus.h"

void	execute_commands(t_pipe_args *args)
{
	int	i;
	int	prev_pipe_fd;

	i = 0;
	prev_pipe_fd = -1;
	while (i < args->cmd_count)
	{
		if (i != args->cmd_count - 1 && pipe(args->pipe_fd) == -1)
			perror_exit("Error: pipe creation failed");
		if (fork() == 0)
		{
			if (i == 0)
				dup2(args->here_doc ? args->pipe_fd[0] : open_file(args->file_in, 0, args), STDIN_FILENO);
			else
				dup2(prev_pipe_fd, STDIN_FILENO);
			if (i != args->cmd_count - 1)
				dup2(args->pipe_fd[1], STDOUT_FILENO);
			else
				dup2(open_file(args->file_out, args->here_doc ? 2 : 1, args), STDOUT_FILENO);
			close(args->pipe_fd[0]);
			execve(args->paths[i], args->cmds[i], args->envp);
			perror_exit("Error: execve failed");
		}
		close(args->pipe_fd[1]);
		if (prev_pipe_fd != -1)
			close(prev_pipe_fd);
		prev_pipe_fd = args->pipe_fd[0];
		i++;
	}
	while (wait(NULL) > 0)
		;
}


int	open_file(char *file, int mode, t_pipe_args *args)
{
	int	fd;

	fd = 0;
	if (mode == 0)
		fd = open(file, O_RDONLY);
	else if (mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(file);
		free_args(args);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	handle_here_doc(char *limiter, t_pipe_args *args)
{
	char	*line;

	if (pipe(args->pipe_fd) == -1)
		perror_exit("Error: pipe creation failed");
	if (fork() == 0)
	{
		close(args->pipe_fd[0]);
		while (1)
		{
			write(STDOUT_FILENO, "heredoc> ", 9);
			line = get_next_line(STDIN_FILENO);
			if (!line || ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(0);
			write(args->pipe_fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	close(args->pipe_fd[1]);
	wait(NULL);
}


/*
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
		free_split(args->cmd);
		exit(127);
	}
	execute_command(args, infile, outfile);
}

void	create_pipe(t_pipe_args *args)
{
	//int	pipe_fd[2];
	int	infile;
	int	outfile;

	if (pipe(args->pipe_fd) == -1)
		perror_exit("Error: Pipe creation failed");
	infile = open_file(args->file1, 0, args);
	launch_process(args, infile, args->pipe_fd[1], 1);
	close(args->pipe_fd[1]);
	outfile = open_file(args->file2, 1, args);
	launch_process(args, args->pipe_fd[0], outfile, 0);
	close(args->pipe_fd[0]);
	wait(NULL);
	wait(NULL);
	close(infile);
	close(outfile);
}*/
