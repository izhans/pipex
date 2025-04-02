#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

char	*ft_find_path(char *envp[]);

int main(int argc, char const *argv[], char *envp[])
{
	char	*path;

	path = ft_find_path(envp);
	printf("%s\n", path);
	
	return 0;
}

char	*ft_find_path(char *envp[])
{
	while (*envp)
	{
			if (ft_strncmp("PATH=", *envp, 5) == 0)
				return (*envp);
		envp++;
	}
	return (NULL);
}
