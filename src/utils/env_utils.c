/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:27:04 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/22 15:44:11 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env *tmp;

	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void    set_env(t_shell *shell, char *name, char *value)
{
	t_env *tmp;
	char *tmp_value;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, name) == 0)
		{
			tmp_value = ft_strdup(value);
			tmp->value = tmp_value;
			free(tmp_value);
			return ;
		}
		tmp = tmp->next;
	}
	add_env(shell, name, value);
}

char *get_env(t_shell *shell, char *key)
{
	t_env *tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void    add_env(t_shell *shell, char *key, char *value)
{
	t_env *new;

	new = (t_env *)malloc(sizeof(t_env));
	new->var = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (shell->env == NULL)
		shell->env = new;
	else
		ft_lstadd_back_env(&shell->env, new);
}

void    init_env(t_shell *shell)
{
	t_env 	*new;
	char 	**tmp_env;

	tmp_env = shell->tmp_env;
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