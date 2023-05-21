#include "shell.h"

/**
 * isCurrentDirectory - checks if ":" is in the current directory
 * @path: path string
 * @index: pointer to the index
 * Return: 1 if the path is searchable in the current directory, 0 otherwise
 */
int isCurrentDirectory(char *path, int *index)
{
	if (path[*index] == ':')
		return (1);

	while (path[*index] != ':' && path[*index] != '\0')
	{
		(*index)++;
	}

	if (path[*index] != '\0')
		(*index)++;

	return (0);
}

/**
 * findExecutablePath - locates a command in the directories
 * specified by the PATH variable
 *
 * @command: command name
 * @environment: environment variable array
 * Return: the path of the command if found, NULL otherwise
 */
char *findExecutablePath(char *command, char **environment)
{
	char *path, *pathCopy, *pathToken, *directory;
	int directoryLength, commandLength, index;
	struct stat st;

	path = _getenv("PATH", environment);
	if (path)
	{
		pathCopy = _strdup(path);
		commandLength = _strlen(command);
		pathToken = _strtok(pathCopy, ":");
		index = 0;
		while (pathToken != NULL)
		{
			if (isCurrentDirectory(path, &index))
			{
				if (stat(command, &st) == 0)
					return (command);
			}
			directoryLength = _strlen(pathToken);
			directory = malloc(directoryLength + commandLength + 2);
			_strcpy(directory, pathToken);
			_strcat(directory, "/");
			_strcat(directory, command);
			if (stat(directory, &st) == 0)
			{
				free(directory);
				return (directory);
			}
			free(directory);
			pathToken = _strtok(NULL, ":");
		}
		free(pathCopy);
		if (stat(command, &st) == 0)
			return (command);
		return (NULL);
	}
	if (command[0] == '/')
		if (stat(command, &st) == 0)
			return (command);
	return (NULL);
}

/**
 * isExecutable - determines if a command is an executable
 *
 * @shellData: shell data structure
 * Return: 0 if it is not an executable, the index if it is
 */
int isExecutable(data_shell *shellData)
{
	struct stat st;
	int i;
	char *input;

	input = shellData->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	get_error(shellData, 127);
	return (-1);
}

/**
 * checkCommandError - verifies if the user has permissions
 * to access the command
 *
 * @directory: destination directory
 * @shellData: shell data structure
 * Return: 1 if there is an error, 0 if not
 */
int checkCommandError(char *directory, data_shell *shellData)
{
	if (directory == NULL)
	{
		get_error(shellData, 127);
		return (1);
	}

	if (_strcmp(shellData->args[0], directory) != 0)
	{
		if (access(directory, X_OK) == -1)
		{
			get_error(shellData, 126);
			free(directory);
			return (1);
		}
		free(directory);
	}
	else
	{
		if (access(shellData->args[0], X_OK) == -1)
		{
			get_error(shellData, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * execute_command - executes command lines
 *
 * @shellData: data relevant (args and input)
 * Return: 1 on success.
 */
int execute_command(data_shell *shellData)
{
	pid_t childPid;
	pid_t waitPid;
	int state;
	int executableIndex;
	char *commandPath;
	(void) waitPid;

	executableIndex = isExecutable(shellData);
	if (executableIndex == -1)
		return (1);
	if (executableIndex == 0)
	{
		commandPath = findExecutablePath(shellData->args[0], shellData->_environ);
		if (checkCommandError(commandPath, shellData) == 1)
			return (1);
	}

	childPid = fork();
	if (childPid == 0)
	{
		if (executableIndex == 0)
			commandPath = findExecutablePath(shellData->args[0], shellData->_environ);
		else
			commandPath = shellData->args[0];
		execve(commandPath + executableIndex, shellData->args, shellData->_environ);
	}
	else if (childPid < 0)
	{
		perror(shellData->prog_name[0]);
		return (1);
	}
	else
	{
		do {
			waitPid = waitpid(childPid, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	shellData->status = state / 256;
	return (1);
}
