/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:01:34 by lsabik            #+#    #+#             */
/*   Updated: 2023/02/25 15:45:30 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	exit_cmd(t_shell *shell, char *code)
{
    (void)code;
    printf("exit\n");
    free_all(shell);
    exit(EXIT_SUCCESS);
}
