/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftadeu-d <ftadeu-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 20:52:38 by ftadeu-d          #+#    #+#             */
/*   Updated: 2021/09/26 23:25:04 by ftadeu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(void)
{
	perror("Error");
	exit(0);
}

void	run_cmd(char *argv, char **envp)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (execve(valid_cmd(cmd[0], envp), cmd, envp) == -1)
		print_error();
}

void	left_process(char **argv, char **envp, int *fd)
{
	int	file;

	file = open(argv[1], O_RDONLY, 0777);
	if (file == -1)
		print_error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	close(fd[0]);
	run_cmd(argv[2], envp);
}

void	right_process(char **argv, char **envp, int *fd)
{
	int	file;

	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		print_error();
	dup2(file, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	run_cmd(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid[2];

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			print_error();
		pid[0] = fork();
		if (pid[0] < 0)
			print_error();
		if (pid[0] == 0)
			left_process(argv, envp, fd);
		pid[1] = fork();
		if (pid[1] < 0)
			print_error();
		if (pid[1] == 0)
			right_process(argv, envp, fd);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid[0], NULL, 0);
		waitpid(pid[1], NULL, 0);
	}
	else
		write(1, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
	return (0);
}
