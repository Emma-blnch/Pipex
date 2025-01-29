/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:55 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/29 16:49:44 by ema_blnch        ###   ########.fr       */
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

int	launch_process(t_pipe_args *args, int index)
{
	int	pid;
	int	infile;
	int	outfile;

	pid = fork();
	if (pid == -1)
		perror_exit("Error: Fork failed");

	if (pid == 0)
	{
		// Définir l'entrée et la sortie du processus
		infile = (index == 0) ? 
			(args->is_heredoc ? args->pipes[0][0] : open(args->file1, O_RDONLY))
			: args->pipes[index - 1][0];
		
		outfile = (index == args->nb_cmds - 1) ? 
			open(args->file2, O_WRONLY | O_CREAT | O_TRUNC, 0644) 
			: args->pipes[index][1];

		// Redirection des fichiers vers stdin/stdout
		if (dup2(infile, STDIN_FILENO) == -1 || dup2(outfile, STDOUT_FILENO) == -1)
			perror_exit("Error: dup2 failed");

		// Fermer les pipes inutilisés
		close(infile);
		close(outfile);

		// Vérification du path de la commande
		if (!args->paths_cmds[index])
		{
			ft_putstr_fd(args->cmds[index][0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			exit(127);
		}

		// Exécuter la commande
		if (execve(args->paths_cmds[index], args->cmds[index], args->envp) == -1)
		{
			perror(args->cmds[index][0]);
			if (errno == EACCES)
				exit(126);
			exit(127);
		}
	}
	return (pid); // ✅ On retourne le PID du processus enfant
}

void	create_pipes(t_pipe_args *args)
{
	int	i;

	args->pipes = malloc(sizeof(int *) * (args->nb_cmds - 1));
	if (!args->pipes)
		perror_exit("Error: Memory allocation failed");
	i = 0;
	while (i < args->nb_cmds - 1)
	{
		args->pipes[i] = malloc(sizeof(int) * 2);
		if (!args->pipes[i] || pipe(args->pipes[i]) == -1)
		{
			//free_split(args->pipes);
			perror_exit("Error: Pipe creation failed");
		}
		i++;
	}
}

