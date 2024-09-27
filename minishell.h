/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:35:30 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/27 14:45:05 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

typedef enum e_lexeme
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
}				e_lexeme;

typedef struct s_token
{
	e_lexeme	lexeme;
	char		*litteral;
	double		value;
	int		position;
}				t_token;

typedef struct	s_data
{
	t_token *token;
	int nb_token;
	int lenght_token;
	char *source;
	int cur;
	int source_lenght;
	int start;
}               t_data;


void	handle_signal(int signum);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_exit(char *arg);
void	init_data(t_data *tok, char *s);
void	init_token(t_token *token);
size_t    ft_countword(const char *s, int i);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
int		search_token(char *s, t_data *data);
int     check_quote(const char *s, int i, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void 	ft_error();
int    identify_token(t_data *data);
void	free_data_token(t_data *data);
int	ft_isdigit(char *c);
int	ft_atoi(const char *nptr);
int    check_error(t_data *data, int i);

#endif