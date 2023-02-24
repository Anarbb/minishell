/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:33:10 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/24 16:02:05 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *token_new(char *cmd, int type)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    new->content = cmd;
    new->type = type;
    new->next = NULL;
    return (new);
}

void    token_add_b(t_token *tokens, t_token *new)
{
    t_token *ptr;
    
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

int is_cmd_c(char c)
{
    char **strs;

    strs = ft_split("| $ < << >> > \" \' *", ' ');
    while (*strs)
    {
        if (ft_strchr(*strs, c))
            return (0);
        free(*strs);
        strs++;
    }
    return (1);
}