/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 15:05:09 by akamlah           #+#    #+#             */
/*   Updated: 2021/09/21 16:33:09 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	gnl_free_and_set_to_null(char **str)
{
	free(*str);
	*str = NULL;
}

static int	ft_nl_found(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}	
	return (-1);
}

static char	*ft_do_stuff(char **saved_line)
{
	char	*tmp;
	char	*line_out;
	int		i;

	if (ft_nl_found(*saved_line) >= 0)
	{
		i = ft_nl_found(*saved_line);
		tmp = ft_strdup(&saved_line[0][i + 1]);
		line_out = ft_substr(*saved_line, 0, i + 1);
		free(*saved_line);
		*saved_line = tmp;
		return (line_out);
	}
	if (*saved_line[0] == '\0')
	{
		gnl_free_and_set_to_null(&(*saved_line));
		return (NULL);
	}
	else
	{
		line_out = ft_strdup(*saved_line);
		gnl_free_and_set_to_null(&(*saved_line));
	}
	return (line_out);
}

static int	ft_read_stuff(int fd, char *buffer, char **saved_line, int n_read)
{
	char	*tmp;

	while (n_read > 0)
	{
		buffer[n_read] = '\0';
		if (*saved_line == NULL)
			*saved_line = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(*saved_line, buffer);
			free(*saved_line);
			*saved_line = tmp;
		}
		if (ft_nl_found(buffer) >= 0)
			break ;
		n_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (n_read);
}

char	*get_next_line(int fd)
{
	static char	*saved_line;
	char		*buffer;
	char		*line_out;
	int			n_read;

	if (fd < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	n_read = read(fd, buffer, BUFFER_SIZE);
	if (n_read <= 0 && saved_line == NULL)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	n_read = ft_read_stuff(fd, buffer, &saved_line, n_read);
	free(buffer);
	buffer = NULL;
	line_out = ft_do_stuff(&saved_line);
	return (line_out);
}
