/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmmous <mahmmous@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:51:48 by mahmmous          #+#    #+#             */
/*   Updated: 2025/07/31 11:51:48 by mahmmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_to_stash(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read;
	char	*temp;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!stash || !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		if (temp)
			free(temp);
	}
	free(buffer);
	return (stash);
}

static char	*extract_line(const char *stash)
{
	int	line_len;

	line_len = 0;
	if (!stash || !*stash)
		return (NULL);
	while ((stash[line_len] && stash[line_len] != '\n'))
		line_len++;
	if (stash[line_len] == '\n')
		line_len++;
	return (ft_substr(stash, 0, line_len));
}

static char	*get_remainder(char *stash)
{
	int		line_len;
	char	*remainder;

	if (!stash)
		return (NULL);
	line_len = 0;
	while (stash[line_len] && stash[line_len] != '\n')
		line_len++;
	if (!stash[line_len])
	{
		free(stash);
		return (NULL);
	}
	line_len++;
	remainder = ft_substr(stash, line_len, ft_strlen(stash) - line_len);
	free(stash);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = get_remainder(stash);
	return (line);
}
