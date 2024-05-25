#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "feed.h"
#include "users.h"
#include "structures.h"

void search_user_reposts(void *data, unsigned int user_id, char *title)
{
	if (!data)
		return;
	node_t *parent = (node_t *)data;

	if (((tree_t *)parent->data)->info->user_id ==
		user_id && !((tree_t *)parent->data)->info->title)
		printf("Reposted: %s\n", title);

	node_t *cr = ((tree_t *)parent->data)->sons->head;
	if (!cr)
		return;

	while (cr->next)
		cr = cr->next;

	while (cr) {
		search_user_reposts(cr, user_id, title);
		cr = cr->prev;
	}
}

void search_user_posts(void *data, unsigned int user_id)
{
	if (!data)
		return;
	node_t *root = (node_t *)data;

	node_t *cr = ((tree_t *)(root->data))->sons->head;
	if (!cr)
		return;

	while (cr->next)
		cr = cr->next;

	// Posts
	while (cr) {
		char *title = ((tree_t *)cr->data)->info->title;
		if (((tree_t *)cr->data)->info->user_id == user_id)
			printf("Posted: %s\n", title);
		cr = cr->prev;
	}

	// Reposts
	cr = ((tree_t *)root->data)->sons->head;
	while (cr->next)
		cr = cr->next;

	while (cr) {
		char *title = ((tree_t *)cr->data)->info->title;
		search_user_reposts(cr, user_id, title);
		cr = cr->prev;
	}
}

void handle_input_feed(char *input, void *data1, void *data2)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");
	graph_t *social_media = (graph_t *)data1;
	all_posts_t *posts = (all_posts_t *)data2;

	if (!strcmp(cmd, "feed")) {
		cmd = strtok(NULL, "\n ");
		unsigned int user_id = get_user_id(cmd);
		cmd = strtok(NULL, "\n");
		int feed_size = atoi(cmd);
		node_t *cr = ((tree_t *)posts->root->data)->sons->head;
		while (feed_size && cr) {
			post_info_t *post_info = ((tree_t *)(cr->data))->info;
			if (user_id == post_info->user_id ||
				is_friend(social_media, user_id, post_info->user_id)) {
				printf("%s: %s\n", get_user_name(post_info->user_id),
					   post_info->title);
				feed_size--;
			}
			cr = cr->next;
		}
	} else if (!strcmp(cmd, "view-profile")) {
		cmd = strtok(NULL, "\n ");
		search_user_posts(posts->root, get_user_id(cmd));
	} else if (!strcmp(cmd, "friends-repost")) {
		cmd = strtok(NULL, "\n ");
		unsigned int a = get_user_id(cmd);
		cmd = strtok(NULL, "\n");
		node_t *cr = find_node_in_tree(posts->root, atoi(cmd), 0);
		cr = ((tree_t *)cr->data)->sons->head;
		while (cr) {
			post_info_t *post_info = ((tree_t *)(cr->data))->info;
			if (is_friend(social_media, a, post_info->user_id))
				printf("%s\n", get_user_name(post_info->user_id));
			cr = cr->next;
		}
	} else if (!strcmp(cmd, "common-group")) {
		cmd = strtok(NULL, "\n ");
		unsigned int user_id = get_user_id(cmd);
		clique_t *x = maximal_clique(social_media, user_id);
		printf("The closest friend group of %s is:\n", cmd);
		for (unsigned int i = 0; i < social_media->nodes; i++)
			if (x->state[i])
				printf("%s\n", get_user_name(i));
		free_clique(&x);
	}

	free(commands);
}
