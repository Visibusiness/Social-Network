#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "posts.h"
#include "graph.h"

void handle_input_posts(char *input, void *data)
{
	all_posts *posts = (all_posts *)data;
	if(!posts)
		return;

	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "create")) {
		// create Mihai "Titlu postare"

		cmd = strtok(NULL, "\n ");
		char *user_name = cmd;
		unsigned int a = get_user_id(user_name);
		cmd = strtok(NULL, "\n");
		char *post_title = stdup(cmd);

		create_repost(posts->root, ++posts->nr_posts, a, post_title);
		printf("Created %s for %s\n", post_title, user_name);
	}
	else if (!strcmp(cmd, "repost"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "common-repost"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "like"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "ratio"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "delete"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "get-likes"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "get-reposts"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "get-likes"))
		(void)cmd;
		// TODO: Add function

	free(commands);
}

