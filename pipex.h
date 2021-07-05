#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct  	s_cmd
{
	const char      *cmd[5];
	char * const    *argv;
	char * const	*envp;
}                   t_cmd;

char				**ft_split(char const *s, char c);
char				*ft_strjoin(char const *s1, char const *s2);

#endif