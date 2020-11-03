#include "libft.h"

/*
**  add str to str and space between them
*/

char		*ft_str_to_str(char *s1, char *s2)
{
	char		*res;
	char		*s2_tmp;
	int			s1_size;
	int			s2_size;

	if (!s1)
		s1_size = 0;
	else
		s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	if ((res = malloc(s1_size + s2_size + 1)) == NULL)
		return (NULL);
	ft_strlcpy(res, s1, (size_t)(s1_size + 1));
	s2_tmp = (char *)s2;
	while (*s2_tmp != '\0')
	{
		res[s1_size] = *s2_tmp;
		s2_tmp++;
		s1_size++;
	}
	res[s1_size] = '\0';
	free(s1);
	free(s2);
	return (res);
}

// char		*ft_str_to_str(char *s1, char *s2)
// {
// 	char		*res;
// 	char		*s2_tmp;
// 	int			s1_size;
// 	int			s2_size;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	s1_size = ft_strlen(s1);
// 	s2_size = ft_strlen(s2);
// 	if ((res = malloc(s1_size + s2_size + 2)) == NULL)
// 		return (NULL);
// 	ft_strlcpy(res, s1, (size_t)(s1_size + 1));
// 	s2_tmp = (char *)s2;
// 	res[s1_size] = ' ';
// 	s1_size++;
// 	while (*s2_tmp != '\0')
// 	{
// 		res[s1_size] = *s2_tmp;
// 		s2_tmp++;
// 		s1_size++;
// 	}
// 	res[s1_size] = '\0';
// 	free(s1);
// 	free(s2);
// 	return (res);
// }