#include "shell.h"

/**
 * cd_dot - changes to the parent directory
 * @shell_data: data relevant (environ)
 * Return: no return
 */
void cd_dot(data_shell *shell_data)
{
	char pwd[PATH_MAX];
	char *directory, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, shell_data);
	directory = shell_data->args[1];
	if (_strcmp(".", directory) == 0)
	{
		set_env("PWD", cp_pwd, shell_data);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_str(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_str(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, shell_data);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", shell_data);
	}
	shell_data->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @shell_data: data relevant (directories)
 * Return: no return
 */
void cd_to(data_shell *shell_data)
{
	char pwd[PATH_MAX];
	char *directory, *cp_pwd, *cp_directory;

	getcwd(pwd, sizeof(pwd));

	directory = shell_data->args[1];
	if (chdir(directory) == -1)
	{
		get_error(shell_data, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, shell_data);

	cp_directory = _strdup(directory);
	set_env("PWD", cp_directory, shell_data);

	free(cp_pwd);
	free(cp_directory);

	shell_data->status = 0;

	chdir(directory);
}

/**
 * cd_previous - changes to the previous directory
 *
 * @shell_data: data relevant (environ)
 * Return: no return
 */
void cd_previous(data_shell *shell_data)
{
	char pwd[PATH_MAX];
	char *previous_pwd, *old_pwd, *cp_pwd, *cp_old_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	old_pwd = _getenv("OLDPWD", shell_data->_environ);

	if (old_pwd == NULL)
		cp_old_pwd = cp_pwd;
	else
		cp_old_pwd = _strdup(old_pwd);

	set_env("OLDPWD", cp_pwd, shell_data);

	if (chdir(cp_old_pwd) == -1)
		set_env("PWD", cp_pwd, shell_data);
	else
		set_env("PWD", cp_old_pwd, shell_data);

	previous_pwd = _getenv("PWD", shell_data->_environ);

	write(STDOUT_FILENO, previous_pwd, _strlen(previous_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (old_pwd)
		free(cp_old_pwd);

	shell_data->status = 0;

	chdir(previous_pwd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @shell_data: data relevant (environ)
 * Return: no return
 */
void cd_to_home(data_shell *shell_data)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", shell_data->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, shell_data);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(shell_data, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, shell_data);
	set_env("PWD", home, shell_data);
	free(p_pwd);
	shell_data->status = 0;
}
