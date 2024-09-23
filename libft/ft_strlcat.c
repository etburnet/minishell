/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:07:24 by eburnet           #+#    #+#             */
/*   Updated: 2024/04/05 13:59:18 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		dst_len;
	size_t		src_len;
	size_t		total_len;

	i = 0;
	if ((dst == NULL || src == NULL) && size == 0)
		return (0);
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	total_len = dst_len + src_len;
	if (size == 0)
		return (src_len);
	while (src[i] != '\0' && dst_len < size - 1)
	{
		dst[dst_len] = src[i];
		dst_len++;
		i++;
	}
	if (dst_len < size)
		dst[dst_len] = '\0';
	if (dst_len > size)
		return (size + src_len);
	return (total_len);
}

/* #include <stdio.h>
int	main(void)
{
	char b[0xF] = "nyan !";

	printf("%ld\n", ft_strlcat(NULL, b, 0));
	printf("%s", b);
} */