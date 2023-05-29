#include <stdio.h>
#include <time.h>
#include "schedule_rr_p.h"
#include "list.h"
#include "task.h"
#include "cpu.h"
#include <stddef.h>
#include <stdbool.h>

struct node *taskList = NULL;

void swap(struct node *node1, struct node *node2) {
    Task *tempTask = node1->task;
    node1->task = node2->task;
    node2->task = tempTask;
}

void sort(struct node **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    struct node *current = *head;
    struct node *prev = NULL;
    bool swapped;

    do {
        swapped = false;
        current = *head;

        while (current->next != prev) {
            if (current->task->priority < current->next->task->priority) {
                swap(current, current->next);
                swapped = true;
            }
            current = current->next;
        }        
        prev = current;
    } while (swapped);
}

void add(char *name, int priority, int burst) {
    Task *newTask = malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    insert(&taskList, newTask);
}

void schedule() {
    const int timeSlice = 10;  // Time quantum for Round Robin
    struct node *temp = taskList;
    bool allTasksCompleted = false;

    clock_t start_time;

    sort(&taskList);

    start_time = clock();

    while (!allTasksCompleted) {
        allTasksCompleted = true;
        temp = taskList;

        while (temp != NULL) {
            clock_t end_time;
            double total_time;


            if (temp->task->burst > 0) {
                allTasksCompleted = false;

                if (temp->task->burst > timeSlice) {
                    run(temp->task, timeSlice);
                    temp->task->burst -= timeSlice;
                } else {
                    run(temp->task, temp->task->burst);
                    temp->task->burst = 0;
                }

                end_time = clock();

                total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                printf("A tarefa %s iniciou sua execucao em: %f segundos\n", temp->task->name, total_time);
            }

            temp = temp->next;
        }

        sort(&taskList); // Reordena a lista de tarefas com base na prioridade após cada iteração
    }
}




// void insert(struct node **head, Task *task) {
//     struct node *newNode = malloc(sizeof(struct node));
//     newNode->task = task;
//     newNode->next = NULL;

//     if (*head == NULL) {
//         *head = newNode;
//     } else {
//         struct node *current = *head;
//         struct node *prev = NULL;
//         while (current != NULL && current->task->priority <= task->priority) {
//             prev = current;
//             current = current->next;
//         }
//         if (prev == NULL) {
//             newNode->next = *head;
//             *head = newNode;
//         } else {
//             newNode->next = current;
//             prev->next = newNode;
//         }
//     }
// }

// void delete(struct node **head, Task *task) {
//     if (*head == NULL) {
//         return;
//     }

//     struct node *temp = *head;
//     if (temp->task == task) {
//         *head = temp->next;
//         free(temp);
//         return;
//     }

//     struct node *prev = NULL;
//     while (temp != NULL && temp->task != task) {
//         prev = temp;
//         temp = temp->next;
//     }

//     if (temp == NULL) {
//         return;
//     }

//     prev->next = temp->next;
//     free(temp);
// }
