#ifndef CARDS_H_
#define CARDS_H_

enum CardType
{
	Spade,
	Clover,
	Heart,
	Diamond,
	UNDEF_TYPE
};

enum CardRank
{
	UNDEF_RANK = 0,
	Six = 6, Seven = 7, Eight = 8, Nine = 9, Ten = 10,
	Jack = 11, Queen = 12, King = 13, Ace = 14
};

struct Card
{
	CardType cardType = CardType::UNDEF_TYPE;
	CardRank cardRank = CardRank::UNDEF_RANK;
	int points = 0;

	Card() = default;
	Card(CardType type, CardRank rank, int pts) : cardType(type), cardRank(rank), points(pts) {}
};

struct Deck
{
	Card* cards = nullptr;
	int topCardIndex = -1;

	Deck(Card* localCards, int topIndex) : cards(localCards), topCardIndex(topIndex) {}
};

void Shuffle(Deck& deck);
Card* GetRandomCards(Deck& deck, Card *cards, int cardsCount, int neededAmount);
int GetPointSum(const Card *cards, int cardsCount);

void PrintStats(const Card& card);
void PrintStats(const Card *card);

#endif //!CARDS_H_