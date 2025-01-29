/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:08:02 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/29 13:18:23 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe_args	args;
	int	status;
	char	**path;
	
	args.is_heredoc = ft_strncmp(argv[1], "here_doc", 9) == 0;
	if (argc < 5 || (args.is_heredoc && argc < 6))
		return (perror_return("Usage: ./pipex here_doc/file1 [LIMITER] cmd1 cmd2 file2", 1));
	init_args(&args, argc, argv, envp);
	path = find_path(envp);
	execute_command(argv + 2, path, argc - 4, args.pipe_fd);
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			args.exit_code = WEXITSTATUS(status);
	}
	// free(args.path_cmd1);
	// free(args.path_cmd2);
	// free_split(args.cmd1);
	// free_split(args.cmd2);
	free_split(path);
	return (args.exit_code);
}
