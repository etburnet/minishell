/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/10/04 15:32:27 by opdi-bia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_close(int fd1, int fd2)
{
	if (fd1 > 0 && fd1 != STDIN_FILENO)
		close(fd1);
	if (fd2 > 0 && fd2 != STDOUT_FILENO)
		close(fd2);
}

int	open_file(t_token token, int i)
{
	int	fd;

	fd = 0;
	if (i == 0)
		fd = open(token.litteral[0], O_RDONLY);
	else if (i == 1)
		fd = open(token.litteral[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(token.litteral[0]), -1);
	return (fd);
}

int which_builtin(t_data *data, char **cmd_tab)
{
	int ret;
	
	ret = 0;
	if (strncmp(cmd_tab[0], "echo", 5) == 0)
		ret = echo(cmd_tab);
	else if(strncmp(cmd_tab[0], "cd", 3) == 0)
		ret =cd(data, cmd_tab);
	else if(strncmp(cmd_tab[0], "pwd", 4) == 0)
		ret = pwd();
	else if(strncmp(cmd_tab[0], "export", 7) == 0)
		ret = export(data, cmd_tab);
	else if(strncmp(cmd_tab[0], "unset", 6) == 0)
		ret = unset(data, cmd_tab);
	else if(strncmp(cmd_tab[0], "env", 4) == 0)
		ret = print_env(data);
	else if(strncmp(cmd_tab[0], "exit", 5) == 0)
		ft_exit(data, cmd_tab, 0);
		// ret = ft_exit(data, cmd_tab, 0);
	else
		return (put_error("This is not a builtin:", cmd_tab[0]), 1);	
	return (ret);
}

int	exec_built_in(t_data *data, char **cmd_tab, int fdin, int fdout)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	ret = 0;
	// printf("pid = %d\n", pid);
	if (pid == -1)
		return (perror("fork"), 1);
	else if (pid == 0)
	{
		if (dup2(fdin, STDIN_FILENO) == -1 || dup2(fdout, STDOUT_FILENO) == -1)
			return (perror("dup2"), 1);
		ft_close(fdin, fdout);
		ret = which_builtin(data, cmd_tab);
		return (ret);
	}
	ft_close(fdin, fdout);
	return (0);
}

int	ft_execute(char *full_path, char **cmd_tab, int fdin, int fdout)
{
	pid_t	pid;

	if(full_path == NULL)
		return(put_error("error invalid command", NULL), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	else if (pid == 0)
	{
		if (dup2(fdin, STDIN_FILENO) == -1 || dup2(fdout, STDOUT_FILENO) == -1)
			return (perror("dup2"), 1);
		ft_close(fdin, fdout);
		execve(full_path, cmd_tab, NULL);
		return (1);
	}
	ft_close(fdin, fdout);
	return (0);
}


int	execution(t_data *data)
{
	int		i;
	int		fdin;
	int		fdout;
	int		cmd;
	int		last;
	int		first;
	int		n_pipe[2];
	pid_t	pid;
	int		status;

	pid = 0;
	last = 0;
	status = 0;
	i = 0;
	if (pipe(n_pipe) == -1)
		return (perror("pipe"), 1);
	while (i <= data->lenght_token)
	{
		fdin = n_pipe[0];
		fdout = n_pipe[1];
		cmd = -1;
		first = 0;
		if (i == 0)
			first = 1;
		while (i < data->lenght_token && data->token[i].type != pipes)
		{
			if (data->token[i].type == command
				|| data->token[i].type == built_in)
				cmd = i;
			else if (data->token[i].type == infile)
				fdin = open_file(data->token[i], 0);
			else if (data->token[i].type == outfile)
				fdout = open_file(data->token[i], 1);
			if (fdin == -1 || fdout == -1)
			{
				while (i < data->lenght_token && data->token[i].type != pipes)
					i++;
				cmd = -1;
				break ;
			}
			i++;
		}
		if (data->token[i - 1].type != pipes)
			last = 1;
		if (cmd != -1)
		{
			if (fdout == n_pipe[1] && last == 1)
				fdout = STDOUT_FILENO;
			if (fdin == n_pipe[0] && first == 1)
				fdin = STDIN_FILENO;
			if (data->token[cmd].type == command)
				ft_execute(data->token[cmd].full_path,
					data->token[cmd].litteral, fdin, fdout);
			else if (data->token[cmd].type == built_in)
			{
				if(strncmp(data->token[cmd].litteral[0], "exit", 5) == 0 && last == 1 && first == 1)
					ft_exit(data, data->token[cmd].litteral, 0);
				exec_built_in(data, data->token[cmd].litteral, fdin, fdout);	
			}	
		}
		i++;
	}
	ft_close(fdin, fdout);
	ft_close(n_pipe[0], n_pipe[1]);
	while (pid != -1)
	{
		pid = waitpid(-1, &status, 0);
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		{
			printf("erreur wifexited\n");
			return (ft_close(n_pipe[0], n_pipe[1]), 1);
		}
	}
	// waitpid(-1, &status, 0);
	// printf("%d\n", status);
	// if (WIFEXITED(status))
	// 	printf("fils a termine correctement\n");
	// if (WIFSIGNALED(status))
	// {
	// 	printf("fils a ete interompu\n");
	// 	if (WTERMSIG(status) == SIGINT)
	// 		printf("fils a recu signal ctrl_c\n");	
	// }	
	return (ft_close(n_pipe[0], n_pipe[1]), 0);
}
