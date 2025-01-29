/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:44:47 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/29 11:44:55 by eblancha         ###   ########.fr       */
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

# define INFILE 1
# define OUTFILE 2

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
	int		pipe_fd[2];
	int		exit_code;
}	t_pipe_args;

// Main
int		main(int argc, char **argv, char **envp);

// Errors
int		perror_return(const char *message, int return_value);
void	perror_exit(const char *message);

// Init
int		open_file(char *file, int in_or_out, t_pipe_args *args);
void	init_args(t_pipe_args *args, char **argv, char **envp);

// Process
void	launch_process(t_pipe_args *args, int infile, int outfile,
			int is_first_cmd);
void	create_pipe(t_pipe_args *args);
void	child(t_pipe_args *args, int infile, int outfile, int is_first_cmd);

// Command
void	execute_command(t_pipe_args *args, int infile, int outfile);

// Get path
char	*get_path(const char *cmd, char **envp);
char	*build_full_path(const char *path, const char *cmd);
char	*find_path(const char *cmd, char **envp);

// Free
void	free_split(char **split);
void	free_args(t_pipe_args *args);

#endif
