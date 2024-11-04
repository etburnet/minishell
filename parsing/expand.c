/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:09:58 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/04 16:27:24 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	variable_expansion(t_data *data, t_expand *exp)
{
	if (ft_isdigit(exp->tok_dup[exp->j]))
		exp->var[exp->k++] = exp->tok_dup[exp->j++];
	else
		while (ft_isalnum(exp->tok_dup[exp->j]) || exp->tok_dup[exp->j] == '_')
			exp->var[exp->k++] = exp->tok_dup[exp->j++];
	exp->var[exp->k] = '\0';
	if (exp->var[0] != '\0')
	{
		exp->replaced = 1;
		if (replace_var(data, exp->res, exp->var, &exp->i) == 3)
			return (3);
	}
	else
	{
		if (exp->tok_dup[exp->j - 1] == '$')
			exp->j--;
		while (exp->tok_dup[exp->j] == '$' && (exp->tok_dup[exp->j + 1] == '$'
				|| exp->tok_dup[exp->j + 1] == '\0'))
			exp->res[exp->i++] = exp->tok_dup[exp->j++];
		if (exp->tok_dup[exp->j] == '$' && !ft_isalnum(exp->tok_dup[exp->j + 1])
			&& exp->tok_dup[exp->j + 1] != '_')
			exp->res[exp->i++] = exp->tok_dup[exp->j++];
	}
	return (0);
}

int	process_dollar_sign(t_data *data, t_expand *exp)
{
	char	*itoa;
	int		l_res;
	int		l_itoa;

	if (exp->tok_dup[exp->j] == '?')
	{
		itoa = ft_itoa(data->status);
		if (itoa == NULL)
			return (ft_free(exp->res), put_error(ERR_MALLOC, NULL), 3);
		l_res = ft_strlen(exp->res);
		l_itoa = ft_strlen(itoa);
		ft_strlcat(&exp->res[exp->i], itoa, (l_itoa + l_res + 1));
		exp->i = ft_strlen(exp->res);
		ft_free(itoa);
		exp->replaced = 1;
		exp->j++;
	}
	else if (variable_expansion(data, exp) == 3)
		return (3);
	return (0);
}

int	expand_check(t_expand *exp)
{
	while (exp->tok_dup[exp->j])
	{
		if (exp->tok_dup[exp->j] == '$')
			return (0);
		else if (exp->tok_dup[exp->j] == '\'' && exp->dq == 0)
			return (0);
		else if (exp->tok_dup[exp->j] == '\"')
		{
			exp->dq = check_quote(exp->tok_dup, exp->j, '\"');
			exp->res[exp->i++] = exp->tok_dup[exp->j++];
		}
		else
			exp->res[exp->i++] = exp->tok_dup[exp->j++];
	}
	return (1);
}

int	expand_loop(t_data *data, t_expand *exp)
{
	int	i;

	while (exp->tok_dup[exp->j])
	{
		exp->k = 0;
		ft_memset(exp->var, '\0', (ft_strlen(exp->tok_dup) + 1));
		if (expand_check(exp) == 1)
			return (0);
		else if (exp->tok_dup[exp->j] == '\'' && exp->dq == 0)
		{
			i = check_quote(exp->tok_dup, exp->j, '\'');
			if (i != -1)
				while (exp->j < i)
					exp->res[exp->i++] = exp->tok_dup[exp->j++];
		}
		else
		{
			exp->j++;
			if (process_dollar_sign(data, exp) == 3)
				return (put_error(ERR_MALLOC, NULL), 3);
		}
	}
	return (0);
}

int	expand(t_data *data, t_token tok, int i)
{
	t_expand	exp;

	exp.i = 0;
	exp.j = 0;
	exp.k = 0;
	exp.dq = 0;
	exp.replaced = 0;
	if (tok.type != undefine)
		return (0);
	if (expand_init(tok, &exp.res, &exp.var, &exp.tok_dup) == 3)
		return (put_error(ERR_MALLOC, NULL), 3);
	if (expand_loop(data, &exp) == 3)
		return (ft_free(exp.var), ft_free(exp.res), ft_free(exp.tok_dup), 3);
	exp.res[exp.i] = '\0';
	ft_free(tok.tab[0]);
	tok.tab[0] = exp.res;
	if (exp.replaced == 1)
		data->token[i].type = variable;
	return (ft_free(exp.var), ft_free(exp.tok_dup), 0);
}
