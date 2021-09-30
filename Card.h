//Grace Jung
//1610447
//Henry Kutlik
//1662812
//Anthony Perez
//1714958
//Lynn Tran
//1585079

#ifndef Card_h
#define Card_h

#include "Vector.h"

using namespace std;
enum Suit {CLUB, DIAMOND, HEART, SPADE};

class Card
{
  
  static int count; //cardID counter
  int cardID;
  int number;
  Suit suit;
  string description;
  
public:
  
  Card();
  Card (int n, Suit s);
  
  int getID() { return cardID;  }
  int getNumber() { return number; }
  Suit getSuit() { return suit; }
  string getDescription() { return description; }
  static void incrementCount()  { count++; }
  void setDesciption();
  bool operator < (const Card& x);
  
 static void displayDeck(Vector<Card>& x);
 static void shuffleDeck(Vector<Card>& deck);
 static void sortDeck(Vector<Card>& deck);
};

Card::Card()
  {
    number = 1;
    suit = (Suit)0;
    setDesciption();
  }

Card::Card( int n, Suit s )
{
  number = n;
  suit = s;
  setDesciption();
  incrementCount();
  cardID = count;
}

void Card::setDesciption()
{
  if (number == 1)
    description = "Ace of ";
  else if (number == 11)
      description = "Jack of ";
  else if (number == 12)
        description = "Queen of ";
  else if (number == 13)
    description = "King of ";
  else
    description = to_string(number) + " ";
            
    if (suit == CLUB)
      description += "Clubs";
    else if (suit == DIAMOND)
      description += "Diamonds";
    else if (suit == HEART)
      description += "Hearts";
    else if (suit == SPADE)
      description += "Spades";
  }

bool Card:: operator < (const Card& x)
{
  if (suit < x.suit)
    return true;
  else if ((suit == x.suit) && (x.number == 1))
    return true;
  else if ((suit == x.suit) && (number == 1))
    return false;
  else if ((suit == x.suit) && (number < x.number))
    return true;
  else
    return false;
}

void Card::displayDeck(Vector<Card>& x)
{
  int count = 0; //Displaying Deck
  for (int i = 0; i < 13; i++){
    int j = 0;
    while (j < 4){
      cout << setw(20) << left << x[count++].getDescription();
      j++;
    }
    cout << endl;
  }
}

void Card::shuffleDeck(Vector<Card>& deck)
{
  int ranNum1, ranNum2;
  Card temp1;
  
  for (int i = 0; i < 1000; i++){ //Shuffling Deck
    ranNum1 = rand() %52;
    ranNum2 = rand() %52;
    temp1 = deck[ranNum1];
    deck[ranNum1] = deck[ranNum2];
    deck[ranNum2] = temp1;
  }
}

void Card::sortDeck(Vector<Card>& deck)
{
  
  Card largest;
  int index;
  Card temp;
  for(int i = 0; i < deck.size(); i++)
  {
    largest = deck[i];
    index = i;
    for(int j = i+1; j < deck.size(); j++)
    {
      if(largest < deck[j])
      {
        largest = deck[j];
        index = j;
      }
    }
    temp = deck[i];
    deck[i] = deck[index];
    deck[index] = temp;
  }
}

#endif /* Card_h */

