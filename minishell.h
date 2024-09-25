/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:35:30 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/25 17:03:33 by opdi-bia         ###   ########.fr       */
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
	number,
	less,
	greater,
	greatergreater,
	here_doc,
	semi_colon,
	open_par,
	close_par,
	pipes,
	word,
	var_env,
}				e_lexeme;

typedef struct s_token
{
	e_lexeme	lexeme;
	char		*litteral;
	double		value;
	int		position;
}				t_token;

typedef struct	s_tokenizer
{
	t_token *token;
	int nb_token;
	int lenght_token;
	char *source;
	int cur;
	int source_lenght;
	int start;
}               t_tokenizer;

int				check_arg(char *s, t_tokenizer *tok);
void			ft_exit(char *arg);
size_t	ft_strlen(const char *s);
void	init_tokenizer_state(t_tokenizer *tok, char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			**ft_split(char const *s, char c);
void			handle_signal(int signum);
void			ft_error(void);
#endif