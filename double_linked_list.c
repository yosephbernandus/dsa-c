// typedef struct Node {
//   int data;
//   struct Node* next;
//   struct Node* prev;
// } Node;
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define CACHE_CAPACITY 3
#define HASH_SIZE 100

typedef struct Node {
  int key;
  int value;
  struct Node *next;
  struct Node *prev;
} Node;

Node *head = NULL;
Node *tail = NULL;
Node *cache_map[HASH_SIZE];

Node *create_node(int key, int value) {
  Node *new_node = (Node *)malloc(sizeof(Node));

  if (!new_node) {
    fprintf(stderr, "failed to create new node\n");
    exit(EXIT_FAILURE);
  }

  new_node->key = key;
  new_node->value = value;
  new_node->next = NULL;
  new_node->prev = NULL;

  return new_node;
}

void delete_node(Node *node) {
  if (node->prev) {
    node->prev->next = node->next;
  } else {
    head = node->next;
  }

  if (node->next) {
    node->next->prev = node->prev;
  } else {
    tail = node->prev;
  }
}

void add_node_at_front(Node *node) {
  node->next = head;
  node->prev = NULL;

  if (head) {
    head->prev = node;
  }

  head = node;

  if (tail == NULL) {
    tail = node;
  }
}

Node *delete_tail() {
  if (tail == NULL) {
    return NULL;
  }
  Node *node = tail;
  delete_node(node);
  return node;
}

bool access_data(int key, int *value) {
  int indexs = key % HASH_SIZE;
  Node *node = cache_map[indexs];

  if (node && node->key == key) {
    delete_node(node);
    add_node_at_front(node);
    *value = node->value;
    printf("data key = %d, value = %d\n", key, node->value);
    return true;
  }

  printf("data from key = %d not found \n", key);
  return false;
}

void add(int key, int value) {
  int indexs = key % HASH_SIZE;
  Node *node = cache_map[indexs];

  if (node && node->key == key) {
    node->value = value;
    delete_node(node);
    add_node_at_front(node);
    printf("update data: %d, value = %d\n", key, value);
    return;
  }

  int current_size = 0;
  Node *current_node = head;

  while (current_node) {
    current_size++;
    current_node = current_node->next;
  }

  if (current_size >= CACHE_CAPACITY) {
    Node *delete = delete_tail();
    if (delete) {
      int old_index = delete->key % HASH_SIZE;
      cache_map[old_index] = NULL;
      printf("data key = %d\n", delete->key);
      free(delete);
    }
  }

  Node *new_node = create_node(key, value);
  add_node_at_front(new_node);
  cache_map[indexs] = new_node;
  printf("add insert data key = %d, value = %d\n", key, value);
}

void show_cache() {
  printf("cache data (old -> new): ");
  Node *current_node = head;

  if (!current_node) {
    printf("Empty node, need to fill the node");
  }

  while (current_node) {
    printf("[%d  : %d]", current_node->key, current_node->value);
    if (current_node->next) {
      printf(" => ");
    }
    current_node = current_node->next;
  }
  printf("\n\n");
}

void hapus_semua() {
  Node *current_node = head;

  while (current_node) {
    Node *next = current_node->next;
    free(current_node);
    current_node = next;
  }

  for (int i = 0; i < HASH_SIZE; i++) {
    cache_map[i] = NULL;
  }

  head = tail = NULL;
  printf("Cleared cache data\n");
}

int main() {
  add(1, 100);
  add(2, 200);
  add(3, 300);

  show_cache();

  int value;
  access_data(2, &value);

  add(4, 400);
  show_cache();

  hapus_semua();

  show_cache();

  return 0;
}
