#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//* Struct each Node of Tree
typedef struct Node {
    char title_node[100]; 
    int number_page_node;    
    struct Node* first_child; 
    struct Node* next_sibling; 
} Node;

//? Create Node of Tree
Node* create_node_tree(const char* title, int number_pages) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->title_node, title);
    node->number_page_node = number_pages;
    node->first_child = NULL;
    node->next_sibling = NULL;
    return node;
}

//? Add Node Child of Node Parent
void add_child_to_parent(Node* parent, Node* child) {
    if (!parent->first_child) {
        parent->first_child = child;
    } else {
        Node* temp = parent->first_child;
        while (temp->next_sibling) {
            temp = temp->next_sibling;
        }
        temp->next_sibling = child;
    }
}

//* Count the number of Chapters
int count_chapters(Node* root) {
    int count = 0;
    Node* temp = root->first_child;
    while (temp) {
        count++;
        temp = temp->next_sibling;
    }
    return count;
}

//* Find the Chapter longest
Node* find_chapter_longest(Node* root) {
    Node* longest = NULL;
    int max_pages = 0;
    Node* current = root->first_child;
    while (current) {
        if (current->number_page_node > max_pages) {
            max_pages = current->number_page_node;
            longest = current;
        }
        current = current->next_sibling;
    }
    return longest;
}

//? Update number pages of each node after delete
void update_page(Node* parent) {
    if (!parent || !parent->first_child) return;
    Node* current = parent->first_child;
    int previousPages = 0;
    while (current) {
        current->number_page_node += previousPages;
        previousPages = current->number_page_node;
        current = current->next_sibling;
    }
}

//* Find and Delete Node 
Node* find_and_delete_node(Node* parent, const char* title) {
    if (!parent) return NULL;
    Node* prev = NULL;
    Node* current = parent->first_child;
    while (current) {
        if (strcmp(current->title_node, title) == 0) {
            if (prev) {
                prev->next_sibling = current->next_sibling;
            } else {
                parent->first_child = current->next_sibling;
            }
            update_page(parent);
            current->next_sibling = NULL;
            return current;
        }
        prev = current;
        current = current->next_sibling;
    }
    current = parent->first_child;
    while (current) {
        Node* result = find_and_delete_node(current, title);
        if (result) return result;
        current = current->next_sibling;
    }
    return NULL;
}

//* Driver Code
int main() {
    Node* root = create_node_tree("Book", 0);
    Node* chapter1 = create_node_tree("Chapter 1", 16);
    Node* chapter2 = create_node_tree("Chapter 2", 32);
    Node* chapter3 = create_node_tree("Chapter 3", 64);

    add_child_to_parent(root, chapter1);
    add_child_to_parent(root, chapter2);
    add_child_to_parent(root, chapter3);
    add_child_to_parent(chapter1, create_node_tree("Section 1.1", 8));
    add_child_to_parent(chapter1, create_node_tree("Section 1.2", 8));
    add_child_to_parent(chapter2, create_node_tree("Section 2.1", 10));
    add_child_to_parent(chapter2, create_node_tree("Section 2.2", 22));
    add_child_to_parent(chapter3, create_node_tree("Section 3.1", 20));
    add_child_to_parent(chapter3, create_node_tree("Section 3.2", 30));
    add_child_to_parent(chapter3, create_node_tree("Section 3.3", 14));

    printf("So chuong: %d\n", count_chapters(root));

    Node* longest = find_chapter_longest(root);
    if (longest) {
        printf("Chuong dai nhat: %s\n", longest->title_node);
    }

    Node* deleted = find_and_delete_node(root, "Section 3.3");
    if (deleted) {
        printf("Da xoa: %s\n", deleted->title_node);
        free(deleted);
    }

    return 0;
}