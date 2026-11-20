#ifndef GAME_H_
#define GAME_H_

#include "player.h"

enum Actions { Hit = 0, Stand = 1 };

struct RoundResult
{
	bool playerLoss = false;
	bool dealerLoss = false;
	bool playerBlackjack = false;
	bool dealerBlackjack = false;
};

void PlayerHit(Player& player, Card* cards);
void PlayerStand(Player& player, Card* cards);

typedef void (*PlayerActions)(Player& player, Card* cards);
extern PlayerActions playerActions[2];

bool PlayerChoose(Player& player, Deck& deck, int& choice);
bool DealerChoose(Player& dealer, Deck& deck, int& choice);

RoundResult Cycle(Deck& deck, Player& player, Player& dealer);
int PrintRoundResults(Player& player, Player& dealer, RoundResult roundResult);


#endif // !GAME_H_

