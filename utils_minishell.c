/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:39:22 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/09/25 14:15:50 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*news;
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	if (s == 0)
		return (NULL);
	while (s[size] != '\0')
		size++;
	if (start >= size)
		len = 0;
	if ((len > start + size || start + len > size) && start < size)
		len = size - start;
	news = malloc((len + 1) * sizeof(char));
	if (news == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0' && start < size)
	{
		news[i] = s[start + i];
		i++;
	}
	news[i] = '\0';
	return (news);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
	{
		i++;
		if (i == n)
			return (0);
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

void	ft_exit(char *arg)
{
	clear_history();
	free(arg);
	exit(EXIT_FAILURE);
}

void 	ft_error()
{
	printf("error invalid command\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

