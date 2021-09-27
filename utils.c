/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftadeu-d <ftadeu-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:37:10 by ftadeu-d          #+#    #+#             */
/*   Updated: 2021/09/26 22:44:59 by ftadeu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*valid_cmd(char *cmd, char **envp)
{
	char	*full_path;
	char	*tmp;
	char	**all_paths;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	all_paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		tmp = ft_strjoin(all_paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_l;

	if (*needle == '\0')
		return ((char *)haystack);
	needle_l = ft_strlen(needle);
	while (*haystack != '\0' && len-- >= needle_l)
	{
		if (*haystack == *needle && ft_memcmp(haystack, needle, needle_l) == 0)
			return ((char *)haystack);
		else
			haystack++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	len;
	size_t	i;
	char	*dest;

	i = 0;
	l1 = ft_strlen(s1);
	len = l1 + ft_strlen(s2);
	if (!s1 || !s2)
		return (0);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (0);
	while (i < l1)
	{
		dest[i] = s1[i];
		i++;
	}
	while (i < len)
	{
		dest[i] = s2[i - l1];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
