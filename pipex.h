/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:22:10 by eburnet           #+#    #+#             */
/*   Updated: 2024/09/24 12:58:11 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_pipe_cmd
{
	int				fd_pipe[2];
	int				next_pipe[2];
	int				fd1;
	int				fd2;
	char			*cmd_path;
	char			**cmd_tab;
}	t_pipe_cmd;

extern char		**environ;
int				ft_execute(char **argv, int argc, t_pipe_cmd pipe_cmd);
void			ft_free_split(char	**tab);
void			ft_close(int fd1, int fd2);
int				ft_free_all(char ***cmd_tab, char *error);
char			*ft_find_cmd(char **cmd_tab);
int				ft_create_pipe(int pipe_fd[2]);
int				ft_wait_all(int *status, t_pipe_cmd p);

#endif