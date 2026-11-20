#include "player.h"
#include <cstdlib>
#include <iostream>
#include <cstring>

Player::Player(char n[MAX_NAME_LENGTH], Card* localCards,
	int cardCount, int pointCount)
	: cards(localCards), cardsCount(cardCount), pointsCount(pointCount)
{
	strncpy_s(name, n, MAX_NAME_LENGTH);
	name[MAX_NAME_LENGTH - 1] = '\0';
}

bool GiveCards(Player& player, const Card* cards, const int cardsCount)
{
	Card* temp = (Card*)realloc(player.cards, sizeof(Card) * (player.cardsCount + cardsCount));
	if (temp == NULL) { return false; }

	player.cards = temp;
	for (int i = 0; i < cardsCount; i++)
	{
		player.cards[i + player.cardsCount] = cards[i];
	}
	player.cardsCount += cardsCount;

	player.pointsCount = 0;
	for (int i = 0; i < player.cardsCount; i++)
	{
		player.pointsCount += player.cards[i].points;
	}
	std::cout << "Gave " << cardsCount << " cards to " << player.name << std::endl;
	return true;
}

void PrintStats(const Player& player)
{
	std::cout << player.name << " stats\n Cards count: " << player.cardsCount << "\nPoints count: " << player.pointsCount << std::endl;
}