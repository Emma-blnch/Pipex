/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:44:47 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/29 16:50:09 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include "../libft/libft.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

# define INFILE 0
# define OUTFILE 1

//struct
typedef struct s_pipe_args
{
	char	*file1;
	char	*file2;
	char	***cmds;
	char	**paths_cmds;
	char	**envp;
	int		**pipes;
	int		nb_cmds;
	int		exit_code;
	int		is_heredoc;
	int		pipe_fd[2];
	char	*limiter;
}	t_pipe_args;

// Main
int		main(int argc, char **argv, char **envp);

// Errors
int		perror_return(const char *message, int return_value);
void	perror_exit(const char *message);

// Init
int		open_file(char *file, int in_or_out, t_pipe_args *args);
void	init_args(t_pipe_args *args, int argc, char **argv, char **envp);

// Process
//void	launch_process(t_pipe_args *args, int infile, int outfile,
//			int is_first_cmd);
void	create_pipe(t_pipe_args *args);
void	child(t_pipe_args *args, int infile, int outfile, int is_first_cmd);

// Here doc
void	handle_here_doc(t_pipe_args *args, char *limiter);

// Command
void	execute_command(t_pipe_args *args, int infile, int outfile);

// Get path
char	*get_path(const char *cmd, char **envp);
char	*build_full_path(const char *path, const char *cmd);
char	*find_path(const char *cmd, char **envp);

// Free
void	free_split(char **split);
void	free_args(t_pipe_args *args);

void	cmd_handle(t_pipe_args *args, char **argv, char **envp);
void	create_pipes(t_pipe_args *args);
int	launch_process(t_pipe_args *args, int index);

#endif
