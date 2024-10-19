/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:34:11 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/19 18:14:13 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(t_data *data)
{
	int	id_env;

	id_env = get_this_env("PWD", data->cp_env);
	if (id_env < 0)
		return (1);
	printf("%s\n", &data->cp_env[id_env][4]);
	return (0);
}
