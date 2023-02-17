/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:18:52 by lsabik            #+#    #+#             */
/*   Updated: 2023/02/16 21:20:14 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	is_redirection(int type)
{
	if (type == REDIR_OUT || type == REDIR_IN || type == APPEND_IN
		|| type == APPEND_OUT)
		return (1);
	return (0);
}
