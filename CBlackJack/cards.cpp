#include "cards.h"
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <cstdlib>

void Shuffle(Deck& deck)
{
	std::random_device rand;
	std::mt19937 gen(rand());

	std::vector<Card> localCards;
	localCards.reserve(deck.topCardIndex + 1);

	for (int i = 0; i <= deck.topCardIndex; i++)
	{
		localCards.push_back(deck.cards[i]);
	}

	shuffle(localCards.begin(), localCards.end(), gen);
	copy(localCards.begin(), localCards.end(), deck.cards);
}

Card* GetRandomCards(Deck& deck, Card *cards, int cardsCount, int neededAmount)
{
	std::random_device rand;
	std::mt19937 gen(rand());

	int* randomValues = new int[cardsCount];
	for (int i = 0; i < cardsCount; i++) { randomValues[i] = i; }
	shuffle(randomValues, randomValues + cardsCount, gen);

	Card* cardSelection = (Card*)malloc(sizeof(Card) * neededAmount);
	if (cardSelection == NULL)
	{
		delete[] randomValues;
		return NULL;
	}

	for (int i = 0; i < neededAmount; i++) { cardSelection[i] = cards[randomValues[i]]; }
	std::sort(randomValues, randomValues + neededAmount, std::greater<int>());
	for (int i = 0; i < neededAmount; i++)
	{
		int k = randomValues[i];
		for (int j = k; j < cardsCount - 1; j++)
		{
			deck.cards[j] = deck.cards[j + 1];
		}
	}

	Card* temp = (Card*)realloc(cards, sizeof(Card) * (cardsCount - neededAmount));
	if (temp == NULL)
	{
		free(cardSelection);
		delete[] randomValues;
		return NULL;
	}
	deck.cards = temp;
	deck.topCardIndex -= neededAmount;

	delete[] randomValues;
	return cardSelection;
}

int GetPointSum(const Card* cards, int cardsCount)
{
	int counter = 0;
	for (int i = 0; i < cardsCount; i++)
	{
		counter += cards[i].points;
	}
	return counter;
}

void PrintStats(const Card& card)
{
	std::cout << "Type: " << card.cardType << "\nRank: " << card.cardRank << "Points: " << card.points << std::endl;
}

void PrintStats(const Card* card)
{
	std::cout << "Type: " << card->cardType << "\nRank: " << card->cardRank << "Points: " << card->points << std::endl;
}