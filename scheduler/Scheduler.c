#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Stores information about a particular job on the system
// Do NOT modify!
typedef struct
{
    int id;              // Unique numeric ID for this job
    int startTime;       // Time the job entered the system
    int totalCycles;     // Total CPU cycles required by this job
    int remainingCycles; // How many cycles remaining before it is done
} Job;

// Node in the doubly linked list
// Do NOT modify!
typedef struct node
{
    Job job;           // Data about this particular job
    struct node *next; // Pointer to the next node in the doubly linked list
    struct node *prev; // Pointer to the prev node in the doubly linked list
} Node;

// Tracks information about the state of the CPU scheduler
// Do NOT modify!
typedef struct
{
    Node *head; // Current head of the linked list
    int time;   // Current time of the simulation
} State;

// Executes one cycle of the CPU scheduling simulation.
// The current job at the head of the linked list gets one cycle of CPU time.
//
// If the current job is done, it should be removed from the list and the function prints:
//   t=A, B done, elapsed C, idle D%\n
//   where A is the current time of the simulation
//         B is the job ID of the completed job
//         C is how many cycles have elapsed since the job was first added (including this cycle)
//         D is the percentage of cycles in which this job was idle (some other job was executing)
//
// The head of the list should be advanced to the next node.
// The current time of the simulation should be advanced by one.
//
// Returns true if a job used the cycle, false if there were no available jobs.
bool executeCycle(State *state)
{
    if (state->head == NULL)
    {
        return false;
    }

    state->head->job.remainingCycles--;
    //job is done
    if (state->head->job.remainingCycles == 0)
    {
        printf("t=%d, %d done, elapsed %d, idle %.2f%%\n", state->time, state->head->job.id, state->time + 1,
               (100 - ((double)state->head->job.totalCycles / (state->time + 1 - state->head->job.startTime)) * 100.00));

        //Delete the node because we dont need it
        state->head->prev->next = state->head->next;
        Node *temp = state->head->prev;
        state->head = state->head->next;
        free(state->head->prev);
        state->head->prev = temp;
    }
    else
        state->head = state->head->next;

    state->time++;
    return true;
}

// Adds a new job to the linked list.
// The job is added as the node before the current head of the list.
// Thus the new job has to wait until all existing jobs get scheduled.
//
// Returns true on succss, false otherwise (e.g. failure to allocate memory).
bool addJob(State *state, int jobID, int jobTime)
{
    Node *new = malloc(sizeof(Node));
    if (new == NULL)
        return false;

    new->job.id = jobID;
    new->job.totalCycles = jobTime;
    new->job.remainingCycles = jobTime;
    new->job.startTime = state->time;
    //there are already nodes there
    if (state->head != NULL)
    {
        new->next = state->head;
        new->prev = state->head->prev;
        state->head->prev->next = new;
        state->head->prev = new;
    }
    //this node is first
    else
    {
        state->head = new;
        state->head->next = state->head;
        state->head->prev = state->head;
    }
    printf("t=%d, added %d\n", state->time, new->job.id);
    return true;
}

// Prints out the jobs currently in the linked list in order of next execution.
// Output format is:
//   t=A, print B:C D:E ...
//   where A is the current time of the simulation
//         B is the ID of the job at the head of the list
//         C is the remaining cycles for the job at the head of the list
//         D is the ID of the next job to be scheduled
//         E is the remaining cycles of the next job to be schedule
//         ... and so on for all jobs in the list
void printJobs(const State *state)
{
    printf("t=%d, print ", state->time);
    if(state->head == NULL)
    {
        printf("\n");
        return;
    }
    printf("%d:%d ", state->head->job.id, state->head->job.remainingCycles);
    for (Node* node = state->head->next; node != state->head; node = node->next)
    {
        printf("%d:%d ", node->job.id, node->job.remainingCycles);
    } printf("\n");
}

// Remove all remaining jobs from the linked list, deallocating the associated memory.
// Also results in the head of the list being changed to NULL.
//
// Returns the number of removed jobs (0 if list is empty).
int freeJobs(State *state)
{
    if (state->head == NULL) { return 0; }
    int count = 0;

    Node* current = state->head;
    while (true)
    {
        if(current->next == current){
            free(current);
            state->head = NULL;
            count++;
            return count;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            current = current->next;
            count++;
        }
    }
}

// Main program that simulates scheduling jobs on a CPU.
// Input is via standard input.
// Input consists of a string command followed by 0 or more integer arguments depending on the command.
// Do NOT modify the main function!
int main(void)
{
    // State struct keeps track of the head of the linked list and the current time of the simulation
    State state;
    state.head = NULL;
    state.time = 0;

    // String literals that are used in the input
    const char *COMMAND_RUN = "run";
    const char *COMMAND_ADD = "add";
    const char *COMMAND_PRINT = "print";

    // Variables used to read in data depending ont he command
    char command[100];
    int cycles = 0;
    int id = 0;
    int jobTime = 0;

    // Used to keep track of how often the CPU was busy or idle
    int busyCycles = 0;
    int idleCycles = 0;

    while (scanf("%99s", command) == 1)
    {
        if (strcmp(command, COMMAND_RUN) == 0)
        {
            // After the run command should come a positive number of cycles to execute
            if ((scanf("%d", &cycles) == 1) && (cycles > 0))
            {
                for (int i = 0; i < cycles; i++)
                {
                    if (executeCycle(&state))
                    {
                        busyCycles++;
                    }
                    else
                    {
                        idleCycles++;
                    }
                }
            }
            else
            {
                printf("Invalid run command\n");
                return 1;
            }
        }
        else if (strcmp(command, COMMAND_ADD) == 0)
        {
            // After the add command should come the process ID and a positive job time
            if ((scanf("%d %d", &id, &jobTime) == 2) && (jobTime > 0))
            {
                if (!addJob(&state, id, jobTime))
                {
                    printf("Failed to add job\n");
                    return 1;
                }
            }
            else
            {
                printf("Invalid add command\n");
                return 1;
            }
        }
        else if (strcmp(command, COMMAND_PRINT) == 0)
        {
            printJobs(&state);
        }
        else
        {
            printf("Unknown command = %s\n", command);
            return 1;
        }
    }

    // Compute how many cycles the CPU was busy
    double utilization = (double)busyCycles / (idleCycles + busyCycles) * 100.0;
    printf("t=%d, end, CPU busy %.2f%%\n", state.time, utilization);

    // Deallocate any remaining jobs in the system
    printf("t=%d, freed %d remaining jobs\n", state.time, freeJobs(&state));

    return 0;
}
