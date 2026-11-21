#ifndef PLAYER_H_
#define PLAYER_H_

#include "cards.h"
#include "globals.h"
#include <cstring>

struct Player
{
	Card* cards = nullptr;
	int cardsCount = 0;
	int pointsCount = 0;
	char name[MAX_NAME_LENGTH]{};

	Player(Card* localCards, int cardCount, int pointCount, char n[MAX_NAME_LENGTH]);

};

bool GiveCards(Player& player, const Card *cards, const int cardsCount);

inline bool CheckIfPointsOverflow(int pointsCount)
{
	return pointsCount > MAX_POINTS;
}

inline bool CheckIfDealerCanHit(int pointsCount)
{
	return pointsCount < HIT;
}

inline bool CheckIfBlackjack(const Player& player)
{
	return player.cardsCount == 2 && player.pointsCount == MAX_POINTS;
}

void PrintStats(const Player& player);
#endif //!PLAYER_H_
