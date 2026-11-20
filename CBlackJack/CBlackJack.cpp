#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <cstring>

#include "globals.h"
#include "cards.h"
#include "game.h"
#include "player.h"

using namespace std;

int main()
{
	Card* deckCards = (Card*)malloc(sizeof(Card) * MAX_CARDS);
	Card* playerCards = (Card*)malloc(sizeof(Card) * MAX_CARDS);
	Card* dealerCards = (Card*)malloc(sizeof(Card) * MAX_CARDS);

	if (!deckCards || !playerCards || !dealerCards) { cout << "malloc failed" << endl; return 1; }


	int c = 0;
	for (int t = 0; t < 4; t++)
	{
		CardType cardType = static_cast<CardType>(t);
		for (int r = 6; r <= 14; r++) // 14 - это Ace
		{
			int points = 0;
			if (r >= 10 && r <= 13) { points = 10; } // Jack(11), Queen(12), King(13)
			else if (r == 14) {points = 11;} // Ace
			else { points = r; }

			CardRank cardRank = static_cast<CardRank>(r);
			Card card(cardType, cardRank, points);
			deckCards[c] = card;
			c++;
		}
	}
	Deck deck(deckCards, c - 1);
	

	char playerName[MAX_NAME_LENGTH] = "";
	char dealerName[MAX_NAME_LENGTH] = "Algorithm";
	char buffer[MAX_NAME_LENGTH];
	cout << "Enter yo name: ";
	cin.getline(buffer, MAX_NAME_LENGTH);
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(10000, '\n');
		return 1;
	}
	strncpy_s(playerName, buffer, MAX_NAME_LENGTH);

	
	Player player(playerName, playerCards, 0, 0);
	Player dealer(dealerName, dealerCards, 0, 0);
	Shuffle(deck);

	int lastResult = 0;
	do
	{
		int playerCardsCount = 0;
		int playerPointsCount = 0;
		int dealerCardsCount = 0;
		int dealerPointsCount = 0;

		if (deck.topCardIndex < 10) {
			c = 0;
			for (int t = 0; t < 4; t++)
			{
				CardType cardType = static_cast<CardType>(t);
				for (int r = 6; r <= 14; r++) // 14 - это Ace
				{
					int points = 0;
					if (r >= 10 && r <= 13) { points = 10; } // Jack(11), Queen(12), King(13)
					else if (r == 14) { points = 11; } // Ace
					else { points = r; }

					CardRank cardRank = static_cast<CardRank>(r);
					Card card(cardType, cardRank, points);
					deckCards[c] = card;
					c++;
				}
			}
			deck.topCardIndex = MAX_CARDS - 1;
			Shuffle(deck);
		}

		RoundResult roundResult = Cycle(deck, player, dealer);
		lastResult = PrintRoundResults(player, dealer, roundResult);

		if (lastResult > 0)
		{ 
			int userInput = -1;
			cout << "Play again? 0 - no; 1 - yes" << endl;
			if (!(cin >> userInput)) { cin.clear(); cin.ignore(10000, '\n'); userInput = 0; }
			if (userInput == 0) { break; }
		}
	} while (true);

	free(player.cards);
	free(dealer.cards);
	free(deck.cards);
	return 0;
}
