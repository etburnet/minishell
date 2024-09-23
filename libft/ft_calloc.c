/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:47:40 by eburnet           #+#    #+#             */
/*   Updated: 2023/11/08 10:44:58 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*tab;
	size_t			i;

	i = nmemb * size;
	if (size && i / size != nmemb)
		return (NULL);
	tab = NULL;
	tab = malloc(i);
	if (!tab || !nmemb || !size)
		return (tab);
	ft_bzero(tab, i);
	return (tab);
}

/* int	main()
{
	ft_calloc(-5, -5);
} */