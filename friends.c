#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "friends.h"
#include "users.h"

void handle_input_friends(char *input)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "add")) {
		cmd = strtok(NULL, "\n ");
		char *name1 = strdup(cmd);
		cmd = strtok(NULL, "\n ");
		char *name2 = strdup(cmd);
		
		free(name1);
		free(name2);
	}
	else if (!strcmp(cmd, "remove"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "suggestions"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "distance"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "common"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "friends"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "popular"))
		(void)cmd;
		// TODO: Add function

	free(commands);
}
