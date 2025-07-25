/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarita <anarita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:59:37 by adores            #+#    #+#             */
/*   Updated: 2025/07/25 16:12:06 by anarita          ###   ########.fr       */
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
}