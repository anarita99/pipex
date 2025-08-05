/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:59:37 by adores            #+#    #+#             */
/*   Updated: 2025/08/05 15:01:01 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*int	main(void)
{
	char *command[] = {"grep", "-E", "c$", "-", 0};
	char *bin_file = command[0];
	
	int redirect_fd = open("redirect_fd.txt", O_CREAT | O_WRONLY);
	dup2(redirect_fd, STDOUT_FILENO);
	close(redirect_fd);
	
	if(execvp(bin_file, command) == -1)
	{
		fprintf(stderr, "Error executing %s\n", bin_file);
	}
	printf("Done!\n");
}*/

void	close_all_files(int *fd, int file)
{
	if (close(fd[0]) < 0 || close(fd[1]) < 0)
		ft_error;
	if (close(file) < 0)
		ft_error();
}

void	call_child1(char **av, char **envp, int *fd)
{
	int file1;
	file1 = open(av[1], O_RDONLY);
	if (file1 < 0)
	{
		close(fd[0]);
		close(fd[1]);
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	dup2(file1, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close_all_files(fd, file1);
	close(fd[0]);
	close(fd[1]);
	if (execve("/usr/bin/ls", ft_split("ls", ' '), envp) == -1)
	{
		perror("ERROR");
		//limpar leaks e sair do programa
	}

}

void	call_child2(char **av, char **envp, int *fd)
{
	int	file2;
	file2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file2 < 0)
	{
		close(fd[0]);
		close(fd[1]);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(file2, STDOUT_FILENO);
	close_all_files(fd, file2);
	if (execve("/usr/bin/wc", ft_split("wc", ' '), envp) == -1)
	{
		exit(EXIT_FAILURE);
		//limpar leaks e sair do programa
	}
}


int	main(int ac, char **av, char *envp[])
{
	int		fd[2];
	pid_t	proc_id[2];

	if(pipe(fd) == -1)
			return(1);
		proc_id[0] = fork();
		if(proc_id[0] < 0)
			return(1);
		if(proc_id[0] == 0)
			call_child1(av, envp, fd);
		else
		{
			proc_id[1] = fork();
			if (proc_id[1] < 0)
				return(1);
			if (proc_id[1] == 0)
				call_child2(av, envp, fd);
		}
		if (close(fd[0]) < 0 || close(fd[1]) < 0)
			ft_error();
		waitpid(proc_id[0], NULL, 0);
		waitpid(proc_id[1], NULL, 0);
	return(0);
	if (ac == 5)
	{
		
	}
	/*
	else
		write(2, "Error", 5);
	*/
	return(1);
}
