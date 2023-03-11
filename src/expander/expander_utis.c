/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:18:45 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/11 22:42:37 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_after_dollar(t_shell *shell, char *str, int *i, int j)
{
	char	*tmp;
	char	*tmp2;
	char	*value;
	char	**env;

	env = shell->env_arr;
	j = *i;
	if (ft_isalpha(str[j++]) || str[j++] == '_')
		while (ft_isalnum(str[j]) || str[j] == '_')
			(j)++;
	tmp = ft_strndup(str, j);
	tmp2 = ft_substr(str, j, ft_strlen(str));
	while (*env != NULL)
	{
		if (ft_strncmp(*env, tmp, j) == 0 && (*env)[j] == '=')
		{
			value = ft_strdup(*env + (j + 1));
			free(tmp);
				tmp = ft_join(value, tmp2);
			return (tmp);
		}
		env++;
	}
	return (*i = j, ft_strdup(""));
}

void	expand_in_dquote(t_token **token, t_shell *shell, t_token **new_tkn)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("");
	*token = (*token)->next;
	while (*token && (*token)->type != DQUOTE)
	{
		if ((*token)->type == DOLLAR && (*token)->next->type == CMD)
		{
			*token = (*token)->next;
			tmp = after_dollar(shell, (*token)->content, tmp, i);
		}
		else
			tmp = ft_join(tmp, (*token)->content);
		*token = (*token)->next;
	}
	if ((*token)->type == DQUOTE)
	{
		*new_tkn = create_token(*new_tkn, tmp, CMD);
		tmp = NULL;
	}
}

void	expand_in_squote(t_token **token, t_token **new_tkn)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("");
	*token = (*token)->next;
	while (*token && (*token)->type != SQUOTE)
	{
		tmp = ft_join(tmp, (*token)->content);
		*token = (*token)->next;
	}
	if ((*token)->type == SQUOTE)
	{
		*new_tkn = create_token(*new_tkn, tmp, CMD);
		tmp = NULL;
	}
}

void	skip_spaces(t_token **token, t_token **new_tkn, char *tmp)
{
	if ((*token)->type != SPACE_MS)
	{
		tmp = ft_join(tmp, (*token)->content);
		*new_tkn = create_token(*new_tkn, tmp, (*token)->type);
	}
}
