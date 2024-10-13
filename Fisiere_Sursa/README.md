
## Description

As Marcel had incredible success with his cloud storage services, he started thinking about how he could expand his services to compete with industry giants, aiming to launch globally. After several days of brainstorming, he realized that it would be very helpful if all his needs weren't so scattered. Instead of having cloud storage on Gogu Drive, social networking on InstaBook, and his favorite opinion-sharing app Z, it would be much simpler to have them all in one place.

Having already implemented the cloud storage part from his previous project, it's time for him to create his favorite social networks, and with the semester approaching, he needs your help. Therefore, he has provided the functionalities he wants in the Alpha version of his platform, and it is your duty to implement his requirements. He has divided the requirements into 3 stages, corresponding effectively with each part of the application (The first stage for the friendship network, the second stage for posts, and the third stage for combining everything into a social media feed). He has provided you with a code skeleton for his overall vision and promised you a stable job and a share of the platform's profit if you manage to help him in time!

## Task 1 (Friendship Network)

### Add Friend

`add name-1 name-2`

Creates a connection between two users. This is a bidirectional connection, meaning both people will be added to each other's friends list.

Example:

```
 add Mihai Andrei
 Added connection Mihai - Andrei
```

For each input, it is guaranteed that non-existing or repeated users won't be used.

### Remove Friend

`remove name-1 name-2`

Removes the connection between two users.

Example:

```
 add Mihai Andrei
 remove Mihai Andrei
 Removed connection Mihai - Andrei
```

### Find Distance

`distance name-1 name-2`

Calculates the distance between 2 people on the platform. The distance is considered to be 1 for each friendship.

Example:

```
 add Mihai Andrei
 add Andrei Alex
 add Alex Mihnea
 distance Mihai Mihnea
 The distance between Mihai - Mihnea is 3
```

If there is no connection between the two users, it will display: `There is no way to get from name-1 to name-2`.

### Suggestions

`suggestions name`

Finds and displays all friends of friends who are not already your friends. Friends will be displayed in ascending order based on the user's id.

Example:

```
 add Alex Andrei
 add Andrei Maria
 add Andrei Mihai
 add Andrei Vlad
 suggestions Alex
 Suggestions for Alex:
 Maria
 Mihai
 Vlad
```

If there are no suggestions for a user, it will display: `There are no suggestions for name`.

### Common Friends

`common name-1 name-2`

You need to find the common friends of two users. A common friend is someone who is friends with both `name-1` and `name-2`. You will display the list of friends sorted in ascending order by the user's id.

Example:

```
 common Alex Ana
 The common friends between Alex and Ana are:
 Andrei
 Maria
 Ioana
```

If there are no common friends, it will display: `No common friends for name-1 and name-2`.

### Number of Friends

`friends name`

```
 friends Andrei
 Andrei has 5 friends
```

You need to display the number of connections a person has.

### Most Popular

`popular name`

You need to display the user with the most connections among `name` and their friends.

Example (assuming Andrei, Mihai, and Ana are all friends):

```
 friends Andrei
 10
 friends Mihai
 15
 friends Ana
 9
 popular Ana
 Mihai is the most popular friend of Ana
 popular Mihai
 Mihai is the most popular
```

In case of a tie with themselves and other friends, they will be considered the most popular friend. In case of a tie among friends, the one with the first id will be chosen.

## Task 2 (Posts and Reposts)

For this stage, we will work with a tree-like data structure, which will be used to store posts and reposts. Each post will have a unique id and can have multiple reposts. A repost will be a post in itself, with a unique id, and it will be linked to the original post. We will use a tree to store these posts and reposts, where each node will have a field `events`, which will be a tree of posts and reposts.

```
struct {
    id number,
    title string,
    user_id number,
    events tree
}
```

### Create a Post

`create name title`

The user `name` will create a post with the title `title`. Each post will have a unique id, which will be incremented with each new post.

Example:

```
 create Mihai Post Title
 Created Post Title for Mihai
```

#### Restrictions and Clarifications

- A user can have multiple posts.
- A user can have multiple posts with the same title.
- The title of a post can have a maximum of 280 characters.
- The post id will be a positive integer, unique for each post.

Indexing will start from 1.

### Repost

`repost name post-id [repost-id]`

Creates a repost of an existing post. If the `repost` command includes a repost id, then it is considered a repost of a repost.

...

