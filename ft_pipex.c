/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:46:59 by eblancha          #+#    #+#             */
/*   Updated: 2024/12/04 17:26:53 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	*parse_command(const char *cmd)
{
	const char	*dir[] = {"/bin", "/user/bin", NULL};
	char		*full_path;
	char		*temp_path;
	int			i;

	i = 0;
	while (dir[i])
	{
		temp_path = ft_strjoin(dir[i], "/");
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe_args args;

	if (argc < 5)
		return (perror_return("Usage: ./pipex file1 cmd1 cmd2 file2\n", 1));
	if (access(argv[1], R_OK) == -1)
		return (perror_return("Error: File cannot be read\n", 1));
	args.file1 = argv[1];
	args.file2 = argv[4];
	args.cmd1 = ft_split(argv[2], ' ');
	args.cmd2 = ft_split(argv[3], ' ');
	if (!args.cmd1 || !args.cmd2)
		return (perror_return("Error: Command parsing failed\n", 1));
	args.path_cmd1 = parse_command(args.cmd1[0]);
	args.path_cmd2 = parse_command(args.cmd2[0]);
	if (!args.path_cmd1 || !args.path_cmd2)
	{
		free(args.path_cmd1);
		free(args.path_cmd2);
		return (perror_return("Error: invalid command\n", 1));
	}
	args.envp = envp;
	create_pipe(&args);
	free(args.path_cmd1);
	free(args.path_cmd2);
	return (0);
}
