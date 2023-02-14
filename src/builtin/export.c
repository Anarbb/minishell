/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:19:14 by lsabik            #+#    #+#             */
/*   Updated: 2023/02/14 16:16:04 by lsabik           ###   ########.fr       */
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

int	check_var(char *cmd, int *plus)
{
	int	i;

	i = 0;
	if (ft_isalpha(cmd[0]) || cmd[0] == '_')
	{
		while (cmd[i] != '=' && cmd[i])
		{
			if (cmd[i] == '+' && cmd[i + 1] == '=')
				*plus = 1;
			else if (!(ft_isalnum(cmd[i]) || ft_isalpha(cmd[0])))
				return (-1);
			i++;
		}
		if (cmd[i] == '=')
			return (2);
		return (1);	
	}
	return (-1);
}

void	declare_env(t_shell	*shell, char *cmd, int plus, int mode)
{
	(void)plus;
	(void)mode;
	char	**key;

	key = ft_split(cmd, '+');
	if (mode == 2)
	{
		printf("%s,%s,%d\n",key[0],key[1],plus);
		if (plus == 0)
			set_env(shell, key[0], key[1]);
		else if(plus == 1)
			add_env(shell, key[0],key[1]);
	}

}

int export_cmd(t_shell *shell)
{
	int		i;
	int		res;
	int		plus;

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
		if (is_arg(shell->cmd[i]))
			return (printf("minishell : export %s invalid option\n",shell->cmd[i]));
		while (shell->cmd[i])
		{
			if ((res = check_var(shell->cmd[i], &plus)))
			{
				if (res == 2)
					declare_env(shell, shell->cmd[i], plus, res);
				else if (res == 1)
					declare_env(shell, shell->cmd[i], plus, res);
			}
			i++;
		}
	}
	
	return(FAILURE);
}