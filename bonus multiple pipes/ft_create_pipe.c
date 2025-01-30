/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:55 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/30 10:44:47 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

// void	execute_command(t_pipe_args *args, int infile, int outfile)
// {
// 	if (dup2(infile, STDIN_FILENO) == -1)
// 		perror_exit("Error: dup2 failed for infile");
// 	if (dup2(outfile, STDOUT_FILENO) == -1)
// 		perror_exit("Error: dup2 failed for outfile");
// 	close(args->pipe_fd[0]);
// 	close(args->pipe_fd[1]);
// 	close(infile);
// 	close(outfile);
// 	if (execve(args->path_cmd, args->cmd, args->envp) == -1)
// 	{
// 		perror("Error: execve failed");
// 		if (errno == EACCES)
// 			args->exit_code = 126;
// 		else
// 			args->exit_code = 127;
// 		exit(args->exit_code);
// 	}
// }

// void	child(t_pipe_args *args, int infile, int outfile, int is_first_cmd)
// {
// 	if (is_first_cmd)
// 	{
// 		args->path_cmd = args->path_cmd1;
// 		args->cmd = args->cmd1;
// 	}
// 	else
// 	{
// 		args->path_cmd = args->path_cmd2;
// 		args->cmd = args->cmd2;
// 	}
// 	if (!args->path_cmd)
// 	{
// 		write(STDERR_FILENO, args->cmd[0], ft_strlen(args->cmd[0]));
// 		write(STDERR_FILENO, ": command not found\n", 20);
// 		close(args->pipe_fd[1]);
// 		close(args->pipe_fd[0]);
// 		close(infile);
// 		close(outfile);
// 		free_args(args);
// 		exit(127);
// 	}
// 	execute_command(args, infile, outfile);
// }

// int	open_file(char *file, int in_or_out, t_pipe_args *args)
// {
// 	int	result;

// 	if (args->is_heredoc && in_or_out == INFILE)
// 		return (args->pipe_fd[0]);
// 	if (in_or_out == INFILE)
// 		result = open(file, O_RDONLY);
// 	else if (in_or_out == OUTFILE)
// 	{
// 		if (args->is_heredoc)
// 			result = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		else
// 			result = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	}
// 	else
// 		result = -1;
// 	if (result == -1)
// 	{
// 		perror(file);
// 		close(args->pipe_fd[1]);
// 		close(args->pipe_fd[0]);
// 		free_args(args);
// 		exit(126);
// 	}
// 	return (result);
// }

void launch_process(t_pipe_args *args, int index, int infile, int outfile)
{
    int pid;
    int i;

    pid = fork();
    if (pid == -1)
        perror_exit("Error: Fork failed");
    if (pid == 0)
    {
        if (dup2(infile, STDIN_FILENO) == -1)
            perror_exit("Error: dup2 failed for infile");
        if (dup2(outfile, STDOUT_FILENO) == -1)
            perror_exit("Error: dup2 failed for outfile");
        i = 0;
        while (i < 2)
        {
            close(args->pipes[i][0]);
            close(args->pipes[i][1]);
            i++;
        }

        if (!args->paths_cmds[index])
        {
            ft_putstr_fd(args->cmds[index][0], STDERR_FILENO);
            ft_putstr_fd(": command not found\n", STDERR_FILENO);
            exit(127);
        }

        if (execve(args->paths_cmds[index], args->cmds[index], args->envp) == -1)
        {
            perror(args->cmds[index][0]);
            if (errno == EACCES)
                exit(126);
            exit(127);
        }
    }
}


void create_pipe(t_pipe_args *args)
{
    int i;
    int infile;
    int outfile;
    int current_pipe;

    if (args->is_heredoc)
    {
        handle_here_doc(args, args->limiter);
        infile = args->pipes[0][0];
    }
    else
    {
        infile = open(args->file1, O_RDONLY);
        if (infile == -1)
            perror_exit("Error: Unable to open input file");
    }
    i = 0;
    current_pipe = 0;
    while (i < args->nb_cmds)
    {
        if (i < args->nb_cmds - 1)
        {
            if (pipe(args->pipes[current_pipe]) == -1)
                perror_exit("Error: Pipe creation failed");
        }
        if (i == args->nb_cmds - 1)
            outfile = open(args->file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else
            outfile = args->pipes[current_pipe][1];

        launch_process(args, i, infile, outfile);
        if (i > 0)
            close(infile);

        close(args->pipes[current_pipe][1]);
        infile = args->pipes[current_pipe][0];
        current_pipe = 1 - current_pipe;
        i++;
    }
    close(infile);
}


