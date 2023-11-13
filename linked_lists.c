#include "shell.h"

/**
 * append_separator - Adds a separator found at the end
 * of a separator list.
 * @head: Head of the linked list.
 * @separator: Separator found (; | &).
 * Return: Address of the head.
 */
sep_list *append_separator(sep_list **head, char separator)
{
	sep_list *new_node, *temp;

	new_node = malloc(sizeof(sep_list));
	if (new_node == NULL)
		return (NULL);

	new_node->separator = separator;
	new_node->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new_node;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}

	return (*head);
}

/**
 * free_separator_list - Frees a separator list.
 * @head: Head of the linked list.
 * Return: No return.
 */
void free_separator_list(sep_list **head)
{
	sep_list *temp;
	sep_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * append_line - Adds a command line at the end
 * of a line list.
 * @head: Head of the linked list.
 * @line: Command line.
 * Return: Address of the head.
 */
line_list *append_line(line_list **head, char *line)
{
	line_list *new_node, *temp;

	new_node = malloc(sizeof(line_list));
	if (new_node == NULL)
		return (NULL);

	new_node->line = line;
	new_node->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new_node;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}

	return (*head);
}

/**
 * free_line_list - Frees a line list.
 * @head: Head of the linked list.
 * Return: No return.
 */
void free_line_list(line_list **head)
{
	line_list *temp;
	line_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
