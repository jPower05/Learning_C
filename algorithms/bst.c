#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treenode{
    char *data;
    int count;
    struct treenode *left;
    struct treenode *right;
}treenode;

treenode *add_node(char *data, treenode *curr);
treenode *create_node(char * data);
void print_tree(treenode *curr, int level);

treenode *create_node(char *data){
    treenode *n = malloc(sizeof(treenode));
        n->data = strdup(data);
        n->count = 1;
        n->left = NULL;
        n->right = NULL;
    return n;
}

treenode *add_node(char *data, treenode *curr){
    int cond;
    if(curr == NULL){
        curr = create_node(data);
        return curr;
    }
    else if((cond = strcmp(data, curr->data)) == 0){
        curr->count++;
    }
    else if(cond < 0){
        curr->left = add_node( data, curr->left);
    }
    else{
        curr->right = add_node(data, curr->right);
    }
    return curr;
}

void printtabs(int numtabs){
    for(int i = 0; i < numtabs; i++){
        printf("\t");
    }
}

void print_tree(treenode *curr, int level){
    if(curr == NULL){
        printtabs(level);
        printf("---empty---\n");
        return;
    }
    printtabs(level);
    printf("value = %s, count = %d\n", curr->data, curr->count);

    printtabs(level);
    printf("---left---\n");
    print_tree(curr->left, level+1);

    printtabs(level);
    printf("---right---\n");
    print_tree(curr->right, level+1);

}

// Traverse and print addresses
void trace_bst(treenode *root, int depth) {
    if (root == NULL) return;

    for (int i = 0; i < depth; i++) printf("  ");
    printf("Node %p -> word='%s' | left=%p | right=%p\n",
           (void*)root,
           root->data,
           (void*)root->left,
           (void*)root->right);

    trace_bst(root->left, depth + 1);
    trace_bst(root->right, depth + 1);
}

// Free all nodes in BST
void free_bst(treenode *root) {
    if (root == NULL) return;

    // Free children first (post-order)
    free_bst(root->left);
    free_bst(root->right);

    printf("Freeing node at %p with word='%s'\n", (void*)root, root->data);
    free(root->data);  // free the string
    free(root);        // free the node itself
}

int main(){
    
    treenode *root = add_node("now", NULL);
    add_node("is", root);
    add_node("the", root);
    add_node("for", root);
    add_node("men of", root);
    add_node("time", root);
    add_node("all", root);
    add_node("good", root);
    add_node("party their", root);
    add_node("to", root);
    add_node("aid", root);
    add_node("come", root);
    add_node("now", root);

    //print_tree(&root, 0);
    printf("\n--- Tracing BST pointers ---\n");
    trace_bst(root, 0);

    printf("\n--- Freeing BST ---\n");
    free_bst(root);



    return 0;
}