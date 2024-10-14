/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:09:58 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/14 12:12:24 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	replace_var(t_data *data, int i, int total_len, char *var_value)
{
	char	*str;
	char	*itoa;
	int		j;
	int		l;
	int		k;

	j = 0;
	l = 0;
	k = 0;
	str = malloc(sizeof(char) * total_len);
	if (str == NULL)
		return (put_error(ERR_MALLOC, NULL), 3);
	ft_memset(str, '\0', total_len);
	while (data->token[i].litteral[0][j])
	{
		if (data->token[i].litteral[0][j] == '$')
		{
			j++;
			if (data->token[i].litteral[0][j] == '?')
			{
				itoa = ft_itoa(data->status);
				ft_strlcat(str, itoa, (ft_strlen(str) + ft_strlen(itoa) + 1));
				l = ft_strlen(str);
				j++;
			}
			else
			{
				while (ft_isalnum(data->token[i].litteral[0][j])
					|| data->token[i].litteral[0][j] == '_')
					j++;
				while (var_value[k])
					str[l++] = var_value[k++];
			}
		}
		else
			str[l++] = data->token[i].litteral[0][j++];
	}
	str[l] = '\0';
	data->token[i].litteral[0] = str;
	return (0);
}

int	remove_var(t_data *data, int i, int total_len)
{
	char	*str;
	int		j;
	int		k;

	j = 0;
	k = 0;
	str = malloc(sizeof(char) * total_len);
	if (str == NULL)
		return (put_error(ERR_MALLOC, NULL), 3);
	while (data->token[i].litteral[0][j])
	{
		if (data->token[i].litteral[0][j] == '$')
		{
			j++;
			while (ft_isalnum(data->token[i].litteral[0][j])
				|| data->token[i].litteral[0][j] == '_')
				j++;
		}
		str[k++] = data->token[i].litteral[0][j];
		j++;
	}
	str[k] = '\0';
	free(data->token[i].litteral[0]);
	data->token[i].litteral[0] = str;
	return (0);
}

int	expand(t_data *data, int i, int start, int len_var, int full_len)
{
	char	*var;
	char	*var_value;
	int		pos_var;
	int		len_value;
	int		ret;

	var_value = NULL;
	len_value = 0;
	var = malloc(sizeof(char) * (len_var + 1));
	if (var == NULL)
		return (put_error(ERR_MALLOC, NULL), 3);
	ft_strlcpy(var, &data->token[i].litteral[0][start], len_var + 1);
	pos_var = get_this_env(var, data->env);
	if (pos_var != -1 || var[0] == '?')
	{
		if (var[0] != '?')
		{
			var_value = ft_strdup(&data->env[pos_var][len_var + 1]);
			if (var_value == NULL)
				return (put_error(ERR_MALLOC, NULL), 3);
			len_value = ft_strlen(var_value);
		}
		ret = replace_var(data, i, ((full_len - len_var) + len_value + 1),
				var_value);
		free(var_value);
	}
	else
		ret = remove_var(data, i, (full_len - len_var) + 1);
	free(var);
	return (ret);
}
