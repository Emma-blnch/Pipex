/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:08:02 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/27 08:56:05 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe_args	args;

	if (argc < 5)
		return (perror_return("Usage: ./pipex file1 cmd1 cmd2 ... cmdx file2", 1));
	if (access(argv[1], R_OK) == -1)
		return (perror_return(argv[1], 1));
	init_args(&args, argv, envp);
	create_pipe(&args);
	free(args.path_cmd1);
	free(args.path_cmd2);
	free_split(args.cmd1);
	free_split(args.cmd2);
	return (0);
}
