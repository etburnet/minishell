/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 12:48:54 by eburnet           #+#    #+#             */
/*   Updated: 2024/10/24 17:43:30 by eburnet          ###   ########.fr       */
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

int	expand_init(t_token tok, char **res, char **var, char **tok_dup)
{
	*res = malloc(sizeof(char) * BUFSIZ);
	if (!*res)
		return (3);
	memset(*res, '\0', BUFSIZ);
	*var = malloc(sizeof(char) * (ft_strlen(tok.tab[0]) + 1));
	if (!*var)
		return (ft_free(*res), 3);
	*tok_dup = ft_strdup(tok.tab[0]);
	if (*tok_dup == NULL)
		return (ft_free(*res), ft_free(*var), 3);
	return (0);
}
