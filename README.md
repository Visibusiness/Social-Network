### Popa Filip-Andrei & Vișănescu Bogdan-Emilian
### ~ 313CAb 2023-2024 ~

## The project consists of implementing three different tasks:

### Task 1 (Friendship Network):
We implemented the friendship network using a graph structure, which contains a vector of doubly linked lists, one for each node in the graph. The list at index `i` will contain the nodes `j` for which there is an edge between node `i` and node `j`.

For the received commands, we do the following:
* For "add"/"remove": we add/remove an edge in/from the graph (i.e., we insert/remove node `i` in the list at position `j` and node `j` in the list at position `i`).
* For "suggestions": we search for the neighbors of the neighbors that are not already neighbors of a node with the given index.
* For "common": we find the common neighbors of two nodes.
* For "friends": we calculate the number of neighbors of a node, i.e., the size of the list in the graph structure at the index of the node.
* For "popular": we calculate the number of neighbors of the neighbors of a given node.
* For "distance": I implemented the `get_distance()` function, which calculates the distance between two nodes in the graph, and it is implemented as follows:
    ```
    1. We consider the `in_use[]` vector, which will function as a queue (we add at the `last` position, and the first element added will be at the `first` position). The queue is considered empty when `first > last`. Initially, the queue contains only the node from which the traversal starts.
    2. We consider the `distance[]` vector, which represents the distance from the initial node to each node in the graph (with the convention that `distance[x] = 0` if and only if node `x` has not yet been visited).
    3. We traverse the graph in breadth-first order: we remove a node from the queue and add all its unvisited neighbors. The distance from the initial node to the neighbors will be 1 greater than the distance to the removed node.
    4. We stop when we reach the target node or when the queue is empty, meaning the entire graph has been traversed without finding the target node, in which case no path exists between the two nodes.
    ```

### Task 2 (Posts and Reposts):
The structure of the posts is implemented as a tree whose root is a fictitious node called `posts->root`. The posts will be direct children of the root node, while reposts are the grandchildren of the nodes representing posts.

The tree is implemented as follows: for each node, the field `node->data` is a structure (named `tree_t` for lack of inspiration) that contains the information related to the post, a pointer to the parent node in the tree, and a list of pointers to the nodes that are direct children in the tree.

For the received commands, we do the following:
* For "create": we add a child to the root node.
* For "repost": we search for the node with the given ID and add a child to it.
* For "delete": we search for the node with the given ID and remove it from the tree.
* For "get-reposts": we call the `get_reposts()` function, which traverses the tree in preorder, starting from the node with the given ID.
* For "like": we search for the node with the given ID in the tree and add a like to it in the list `post_info->like`, which contains nodes of type `like_t`, that store the IDs of those who liked/disliked the post and whether they liked or disliked it.
* For "get-likes": we call the `get_likes()` function, which traverses the previously mentioned list and calculates only the number of likes (not dislikes).
* For "ratio": we call the `find_most_liked_id()` function, which traverses the subtree representing the reposts of the post with the given ID and calculates the number of likes for each repost, then updates `most_likes` and `most_liked_id` if necessary.

### Task 3 (Social Media):
This task is based on the structures implemented in the previous two tasks.

The commands are as follows:
* "feed": it traverses all the posts that are not reposts (i.e., direct children of the root node) and displays the first `feed_size` posts made by friends of the user with the given ID.
* "view-profile": it traverses all posts and reposts and displays the ones made by the user with the given ID.
* "friend-repost": it searches all the reposts of a post and displays those made by friends of the user with the given ID.
* "common-group": it calls the `maximal_clique()` function, which:
    ```
    1. starts with a set containing only the user with the given ID;
    2. using `clique_backtracking()`, it adds or doesn't add a user to the current set, and the addition occurs only if the user is friends with all other users in the current set;
    3. after all users have been traversed, a valid clique is generated, and we update the maximal clique if necessary.
    ```
