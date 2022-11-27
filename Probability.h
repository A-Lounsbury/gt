
#ifndef PROBABILITY_H
#define PROBABILITY_H

class Probability
{
	int player;
	int strat;
	
	int getPlayer() { return player; }
	int getStrat() { return strat; }
	int setPlayer(int p) { player = p; }
	int setStrat(int s) { strat = s; }
}