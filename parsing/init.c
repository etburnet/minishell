/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:06:50 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/22 18:48:45 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_data(t_data *tok, char *s)
{
	tok->nb_token = 0;
	tok->cur = 0;
	tok->source_lenght = count_space(tok, s, 0, 0);
	if (tok->source_lenght < 0)
		return (put_error("len = -1\n", NULL), -1);
	else if (tok->source_lenght == 0)
		return (1);
	tok->start = 0;
	tok->old_pipe[0] = -1;
	tok->old_pipe[1] = -1;
	tok->pipe_fd[0] = -1;
	tok->pipe_fd[1] = -1;
	tok->append_id = 1;
	tok->here = 0;
	tok->del = NULL;
	tok->len_arg = (int)ft_strlen(tok->arg);
	tok->source = set_string(tok, s, tok->source_lenght, tok->len_arg);
	if (tok->source == NULL)
		return (put_error(ERR_MALLOC, NULL), 3);
	tok->lenght_token = ft_countword(tok->source, 0);
	if (tok->lenght_token == -1)
		tok->lenght_token = 0;
	return (0);
}

int	init_token(t_token *token)
{
	token->size = 1;
	token->tab = malloc(sizeof(char *) * 2);
	if (token->tab == NULL)
		return (ft_putstr_fd(ERR_MALLOC, 2), 3);
	token->tab[1] = NULL;
	token->type = undefine;
	token->value = 0;
	token->position = 0;
	token->nb_arg = 0;
	token->full_path = NULL;
	token->here_doc = NULL;
	token->first = 0;
	token->last = 0;
	token->fdin = STDIN_FILENO;
	token->fdout = STDOUT_FILENO;
	return (0);
}
