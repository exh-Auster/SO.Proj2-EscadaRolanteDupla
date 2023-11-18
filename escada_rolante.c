#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int t;
    int d;
} rider;

void readData(char* filePath, rider* riders, int* n) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", filePath);
        return;
    }
    
    fscanf(file, "%d", n);
    for (int i = 0; i < *n; i++) {
        fscanf(file, "%d %d", &riders[i].t, &riders[i].d);
    }
    fclose(file);
}

int escalator(rider* riders, int n) {
    rider currentRider = riders[0];
    
    int mainIndex = 0;
    int auxIndex = 0;

    int estArrival;

    rider pendingRiders[10000];
    int remainingRiders = n;

    int lastMoment = 0;
    int direction = -1;
    int moment = 0;
        
    bool pending = false;

    while (remainingRiders > 0) {
        printf("DEBUG:\n mainIndex: %d\n auxIndex: %d\n riders[mainIndex].t: %d\n estArrival: %d\n remainingRiders: %d\n pending: %d\n direction: %d\n moment: %d\n\n", mainIndex, auxIndex, riders[mainIndex].t, estArrival, remainingRiders, pending, direction, moment);
        //if (pending && (pendingRiders[0].d == direction || direction == -1)) {
        if (pending && (riders[mainIndex].t > estArrival || remainingRiders == 1)) {
            currentRider = pendingRiders[0];
            moment += 10;
            direction = currentRider.d;
            estArrival = moment + 10;
            remainingRiders--;
            pending = false;
        } else {
            currentRider = riders[mainIndex];
            //moment = currentRider.t > moment ? currentRider.t : moment;

            if (direction == -1) {
                moment = currentRider.t;
                direction = currentRider.d;
                estArrival = currentRider.t + 10;

                mainIndex++;
                remainingRiders--;
            } else if (direction == currentRider.d) {
                moment = currentRider.t;
                estArrival = currentRider.t + 10;

                mainIndex++;
                remainingRiders--;
            } else {
                if (riders[mainIndex + 1].t == 0 || riders[mainIndex + 1].t > estArrival) {
                    direction = -1;
                } else {
                    pendingRiders[0] = riders[mainIndex];
                    pending = true;
                    mainIndex++;
                }
            }
        }
    }

    moment += 10;
    lastMoment = moment;
    return lastMoment;
}

int main() {
    rider riders[10000];
    int n;

    readData("./entrada.txt", riders, &n);
    int lastMoment = escalator(riders, n);

    printf("O último momento em que a escada para é %d\n", lastMoment);
    return 0;
}