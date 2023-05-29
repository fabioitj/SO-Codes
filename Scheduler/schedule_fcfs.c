#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include "schedule_fcfs.h"
#include "list.h"
#include "task.h"
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
    clock_t start_time;
    struct node *temp = taskList;
    start_time = clock();
    while (temp != NULL) {
        clock_t end_time;
        double total_time;

        run(temp->task, temp->task->burst);

        end_time = clock();

        total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        printf("A tarefa %s iniciou sua execucao em: %f segundos\n", temp->task->name, total_time);

        temp = temp->next;
    }
}

/*
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
*/
