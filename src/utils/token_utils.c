/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:33:10 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/14 15:27:00 by aarbaoui         ###   ########.fr       */
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

void	delete_one_token(t_token **prev)
{
	t_token	*current;
	t_token	*next;

	current = (*prev)->next;
	next = current->next;
	free(current->content);
	free(current);
	(*prev)->next = next;
}
void	add_token(t_shell *shell, char *str, int type)
{
	if (!shell->token)
		shell->token = token_new(str, type);
	else
		token_add_b(shell->token, token_new(str, type));
}

int	is_cmd(char *cmd)
{
	while (!ft_isspace(*cmd) && *cmd)
	{
		if (ft_strchr("| $ < << >> > \" \' *", *cmd))
			return (0);
		cmd++;
	}
	return (1);
}

int	is_cmd_c(char c)
{
	char **strs;

	strs = ft_split("|\n$\n<\n<<\n>>\n>\n\"\n\'\n*\n ", '\n');
	while (*strs)
	{
		if (ft_strchr(*strs, c))
			return (0);
		free(*strs);
		strs++;
	}
	return (1);
}