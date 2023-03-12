/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:27:04 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/12 18:02:25 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*tmp;

	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	set_env(t_shell *shell, char *name, char *value)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, name) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	add_env(shell, name, value);
}

char	*get_env(t_shell *shell, char *key)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	unset_env(t_shell *shell, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = shell->env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, key) == 0)
		{
			if (prev == NULL)
				shell->env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->var);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	add_env(t_shell *shell, char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->var = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (shell->env == NULL)
		shell->env = new;
	else
		ft_lstadd_back_env(&shell->env, new);
}

void	init_env(t_shell *shell)
{
	t_env	*new;
	char	**tmp_env;

	tmp_env = shell->env_arr;
	while (*tmp_env)
	{
		new = (t_env *)malloc(sizeof(t_env));
		new->var = ft_substr(*tmp_env, 0, ft_strchr(*tmp_env, '=') - *tmp_env);
		new->value = ft_substr(*tmp_env,
				ft_strchr(*tmp_env, '=') - *tmp_env + 1, ft_strlen(*tmp_env));
		new->next = NULL;
		if (shell->env == NULL)
			shell->env = new;
		else
			ft_lstadd_back_env(&shell->env, new);
		tmp_env++;
	}
}
