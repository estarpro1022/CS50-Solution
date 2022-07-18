## Linked Lists

define a node

```C
typedef struct node	// add node here
{
    int number;
    struct node *next;
}
node;
```

create a node

```C
node *list = NULL;
node *n = malloc(sizeof(node));	// tmp var
if (n != NULL) {
    n->number = 1;
    n->next = NULL;
}
list = n;	// list also point to the node
```

## realloc

```C
int *list = malloc(3 * sizeof(int));
list[0] = 1;
list[1] = 2;
list[2] = 3;

int *tmp = realloc(list, 4 * sizeof(int));
if (tmp == NULL) {
    free(list);	// Never forget to free
    return 1;
}
```

`realloc` can extend chunks of memory behind the  old array.

If there's no enough memory, it will copy the old array to a new area.

## implement linked lists

```C
// Print list
for (node *tmp = list; tmp != NULL; tmp = tmp->next) {
    printf("%d\n", tmp->number);
}

// Free list
while (list != NULL) {
    node *tmp = list->next;
    free(list);
    list = tmp;
}
```

## Trees

nodes point to other nodes.

each node point to a left node(value **smaller**) and a right node(value **larger**)

```C
typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
}
node;
```

```C
// Print tree----small to big from left to right
void print_tree(node *root) {
    if (root == NULL) {
        return;
    }
    print_tree(root->left);
    printf("%d\n", root->number);
    print_tree(root->right);
}

// Free tree
void free_tree(node *tree) {
    if (tree == NULL) {
        return;
    }
    free_tree(node->left);
    free_tree(node->right);
    free(tree);
}

// Search tree
bool search_tree(node *tree, int target) {
    if (tree == NULL) {
        return false;
    } else if (tree->number < target) {
        search_tree(tree->right, target);
    } else if (tree->number > target) {
        search_tree(tree->left, target);
    } else {
        return true;
    }
}
```

make the tree balanced if possible

![image-20220717162834840](https://gitee.com/starriverflow/cloud-pictures/raw/master/img/image-20220717162834840.png)

this binary tree has low efficiency

## Hash table

```C
typedef struct node
{
    char word[LONGEST_WORD + 1];
    struct node *next;
}
node;
```

![image-20220717164259915](https://gitee.com/starriverflow/cloud-pictures/raw/master/img/image-20220717164259915.png)

## trie

```c
typedef struct node
{
    bool is_word;
    struct node *children[SIZE_OF_ALPHABET];
}
node;
```

a tree with arrays as nodes

![image-20220717164522538](https://gitee.com/starriverflow/cloud-pictures/raw/master/img/image-20220717164522538.png)

## queue

first-in-first-out (FIFO)

## stack

last-in-last-out (LIFO)