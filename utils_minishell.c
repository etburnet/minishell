/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:39:22 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/30 14:34:33 by opdi-bia         ###   ########.fr       */
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
}


// int	ft_isdigit_edit(char *c)
// {
// 	int	i;

// 	i = 0;
// 	if (c[i] == '-' || c[i] == '+')
// 		i++;
// 	while (c[i] != '\0')
// 	{
// 		if (c[i] >= '0' && c[i] <= '9')
// 			i++;
// 		else
// 			return (0);
// 	}
// 	return (!0);
// }

void *my_realloc(void *src, size_t size)
{
    void *temp;

    temp = malloc(size * 2);
    if(temp == NULL)
        return(NULL);
    ft_memcpy(temp, src, size);
    free(src);
    return(temp);
}
