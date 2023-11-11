#include "shell.h"

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments.
 * @var: the string env var property.
 * @value: the string env var value.
 * Return: 1 on success, 0 on failure.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf;
	list_t *node;

	if (!var || !value)
		return (0);

	buf = malloc(strlen(var) + strlen(value) + 2);
	if (!buf)
		return (0);

	strcpy(buf, var);
	strcat(buf, "=");
	strcat(buf, value);

	node = info->environ;
	while (node)
	{
		char *p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (1); /* On success */
		}
		node = node->next;
	}

	add_node_end(&(info->environ), buf, info->env_changed);
	free(buf);
	info->env_changed = 1;

	return (1); /* On success */
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 * @var: the string env var property.
 * Return: 1 on success, 0 on failure.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node;
	size_t i = 0;

	if (!var)
		return (0);

	node = info->environ;
	while (node)
	{
		char *p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->environ), i);
			return (1); /* On success */
		}
		node = node->next;
		i++;
	}

	return (0); /* On failure */
}
