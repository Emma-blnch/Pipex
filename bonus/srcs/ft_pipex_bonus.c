/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:08:02 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/26 16:53:25 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe_args	args;

	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6))
		return (perror_return("Usage: ./pipex [here_doc limiter] infile cmd ... cmd outfile", 1));
	init_args(&args, argc, argv, envp);
	if (args.here_doc)
		handle_here_doc(argv[2], &args);
	execute_commands(&args);
	free_args(&args);
	return (0);
}

