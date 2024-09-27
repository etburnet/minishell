/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:35:30 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/27 16:05:38 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <linux/limits.h>
# include <sys/types.h>
# include <dirent.h>

# define ERR_MALLOC "Malloc failed !"

typedef struct s_data {
	char **env;
	char **input;
	char *arg;
} t_data;

extern char		**environ;

/* Builtins */
void			print_env(t_data *data);
int				copy_env(t_data *data);
int				echo(char **tab);
int				cd(t_data *data);
int				pwd();
void			ft_exit(t_data *data);
int				update_shlvl(t_data *data);
int				export(t_data *data);

/* Utils */
void			free_tab(char **tab);
int				get_this_env(char *var, char **env);
void			put_error(char *message, char *var);

void			check_arg(char *s);
void			handle_signal(int signum);

#endif