/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:37:52 by asalic            #+#    #+#             */
/*   Updated: 2023/10/09 18:12:07 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
 * Cherche s2 dans s1.
 * Parcours s1 jusqu'a trouver s2 a la suite.
*/
static int	find_opt(char *s1)
{
	size_t	i;

	i = 1;
	if (s1[0] != '-')
		return (0);
	while (s1[i] && s1[i] == 'n')
	{
		i ++;
		if (!s1[i])
			return (1);
	}
	return (0);
}

/* 
 * Affiche caractere par caractere la liste.
 * Suite de ft_echo.
 * // if (list->token == TOKEN_TEMP_VAR)
	// 	process_not_s_quotes(list, env_list, 2);
*/
static int	iter_echo(t_lexer *list)
{
	int		i;

	i = 0;
	if (list->str == NULL)
		return (0);
	while (list->str[i])
	{
		write (1, &list->str[i], 1);
		i ++;
	}
	return (0);
}

static void	echo_loop(t_lexer *list, t_shell *shell)
{
	if (ft_strcmp("$?", list->str) == 0 && ft_strlen(list->str) == 2)
		printf("%d", shell->error);
	else
	{
		while (list)
		{
			if (iter_echo(list) == 0 && list->next != NULL)
				write (1, " ", 1);
			list = list->next;
		}
	}
}

/*
 * Fonction a l'image de 'echo'.
 * Affiche caractere par caractere les arguments en ignorant les quotes.
 * (Attention: cas particuliers, quotes a l'interieur de d'autres).
*/
int	ft_echo(t_lexer *list, t_lexer **env_list, t_shell *shell)
{
	int	bools;

	bools = 0;
	if (list == NULL)
	{
		write (1, "\n", 1);
		return (1);
	}
	while (list && ft_strcmp(list->str, "\t") == 0)
		list = list->next;
	while (list && find_opt(list->str) == 1)
	{
		list = list->next;
		bools = 1;
	}
	echo_loop(list, shell);
	if (bools == 0)
		write (1, "\n", 1);
	if (change_error(env_list, shell, 0) == 1)
		return (1);
	return (0);
}
