/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:35:30 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/10 15:41:52 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# define ERR_MALLOC "Malloc failed !"
# define ERR_CMD "Command not found: "
# define ERR_SYNTAX "Syntax error near unexpected token:"

typedef enum e_type
{
	undefine,
	string,
	word,
	less,
	greater,
	greatergreater,
	here_doc,
	delimiter,
	exit_status,
	pipes,
	infile,
	outfile,
	variable,
	command,
	arg,
	built_in,
}			e_type;

typedef struct s_token
{
	e_type	type;
	char	**litteral;
	char	*full_path;
	double	value;
	int		size;
	int		position;
	int		nb_arg;
	int		first;
	int		last;
	int		fdin;
	int		fdout;
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
	int		status;
	char	**env;
	char	**input;
	char	*arg;
}			t_data;

extern char	**environ;
extern int	g_sig_recieved;

/* Builtins */
int			print_env(t_data *data);
int			print_env(t_data *data);
int			copy_env(t_data *data);
int			echo(char **tab);
int			cd(t_data *data, char **tab);
int			pwd(void);
int			ft_exit(t_data *data, char **tab, int n);
int			ft_exit(t_data *data, char **tab, int n);
int			update_shlvl(t_data *data);
int			export(t_data *data, char **tab);
int			unset(t_data *data, char **tab);
int			ft_err_exit(t_data *data, char *err_msg, int n);
long int	ft_atol(const char *nptr);

/* Utils */
void		free_tab(char **tab);
int			get_this_env(char *var, char **env);
void		put_error(char *message, char *var);
char		**my_realloc(t_token token, size_t size);
void		ft_clean(t_data *data);

/* Signal */
void		init_signal_handler(int i);
void		handle_signal(int signum);
void		handle_sig_heredoc(int signum);

/*Init*/
int			init_data(t_data *tok, char *s);
int			init_token(t_token *token);

/* Parsing */
size_t		ft_countword(const char *s, int i);
int			search_token(char *s, t_data *data);
int			check_quote(const char *s, int i, char c);
void		free_data_token(t_data *data);
int			check_error(t_data *data, int i);
int			ft_strchr_edit(const char *s, char c);
char		*ft_find_cmd(t_data *data, char **cmd_tab);
int			expand(t_data *data, int i, int start, int len_var, int full_len);

/*Token_identify*/
int			identify_token(t_data *data);
void		put_string_to_cpy(char *s, char *tmp, int *i, int *j);
char		*check_to_remove_dquote(char *s, char *tmp, int *j, int *i);
char		*check_to_remove_quote(char *s, char *tmp, int *j, int *i);
char		*remove_quote(char *s, int i, int j);

/*Cmd_identify*/
int			identify_command(t_data *data);
int			search_cmd(t_data *data, int i);
char		*check_line(t_data *data, char *buffer, char *delimiter, int cmd);
int			interrupt_heredoc(t_data *data, int new, int cmd);
int			check_arg(t_data *data, int i, e_type type);

/* Exec */
int			execution(t_data *data);
int			open_file(t_token token, int i);
void		check_first_last(t_data *data);
int	which_builtin(t_data *data, char **cmd_tab);
int	open_file(t_token token, int i);
void	ft_close(int fd1, int fd2);

#endif