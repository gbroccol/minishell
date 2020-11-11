
#include "libft.h"

int			if_smb_in_str(char smb, char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == smb)
			return (1);
		i++;
	}
	return (0);
}