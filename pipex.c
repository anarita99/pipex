/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:59:37 by adores            #+#    #+#             */
/*   Updated: 2025/07/25 14:25:40 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(void)
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
}