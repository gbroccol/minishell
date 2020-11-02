# include "../minishell.h"

char			*check_shielding(char *line)
{
	char		*new_line;
	int			index;
	int			tmp;

	index = 0;
	tmp = 0;
	while (line[index] != '\0')
	{
		if (line[index] == '\\' && line[index + 1] == '$')
			tmp++;
		index++;
	}
	if (tmp == 0)
		return (line);
	if (!(new_line = (char *)malloc(sizeof(char) * (ft_strlen(line) - tmp + 1))))
		return (NULL);
	index = 0;
	tmp = 0;
	while (line[++index] != '\0')
	{
		if (line[index] == '\\' && line[index + 1] == '$')
			continue ;
		new_line[tmp++] = line[index];
	}
	free(line);
	return (new_line);
}
