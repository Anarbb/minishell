/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:32:27 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/11 14:18:08 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    ms_cd(t_shell *shell)
{
    char *oldpwd;
    char *pwd;

    if (!shell->cmd[1] || ft_strcmp(shell->cmd[1], "~") == 0)
        chdir(get_env(shell->env, "HOME"));
    else if (ft_strcmp(shell->cmd[1], "-") == 0)
        chdir(get_env(shell->env, "OLDPWD"));
    else if (chdir(shell->cmd[1]) == -1)
    {
        ft_putstr_fd("cd: no such file or directory: ", 2);
        ft_putendl_fd(shell->cmd[1], 2);
        return ;
    }
    else
    {
        oldpwd = get_env(shell->env, "PWD");
        pwd = getcwd(NULL, 0);
        set_env(shell, "OLDPWD", oldpwd);
        set_env(shell, "PWD", pwd);
        free(oldpwd);
        free(pwd);
    }
}
