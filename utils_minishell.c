/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:39:22 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/11/04 16:26:22 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char *str)
{
	if (str != NULL)
		free(str);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
		ft_free(tab[i++]);
	if (tab != NULL)
		free(tab);
}

int	get_this_env(char *var, char **cp_env)
{
	int		i;
	int		len;
	char	*var_eq;

	len = ft_strlen(var);
	i = 0;
	if (cp_env == NULL)
		return (-1);
	var_eq = malloc(sizeof(char) * (len + 2));
	if (!var_eq)
		return (put_error(ERR_MALLOC, NULL), -1);
	ft_memset(var_eq, '\0', len + 2);
	ft_strlcpy(var_eq, var, len + 1);
	var_eq[len] = '=';
	while (cp_env[i] != NULL)
	{
		if (ft_strncmp(cp_env[i], var_eq, len + 1) == 0)
			break ;
		i++;
	}
	if (cp_env[i] == NULL)
		return (free(var_eq), -1);
	return (free(var_eq), i);
}

void	put_error(char *message, char *var)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(message, 2);
	if (var != NULL)
		ft_putstr_fd(var, 2);
	ft_putstr_fd("\n", 2);
}

char	**my_realloc(t_token token, size_t size)
{
	char	**temp;
	int		i;

	i = 0;
	temp = malloc(sizeof(char *) * (size + 2));
	if (temp == NULL)
		return (put_error(ERR_MALLOC, NULL), NULL);
	temp[size + 1] = NULL;
	while (token.tab[i] != NULL)
	{
		temp[i] = ft_strdup(token.tab[i]);
		if (temp[i] == NULL)
			return (put_error(ERR_MALLOC, NULL), NULL);
		i++;
	}
	ft_free_tab(token.tab);
	return (temp);
}
