/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:35:30 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/22 19:12:57 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <dirent.h>
# include <errno.h>
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
# define ERR_MALLOC "Malloc failed!"
# define ERR_CMD "Command not found: "
# define ERR_SYNTAX "Syntax error near unexpected token: "
# define ERR_IDE "export: not a valid identifier: "
# define ERR_CONT "export: not valid in this context: "

extern int	g_sig_recieved;

typedef enum t_type
{
	undefine,
	string,
	word,
	less,
	greater,
	append,
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
	append_out,
	append_id,
}			t_type;

typedef struct s_token
{
	t_type	type;
	char	**tab;
	char	*full_path;
	double	value;
	int		size;
	int		position;
	int		nb_arg;
	int		first;
	int		last;
	int		fdin;
	int		fdout;
	char 	*here_doc;
}			t_token;

typedef struct s_data
{
	t_token	*token;
	int		pipe_fd[2];
	int		old_pipe[2];
	int		nb_token;
	int		lenght_token;
	int		len_arg;
	char	*source;
	int		cur;
	int		source_lenght;
	int		start;
	int		status;
	int		here;
	char 	*del;
	int		append_id;
	char	**cp_env;
	char	**input;
	char	*arg;
}			t_data;

typedef struct s_expand
{
	char	*res;
	char	*var;
	char	*tok_dup;
	int		i;
	int		j;
	int		k;
	int		dq;
	int		replaced;
}			t_expand;

/* Builtins */
int			print_env(t_data *data);
int			copy_env(t_data *data, char **cp_env);
int			echo(char **tab);
int			cd(t_data *data, char **tab);
int			pwd(t_data *data);
int			ft_exit(t_data *data, char **tab, int n);
int			export(t_data *data, char **tab);
int			unset(t_data *data, char **tab);
int			ft_err_exit(t_data *data, char *err_msg, int n);
long int	ft_atol(const char *nptr);
int			del_env(t_data *data, char *delete);
int			edit_pwd(t_data *data);
int			dup_env(t_data *data, char *new);
int			open_ch_dir(char *dir);
int			is_var_ok(char *name);
int			add_or_update(t_data *data, char *name, char **cat);
int    		cd_home(t_data *data);

/* Utils */
void		free_tab(char **tab);
int			get_this_env(char *var, char **cp_env);
void		put_error(char *message, char *var);
char		**my_realloc(t_token token, size_t size);
void		ft_clean(t_data *data);
int			update_shlvl(t_data *data);
void		ft_free(char *str);

/* Signal */
void		init_signal_handler(t_data *data, int i);
void		handle_signal(int signum);
void		handle_sig_heredoc(int signum);
void		handle_slash(int signum);

/* Init */
int			init_data(t_data *tok, char *s);
int			init_token(t_token *token);

/* Parsing */
int			count_space(t_data *data, char *s, int i, int j);
char		*set_string(t_data *data, char *s, int len, int len_arg);
int			ft_isdigit_edit(char *c);
size_t		ft_countword(const char *s, int i);
int			search_token(char *s, t_data *data);
int			check_quote(const char *s, int i, char c);
void		free_data_token(t_data *data);
int			ft_strchr_edit(const char *s, char c);
char		*ft_find_cmd(t_data *data, char **cmd_tab);
int			check_operator(char c);
int			expand_loop(t_data *data, t_expand *exp);

/* expand */
int			replace_var(t_data *data, char *res, char *var, int *i);
int			expand(t_data *data, t_token tok, int i);
int			expand_init(t_token tok, char **res, char **var, char **tok_dup);

/* Token_identify */
int			identify_token(t_data *data);
void		put_string_to_cpy(char *s, char *tmp, int *i, int *j);
char		*check_to_remove_dquote(char *s, char *tmp, int *j, int *i);
char		*check_to_remove_dquote_edit(char *s, char *tmp, int *j, int *i);
char		*check_to_remove_quote(char *s, char *tmp, int *j, int *i);
char		*check_to_remove_quote_edit(char *s, char *tmp, int *j, int *i);
char		*remove_quote(char *s, int i, int j);
int			count_space(t_data *data, char *s, int i, int j);
void		add_space(char *temp, int *j);
int			check_operator(char c);

/* Cmd_identify */
int			identify_command(t_data *data);
int			search_cmd(t_data *data, int i);
char		*check_line(t_data *data, int fdin, char *buffer, int *del);
int			interrupt_heredoc(t_data *data, int new, int cmd);
int			check_arg(t_data *data, int i, t_type type);
int			is_chevrons(char *s);
int			first_is_chevron(t_data *data, char *s);
int			is_special_char_bis(char *s);
int			is_special_char(char *s);
int			check_outfile(t_data *data);
int			check_infile(t_data *data);
int			expand_here_doc(t_data *data, char **str);

/* Exec */
int			execution(t_data *data);
int			open_file(t_data *data, t_token token, int i, int cmd);
int			which_builtin(t_data *data, char **cmd_tab);
int			exec_built_in(t_data *data, int cmd, int fdin, int fdout);
int			set_heredoc(t_data *data, int i);

/* Exec Utils */
int			ft_child(t_data *data, int cmd, int fdin, int fdout);
void		ft_close(t_data *data, int fd1, int fd2, int cmd);
int			catch_cmd(t_data *data, int i);
void		close_all(t_data *data, int fdin, int fdout, int cmd);
void		check_first_last(t_data *data);
int			command_return(t_data *data, t_token tok, int ret);
int			manage_pipe(t_data *data, t_token *tok);
void		manage_files(t_data *data, t_token tok_i, t_token *tok_cmd, int cmd);

#endif