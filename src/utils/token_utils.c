/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:33:10 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/16 22:08:16 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(char *cmd, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = cmd;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	token_add_b(t_token *tokens, t_token *new)
{
	t_token	*ptr;

	if (!tokens)
	{
		tokens = new;
		return ;
	}
	ptr = tokens;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

t_token	*create_token(t_token *token, char *cmd, int type)
{
	if (!token)
		token = token_new(cmd, type);
	else
		token_add_b(token, token_new(cmd, type));
	return (token);
}

void	add_token(t_shell *shell, char *str, int type)
{
	if (!shell->token)
		shell->token = token_new(str, type);
	else
		token_add_b(shell->token, token_new(str, type));
}

void	free_str_arr(char **str_arr)
{
	char	**temp;

	temp = str_arr;
	while (*str_arr)
	{
		free(*str_arr);
		str_arr++;
	}
	free(temp);
}
