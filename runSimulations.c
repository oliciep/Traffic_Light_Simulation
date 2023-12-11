#include "runSimulations.h"
#include "runOneSimulation.h"
#include <stdio.h>

/* Code to run the runOneSimulation file */
int runSimulations(int arrivalRateLeft, int lightPeriodLeft, int arrivalRateRight, int lightPeriodRight) {
    int i;
    int leftTotalCars = 0;
    int rightTotalCars = 0;
    int leftTotalIterations = 0;
    int rightTotalIterations = 0;
    int leftTotalMaxIterations = 0;
    int rightTotalMaxIterations = 0;
    int leftTotalClearanceTime = 0;
    int rightTotalClearanceTime = 0;
    for (i = 0; i < 100; ++i) {
        struct queueInfo simInfo = runOneSimulation(arrivalRateLeft, lightPeriodLeft, arrivalRateRight, lightPeriodRight);
        leftTotalCars += simInfo.leftNoOfCars;
        rightTotalCars += simInfo.rightNoOfCars;
        leftTotalIterations += simInfo.leftTotalIterations;
        rightTotalIterations += simInfo.rightTotalIterations;
        leftTotalMaxIterations += simInfo.leftMaxIteration;
        rightTotalMaxIterations += simInfo.rightMaxIteration;
        leftTotalClearanceTime += simInfo.leftClearanceTime;
        rightTotalClearanceTime += simInfo.rightClearanceTime;
    }
    fprintf(stdout,"Parameter values:\n");
    fprintf(stdout,"   from left:\n");
    fprintf(stdout,"      traffic arrival rate: %d\n", arrivalRateLeft);
    fprintf(stdout,"      traffic light period: %d\n", lightPeriodLeft);
    fprintf(stdout,"   from right:\n");
    fprintf(stdout,"      traffic arrival rate: %d\n", arrivalRateRight);
    fprintf(stdout,"      traffic light period: %d\n", lightPeriodRight);
    fprintf(stdout,"Results (averaged over 100 runs):\n");
    fprintf(stdout,"   from left:\n");
    fprintf(stdout,"      number of vehicles: %d\n", leftTotalCars / 100);
    fprintf(stdout,"      average waiting time: %d\n", leftTotalIterations / leftTotalCars);
    fprintf(stdout,"      maximum waiting time: %d\n", leftTotalMaxIterations / 100);
    fprintf(stdout,"      clearance time: %d\n", leftTotalClearanceTime / 100);
    fprintf(stdout,"   from right:\n");
    fprintf(stdout,"      number of vehicles: %d\n", rightTotalCars / 100);
    fprintf(stdout,"      average waiting time: %d\n", rightTotalIterations / rightTotalCars);
    fprintf(stdout,"      maximum waiting time: %d\n", rightTotalMaxIterations / 100);
    fprintf(stdout,"      clearance time: %d\n", rightTotalClearanceTime / 100);
}