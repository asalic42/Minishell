/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:52:48 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/05 16:59:22 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    handle_quote_n_expand(t_main *mini)
{
    t_parsing   *node;
    int            i;

    node = mini->cmd_parse;
    while (node)
    {
        i = 0;
        while (node->cmd_tab[i])
        {
            node->doubl = count_quotes(node->cmd_tab[i], 34);
            node->single = count_quotes(node->cmd_tab[i], 39);
            if (!quotes(mini, node, i))
                expanding(mini, node, i, 0);
            i++;
        }
        node = node->next;
    }
}

int    start_in_loop(t_main *mini, char *input)
{
    mini->input_line = malloc(sizeof(char) * (ft_strlen(input) + 1));
    if (!mini->input_line)
        err_mall(mini);
    ft_strlcpy(mini->input_line, input, ft_strlen(input));
    if (!do_lexer(mini))
		main_space("lexer failed.");
    if (!parsing(mini))
    {
        mini->syntaxe_check = 1;
        return (1);
    }
    handle_quote_n_expand(mini);
    check_tab(mini);
    return (0);
}

void    mini_loop(t_main *mini)
{
    char    *input;

    while (42)
    {
        input = readline("$> ");
        if (!input)
            handle_eot(mini);
        if (check_space(input) && !error_quote(mini, input, 34, 39))
        {
            if (input[0] != '\0')
            {
                if (!start_in_loop(mini, input))
                    execute_cmd(mini);
                resets(mini);
            }
        }
        if (input[0] != '\0')
            add_history(input);
        free(input);
    }
    if (mini->tab_input_blank)
        ft_free_tab(mini->tab_input_blank);
    clear_history();
}

int    main(int ac, char **av, char **env)
{
    t_main    mini;

    (void)av;
    if (ac != 1)
        return (main_space("run ./minishell without arg"));
    if (!env[0])
        return (main_space("env is missing"));
    init_main(&mini);
    get_env(&mini, env);
    get_env_export(&mini);
    //get_shlvl(&mini, mini.env);
    mini_loop(&mini);
    return (0);
}