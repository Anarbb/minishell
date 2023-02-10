/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:32:27 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/10 19:35:14 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    ms_cd(t_shell *shell)
{
    char **cmd = shell->cmd;
    char *home;
    char *oldpwd;
    char *pwd;

if (!cmd[1])
    {
        home = get_env(shell->env, "HOME");
        chdir(home);
        free(home);
    }
    else if (ft_strcmp(cmd[1], "-") == 0)
    {
        home = get_env(shell->env, "OLDPWD");
        chdir(home);
        free(home);
    }
    else
    {
        chdir(cmd[1]);
    }
    oldpwd = get_env(shell->env, "PWD");
    pwd = getcwd(NULL, 0);
    free(oldpwd);
    free(pwd);
}