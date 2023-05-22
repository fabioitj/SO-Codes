#include "schedule_fcfs.h"
#include "list.h"
#include "cpu.h"

struct node *taskList = NULL;

void add(char *name, int priority, int burst) {
    Task *newTask = malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    insert(&taskList, newTask);
}

void schedule() {
    struct node *temp = taskList;
    while (temp != NULL) {
        run(temp->task->name, temp->task->burst);
        temp = temp->next;
    }
}

void insert(struct node **head, Task *task) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->task = task;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void delete(struct node **head, Task *task) {
    if (*head == NULL) {
        return;
    }

    struct node *temp = *head;
    if (temp->task == task) {
        *head = temp->next;
        free(temp);
        return;
    }

    struct node *prev = NULL;
    while (temp != NULL && temp->task != task) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return;
    }

    prev->next = temp->next;
    free(temp);
}
