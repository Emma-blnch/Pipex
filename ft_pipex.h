/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:44:47 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/23 09:43:17 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include "libft/libft.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

//struct
typedef struct s_pipe_args
{
	char	*file1;
	char	*path_cmd;
	char	**cmd;
	char	*path_cmd2;
	char	**cmd2;
	char	**cmd1;
	char	*path_cmd1;
	char	*file2;
	char	**envp;
}	t_pipe_args;

// Functions
int		main(int argc, char **argv, char **envp);
int		perror_return(const char *message, int return_value);
int		open_file(char *file, int in_or_out);
void	perror_exit(const char *message);
void	create_pipe(t_pipe_args *args);
void	free_split(char **split);
void	init_args(t_pipe_args *args, char **argv, char **envp);
void	execute_command(t_pipe_args *args, int infile, int outfile);
void	launch_process(t_pipe_args *args, int infile, int outfile,
			int is_first_cmd);
void	child(t_pipe_args *args, int infile, int outfile, int is_first_cmd);
char	*get_path(const char *cmd, char **envp);
char	*build_full_path(const char *path, const char *cmd);

#endif
