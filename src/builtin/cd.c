/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:32:27 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/04 13:30:06 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_cd(t_shell *shell)
{
    char *oldpwd;
    char *pwd;

    if (!shell->cmd[1] || ft_strcmp(shell->cmd[1], "~") == 0)
        chdir(get_env(shell, "HOME"));
    else if (ft_strcmp(shell->cmd[1], "-") == 0)
    {
        printf("%s\n", get_env(shell, "OLDPWD"));   
        chdir(get_env(shell, "OLDPWD"));
    }
    else if (chdir(shell->exec->args[1]) == -1)
    {
        ft_putstr_fd("cd: no such file or directory: ", 2);
        ft_putendl_fd(shell->cmd[1], 2);
        return ;
    }
    else
    {
        oldpwd = get_env(shell, "PWD");
        pwd = getcwd(NULL, 0);
        set_env(shell, "OLDPWD", oldpwd);
        set_env(shell, "PWD", pwd);
        // free(oldpwd);
        // free(pwd);
    }
}
