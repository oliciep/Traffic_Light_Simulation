#include "runOneSimulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

/* Data structure for the vehicle, includes iterationGenerated for calculating statistics. */
struct vehicle {
    int iterationGenerated;
};

/* Data structure for nodes in the queue, with pointers to the vehicle structure and the next node in the queue. */
struct node {
    struct vehicle *vehicle;
    struct node *next;
};

/* Data structure for the queue, contains pointers to the front and back node of the queue. */
struct queue {
    struct node *front, *back;
};

struct queueInfo {
    int leftNoOfCars;
    int leftTotalIterations;
    int leftMaxIteration;
    int rightNoOfCars;
    int rightTotalIterations;
    int rightMaxIteration;
    int leftClearanceTime;
    int rightClearanceTime;
};

/*/ Data structure for the lights, contains the lightPeriod (amount of time light is green), lightStatus (current colour
 of light). */
struct lights {
    int lightPeriod, lightStatus;
};

/* Function to create the queues for each direction. */
struct queue* createQueue() {
    struct queue* newQueue = (struct queue*)malloc(sizeof(struct queue));
    newQueue -> front = newQueue -> back = NULL;
    return newQueue;
}

/* Function to create a new node pointing at a new vehicle for the queue. */
struct node* newNode(int i) {
    struct node* tempNode = (struct node*)malloc(sizeof(struct node));
    struct vehicle* tempVehicle = (struct vehicle*)malloc(sizeof(struct vehicle));
    tempVehicle -> iterationGenerated = i;
    tempNode -> vehicle = tempVehicle;
    tempNode -> next = NULL;
    return tempNode;
}

/* Function calling newNode() that creates a new node, and then points the node to the next node in the queue. */
void addQueue(struct queue* q, int i) {
    struct node* tempNode = newNode(i);
    /* Checks if the queue is empty, and if it is the new node is pointed to as the front and back of the queue. */
    if (q -> back == NULL) {
        q -> front = q -> back = tempNode;
        return;
    }
    q -> back -> next = tempNode;
    q -> back = tempNode;
}

/* Function to remove a node from the front of the queue. */
int removeQueue(struct queue* q, int i) {
    /* If the queue is empty, the function will return nothing. */
    if (q -> front == NULL) {
        return 0;
    }
    struct node* tempNode = q -> front;
    q -> front = q -> front -> next;
    if (q -> front == NULL) {
        q -> back = NULL;
    }
    int iterationsTaken;
    iterationsTaken = i - (tempNode -> vehicle -> iterationGenerated);
    /* Frees the memory allocated to the vehicle and the temporary node. */
    free(tempNode->vehicle);
    free(tempNode);
    return iterationsTaken;
}

int changeLeftLight(struct lights leftLight) {
    if (leftLight.lightStatus == 0) {
        /*printf("Lights have changed to green for the left side, with a time period of %d\n", leftLight.lightPeriod); */
        return 1;
    }
    return 0;
}

int changeRightLight(struct lights rightLight) {
    if (rightLight.lightStatus == 0) {
        /*printf("Lights have changed to green for the right side, with a time period of %d\n", rightLight.lightPeriod); */
        return 1;
    }
    return 0;
}

/* Finds the light period for the light which is currently green. */
int findLightPeriod(struct lights leftLight, struct lights rightLight) {
    if (leftLight.lightStatus == 1) {
        return leftLight.lightPeriod;
    }
    return rightLight.lightPeriod;
}

/* Function that facilitates main traffic management. */
struct queueInfo moveTraffic(int arrivalRateLeft, int arrivalRateRight, struct lights leftLight, struct queue* leftQueue, struct queue* rightQueue, struct queueInfo qInfo, int i) {
    /*printf("Traffic moves: "); */
    /* Checks if arrivalRateLeft probability is higher than the random number chosen. */
    if (i < 500) {
        if ((rand() % 100) < arrivalRateLeft) {
            addQueue(leftQueue, i);
            qInfo.leftNoOfCars += 1;
        }
        if ((rand() % 100) < arrivalRateRight) {
            addQueue(rightQueue, i);
            qInfo.rightNoOfCars += 1;
        }
    }
    int iterationsTaken;
    if (leftLight.lightStatus == 1) { /* If left light is green. */
        /*printf("Car has passed through from left to right.\n"); */
        iterationsTaken = removeQueue(leftQueue, i);
        qInfo.leftTotalIterations += iterationsTaken;
        if (iterationsTaken > qInfo.leftMaxIteration) {
            qInfo.leftMaxIteration = iterationsTaken;
        }
        if (i > 500 && iterationsTaken != 0) {
            qInfo.leftClearanceTime += 1;
        }
    } else { /* If right light is green. */
        /* printf("Car has passed through from right to left.\n"); */
        iterationsTaken = removeQueue(rightQueue, i);
        qInfo.rightTotalIterations = qInfo.rightTotalIterations + iterationsTaken;
        if (iterationsTaken > qInfo.rightMaxIteration) {
            qInfo.rightMaxIteration = iterationsTaken;
        }
        if (i > 500 && iterationsTaken != 0) {
            qInfo.rightClearanceTime += 1;
        }
    }
    return qInfo;
}

/* Main simulation function for the program. */
struct queueInfo runOneSimulation(int arrivalRateLeft, int lightPeriodLeft, int arrivalRateRight, int lightPeriodRight) {
    int i = 0;
    int j;
    int currentLightPeriod;
    struct lights leftLight = {lightPeriodLeft,1};
    struct lights rightLight = {lightPeriodRight,0};
    struct queue *leftQueue = createQueue();
    struct queue *rightQueue = createQueue();
    struct queueInfo qInfo;
    qInfo.leftTotalIterations = 0;
    qInfo.rightTotalIterations = 0;
    qInfo.leftMaxIteration = 0;
    qInfo.rightMaxIteration = 0;
    qInfo.leftNoOfCars = 0;
    qInfo.rightNoOfCars = 0;
    qInfo.leftClearanceTime = 0;
    qInfo.rightClearanceTime = 0;
    srand((unsigned int) time(NULL));
    while (leftQueue -> front != NULL || rightQueue -> front != NULL || i < 500){
        currentLightPeriod = findLightPeriod(leftLight, rightLight);
        for (j = 0; j < currentLightPeriod; ++j) {
            qInfo = moveTraffic(arrivalRateLeft, arrivalRateRight, leftLight, leftQueue, rightQueue, qInfo, i);
            i += 1;
        }
        leftLight.lightStatus = changeLeftLight(leftLight);
        rightLight.lightStatus = changeRightLight(rightLight);
        i += 1;
        if (i > 5000) {
           break;
        }
    }
    return qInfo;
}
