// typedef struct Node {
//   int data;
//   struct Node *next;
// } Node;

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Task {
  int id;
  char description[128];
  int priority;
} Task;

typedef struct Node {
  Task task;
  struct Node *next;
} Node;

Node *head = NULL;

Node *create_node(int id, const char *desc, int priority) {
  Node *new_node = (Node *)malloc(sizeof(Node));

  if (!new_node) {
    fprintf(stderr, "failed to allocate new memory to new_node\n");
    exit(EXIT_FAILURE);
  }

  new_node->task.id = id;
  strncpy(new_node->task.description, desc,
          sizeof(new_node->task.description) - 1);
  new_node->task.description[sizeof(new_node->task.description) - 1] = '\0';
  new_node->task.priority = priority;

  new_node->next = NULL;

  return new_node;
}

void add_task(const char *desc, int priority) {
  static int next_id = 1;
  Node *new_node = create_node(next_id++, desc, priority);

  if (head == NULL) {
    head = new_node;
  } else {
    Node *now = head;
    while (now->next != NULL) {
      now = now->next;
    }
    now->next = new_node;
  }

  printf("Task with ID %d already add: %s (priority: %d)\n", new_node->task.id,
         desc, priority);
}

bool task_execution() {
  if (head == NULL) {
    printf("Queue empty, please add\n");
    return false;
  }

  Node *now = head;
  printf("Task with id %d : %s (priority: %d)\n", now->task.id,
         now->task.description, now->task.priority);

  head = head->next;

  free(now);
  return true;
}

void show_task() {
  if (head == NULL) {
    printf("Task not found in linked list, please add \n");
    return;
  }

  printf("List tasks\n");
  Node *now = head;
  while (now != NULL) {
    printf("%d %s %d\n", now->task.id, now->task.description,
           now->task.priority);
    now = now->next;
  }
  printf("\n");
}

bool delete_task(int id) {
  if (head == NULL) {
    return false;
  }

  Node *now = head;
  Node *before = NULL;

  while (now != NULL && now->task.id != id) {
    before = now;
    now = now->next;
  }

  if (now == NULL) {
    printf("Task with ID requested not found\n");
    return false;
  }

  if (before == NULL) {
    head = now->next;
  } else {
    before->next = now->next;
  }

  printf("Task with id %d deleted: %s\n", id, now->task.description);
  free(now);
  return true;
}

void delete_list() {
  Node *now = head;

  while (now != NULL) {

    Node *next = now->next;
    free(now);
    now = next;
  }
  head = NULL;
  printf("All task cleared\n");
}

int main() {
  add_task("Process add a payment", 5);
  add_task("Sync data", 1);
  add_task("Backup data", 2);
  add_task("Paid chair", 9);

  show_task();
  task_execution();
  task_execution();
  // delete_task(3);
  show_task();
  delete_task(20);

  delete_list();
  return 0;
}
