/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:33:20 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/21 00:03:38 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->var, tmp->value);
		tmp = tmp->next;
	}
}

int	has_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*append_to_var(char *var, char *value)
{
	char	*tmp;

	tmp = ft_strjoin(var, value);
	printf("tmp = %s", tmp);
	return (tmp);
}



int	is_special_char(char c)
{
	if (c == '=' || c == '+' || c == '-' || c == '!' || c == '@' || c == '#'
		|| c == '$' || c == '%' || c == '^' || c == '&' || c == '*' || c == '('
		|| c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == '|'
		|| c == '\\' || c == ';' || c == ':' || c == '\'' || c == '\"' ||
		c == '<' || c == '>' || c == '?' || c == '/' || c == '.' || c == ',')
		return (1);
	return (0);
}

int	is_invalid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[0]) || str[0] == '_') || is_special_char(str[0]))
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && !is_special_char(str[i]))
			return (1);
		i++;
	}
	return (0);
}
