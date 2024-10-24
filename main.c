/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:14:03 by opdi-bia          #+#    #+#             */
/*   Updated: 2024/10/24 17:39:21 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_minishell(char *s, t_data *data)
{
	int	ret;

	ret = search_token(s, data);
	if (ret == 0)
		ret = identify_token(data);
	if (ret == 0)
		ret = identify_command(data);
	if (ret == 0)
		execution(data);
	if(ret == 1)
		ret = 0;
	free_data_token(data);
	return (ret);
}

int	ft_main_loop(t_data *data)
{
	int	ret;

	ret = 0;
	if (g_sig_recieved == 1 || g_sig_recieved == 3)
		data->status = 130;
	else if (g_sig_recieved == 2)
		data->status = 131;
	if (g_sig_recieved != 0)
		g_sig_recieved = 0;
	if (*data->arg)
	{
		add_history(data->arg);
		ret = init_data(data, data->arg);
		if (ret == 3)
			return (ret);
		else if (ret == 0)
		{
			ret = ft_minishell(data->source, data);
			if (ret != 0 && ret != 3)
				return (ft_clean(data), ret);
		}
	}
	ft_free(data->arg);
	return (0);
}

int	ft_init_main(t_data *data, char **env)
{
	int	ret;

	ret = 0;
	// if (!isatty(STDIN_FILENO))
	// 	return (put_error("No infile ./minishell exec", NULL), free(data), 1);
	ret = copy_env(data, env);
	if (ret == 3)
		ft_exit(data, NULL, ret, 0);
	else if (ret == 1)
		edit_pwd(data);
	if (update_shlvl(data) == 3)
		ft_exit(data, NULL, 3, 0);
	return (0);
}

int	main(int argc, char *argv[], char **env)
{
	t_data	*data;
	int		ret;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (!data)
		return (put_error(ERR_MALLOC, NULL), 3);
	ret = ft_init_main(data, env);
	if (ret != 0)
		return (ret);
	data->status = 0;
	while (1)
	{
		init_signal_handler(data, 1);
		data->arg = readline("minishell$ ");
		if (data->arg == NULL)
			ft_exit(data, NULL, 0, 0);
		ft_main_loop(data);
	}
	return (0);
}
