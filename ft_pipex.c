/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:08:02 by eblancha          #+#    #+#             */
/*   Updated: 2024/12/09 10:40:42 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe_args	args;

	if (argc < 5)
		return (perror_return("Usage: ./pipex file1 cmd1 cmd2 file2", 1));
	if (access(argv[1], R_OK) == -1)
		return (perror_return(strerror(errno), 1));
	args.file1 = argv[1];
	args.file2 = argv[4];
	args.cmd1 = ft_split(argv[2], ' ');
	args.cmd2 = ft_split(argv[3], ' ');
	if (!args.cmd1 || !args.cmd2)
		return (perror_return("Error: Command parsing failed", 1));
	args.path_cmd1 = get_path(args.cmd1[0], envp);
	args.path_cmd2 = get_path(args.cmd2[0], envp);
	if (!args.path_cmd1 || !args.path_cmd2)
	{
		free(args.path_cmd1);
		free(args.path_cmd2);
		return (perror_return("Error: invalid command", 1));
	}
	args.envp = envp;
	create_pipe(&args);
	free(args.path_cmd1);
	free(args.path_cmd2);
	return (0);
}
