/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:45:37 by tboulogn          #+#    #+#             */
/*   Updated: 2025/02/05 16:14:43 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*next_line(char *str)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (free(str), NULL);
	new_line = ft_calloc(sizeof(char), (ft_strlen(str) - i + 1));
	if (!new_line)
		return (free(str), NULL);
	i++;
	j = 0;
	while (str[i])
		new_line[j++] = str[i++];
	return (free(str), new_line);
}

char	*read_and_store(int fd, char *str)
{
	char	*buffer;
	char	*tmp;
	int		bytes_read;

	if (!str)
		str = ft_calloc(1, 1);
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(str, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(str), NULL);
		buffer[bytes_read] = 0;
		tmp = ft_strjoin(str, buffer);
		free(str);
		str = tmp;
	}
	return (free(buffer), str);
}

char	*extract_line(char *str)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	new_line = ft_calloc(sizeof(char), i + 2);
	if (!new_line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		new_line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		new_line[i] = '\n';
		i++;
	}
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_and_store(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = next_line(buffer);
	return (line);
}
