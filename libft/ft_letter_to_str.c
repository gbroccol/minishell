#include "libft.h"

char	*ft_letter_to_str(char *s1, char smb, int rm_double)
{
	char	*res;
	int		index;

	index = 0;
	if (s1 != NULL)
	{
		while (rm_double && s1[index] != '\0')
		{
			if (s1[index] == smb)
				return (s1);
			index++;
		}
		index = ft_strlen(s1);
		if (!(res = malloc(index + 2)))
			return (NULL);
		ft_strlcpy(res, s1, (size_t)(index + 1));
		res[index] = smb;
		res[index + 1] = '\0';
		free(s1);
		return (res);
	}
	if (!(res = malloc(sizeof(char) * 2)))
		return (NULL);
	res[0] = smb;
	res[1] = '\0';
	return (res);
}