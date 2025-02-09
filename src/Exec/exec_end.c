#include "../../include/minishell.h"

void	free_process(t_main *mini)
{
	int	i;

	i = 0;
	if (mini->hd_count)
	{
		while (i < mini->hd_count)
		{
			if (mini->here_doc[i].fd[0] > -1)
				close(mini->here_doc[i].fd[0]);
			i++;
		}
		free(mini->here_doc);
	}
	if (mini->cmd_paths)
		ft_free_tab(mini->cmd_paths);
}

void	wait_exec(t_main *mini)
{
	int	i;
	int	status;

	i = 0;
	signal(SIGINT, SIG_IGN);
	waitpid(mini->pid_last, &status, 0);
	while (i < mini->pipe_count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	signal(SIGINT, signal_handler);
	if (WIFEXITED(status))
		mini->return_value = WEXITSTATUS(status);
}

void	exit_error_redir(t_main *mini, int fd[2])
{
	if (fd[0] > 1)
		close (fd[0]);
	if (fd[1] > 1)
		close(fd[1]);
	resets(mini);
	exit (1);
}

/* Free tous les char * et char ** de la struct shell */
static void	free_shell_var(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->is_oldpwd)
		free(shell->is_oldpwd);
	if (shell->is_pwd)
		free(shell->is_pwd);
	if (shell->oldpwd)
		free(shell->oldpwd);
	if (shell->pwd)
		free(shell->pwd);
	if (shell->home)
		free(shell->home);
	if (shell->path)
		free(shell->path);
	if (shell->input_bis)
		free(shell->input_bis);
	if (shell->shlvl)
		free(shell->shlvl);
	if (shell->cmd_paths)
	{
		while (shell->cmd_paths[i])
			free(shell->cmd_paths[i++]);
		free(shell->cmd_paths);
	}
	i = 0;
	if (shell->input)
	{
		while (shell->input[i])
			free(shell->input[i++]);
		free(shell->input);
	}
}

//a voir: avec les trucs en commentaires ca segfault
//regarder si c'est bien allouer sur la heap pour pouvoir les free
void	built_in_free(t_main *mini)
{
	// if (mini->cmd_paths)
	// {
	// 	ft_free_tab(mini->cmd_paths);
	// }
	if (mini->env)
		ft_free_tab(mini->env);
	// if (mini->env_exp)
	// {
	// 	ft_free_tab(mini->env_exp);
	// }
	free_shell_var(&mini->shell);
	free(mini->env_list);
	// if (mini->here_doc)
	// 	free(mini->here_doc);
	resets(mini);
}

int	close_error(int in, int out)
{
	if (in > 1)
		close (in);
	if (out > 1)
		close (out);
	return (-2);
}
