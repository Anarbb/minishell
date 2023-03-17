/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:18:36 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/17 16:14:04 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join(char *tmp, char *value)
{
	tmp = ft_strjoin(tmp, value);
	return (tmp);
}

char	*after_dollar(t_shell *shell, char *str, char *tmp, int i)
{
	int		len;
	char	*value;

	len = ft_strlen(str);
	if (ft_isdigit(str[i]))
		i++;
	else if (str[i] == '?')
	{
		tmp = ft_join(tmp, ft_itoa((uint8_t)shell->exit_status));
		i++;
	}
	while (i < len)
	{
		if (i == 0)
			return (value = expand_after_dollar(shell, str, &i) \
				, ft_join(tmp, value));
		else
			tmp = ft_join(tmp, ft_substr(str, i, 1));
		i++;
	}
	return (tmp);
}

void	expand_wildcard(t_token **new_tkn, char *tmp)
{
	DIR				*dirp;
	struct dirent	*direc_p;

	dirp = opendir(getcwd(NULL, 0));
	while ((direc_p = readdir(dirp)) != NULL)
	{
		if (ft_strncmp(direc_p->d_name, ".", 1))
		{
			tmp = ft_join(tmp, direc_p->d_name);
			*new_tkn = create_token(*new_tkn, tmp, CMD);
			tmp = NULL;
			tmp = ft_strdup("");
		}
	}
	closedir(dirp);
}

void	expand_cmd(t_token **token, t_shell *shell, t_token **new_tkn)
{
	char	*tmp;

	tmp = ft_strdup("");
	if ((*token)->type == WC)
		expand_wildcard(new_tkn, tmp);
		
	else if ((*token)->type == DOLLAR && (*token)->next)
	{
		if ((*token)->next->type == CMD)
		{	
		*token = (*token)->next;
		tmp = after_dollar(shell, (*token)->content, tmp, 0);
		*new_tkn = create_token(*new_tkn, tmp, CMD);
		}	
	}
	else if ((*token)->type == CMD || (*token)->type == DOLLAR)
	{
		tmp = ft_join(tmp, (*token)->content);
		*new_tkn = create_token(*new_tkn, tmp, CMD);
	}
	else
		skip_spaces(token, new_tkn, tmp);
	tmp = NULL;
}

void	expander(t_shell *shell, t_token *token)
{
	t_token	*new_tkn;

	new_tkn = NULL;
	while (token)
	{
		if (token->type == DQUOTE)
			expand_in_dquote(&token, shell, &new_tkn);
		else
		{
			if (token->type == SQUOTE)
				expand_in_squote(&token, &new_tkn);
			else
				expand_cmd(&token, shell, &new_tkn);
		}
		token = token->next;
	}
	free(shell->token);
	shell->token = new_tkn;
}
