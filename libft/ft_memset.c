/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:40:06 by eburnet           #+#    #+#             */
/*   Updated: 2023/11/07 12:57:03 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;

	str = s;
	while (n)
	{
		*str = (unsigned char)c;
		str++;
		n--;
	}
	return (s);
}

/* #include <stdio.h>
int	main(void)
{
	char str[50] = "GeeksForGeeks is for programming geeks."; 
	ft_memset(str + 0, 'A', 8*sizeof(char));
	printf("%s\n", str);
	memset(str + 0, 'A', 8*sizeof(char)); 
	printf("%s", str);
} */