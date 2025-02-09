/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:13:22 by asalic            #+#    #+#             */
/*   Updated: 2023/10/10 16:25:36 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
 * Affiche le repertoire courrant 
 * Fonction a l'image de 'pwd'
*/
int	ft_pwd(t_shell *shell, t_lexer **env_list)
{
	if (shell->is_pwd == NULL)
	{
		change_error(env_list, shell, errno);
		return (1);
	}
	else
		printf("%s\n", shell->is_pwd);
	if (change_error(env_list, shell, 0) == 1)
		return (1);
	return (0);
}

/* 
 * Fonction unset.
 * Supprime une variable d'environnement appelee.
 * Change aussi les VE saved dans struct t_shell a NULL.
 * Si elle est vide ou n'existe pas, renvoie juste l'invite de commande.
*/
int	ft_unset(t_main *mini, t_parsing *parse, t_lexer **env_list)
{
	if (!parse->cmd_tab[parse->incr + 1])
		return (1);
	if (searchin_env(env_list, parse->cmd_tab[parse->incr +1]))
		shell_change(&mini->shell, parse->cmd_tab[parse->incr +1], NULL);
	if (parse->cmd_tab[parse->incr + 2] != NULL)
	{
		parse->incr ++;
		ft_unset(mini, parse, env_list);
	}
	if (change_error(env_list, &mini->shell, 0) == 1)
		return (1);
	return (0);
}
