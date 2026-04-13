#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node* left;
    struct node* right;
};

struct node * Newnode(int data){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left=temp->right=NULL;
    return temp;
}

struct node * insertnode(struct node * root,int data)
{
    if(root==NULL){
        return Newnode(data);
    }
    if(data<root->data)
    {
        root->left = insertnode(root->left,data);
    }
    else if(root->data<data)
    {
        root->right = insertnode(root->right,data);
    }
    return root;
}
void inorder(struct node * root)
{
    if(root == NULL)return;

    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}
struct node *search(struct node *root,int n)
{
    if(root==NULL || root->data==n)
    {
        return root;
    }
    if (n<root->data)
    {
        return search(root->left,n);
    }
    if (n>root->data)
    {
        return search(root->right,n);
    }
    
}

struct node*minvalue(struct node* root, int data)
{
    struct node* current = root;
    while(current!=NULL && current->left!=NULL)
    {
        current = current->left;
    }
}
struct node *deletenode(struct node* root,int data)
{
    if(root == NULL)
        return root;
    if(root->data==data)
    if(data<root->data)
    {
        root->left = deletenode(root->left,data);
    }
    if(data>root->data)
    {
        root->right = deletenode(root->right,data);
    }
    else
    {
        if(root->left==NULL)
        {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        struct node* temp = minvalue(root->right,data);
        root->data = temp->data;
        root->right = deletenode(root->right,temp->data);
    }
    return root;
}


int main()
{
    struct node* root = NULL;
    root = insertnode(root,50);
    insertnode(root,30);
    insertnode(root,20);
    insertnode(root,40);
    insertnode(root,70);
    insertnode(root,60);
    insertnode(root,80);
    printf("Inorder traversal of the given tree \n");
    inorder(root);
    printf("\n");
    printf("Delete 20\n");
    root = deletenode(root,20);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);
    printf("\n");
    printf("Delete 30\n");
    root = deletenode(root,30);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);
    printf("\n");
    printf("Delete 50\n");
    root = deletenode(root,50);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);
    printf("\n");
    struct node* result = search (root,60);
    if(result!=NULL)
    {
        printf("Element %d found in the BST\n",result->data);
    }
    else
    {
        printf("Element not found in the BST\n");
    }
    return 0;
}