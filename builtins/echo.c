/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:14:53 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/07 17:50:10 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n(char *str)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(str);
	if (str[i] && str[i] == '-')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if (i == len)
			return (0);
		else
			return (1);
	}
	return (1);
}

int	echo(char **tab)
{
	int	i;
	int	last;

	i = 1;
	last = 1;
	if (tab[1] == NULL)
		return (printf("\n"), 0);
	if (check_n(tab[1]) == 0)
		last = 0;
	while (tab[i] != NULL && check_n(tab[i]) == 0)
		i++;
	while (tab[i] != NULL)
	{
		printf("%s", tab[i++]);
		if (tab[i] != NULL)
			printf(" ");
	}
	if (last == 1)
		printf("\n");
	return (0);	
}

