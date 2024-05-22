#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "feed.h"
#include "users.h"
#include "graph.h"

void search_user_reposts(node_t *parent, unsigned int user_id, char *title)
{
    if(!parent) {
        return;
	}

	if(((tree_t*)(parent->data))->info->user_id == user_id && !((tree_t*)(parent->data))->info->title)
		printf("Reposted: %s\n", title);

    node_t *cr = ((tree_t*)(parent->data))->sons->head;
	if(!cr)
		return;
	
	while(cr->next)
		cr=cr->next;

    while(cr) {
        search_user_reposts(cr, user_id, title);
        cr = cr->prev;
    }
}

void search_user_posts(node_t *root, unsigned int user_id)
{
    if(!root)
        return;

    node_t *cr = ((tree_t*)(root->data))->sons->head;
	if(!cr)
		return;

	while(cr->next)
		cr=cr->next;

    while(cr) {
		char *title = ((tree_t*)(cr->data))->info->title;
		if(((tree_t*)(cr->data))->info->user_id == user_id)
			printf("Posted: %s\n", title);
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
	if (!cmd)
		return;

	if (!strcmp(cmd, "feed")) {
		cmd = strtok(NULL, "\n ");
		unsigned int a = get_user_id(cmd);
		cmd = strtok(NULL, "\n");
		int feed_size = atoi(cmd);
		node_t *cr = ((tree_t *)(posts->root->data))->sons->head;
		while(feed_size && cr) {
			post_info_t *post_info = ((tree_t *)(cr->data))->info;
			if(a == post_info->user_id || is_friend(social_media, a, post_info->user_id)) {
				printf("%s: %s\n", get_user_name(post_info->user_id), post_info->title);
				feed_size--;
			}
			cr=cr->next;
		}
		/*
		unsigned int latest_post_id = posts->nr_posts - 1;
		while(feed_size) {
			node_t *post = find_node_in_tree(posts->root, latest_post_id, latest_post_id);
			if(!post) {
				break;
			}
			post_info_t *post_info = ((tree_t *)(post->data))->info;
			if(post_info->title)
				if(a == post_info->user_id || is_friend(social_media, a, post_info->user_id)) {
					printf("%s: %s\n", get_user_name(post_info->user_id), post_info->title);
					feed_size--;
				}
			latest_post_id--;
		}*/
	} else if (!strcmp(cmd, "view-profile")) {
		cmd = strtok(NULL, "\n ");
		search_user_posts(posts->root, get_user_id(cmd));
	} else if (!strcmp(cmd, "friends-repost")) {
		cmd = strtok(NULL, "\n ");
		unsigned int a = get_user_id(cmd);
		cmd = strtok(NULL, "\n");
		unsigned int b = atoi(cmd);
		node_t *cr = ((tree_t *)posts->root->data)->sons->head;
		while(cr) {
			if(((tree_t *)cr->data)->info->id == b)
				break;
			cr = cr->next;
		}
		if(!cr) {
			printf("No such post\n");
			// exit(1);
			free(commands);
			return;
		}
		cr = ((tree_t *)cr->data)->sons->head;
		while(cr) {
			post_info_t *post_info = ((tree_t *)(cr->data))->info;
			if(is_friend(social_media, a, post_info->user_id)) {
				printf("%s\n", get_user_name(post_info->user_id));
			}
			cr = cr->next;
		}
	} else if (!strcmp(cmd, "common-groups")) {
		// TODO: Add function

	}

	free(commands);
}
