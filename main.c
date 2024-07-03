#include <stdio.h>
#include <math.h>

#define GConst 6.6743e-11
#define nBodies 5


struct Body {
	double Mass;
	double PosX;
	double PosY;
	double VelX;
	double VelY;
};


double getDistance(struct Body* mainBody, struct Body* otherBody){
	double distX2 = pow(mainBody->PosX-otherBody->PosX,2);
	double distY2 = pow(mainBody->PosY-otherBody->PosY,2);

	return pow(distX2+distY2,0.5);
}

double calculateVdotX(struct Body* mainBody,struct Body* otherBody){
	double xVdot = -(mainBody->PosX - otherBody->PosX) * (GConst * otherBody->Mass) / pow(getDistance(mainBody, otherBody),3);
	return xVdot;
}

double calculateVdotY(struct Body* mainBody,struct Body* otherBody){
	double yVdot = -(mainBody->PosY - otherBody->PosY) * (GConst * otherBody->Mass) / pow(getDistance(mainBody, otherBody),3);
	return yVdot;
}

void updateVeloecity(struct Body* mainBody,struct Body* otherBody) {
	// Update the velocity of the struct Body from the influence of another body->
	mainBody->VelX = mainBody->VelX + calculateVdotX(mainBody, otherBody);
	mainBody->VelY = mainBody->VelY + calculateVdotY(mainBody, otherBody);
	//Run this on with all Other Bodies to Get resultant force->
}

void updatePosition(struct Body* mainBody, double timeStep) {
	mainBody->PosX += mainBody->VelX * timeStep;
	mainBody->PosY += mainBody->VelY * timeStep;
}

int main() {
	double timeStep = 1.0;

	int numberOfTimeSteps = 365 * 60 * 60 * 24;
	int checkInTime = 60 * 60 * 24;

	struct Body Sun = {2e30, 0., 0., 0., 0.};
	struct Body Mercury = {3.3e23, 0, 57e9, 47.3e3, 0};
	struct Body Venus = {4.8e24, 0, 108e9, 35e3, 0};
	struct Body Earth = {6e24, 0, -150e9, -29782, 0};
	struct Body Mars = {6.4e23, 0, 227e9, 24e3, 0};

	struct Body allBodies[nBodies] = {Sun,Mercury,Venus,Earth,Mars};
	printf("Starting Loop \n");

	for(int nT = 0; nT < numberOfTimeSteps; nT++ ){
		for(int i = 0; i < nBodies; i++ ){
			for(int j = 0; j < nBodies; j++ ){
				if(i == j){
					continue;
				} else {
					updateVeloecity(&allBodies[i], &allBodies[j]);
				}
			}
			updatePosition(&allBodies[i], 1.0);
		}
		if(nT%checkInTime == 0 ){
			printf("Time Passed : %f days \n",timeStep*nT/checkInTime);
		}

	}
return 1;
}
