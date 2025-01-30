/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:44:47 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/30 12:18:05 by ema_blnch        ###   ########.fr       */
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
	char	**envp;
	char	***cmds;
	char	**paths_cmds;
	int		nb_cmds;
	int		pipe_fd[2];
	int		is_heredoc;
	char	*limiter;
}	t_pipe_args;

// Main
int		main(int argc, char **argv, char **envp);

// Utils
int		open_file(char *argv, int mode);
void	child_process(char *argv, char **envp);
void	execute(char *argv, char **envp);

// Find path
char	*find_path(char *cmd, char **envp);
char	*get_path(char *cmd, char **envp);
char	**get_paths_from_env(char **envp);
char	*search_executable(char *cmd, char **paths);

// Here_doc
void	handle_here_doc(char *limiter);

// Errors
void	usage_return(void);
void	perror_exit(const char *message);

#endif
