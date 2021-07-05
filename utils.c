#include "pipex.h"

int     ft_strlen(char const *str)
{
    int     i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		n1;
	int		n2;
	char	*p;
	int		i;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	n1 = ft_strlen(s1);
	n2 = ft_strlen(s2);
	p = (char*)malloc(sizeof(char) * (n1 + n2 + 1));
	if (p == NULL)
		return (NULL);
	i = -1;
	while (++i < n1)
		p[i] = s1[i];
	i = 0;
	while (i < n2)
	{
		p[n1 + i] = s2[i];
		i++;
	}
	p[n1 + i] = '\0';
	return (p);
}
