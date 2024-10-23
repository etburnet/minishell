/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:14:53 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/23 10:54:59 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n(char *str)
{
	int	i;
	int	len;

	i = 0;
	if (str == NULL)
		return (1);
	len = ft_strlen(str);
	if (str[i] && str[i] == '-')
	{
		if (str[i + 1] == 'n')
			i++;
		while (str[i] == 'n')
			i++;
		if (i == len)
			return (0);
		else
			return (1);
	}
	return (1);
}

int	echo_loop(int *i, char **tab)
{
	int	j;

	j = 0;
	while (tab[(*i)][j])
		if (write(1, &tab[(*i)][j++], 1) != 1)
			return (perror("echo: write error"), 1);
	(*i)++;
	j = 0;
	if (tab[(*i)] != NULL && tab[(*i) - 1][0] != '\0')
		if (write(1, " ", 1) != 1)
			return (perror("echo: write error"), 1);
	return (0);
}

int	echo(char **tab)
{
	int	i;
	int	last;

	i = 1;
	last = 1;
	if (tab[1] == NULL)
	{
		if (write(1, "\n", 1) != 1)
			return (perror("echo: write error"), 1);
		return (0);
	}
	if (check_n(tab[1]) == 0)
		last = 0;
	while (check_n(tab[i]) == 0)
		i++;
	while (tab[i] != NULL)
		if (echo_loop(&i, tab) == 1)
			return (1);
	if (last == 1)
		if (write(1, "\n", 1) != 1)
			return (perror("echo: write error"), 1);
	return (0);
}