#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "posts.h"
#include "graph.h"

void print_reposts(node_t *post, int must_print)
{
    tree_t *tree = (tree_t *)(post->data);
    post_info_t *post_info = tree->info;
	if(must_print)
	    printf("Repost #%d by %s\n", post_info->id, get_user_name(post_info->user_id));
	node_t *cr = tree->sons->head;
	if(!cr)
		return;
	while(cr->next)
		cr = cr->next;
	while (cr) {
		print_reposts(cr, 1);
		cr = cr->prev;
	}
}

void handle_input_posts(char *input, void *data)
{
	all_posts_t *posts = (all_posts_t*)data;
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
		char *post_title = strdup(cmd);

		create_repost(posts->root, ++posts->nr_posts, a, post_title);
		printf("Created %s for %s\n", post_title, user_name);
	} else if (!strcmp(cmd, "repost")) {
		cmd = strtok(NULL, "\n ");
		char *user_name = cmd;
		unsigned int a = get_user_id(user_name);
		cmd = strtok(NULL, "\n ");
		unsigned int b = atoi(cmd);
		cmd = strtok(NULL, "\n");
		unsigned int c = 0;
		if(cmd)
			c = atoi(cmd);
		create_repost(find_node_in_tree(posts->root, b, c), ++posts->nr_posts, a, NULL);
		printf("Created repost #%d for %s\n", posts->nr_posts, user_name);
	} else if (!strcmp(cmd, "get-reposts")) {
		cmd = strtok(NULL, "\n ");
		unsigned int b = atoi(cmd);
		cmd = strtok(NULL, "\n");
		unsigned int c = 0;
		if(cmd)
			c = atoi(cmd);
		node_t *post = find_node_in_tree(posts->root, b, c);
		post_info_t *post_info = ((tree_t *)(post->data))->info;
		// printf("%s - Post #%d by %s\n", post_info->title, post_info->id, get_user_name(post_info->user_id));
		printf("%s - Post by %s\n", post_info->title, get_user_name(post_info->user_id));
		print_reposts(post, 0);
	}
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
	else if (!strcmp(cmd, "get-likes"))
		(void)cmd;
		// TODO: Add function

	free(commands);
}

