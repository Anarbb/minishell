/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:30:01 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/19 15:26:22 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*exec_new(char *tmp, int type)
{
	t_exec	*exec;

	exec = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (tmp)
		exec->cmd = ft_strdup(tmp);
	if (type)
		exec->type = type;
	exec->limiter = NULL;
	exec->fd_in = 0;
	exec->fd_out = 1;
	exec->next = NULL;
	exec->prev = NULL;
	return (exec);
}

void	exec_add_b(t_shell *shell, char *tmp, int type)
{
	t_exec	*new;
	t_exec	*tmp_exec;

	new = exec_new(tmp, type);
	tmp_exec = shell->exec;
	while (tmp_exec->next)
		tmp_exec = tmp_exec->next;
	tmp_exec->next = new;
	new->prev = tmp_exec;
}

int	exec_size(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec)
	{
		i++;
		exec = exec->next;
	}
	return (i);
}

void	exec_create(t_shell *shell, char *tmp, int type)
{
	if (shell->exec == NULL)
		shell->exec = exec_new(tmp, type);
	else
		exec_add_b(shell, tmp, type);
}

void	init_env(t_shell *shell)
{
	t_env	*new;
	char	**tmp_env;

	tmp_env = shell->env_arr;
	while (*tmp_env)
	{
		new = (t_env *)ft_calloc(1, sizeof(t_env));
		new->var = ft_substr(*tmp_env, 0, ft_strchr(*tmp_env, '=') - *tmp_env);
		new->value = ft_strdup(ft_strchr(*tmp_env, '=') + 1);
		new->next = NULL;
		if (shell->env == NULL)
			shell->env = new;
		else
			ft_lstadd_back_env(&shell->env, new);
		tmp_env++;
	}
}
