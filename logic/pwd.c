
#include "../libminishell.h"

void	ft_pwd()
{
	char	*buf;

	if (!(buf = malloc(100000)))
		fn_error("no memory allocate");
	getcwd(buf, 100000);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
}
