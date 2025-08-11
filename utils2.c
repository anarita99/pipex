/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:43:04 by adores            #+#    #+#             */
/*   Updated: 2025/08/11 15:08:08 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_all_files(int *fd, int file)
{
	if (close(fd[0]) < 0 || close(fd[1]) < 0)
		ft_error();
	if (close(file) < 0)
		ft_error();
}

void	close_and_error(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	ft_error();
}
