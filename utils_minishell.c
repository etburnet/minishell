/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:39:22 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/10 15:41:49 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}

int	get_this_env(char *var, char **env)
{
	int		i;
	int		len;

	len = ft_strlen(var);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], var, len) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (-1);
	return (i);
}

void	put_error(char *message, char *var)
{
	ft_putstr_fd(message, 2);
	if (var != NULL)
		ft_putstr_fd(var, 2);
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char **my_realloc(t_token token, size_t size)
{
	char **temp;
	int i;
	
	i = 0;
	temp = malloc(sizeof(char *) * (size + 2));
	if(temp == NULL)
		return(put_error(ERR_MALLOC, NULL), NULL);
	temp[size + 1] = NULL;
	while(token.litteral[i] != NULL)
	{
		temp[i] = ft_strdup(token.litteral[i]);
		if(temp[i] == NULL)
			return(put_error(ERR_MALLOC, NULL), NULL);
		i++;
	}
	free_tab(token.litteral);
	return(temp);
}
