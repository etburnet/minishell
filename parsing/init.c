/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:06:50 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/14 17:38:40 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_data(t_data *tok, char *s)
{
	tok->nb_token = 0;
	tok->lenght_token = ft_countword(s, 0);
	if(tok->lenght_token == -1)
		return(-1);
	tok->cur = 0;
	tok->source_lenght = (int)ft_strlen(s);
	tok->start = 0;
	tok->old_pipe[0] = -1;
	tok->old_pipe[1] = -1;
	tok->pipe_fd[0] = -1;
	tok->pipe_fd[1] = -1;
	tok->source = ft_strdup(s);
	if(tok->source == NULL)
		return(put_error(ERR_MALLOC, NULL), 3);
	return(0);
}
int	init_token(t_token *token)
{
	token->size = 1;
	token->litteral = malloc(sizeof(char *) * 2);
	if(token->litteral == NULL)
		return(ft_putstr_fd(ERR_MALLOC, 2), 3);
	token->litteral[1] = NULL;
	token->type = undefine;
	token->value = 0;
	token->position = 0;
	token->nb_arg = 0;
	token->full_path = NULL;
	token->first = 0;
	token->last = 0;
	token->fdin = STDIN_FILENO;
	token->fdout = STDOUT_FILENO;
	return(0);
}
