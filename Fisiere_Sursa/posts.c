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
	if (must_print)
		printf("Repost #%d by %s\n", post_info->id,
			   get_user_name(post_info->user_id));
	node_t *cr = tree->sons->head;
	if (!cr)
		return;
	while (cr->next)
		cr = cr->next;
	while (cr)
	{
		print_reposts(cr, 1);
		cr = cr->prev;
	}
}

void handle_input_posts(char *input, void *data)
{
	all_posts_t *posts = (all_posts_t *)data;
	if (!posts)
		return;

	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "create"))
	{
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
		if (cmd)
			c = atoi(cmd);
		create_repost(find_node_in_tree(posts->root, b, c),
					  ++posts->nr_posts, a, NULL);
		printf("Created repost #%d for %s\n", posts->nr_posts, user_name);
	} else if (!strcmp(cmd, "get-reposts")) {
		cmd = strtok(NULL, "\n ");
		unsigned int b = atoi(cmd);
		cmd = strtok(NULL, "\n");
		unsigned int c = 0;
		if (cmd)
			c = atoi(cmd);
		node_t *post = find_node_in_tree(posts->root, b, c);
		post_info_t *post_info = ((tree_t *)(post->data))->info;
		if (!c) {
			printf("%s - Post by %s\n", post_info->title,
				   get_user_name(post_info->user_id));
			print_reposts(post, 0);
		} else {
			print_reposts(post, 1);
		}
	} else if (!strcmp(cmd, "common-repost")) {
		cmd = strtok(NULL, "\n ");
		unsigned int a = atoi(cmd);
		cmd = strtok(NULL, "\n ");
		unsigned int b = atoi(cmd);
		cmd = strtok(NULL, "\n");
		unsigned int c = atoi(cmd);
		node_t *post1 = find_node_in_tree(posts->root, a, b);
		node_t *post2 = find_node_in_tree(posts->root, a, c);
		node_t *common = common_repost_id(posts->root, post1, post2);
		int repost_id = ((tree_t *)common->data)->info->id;
		printf("The first common repost of %d and %d is %d\n", b, c, repost_id);
	} else if (!strcmp(cmd, "like")) {
		cmd = strtok(NULL, "\n ");
		char *user_name = cmd;
		unsigned int a = get_user_id(user_name);
		cmd = strtok(NULL, "\n ");
		unsigned int b = atoi(cmd);
		cmd = strtok(NULL, "\n");
		unsigned int c = 0;
		if (cmd)
			c = atoi(cmd);
		node_t *post = find_node_in_tree(posts->root, b, c);
		post_info_t *post_info = ((tree_t *)(post->data))->info;
		list_t *likes = post_info->likes;
		node_t *like = find_like(likes, a);
		node_t *aux = find_node_in_tree(posts->root, b, 0);
		char *title = ((tree_t *)(aux->data))->info->title;
		printf("User %s ", user_name);
		if (!like) {
			add_in_list(likes, new_node(new_like(a)));
		} else {
			like_t *edited_like = (like_t *)(like->data);
			if (edited_like->like == 1)
				printf("un");
			edited_like->like *= -1;
		}
		if (c)
			printf("liked repost %s\n", title);
		else
			printf("liked post %s\n", title);
	} else if (!strcmp(cmd, "get-likes")) {
		cmd = strtok(NULL, "\n ");
		unsigned int b = atoi(cmd);
		cmd = strtok(NULL, "\n");
		unsigned int c = 0;
		if (cmd)
			c = atoi(cmd);
		node_t *found = find_node_in_tree(posts->root, b, c);
		post_info_t *post_info = ((tree_t *)(found->data))->info;
		list_t *likes = post_info->likes;
		unsigned int nr_likes = like_count(likes);
		if (c) {
			printf("Repost #%d has %d likes\n", post_info->id, nr_likes);
		} else {
			node_t *found = find_node_in_tree(posts->root, b, 0);
			char *title = ((tree_t *)(found->data))->info->title;
			printf("Post %s has %d likes\n", title, nr_likes);
		}
	} else if (!strcmp(cmd, "ratio")) {
		cmd = strtok(NULL, "\n ");
		unsigned int post_id = atoi(cmd);
		node_t *post = find_node_in_tree(posts->root, post_id, 0);
		unsigned int most_likes = 0, most_liked_id = 0;
		find_most_liked_id(post, &most_likes, &most_liked_id);
		if (most_likes > like_count(((tree_t *)post->data)->info->likes))
			printf("Post %d got ratio'd by repost %d\n",
				   post_id, most_liked_id);
		else
			printf("The original post is the highest rated\n");
	} else if (!strcmp(cmd, "delete")) {
		cmd = strtok(NULL, "\n ");
		unsigned int b = atoi(cmd);
		cmd = strtok(NULL, "\n");
		unsigned int c = 0;
		if (cmd)
			c = atoi(cmd);
		node_t *post = find_node_in_tree(posts->root, b, c);
		tree_t *tree = (tree_t *)(post->data);
		node_t *parent = tree->parent;
		if (c) {
			node_t *found = find_node_in_tree(posts->root, b, 0);
			char *title = ((tree_t *)(found->data))->info->title;
			printf("Deleted repost #%d of post %s\n", tree->info->id, title);
		} else {
			printf("Deleted post %s\n", tree->info->title);
		}
		remove_repost(((tree_t *)(parent->data))->sons, post);
		free_post(&post);
	}

	free(commands);
}

