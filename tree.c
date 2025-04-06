#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct doctor {
    char name[50];
    char title[50];
    char department[50];
    struct doctor*left; 
    struct doctor*right; 
}doctor;
doctor* create(const char* name, const char* title, const char* department) {
    doctor* newdoc = (doctor*)malloc(sizeof(doctor));
    strncpy(newdoc->name, name, 49);
    strncpy(newdoc->title, title, 49);
    strncpy(newdoc->department, department, 49);
    newdoc->name[49] = '\0';
    newdoc->title[49] = '\0';
    newdoc->department[49] = '\0';
    newdoc->left = NULL;
    newdoc->right = NULL;
    return newdoc;
}
void preorderTraversal(doctor* root,int level) {
    if (root == NULL) return;
    int i;
    for (i=0;i<level;i++) {
        printf(" ");
    }
    printf("+-- %s (%s, %s)\n", root->name, root->title, root->department);
    preorderTraversal(root->left,level+1);
    preorderTraversal(root->right,level+1);
}
void inorder(doctor* root,int level) {
    if (root==NULL) return;
    inorder(root->left,level+1);
    int i;
    for(i=0;i<level;i++){
    	printf("  ");
	}
    printf("+-- %s (%s,%s)\n", root->name, root->title, root->department);
    inorder(root->right,level+1);
}
void postorder(doctor* root,int level){
    if (root == NULL) return;
    postorder(root->left,level+1);
    postorder(root->right,level+1);
    int i;
    for(i=0;i<level;i++){
    	printf("  ");
	}
    printf("+-- %s (%s,%s)\n", root->name, root->title, root->department);
}
int main() {
    doctor* root = create("Dr.Snehal B Shinde","Chief Medical Officer","Administration");
    root->left = create("Dr. Orange", "Head of Surgery", "Surgery");
    root->right = create("Dr. Blue", "Head of Cardiology", "Cardiology");
    root->left->left = create("Dr. Aditya", "Surgeon", "Surgery");
    root->left->right = create("Dr. Tushar", "Surgeon", "Brain Surgery");
    root->right->left = create("Dr. Raveena", "Cardiologist", "Cardiology");
    root->right->right = create("Dr. Aryan", "Cardiologist", "Cardiology");
    printf("\nPre-order Traversal:\n");
    preorderTraversal(root, 0);
    printf("\nIn-order Traversal:\n");
    inorder(root,0);
    printf("\nPost-order Traversal:\n");
    postorder(root,0);
    return 0;
}
