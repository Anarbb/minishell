/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:19:14 by lsabik            #+#    #+#             */
/*   Updated: 2023/02/11 21:50:22 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exported_env(t_shell *shell)
{
	int	i;

	i = 0;
	while(shell->env[i])
		printf("declare -x %s\n",shell->env[i++]);
}

int	check_value(char *cmd, int pos)
{
	while(cmd[pos] != '\0')
	{
		if (cmd[pos])
	}
}

int	check_var(char	*cmd, int *plus)
{
	int	i;

	i = 0;
	while(cmd[i] != "=")
	{
		if(!(ft_isalnum(cmd[i]) && ft_isalpha(cmd[0])))
			return (-1);
		i++;
	}
	if (cmd[i] == "=")
	{
		if (cmd[i - 1] == "+")
			*plus = 1;
		return (2);
	}
	return (1);	
}

int export_cmd(t_shell *shell)
{
	int		i;
	int		res;
	int		plus;
	char	**exp;

	i = 1;
	res = 0;
	plus = 0;
	if (!shell->cmd[1])
	{
		exported_env(shell);
		return (SUCCESS);
	}
	else
	{
		exp = ft_split(shell->cmd[i], '=');
		while (shell->cmd[i])
		{
			if ((res = check_var(shell->cmd[i], &plus)))
			{
				// if()
			}
			i++;
		}
	}
	return(SUCCESS);
}