/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:35:30 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/27 18:08:31 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <dirent.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <termios.h>
# include <unistd.h>

# define ERR_MALLOC "Malloc failed !"

typedef enum e_type
{
	undefine,
	string,
	word,
	number,
	less,
	greater,
	greatergreater,
	here_doc,
	semi_colon,
	exit_status,
	pipes,
	infile,
	outfile,
	var,
	command,
	arg,
}			e_type;

typedef struct s_token
{
	e_type	type;
	char	**litteral;
	double	value;
	int		position;
	int		nb_arg;
}			t_token;

typedef struct s_data
{
	t_token	*token;
	int		nb_token;
	int		lenght_token;
	char	*source;
	int		cur;
	int		source_lenght;
	int		start;
	char	**env;
	char	**input;
	char	*arg;
}			t_data;

extern char	**environ;

/* Builtins */
void		print_env(t_data *data);
int			copy_env(t_data *data);
int			echo(char **tab);
int			cd(t_data *data);
int			pwd(void);
void		ft_exit(t_data *data);
int			update_shlvl(t_data *data);
int			export(t_data *data);

/* Utils */
void		free_tab(char **tab);
int			get_this_env(char *var, char **env);
void		put_error(char *message, char *var);
int			ft_isdigit_edit(char *c);

/* Signal */
void		handle_signal(int signum);

/* Parsing */
void		init_data(t_data *tok, char *s);
void		init_token(t_token *token);
size_t		ft_countword(const char *s, int i);
int			search_token(char *s, t_data *data);
int			check_quote(const char *s, int i, char c);
void		ft_error(void);
int			identify_token(t_data *data);
void		free_data_token(t_data *data);
int			check_error(t_data *data, int i);
void		identify_command(t_data *data);
int	ft_strchr_edit(const char *s, char c);

#endif