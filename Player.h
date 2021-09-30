//Grace Jung
//1610447
//Henry Kutlik
//1662812
//Anthony Perez
//1714958
//Lynn Tran
//1585079

#ifndef Player_h
#define Player_h

#include <iostream>
#include <string>
#include "Card.h"
#include "Vector.h"

using namespace std;

class Player
{
private:
  string name;
  Vector<Card> hand;
  int points;
  int roundPoints;
  
  
public:
  
  Player();
  Player(string n, int p);
  void displayHand();
  void addCard(Card c) { hand.pushBack(c); }
  int getSize() { return hand.size(); }
  string getName() { return name; }
  int getPoints() { return points; }
  int getRoundP() { return roundPoints; }
  void addPoints() { points = points + roundPoints; }
  void setRoundPointsZero() { roundPoints = 0; }
  void addRoundPoints (int p) { roundPoints = roundPoints + p; }
  void sortHand() { Card::sortDeck(hand); }
  Card getCard(int i) { return hand[i]; }
  Card playCard(Suit first, bool lead, bool player);
  static void displayInfo(Vector<Player>&,int);
  
};
 
Player::Player()
{
  name = "";
  points = 0;
  roundPoints = 0;
}

Player::Player( string n, int p )
{
  name = n;
  points = p;
  roundPoints = 0;
}

void Player:: displayHand()
{
  for (int i = 0; i < hand.size(); i++)
  {
    cout << i+1 << ": " << hand[i].getDescription() << endl;
  }
}

void Player::displayInfo(Vector<Player>&p, int round)
{
  cout << setw(19) << "Points" << setw(10) << "Points" << endl;
  cout << "Player" << setw(14) << "Round (" << round-1 <<")"<< setw(10) << "Total" << endl;
  cout << "------       ---------    ------" << endl;
  cout << setw(20) << left << p[0].getName() << right << p[0].getRoundP() << setw(10) << p[0].getPoints() << endl;
  cout << setw(20) << left << p[1].getName() << right << p[1].getRoundP() << setw(10) << p[1].getPoints() << endl;
  cout << setw(20) << left << p[2].getName() << right << p[2].getRoundP() << setw(10) << p[2].getPoints() << endl;
  cout << setw(20) << left << p[3].getName() << right << p[3].getRoundP() << setw(10) << p[3].getPoints() << endl;
}

Card Player::playCard(Suit first, bool lead, bool player)
{
  
   // CHOOSING CARD ROBOT/LEADER/PLAYER
  
  bool hasSuit = false, playable = false;
  
  if (lead == true)
  { // leader auto selects 2 of club
    
    for(int i = 0; i < hand.size(); i++)
    {
      if(hand[i].getSuit() == CLUB && hand[i].getNumber() == 2)
      {
        Card temp = hand[i];
        hand[i] = hand.back();
        hand.popBack();
        cout << name << ": " << temp.getDescription() << endl;
        return temp;
      }//If hand[i].getSuit() == CLUB && hand[i].getNumber() == 2
    }//For Loop
    
    if (player == false)
    {
      int choice = rand()%hand.size();
      Card temp = hand[choice];
      hand[choice] = hand.back();
      hand.popBack();
      cout << name << ": " << temp.getDescription() << endl;
      return temp;
    }//If Player == false
    
    else if(player == true)
    { //player card select as leader
      int input;
      
      for(int i = 0; i < hand.size(); i++)
      {
        if(hand[i].getSuit() == first)
        {
          hasSuit = true;
        }//If hand[i].getSuit() == first
      }//For Loop
      
      cout << "Select a card to play: ";
      cin >> input;
      
      while ( (input <= 0)||(input >= hand.size()+1) )
      {
        cout << "You must use a number corresponding to the card: ";
        cin >> input;
      }//While (input <= 0)||(input >= hand.size()+1)
      
      Card temp = hand[input-1];
      hand[input-1] = hand.back();
      hand.popBack();
      sortHand();
      cout << name << ": " << temp.getDescription() << endl;
      return temp;
    }
  } //if lead == true
  
  else if ( lead == false )
  {
    if(player == true)
    { //player card select
      int input;
      for(int i = 0; i < hand.size(); i++)
      {
        if(hand[i].getSuit() == first)
        {
          hasSuit = true;
        }//If hand[i].getSuit() == first
      }//For Loop
      cout << "Select a card to play: ";
      cin >> input;
      while ( (input <= 0)||(input >= hand.size()+1) )
      {
        cout << "You must use a number corresponding to the card: ";
        cin >> input;
      }//While input <= 0)||(input >= hand.size()+1)
      
      while (playable == false)
      {
        if( (hasSuit == true) && (hand[input-1].getSuit() != first) )
        {
          cout << "You need to play a card following suit: ";
          cin >> input;
        }// if hasSuit == true && hand[input-1].getSuit() != first
        else
          playable = true;
      }//While player == false
      Card temp = hand[input-1];
      hand[input-1] = hand.back();
      hand.popBack();
      sortHand();
      cout << name << ": " << temp.getDescription() << endl;
      return temp;
    }// If  player == true
    
    else if(player == false)
    { //Computer player card select
      
      for(int i = 0; i < hand.size(); i++)
      {
        if(hand[i].getSuit() == first)
        {
          hasSuit = true;
        }//If First
        
      }//For Loop
      
      if(hasSuit == true)
      {
        for(int i = 0; i < hand.size(); i++)
        {
          if(hand[i].getSuit() == first)
          {
            Card temp = hand[i];
            hand[i] = hand.back();
            hand.popBack();
            cout << name << ": " << temp.getDescription() << endl;
            return temp;
          }//If first
        }//For Loop
      }//If hasSuit == true
      
      else if(hasSuit == false)
      {
        Card temp = hand[0];
        hand[0] = hand.back();
        hand.popBack();
        cout << name << ": " << temp.getDescription() << endl;
        return temp;
      }//Else-If hasSuit == false
      
    }//Else-If player == false
    
  }//Else
  
  Card fail;
  return fail;
  
}//End Play Card

#endif /* Player_h */
