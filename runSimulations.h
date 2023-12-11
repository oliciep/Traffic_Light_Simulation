int runSimulations(int arrivalRateLeft, int lightPeriodLeft, int arrivalRateRight, int lightPeriodRight);

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