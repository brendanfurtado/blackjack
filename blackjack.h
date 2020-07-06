//
// Created by Brendan Furtado on 2/29/20.
//

#ifndef ASSIGNMENT2_BLACKJACK_H
#define ASSIGNMENT2_BLACKJACK_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

//Declaring rank and type enums
enum class Rank{ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
    EIGHT, NINE, TEN, JACK, QUEEN, KING};

enum class Type{CLUBS, DIAMONDS, HEARTS, SPADES};


//Class Card
class Card {

public:

    Card(Rank rank, Type type);

    Rank getValue();
    Type getType();
    void displayCard();

private:
    Rank rank;
    Type type;
};

//Class Hand
class Hand {

public:

    Hand(); //Constructor takes no arguments and just initializes vector hand to empty
    void add(Card c);
    void clear();
    int getTotal() const;

    //Helper methods
    vector<Card> getHand();
    void displayHand();

protected:
    vector<Card> hand;

};

//Class Deck
class Deck{

public:

    Deck();
    void populate();
    void shuffle();
    Hand deal(Hand h);

    //Helper functions
    int getSize();
    void printDeck();


protected:
    vector<Card> deck;
};

//Abstract Class AbstractPlayer
class AbstractPlayer{

public:
    AbstractPlayer();
    virtual ~AbstractPlayer();
    virtual bool isDrawing() const = 0;
    bool isBusted();
    Hand hand;
};

class HumanPlayer : public AbstractPlayer {

public:

    HumanPlayer();
    virtual ~HumanPlayer();

    bool isDrawing() const;
    void announce(Hand h2);

};

class ComputerPlayer : public AbstractPlayer {

public:
    ComputerPlayer();
    virtual ~ComputerPlayer();
    bool isDrawing() const;
};

class BlackJackGame {

public:
    BlackJackGame();
    void play();
    Deck m_deck;
    ComputerPlayer m_casino;
};



#endif //ASSIGNMENT2_BLACKJACK_H
