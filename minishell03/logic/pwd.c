
#include "../libminishell.h"
/*
* Возвращает путь папки в которой находишься
*/

char	*ft_pwd()
{
	char *buf;

	if (!(buf = malloc(100000)))
		return (NULL);
	getcwd(buf, 100000);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	return (buf);
}
