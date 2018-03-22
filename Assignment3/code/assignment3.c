#include "assignment3.h"

double calcAverageWaitingTime(struct Simulation * S) {
	int packetCount = S->eventQueue.currSize;
//	printf("Number of packets: %d\n", packetCount);
	double sumTime = 0; struct Data tmpD;
	while(S->eventQueue.currSize) {
		tmpD = dequeue(&(S->eventQueue));
		sumTime += tmpD.departureTime - tmpD.arrivalTime;
//		printf("%f\n", tmpD.departureTime - tmpD.arrivalTime);
	}
	return sumTime/packetCount;
}

struct Simulation initSimulation(double arrivalRate,
 double serviceTime, double simTime) {
	struct Simulation sim;
	sim.totalSimTime = simTime;
	sim.arrivalRate = arrivalRate; sim.serviceTime = serviceTime;
	sim.timeForNextArrival = getRandTime(arrivalRate);
	sim.timeForNextDeparture = sim.timeForNextArrival+serviceTime;
	sim.buffer = initQueue(); sim.eventQueue = initQueue();
	sim.e = ARRIVAL; sim.currTime = sim.timeForNextArrival;
	return sim;
}

double runSimulation(double arrivalRate, double serviceTime, double simTime) {
	struct Simulation s = initSimulation(arrivalRate, serviceTime, simTime);
	struct Data newD; double result;
	while(s.currTime < simTime) {
//		printf("time %f\n", s.currTime);
		if(s.e==ARRIVAL) {
			if(s.buffer.currSize==0)
				s.timeForNextDeparture = s.currTime +
				 serviceTime;
			newD.arrivalTime = s.currTime;
//			printf("Arrival: ");
			enqueue(&(s.buffer), newD);
			s.timeForNextArrival = s.currTime +
			  getRandTime(arrivalRate);
		}
		else if(s.e==DEPARTURE) {
//			printf("Departure: ");
			newD=dequeue(&(s.buffer));
			newD.departureTime = s.currTime;
			enqueue(&(s.eventQueue), newD);
			if(s.buffer.currSize)
				s.timeForNextDeparture = s.currTime +
				 serviceTime;
		}
//		printf("%f\n", s.currTime);
		if(s.timeForNextDeparture < s.timeForNextArrival && s.buffer.currSize) {
			s.e = DEPARTURE;
			s.currTime = s.timeForNextDeparture;
//			printf("currTime set for departure: %f\n", s.currTime);
		} else {
			s.e = ARRIVAL;
			s.currTime = s.timeForNextArrival;
//			printf("currTime set for arrival: %f\n", s.currTime);
		}
	}
//	printf("Generating statistics\n");
	result = calcAverageWaitingTime(&s);
//	printf("Freeing queues\n");
	freeQueue(&(s.buffer));
	freeQueue(&(s.eventQueue));
	return result;
}
