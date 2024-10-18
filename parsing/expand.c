/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:09:58 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/18 15:10:02 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	replace_var(t_data *data, char *res, char *var, int *i)
{
	int		env_id;
	int		len_value;
	int		len_var;
	char	*var_value;
	
	len_value = 0;
	len_var = ft_strlen(var);
	env_id = get_this_env(var, data->cp_env);
	if (env_id > 0)
	{
		var_value = ft_strdup(&data->cp_env[env_id][len_var + 1]);
		if (var_value == NULL)
			return (ft_free(var), ft_free(res), put_error(ERR_MALLOC, NULL), 3);
		len_value = ft_strlen(var_value);
		ft_strlcat(&res[*i], var_value, (len_value + ft_strlen(res) + 1));
		*i = ft_strlen(res);
		free(var_value);
	}
	return (0);
}

int	add_status(t_data *data, char *res, int *i)
{
	char *itoa;
	
	itoa = ft_itoa(data->status);
	if (itoa == NULL)
			return (ft_free(res), put_error(ERR_MALLOC, NULL), 3);
	ft_strlcat(&res[*i], itoa, (ft_strlen(res) + ft_strlen(itoa) + 1));
	*i = ft_strlen(res);
	ft_free(itoa);
	return (0);
}

int	expand(t_data *data, t_token tok)
{
	int		j;
	int		i;
	int		k;
	char	*res;
	char	*var;
	char 	*str;
	int		first;
	
	j = 0;
	i = 0;
	k = 0;
	first = 0;
	if (tok.type != undefine)
		return (1);
	res = malloc(sizeof(char) * BUFSIZ);
	if (!res)
		return (put_error(ERR_MALLOC, NULL), 3);
	memset(res, '\0', BUFSIZ);
	var = malloc(sizeof(char) * (ft_strlen(tok.tab[0]) + 1));
	if (!var)
		return (ft_free(res), put_error(ERR_MALLOC, NULL), 3);
	str = ft_strdup(tok.tab[0]);
	while (str[j])
	{
		if (str[j] == '$')
			k = 1;
		j++;
	}
	if (k == 0)
		return (ft_free(var), ft_free(str), ft_free(res), 1);
	j = 0;
	while (str[j])
	{
		k = 0;
		memset(var, '\0', (ft_strlen(tok.tab[0]) + 1));
		//printf("char str:%c\n", str[j]);
		while (str[j] && str[j] != '$')
			res[i++] = str[j++];
		if (str[j] == '\0')
			break ;
		j++;
		if (str[j] == '?')
		{
			if (add_status(data, res, &i) == 3)
				return (ft_free(var), ft_free(res), ft_free(str), 3);
			j++;
		}
		else 
		{
			//printf("2char str:%c\n", str[j]);
			if (ft_isdigit(str[j]))
				var[k++] = str[j++];
			else
				while (ft_isalnum(str[j]) || str[j] == '_')
					var[k++] = str[j++];
			//printf("var:%s\n", var);
			if (var[0] != '\0')
			{
				if (replace_var(data, res, var, &i) == 3)
					return (ft_free(var), ft_free(res), ft_free(str), 3);
			}
			else
			{
				if (str[j-1] == '$')
					j--;
				while (str[j] == '$' && (str[j + 1] == '$' || str[j + 1] == '\0'))
					res[i++] = str[j++];
				if (str[j] == '$' && !ft_isalnum(str[j + 1]) && str[j +1] != '_')
					res[i++] = str[j++];
			}
		}
		//printf("res:%s\n", res);
	}
	res[i] = '\0';
	ft_free(var);
	ft_free(str);
	ft_free(tok.tab[0]);
	tok.tab[0] = res;
	return(0);
}
