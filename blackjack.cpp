//
// Created by Brendan Furtado on 2/29/20.
//
#include "blackjack.h"

//Helper toString function for suits (used in displayCard function)
std::string toString(Type types){
    switch (types){
        case Type::CLUBS: return "C";
        case Type::DIAMONDS: return "D";
        case Type::HEARTS: return "H";
        case Type::SPADES: return "S";
        default:
            return "";
    }
}

//Helper toString function for ranks (used in displayCard function)
std::string toString(Rank ranks){
    switch (ranks){
        case Rank::ACE: return "1";
        case Rank::JACK: return "J";
        case Rank::QUEEN: return "Q";
        case Rank::KING: return "K";
        case Rank::TWO: return "2";
        case Rank::THREE: return "3";
        case Rank::FOUR: return "4";
        case Rank::FIVE: return "5";
        case Rank::SIX: return "6";
        case Rank::SEVEN: return "7";
        case Rank::EIGHT: return "8";
        case Rank::NINE: return "9";
        case Rank::TEN: return "10";
        default:
            return "";
    }
}

//-----------Card Class implementation-----------//

Card::Card(Rank rank, Type type){
    this->rank = rank;
    this->type= type;
}

Rank Card::getValue() {return this->rank;}
Type Card::getType() {return this->type;}

void Card::displayCard() {

    string type = toString(this->getType());
    string num = toString(this->getValue());

    cout << num << "" <<type << " ";
}


//-----------Hand Class implementation-----------//

//Constructor to instantiate hand object with empty vector
Hand::Hand() {
    vector<Card> h;
    this->hand = h;
}

void Hand::add(Card c) {
    this->hand.push_back(c);
}

void Hand::clear(){
    this->hand.clear();
}

//Calculate the total value of a player's hand
int Hand::getTotal() const {
    int totalValue = 0;
    int aces = 0; //Counter for the aces

    //Use switch cases on rank to get the total of the player's hand
    for(Card c : this->hand){
        switch(c.getValue()){
            case Rank::TWO: totalValue += 2; break;
            case Rank::THREE: totalValue += 3; break;
            case Rank::FOUR: totalValue += 4; break;
            case Rank::FIVE: totalValue += 5; break;
            case Rank::SIX: totalValue += 6; break;
            case Rank::SEVEN: totalValue += 7; break;
            case Rank::EIGHT: totalValue += 8; break;
            case Rank::NINE: totalValue += 9; break;
            case Rank::TEN: totalValue += 10; break;
            case Rank::JACK: totalValue += 10; break;
            case Rank::KING: totalValue += 10; break;
            case Rank::QUEEN: totalValue += 10; break;
            case Rank::ACE: aces += 1; break;
        }
    }

    //Iterate through aces
    for(int i = 0; i < aces; i++ ){
        if(totalValue > 10){ //Any value greater than 10, the ace will be 1
            totalValue += 1;
        }
        else{totalValue += 11;} //Any value less than or equal to ten, the ace will be 11
    }
    return totalValue;

}

void Hand::displayHand(){
    vector<Card> temp;
    while(!this->hand.empty()){
        Card c = this->hand.back();
        temp.push_back(c);
        this->hand.pop_back();
        c.displayCard();
    }
    this->hand = temp;
}


vector<Card> Hand::getHand() {return this->hand;}

//-----------Deck Class implementation-----------//

//Constructor
Deck::Deck(){
    vector<Card> deck;
    this->deck = deck;
}

void Deck::populate() {

    //Iterate through the type and rank enumerators and push the card
    //Should get 4 cards for each rank
    for(int i = static_cast<int>(Type::CLUBS); i < 4; ++i){
        for(int j = static_cast<int>(Rank::ACE); j < 13; ++j){
            Type suit = static_cast<Type>(i);
            Rank value = static_cast<Rank>(j);
            deck.push_back(Card(value,suit));
        }
    }
}

void Deck::shuffle() {
    std::shuffle(std::begin(this->deck), std::end(this->deck),     std::random_device());
}

Hand Deck::deal(Hand h) {
    Card c = this->deck.back(); //Take the back card
    this->deck.pop_back(); //Remove the back card
    h.add(c);
    return h;
}

//Helper methods for Deck
int Deck::getSize() {return this->deck.size();}

void Deck::printDeck() {
    for(int i = 0; i < this->deck.size(); i++){
        Card c = deck[i];
        c.displayCard();
    }
}

//-----------AbstractPlayer Class implementation-----------//

AbstractPlayer::AbstractPlayer(){}
AbstractPlayer::~AbstractPlayer() {}
bool AbstractPlayer::isDrawing() const {return 0;}
bool AbstractPlayer::isBusted() {return this->hand.getTotal() > 21;}


//-----------HumanPlayer Class implementation-----------//

HumanPlayer::HumanPlayer(){
    Hand h;
    this->hand = h;
}
HumanPlayer::~HumanPlayer(){}

bool HumanPlayer::isDrawing() const{
    string startInput;
    cout << "Do you want to draw? (y/n):";

    while(true) {
        cin >> startInput;

        if (startInput.compare("n") == 0) {
            return false;
        }
        else if (startInput.compare("y") != 0 && startInput.compare("n") != 0){
            cout << "Invalid input, type 'y' to play or 'n' to quit" << endl;
        }
        else{
            break;
        }
    }
    return true;
}

void HumanPlayer::announce(Hand h2) {
    if(this->hand.getTotal() > h2.getTotal() && this->hand.getTotal() <= 21){
        cout << "Player wins." << "\n";
    }
    else if (this->hand.getTotal() == h2.getTotal()){
        cout << "Push: No one wins." << "\n";
    }
    else{
        if(this->hand.getTotal() > 21){
            cout << "Player Busts." << "\n";
            cout << "Casino Wins." << "\n";

        }
        else {
            if(h2.getTotal() > 21){ //Casino busts
                cout << "Player Wins." << "\n";
            }
            else {
                cout << "Player Loses." << "\n";
            }
        }

    }
}

//-----------ComputerPlayer Class implementation-----------//

ComputerPlayer::ComputerPlayer(){
    Hand h;
    this->hand = h;
}
ComputerPlayer::~ComputerPlayer(){}

bool ComputerPlayer::isDrawing() const{
    return this->hand.getTotal() <= 16;
}

//-----------BlackJack Class implementation-----------//
BlackJackGame::BlackJackGame(){
    Deck m_deck;
    ComputerPlayer m_casino;

    this->m_deck = m_deck;
    this->m_casino= m_casino;
}

//Play function for the main game
void BlackJackGame::play() {

    //Populate and shffulethe deck
    m_deck.populate();
    m_deck.shuffle();

    //Instantiate human player
    HumanPlayer player;

    //Deal the two initial cards to the player and one card to the computer
    player.hand = m_deck.deal(player.hand);
    player.hand = m_deck.deal(player.hand);

    m_casino.hand = m_deck.deal(m_casino.hand);

    cout << "Casino: ";
    m_casino.hand.displayHand();
    cout << "[" << m_casino.hand.getTotal() << "]\n";

    cout << "Player: ";
    player.hand.displayHand();
    cout << "[" << player.hand.getTotal() << "]\n";


    //Enter main hit loop
    while(player.isDrawing()){
        //Player wants to continue, Deal a card to the player
        player.hand = m_deck.deal(player.hand);

        //Display new hand
        cout << "Player: ";
        player.hand.displayHand();
        cout << "[" << player.hand.getTotal() << "]\n";

        if(player.isBusted()){
            break;
        }
    }

    while(m_casino.isDrawing() && !(player.isBusted())){
        //Deal card to casino
        m_casino.hand = m_deck.deal(m_casino.hand);

        cout << "Casino: ";
        m_casino.hand.displayHand();
        cout << "[" << m_casino.hand.getTotal() << "]\n";

        //Check if casino busted
        if(m_casino.isBusted()){
            break;
        }
    }

    player.announce(m_casino.hand); //Display winner

    player.hand.clear();
    m_casino.hand.clear();

    Deck d;
    m_deck = d;

}
