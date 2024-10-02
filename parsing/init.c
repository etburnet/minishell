/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:06:50 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/02 16:34:11 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_data(t_data *tok, char *s)
{
	tok->nb_token = 0;
	tok->lenght_token = ft_countword(s, 0);
	tok->cur = 0;
	tok->source_lenght = (int)ft_strlen(s);
	tok->start = 0;
	tok->source = ft_strdup(s);
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
	return(0);
} 