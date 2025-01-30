/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:08:02 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/30 14:41:40 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	check_filein(int *filein, char **argv)
{
	if (*filein == -1)
	{
		perror(argv[1]);
		*filein = STDIN_FILENO;
	}
	if (*filein != STDIN_FILENO)
	{
		if (dup2(*filein, STDIN_FILENO) == -1)
			perror_exit("Error: dup2 failed for infile");
		close(*filein);
	}
}

int	setup_here_doc(char **argv)
{
	handle_here_doc(argv[2]);
	return (3);
}

void	execute_pipeline(t_pipe_args *args, int argc, char **argv, int fileout)
{
	int		status;
	pid_t	last_pid;

	while (args->arg_nbr < argc - 2)
	{
		last_pid = child_process(argv[args->arg_nbr], args->envp);
		args->arg_nbr++;
	}
	if (dup2(fileout, STDOUT_FILENO) == -1)
		perror_exit("Error: dup2 failed for outfile");
	close(fileout);
	last_pid = child_process(argv[argc - 2], args->envp);
	while (waitpid(last_pid, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			args->exit_code = WEXITSTATUS(status);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	filein;
	int	fileout;
	t_pipe_args	args;

	if (argc >= 5)
	{
		args.exit_code = 0;
		args.envp = envp;
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			fileout = open_file(argv[argc - 1], 0);
			args.arg_nbr = setup_here_doc(argv);
		}
		else
		{
			args.arg_nbr = 2;
			fileout = open_file(argv[argc - 1], 1);
			filein = open_file(argv[1], 2);
			check_filein(&filein, argv);
		}
		execute_pipeline(&args, argc, argv, fileout);
	}
	usage_return();
	return (args.exit_code);
}
