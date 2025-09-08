#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Siswa {
  int id;
  char name[50];
  float value;
} Siswa;

typedef struct Node {
  Siswa data;
  struct Node *next;
} Node;

Node *head = NULL;

Node *create_node(int id, const char *name, float value) {
  Node *new_node = (Node *)malloc(sizeof(Node));

  if (!new_node) {
    fprintf(stderr, "failed to allocated memory to new node\n");
    exit(EXIT_FAILURE);
  }

  new_node->data.id = id;
  strncpy(new_node->data.name, name, sizeof(new_node->data.name) - 1);
  new_node->data.name[sizeof(new_node->data.name) - 1] = '\0';
  new_node->data.value = value;
  new_node->next = NULL;

  return new_node;
}

void add_node_in_head(int id, char *name, float value) {
  Node *new_node = create_node(id, name, value);
  if (head == NULL) {
    head = new_node;
    new_node->next = head;
  } else {
    Node *tail = head;
    while (tail->next != head) {
      tail = tail->next;
    }

    new_node->next = head;
    tail->next = new_node;
    head = new_node;
  }

  printf("Data %s added in the head\n", name);
}

void add_node_in_tail(int id, char *name, float value) {
  Node *new_node = create_node(id, name, value);
  if (head == NULL) {
    head = new_node;
    new_node->next = head;
  } else {
    Node *tail = head;
    while (tail->next != head) {
      tail = tail->next;
    }

    tail->next = new_node;
    new_node->next = head;
  }

  printf("Data %s added in the tail\n", name);
}

void show_all() {
  if (head == NULL) {
    printf("data not found, or empty\n");
    return;
  }

  printf("List of student: ");
  Node *current_node = head;

  do {
    printf("[ %d -> %s - value -> %.2f] - ", current_node->data.id,
           current_node->data.name, current_node->data.value);
    current_node = current_node->next;
  } while (current_node != head);

  printf("Back to start [head]\n\n");
}

bool find_student(int id) {
  if (head == NULL) {
    return false;
  }

  Node *current_node = head;

  do {
    if (current_node->data.id == id) {
      printf("Data found: id -> %id, name = %s, value -> %.2f\n",
             current_node->data.id, current_node->data.name,
             current_node->data.value);

      return true;
    }
    current_node = current_node->next;
  } while (current_node != head);

  printf("Data from id %d not found\n", id);
  return false;
}

bool delete_student(int id) {
  if (head == NULL) {
    printf("List student empty\n");
    return false;
  }

  Node *current_node = head;
  Node *previous_node = NULL;

  do {
    if (current_node->data.id == id) {
      break;
    }

    previous_node = current_node;
    current_node = current_node->next;
  } while (current_node != head);

  if (current_node->data.id != id) {
    printf("Data not found\n");
    return false;
  }

  if (current_node->next == head && previous_node == NULL) {
    free(current_node);
    head = NULL;
    return true;
  }

  if (current_node == head) {
    Node *tail = head;
    while (tail->next != head) {
      tail = tail->next;
    }
    tail->next = head;
  } else {
    previous_node->next = current_node->next;
  }

  printf("Deleted %s already deleted from list student\n",
         current_node->data.name);
  free(current_node);
  return true;
}

void clean_up() {
  if (head == NULL) {
    return;
  }

  Node *current_node = head;
  Node *next;

  do {
    next = current_node->next;
    free(next);
    current_node = next;
  } while (current_node != head);

  head = NULL;
  printf("Clean up data succesfull\n");
}

int main() {
  add_node_in_head(101, "yb", 20.30);
  add_node_in_head(102, "ya", 50.30);
  add_node_in_tail(103, "ys", 99.30);

  show_all();
  find_student(101);
  find_student(103);
  find_student(9);

  delete_student(101);
  show_all();
  return 0;
}
