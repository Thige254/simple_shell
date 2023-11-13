#include "shell.h"

/**
 * append_variable - Adds a variable at the end
 * of a variable list.
 * @head: Head of the linked list.
 * @length_var: Length of the variable.
 * @value: Value of the variable.
 * @length_val: Length of the value.
 * Return: Address of the head.
 */
r_var *append_variable(r_var **head,
int length_var, char *value, int length_val)
{
	r_var *new_node, *temp;

	new_node = malloc(sizeof(r_var));
	if (new_node == NULL)
		return (NULL);

	new_node->len_var = length_var;
	new_node->val = value;
	new_node->len_val = length_val;

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
 * free_variable_list - Frees a variable list.
 * @head: Head of the linked list.
 * Return: No return.
 */
void free_variable_list(r_var **head)
{
	r_var *temp;
	r_var *curr;

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
