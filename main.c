/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:14:03 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/19 18:28:56 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_minishell(char *s, t_data *data)
{
	int	ret;

	ret = search_token(s, data);
	if (ret != 0)
		return (ret);
	ret = identify_token(data);
	if (ret != 0)
		return (ret);
	data->here = 0;
	ret = identify_command(data);
	if (ret == 3 && ret != 1)
		return (ret);
	if (ret == 0)
		execution(data);
	free_data_token(data);
	return (0);
}

int	main(int argc, char *argv[], char **env)
{
	t_data	*data;
	int		ret;

	(void)argc;
	(void)argv;
	ret = 0;
	/* if (!isatty(STDIN_FILENO))
		return (put_error("No infile ./minishell exec", NULL), 1); */
	data = malloc(sizeof(t_data));
	if (!data)
		return (put_error(ERR_MALLOC, NULL), 3);
	ret = copy_env(data, env);
	if (ret == 3)
		ft_exit(data, NULL, ret);
	else if (ret == 1)
		edit_pwd(data);
	if (update_shlvl(data) == 3)
		ft_exit(data, NULL, 3);
	data->status = 0;
	while (1)
	{
		init_signal_handler(data, 1);
		data->arg = readline("minishell$ ");
		if(g_sig_recieved == 1)
			data->status = 130;
		else if(g_sig_recieved == 2)
			data->status = 131;
		if (g_sig_recieved != 0)
			g_sig_recieved = 0;
		if (data->arg == NULL)
			ft_exit(data, NULL, 0);
		if (*data->arg)
		{
			add_history(data->arg);
			ret = init_data(data, data->arg);
			if (ret == 3)
				return (ft_clean(data), ret);
			else if(ret == 0)
			{
				ret = ft_minishell(data->source, data);
				if (ret != 0)
					return (ft_clean(data), ret);
			}
		}
		ft_free(data->arg);
	}
	return (0);
}
