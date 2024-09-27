/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:06:50 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/27 18:06:26 by eburnet          ###   ########.fr       */
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
void	init_token(t_token *token)
{
	token->litteral = malloc(sizeof(char *));
	token->type = undefine;
	token->value = 0;
	token->position = 0;
	token->nb_arg = 0;
} 