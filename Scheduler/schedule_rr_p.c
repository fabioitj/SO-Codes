#include "schedule_rr_p.h"
#include "list.h"
#include "cpu.h"

struct node *taskList = NULL;

// add a task to the list 
void add(char *name, int priority, int burst) {
    Task *newTask = malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    insert(&taskList, newTask);
}

// invoke the scheduler
void schedule() {
    const int timeSlice = 10;  // Tamanho do quantum para o Round Robin
    struct node *temp = taskList;

    while (temp != NULL) {
        int remainingBurst = temp->task->burst;
        while (remainingBurst > 0) {
            if (remainingBurst > timeSlice) {
                run(temp->task->name, timeSlice);
                remainingBurst -= timeSlice;
            } else {
                run(temp->task->name, remainingBurst);
                remainingBurst = 0;
            }
        }
        temp = temp->next;
    }
}

// insert a task into the list based on Round Robin with Priority criteria
void insert(struct node **head, Task *task) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->task = task;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct node *current = *head;
        struct node *prev = NULL;
        while (current != NULL && current->task->priority <= task->priority) {
            prev = current;
            current = current->next;
        }
        if (prev == NULL) {
            newNode->next = *head;
            *head = newNode;
        } else {
            newNode->next = current;
            prev->next = newNode;
        }
    }
}

// delete a task from the list
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
