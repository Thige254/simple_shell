#include "shell.h"
#include <stdlib.h>
#include <string.h>

/**
 * Deletes the node at the given index in the list.
 * Returns 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, size_t index)
{
	size_t i; /* Declare i at the beginning */
	list_t *prev = NULL;
	list_t *current = *head;

	if (*head == NULL)
		return (0);

	for (i = 0; current != NULL && i < index; i++)
	{
		prev = current;
		current = current->next;
	}

	if (current == NULL)
		return (0);

	if (index == 0)
	{
		*head = current->next;
	}
	else
	{
		prev->next = current->next;
	}

	free(current->str);
	free(current);
	return (1);
}
