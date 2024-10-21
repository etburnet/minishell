/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:34:11 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/21 13:14:47 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(t_data *data)
{
	int	id_env;
	int	len;

	id_env = get_this_env("PWD", data->cp_env);
	if (id_env < 0)
		return (1);
	len = ft_strlen(&data->cp_env[id_env][4]);
	if (write(1, &data->cp_env[id_env][4], len) != len)
		return (perror("pwd: write error"), 1);
	if (write(1, "\n", 1) != 1)
		return (perror("pwd: write error"), 1);
	return (0);
}
