/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:11:57 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/21 17:38:06 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_special_char(char *s)
{
	if (ft_strncmp(s, "#", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "!", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "$#", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "$*", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "$@", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "$_", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "$-", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "$!", 3) == 0)
		return (1);
	else if (ft_strncmp(s, ";", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "|", 2) == 0)
		return (1);
	return (0);
}

int	is_special_char_bis(char *s)
{
	if (ft_strncmp(s, ";;", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "`", 2) == 0)
		return (1);
	else if (ft_strncmp(s, ":", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "&", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "&&", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "()", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "(", 1) == 0)
		return (1);
	else if (ft_strncmp(s, ")", 1) == 0)
		return (1);
	else if (ft_strncmp(s, "||", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "%%", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "<>", 3) == 0)
		return (1);
	return (0);
}

int	first_is_chevron(t_data *data, char *s)
{
	if (ft_strncmp(s, "<", 2) == 0 && data->token[1].type != infile)
		return (1);
	else if (ft_strncmp(s, ">", 2) == 0 && data->token[1].type != outfile)
		return (1);
	else if (ft_strncmp(s, "<<", 3) == 0 && data->token[1].type != delimiter)
			return (1); 
	else if (ft_strncmp(s, ">>", 3) == 0 && data->token[1].type != outfile)
		return (1);
	return (0);
}

int	is_chevrons(char *s)
{
	if (ft_strncmp(s, "<", 2) == 0)
		return (1);
	else if (ft_strncmp(s, ">", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "<<", 3) == 0)
		return (1);
	else if (ft_strncmp(s, ">>", 3) == 0)
		return (1);
	return (0);
}
