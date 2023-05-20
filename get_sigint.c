#include "shell.h"

/**
 * get_sigint - the crtl + c call is handle in prompt
 * @sig: Signal handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
