#include "pipex.h"

int		find_num(char const *s, char c)
{
	int			num;
	int			i;

	num = 0;
	i = -1;
	while (s[++i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == 0))
			num++;
	}
	return (num);
}

char	*ft_strncpy(char const *str, int start, int end)
{
	char	*p;
	int		i;

	p = (char*)malloc(sizeof(char) * (end - start + 1));
	i = 0;
	while (i < end - start)
	{
		p[i] = str[start + i];
		i++;
	}
	p[end - start] = '\0';
	return (p);
}

int		reset(int *index, int *start, char const *s)
{
	int		i;

	*index = 0;
	*start = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			i++;
		else
			break;
	}
	if (i != 0)
		*start = i;
	return (i - 1);
}

int		find_next_start(char const *s, int i)
{
	int		j;

	j = 0;
	while (s[i + j])
	{
		if (s[i + j] != ' ')
			break;
		j++;
	}
	return (i + j);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		start;
	int		end;
	int		i;
	int		index;

	p = (char**)malloc(sizeof(char*) * (find_num(s, c) + 1));
	if (p == 0)
		return (NULL);
	i = reset(&index, &start, s);
	while (s[++i])
	{
		if (s[i] != c && s[i + 1] == c)
		{
			end = i + 1;
			if (start != end)
				p[index++] = ft_strncpy(s, start, end);
			start = find_next_start(s, i + 1);
		}
	}
	if (start != i)
		p[index++] = ft_strncpy(s, start, i);
	p[index] = NULL;
	return (p);
}
