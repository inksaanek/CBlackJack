#include "game.h"
#include <iostream>
#include <random>
#include <cstdlib>

void PlayerHit(Player& player, Card* cards)
{
	if (!GiveCards(player, cards, GIVE_AMOUNT))
	{
		std::cout << "malloc failed" << std::endl;
	}
	free(cards);
}

void PlayerStand(Player& player, Card* cards)
{
	std::cout << player.name << " skips their turn!" << std::endl;
	free(cards);
}

PlayerActions playerActions[2] = { PlayerHit, PlayerStand };

bool PlayerChoose(Player& player, Deck& deck, int& choice)
{
	int chosenIndex = -1;
	std::cout << "Choose action:\n1. Hit\n2. Stand" << std::endl;
	if (!(std::cin >> chosenIndex))
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "invalid input" << std::endl;
		return false;
	}
	chosenIndex -= 1;

	if (chosenIndex != Actions::Hit && chosenIndex != Actions::Stand)
	{
		std::cout << "invalid action" << std::endl;
		return false;
	}

	Card* localCards = GetRandomCards(deck, deck.cards, deck.topCardIndex + 1, GIVE_AMOUNT);
	if (localCards == NULL)
	{
		return false;
	}

	playerActions[chosenIndex](player, localCards);
	choice = chosenIndex;
	return true;
}

bool DealerChoose(Player& dealer, Deck& deck, int& choice)
{
	if (!CheckIfDealerCanHit(dealer.pointsCount))
	{
		choice = Actions::Stand;
		return true;
	}

	Card* localCards = GetRandomCards(deck, deck.cards, deck.topCardIndex + 1, GIVE_AMOUNT);
	if (localCards == NULL)
	{
		return false;
	}

	bool ok = GiveCards(dealer, localCards, GIVE_AMOUNT);
	free(localCards);
	if (!ok)
	{
		return false;
	}
	return DealerChoose(dealer, deck, choice);
}

RoundResult Cycle(Deck& deck, Player& player, Player& dealer)
{
	
	Card* playerCardSelection = GetRandomCards(deck, deck.cards, deck.topCardIndex + 1, START_GIVE_AMOUNT);
	if (playerCardSelection == NULL)
	{
		
		std::cout << "malloc failed" << std::endl;
		RoundResult r{};
		return r;
	}

	Card* dealerCardSelection = GetRandomCards(deck, deck.cards, deck.topCardIndex + 1, START_GIVE_AMOUNT);
	if (dealerCardSelection == NULL)
	{
		std::cout << "malloc failed" << std::endl;
		free(playerCardSelection);
		RoundResult r{};
		return r;
	}


	if (!GiveCards(player, playerCardSelection, START_GIVE_AMOUNT) || !GiveCards(dealer, dealerCardSelection, START_GIVE_AMOUNT))
	{
		free(playerCardSelection);
		free(dealerCardSelection);
		std::cout << "malloc failed" << std::endl;
		RoundResult r{};
		return r;
	}

	free(playerCardSelection);
	free(dealerCardSelection);

	int playerChoice = -1;
	int dealerChoice = -1;

	std::cout << "Dealer's upcard stats:" << std::endl;
	PrintStats(dealer.cards[0]);

	std::cout << "Ur cards' stats: " << std::endl;
	for (int i = 0; i < player.cardsCount; i++)
	{
		PrintStats(player.cards[i]);
	}

	while (true)
	{
		if (!PlayerChoose(player, deck, playerChoice)) { continue; }
		if (playerChoice == Actions::Stand) { break; }
		if (playerChoice == Actions::Hit && CheckIfPointsOverflow(player.pointsCount)) { break; }
	}

	if (!DealerChoose(dealer, deck, dealerChoice))
	{
		std::cout << "malloc failed" << std::endl;
		RoundResult r{};
		return r;
	}

	bool playerLoss = CheckIfPointsOverflow(player.pointsCount);
	bool dealerLoss = CheckIfPointsOverflow(dealer.pointsCount);
	bool playerBlackjack = CheckIfBlackjack(player);
	bool dealerBlackjack = CheckIfBlackjack(dealer);

	RoundResult r = { playerLoss, dealerLoss, playerBlackjack, dealerBlackjack };
	return r;
}

int PrintRoundResults(Player& player, Player& dealer, RoundResult roundResult)
{
	static int roundCounter = 0;
	roundCounter++;
	std::cout << "\nround " << roundCounter << " results:" << std::endl;

	PrintStats(player);
	PrintStats(dealer);

	if (roundResult.playerLoss && roundResult.dealerLoss) { std::cout << "\nBoth lost! bruh" << std::endl; }
	else if (roundResult.playerLoss) { std::cout << "\nYou lose!" << std::endl; }
	else if (roundResult.dealerLoss) { std::cout << "\nYou win!" << std::endl; }
	else if (roundResult.playerBlackjack && roundResult.dealerBlackjack) { std::cout << "\nBoth got blackjack. Tie!" << std::endl; }
	else if (roundResult.playerBlackjack) { std::cout << "\nYou got blackjack! You win!" << std::endl; }
	else if (roundResult.dealerBlackjack) { std::cout << "\nDealer got blackjack! You lose!" << std::endl; }
	else if (player.pointsCount > dealer.pointsCount) { std::cout << "\nYou got more points! You win!" << std::endl; }
	else if (player.pointsCount < dealer.pointsCount) { std::cout << "\nDealer got more points! You lose!" << std::endl; }
	else { { std::cout << "\nBoth got the same amount of points! Tie!" << std::endl; } }
	return roundCounter;
}