/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:08:02 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/29 15:40:22 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe_args	args;
	int	status;
	
	if (argc < 5)
		return (perror_return("Usage: ./pipex here_doc | file1 [LIMITER] cmd1 cmd2 file2", 1));
	args.is_heredoc = ft_strncmp(argv[1], "here_doc", 9) == 0;
	if (args.is_heredoc && argc < 6)
		return (perror_exit("Usage: ./pipex here_doc LIMITER cmd1 cmd2 file"), 1);
	init_args(&args, argv, envp);
	create_pipe(&args);
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			args.exit_code = WEXITSTATUS(status);
	}
	free_args(&args);
	return (args.exit_code);
}
