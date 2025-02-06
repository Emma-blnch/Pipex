/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:08:02 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/06 10:15:11 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe_args	args;
	int			status;

	if (argc < 2)
		return (perror_return("Error: not enough arguments", 1));
	args.is_heredoc = ft_strncmp(argv[1], "here_doc", 8) == 0;
	if (!args.is_heredoc && argc != 5)
		return (perror_return("Usage: ./pipex file1 cmd1 cmd2 file2", 1));
	if (args.is_heredoc && argc != 6)
		return (perror_exit("Usage: ./pipex here_doc "
				"LIMITER cmd1 cmd2 file"), 1);
	if (!args.is_heredoc && access(argv[1], R_OK) == -1)
		return (perror_return(argv[1], 1));
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
