#include "../../include/minishell.h"

void	close_hds(t_main *mini, t_parsing *node)
{
	int	i;

	i = 0;
	if (node->hdc == 0)
	{
		while (i < mini->hd_count)
		{
			if (mini->here_doc[i].fd[0] > -1)
				close(mini->here_doc[i].fd[0]);
			i++;
		}
		return ;
	}
	while (i < mini->hd_count)
	{
		if (i != mini->hd_pos)
		{
			if (mini->here_doc[i].fd[0] > -1)
				close(mini->here_doc[i].fd[0]);
		}
		i++;
	}
}

int	open_outfile(t_main *mini, t_parsing *node, int old_fd)
{
	int	out;

	if (old_fd > 1)
		close(old_fd);
	out = open(node->redirection->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (out == -1)
	{
		perror(node->redirection->str);
		ft_free_tab(mini->cmd_paths);
		ft_free_tab(mini->env);
		ft_free_tab(mini->env_exp);
		return (-2);
	}
	return (out);
}

int	open_infile(t_main *mini, t_parsing *node, int old_fd)
{
	int	in;

	node->hd_check = 0;
	in = open(node->redirection->str, O_RDWR);
	if (in == -1)
	{
		if (old_fd > -1)
			close(old_fd);
		perror(node->redirection->str);
		ft_free_tab(mini->cmd_paths);
		ft_free_tab(mini->env);
		ft_free_tab(mini->env_exp);
		return (-2);
	}
	return (in);
}

int	open_append(t_main *mini, t_parsing *node, int old_fd)
{
	int	out;

	if (old_fd > 1)
		close(old_fd);
	out = open(node->redirection->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (out == -1)
	{
		perror(node->redirection->str);
		ft_free_tab(mini->cmd_paths);
		ft_free_tab(mini->env);
		ft_free_tab(mini->env_exp);
		return (-2);
	}
	return (out);
}

void	exit_access(t_main *mini, char *cmd)
{
	perror(cmd);
	free_process(mini);
	resets(mini);
	free_kill(mini);
	exit (126);
}
