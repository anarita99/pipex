/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarita <anarita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:59:37 by adores            #+#    #+#             */
/*   Updated: 2025/07/31 12:34:20 by anarita          ###   ########.fr       */
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
/*int main(int ac, char **av)
{
	int id = fork();
	if (id != 0)
		fork();
	printf("Hello world\n");
	//if (id == 0)
	//	printf("Hello from child process\n");
	//else
	//	printf("Hello from the main process\n");
	return (0);
}*/
/*
int main(int ac, char **av)
{
	int id = fork();
	int n;
	if (id == 0)
		n = 1;
	else
		n = 6;
	if (id != 0)
		wait(NULL);
	int i;
	for (i = n; i < n + 5; i++)
	{
		printf("%d ", i);
		fflush(stdout);
	}
	if (id != 0)
	{
		printf("\n");
	}
}*/

/*int	main(int ac, char **av)
{
	int fd[2];
	//fd[0] - read
	//fd[1] - write
	if (pipe(fd) == -1)
	{
		printf("ERROR");
		return(1);
	}
	int id = fork();
	if (id == -1)
	{
			printf("Error");
			return (4);
	}
	if (id == 0)
	{
		close(fd[0]);
		int x;
		printf("Input a number: ");
		scanf("%d", &x);
		if(write(fd[1], &x, sizeof(int)) == -1)
		{
			printf("Error");
			return (2);
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int y;
		if (read(fd[0], &y, sizeof(int)) == -1)
		{
			printf("Error");
			return (3);
		}
		y = y * 3;
		close(fd[0]);
		printf("Got from child process: %d\n", y);
	}
	return (0);
}*/

/*int main(int argc, char **argv)
{
	int fd[2];
	if (pipe(fd) == -1)
	{
		return (1);
	}
	int pid1 = fork();
	if(pid1 < 0)
		return (2);
	if (pid1 == 0)
	{	//Child process 1(ping)
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	int pid2 = fork();
	if(pid2 < 0)
		return (3);
	if (pid2 == 0)
	{	//Child process 1(ping)
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return(0);
}*/

void	call_child1(char **av, char **envp, int *fd)
{
	int file1;
	file1 = open(av[1], O_RDONLY);
	if (file1 < 0)
	{
		close(fd[0]);
		close(fd[1]);
	}
	dup2(file1, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	call_child2(char **av, char **envp, int *fd)
{
	int	file2;
	file2 = open(av[4], O_WRONLY);
	if (file2 < 0)
	{
		close(fd[0]);
		close(fd[1]);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(file2, STDOUT_FILENO);
	
	close(fd[0]);
	close(fd[1]);
}

int	main(int ac, char **av, char *envp[])
{
	int		fd[2];
	pid_t	proc_id[2];

	if (ac == 5)
	{
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
		close(fd[0]);
		close(fd[1]);
		waitpid(proc_id[0], NULL, 0);
		waitpid(proc_id[1], NULL, 0);
		return(0);
	}
	else
		write(2, "Error", 5);
		return(1);
}