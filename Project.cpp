//Grace Jung
//1610447
//Henry Kutlik
//1662812
//Anthony Perez
//1714958
//Lynn Tran
//1585079

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <queue>
#include "Player.h"
#include "Card.h"
#include "Vector.h"
#include "AssociativeArray.h"
#include "PriorityQueue.h"


using namespace std;

#include <ctime>
#include <cctype>
#include <cstdlib>


int Card::count = 0;
int main()
{
  string buf;
  
  while ( true )
  {
    
    cout << endl;
    cout << "What Would You Like To Do?\n";
    cout << "(1)Play Game" << endl;
    cout << "(2)Look At The Lowest Scores" << endl;
    cout << "(3)Know Rules" << endl;
    cout << "(4)Simulate Game" << endl;
    cout << "(N)Clear Saved Scores" << endl;
    cout << "(Q)Quit\n" << endl;
    cout << "Your Coice:";
    cin >> buf;
    
    if ( buf == "q" || buf == "Q")
      break;
    
    if ( buf == "n" || buf == "N")
    {
      buf = "5";
    }
    
    int choice = atoi(buf.c_str());
    
  switch(choice)
    {
    
      case 1:
      {
        srand(time(0));
  
        //Creating Deck
        Vector<Card> gameDeck;
        for (int i = 1; i < 14; i++)
        {
          for (int j = 0; j < 4; j++)
          {
            gameDeck.pushBack( Card (i,(Suit)j)  );
          }
        }
  
        Card::shuffleDeck(gameDeck); // Making sure its shuffled well.
        Card::shuffleDeck(gameDeck);
        
        Vector<Player> p;
        
        p[0] = Player("You", 0);
        p[1] = Player("Oscar", 0);
        p[2] = Player("Nkosi", 0);
        p[3] = Player("Jordan", 0);
  
        for(int i = 0; i < 13; i++) // 13 card per person
          p[0].addCard(gameDeck[i]);
        for(int i = 13; i < 26; i++)
          p[1].addCard(gameDeck[i]);
        for(int i = 26; i < 39; i++)
          p[2].addCard(gameDeck[i]);
        for(int i = 39; i < 52; i++)
          p[3].addCard(gameDeck[i]);
  
        p[0].sortHand();
        p[1].sortHand();
        p[2].sortHand();
        p[3].sortHand();
        
  
        int leader = 1;
        int round = 1;
  
        for (int i = 0; i < 13; i++)
        { //finding who has 2 clubs
          if(p[0].getCard(i).getSuit() == CLUB && p[0].getCard(i).getNumber() == 2)
          {
            leader = 4;
            break;
          }
          if(p[1].getCard(i).getSuit() == CLUB && p[1].getCard(i).getNumber() == 2)
          {
            leader = 5;
            break;
          }
          if(p[2].getCard(i).getSuit() == CLUB && p[2].getCard(i).getNumber() == 2)
          {
            leader = 6;
            break;
          }
          if(p[3].getCard(i).getSuit() == CLUB && p[3].getCard(i).getNumber() == 2)
          {
            leader = 7;
            break;
          }
        }
  
  
        /* START OF 13 ROUND GAME */
        while (round < 14)
        {
          bool isPlayer = false;
          Suit leadingS = CLUB; //default CLUB
          if (leader%4 == 0)
            isPlayer = true;
          
          Player::displayInfo(p, round);
          cout << endl << "My Hand" << endl;
          cout << "-------" << endl;
          p[0].displayHand();
          cout << endl;
          cout << "Round (" << round  << ")"<< endl;
          cout << "---------" << endl;
    
          for (int i = 0; i < 4; i++) //resetting round points
            p[i].setRoundPointsZero();
    
          Vector<Card> temp; //card placement holder
          Vector<int> playerTrack;
    
          /* Making each player choose a card after leader */
          temp.pushBack(p[leader%4].playCard(leadingS, 1, isPlayer));
          leadingS = temp[0].getSuit();
          playerTrack[0] = leader%4;
          leader++;
    
          if (leader%4 == 0)
            isPlayer = true;
          else
            isPlayer = false;
    
          temp.pushBack(p[leader%4].playCard(leadingS, 0, isPlayer));
          playerTrack[1] = leader%4;
          leader++;
    
          if (leader%4 == 0)
            isPlayer = true;
          else
            isPlayer = false;
    
          temp.pushBack(p[leader%4].playCard(leadingS, 0, isPlayer));
          playerTrack[2] = leader%4;
          leader++;
    
          if (leader%4 == 0)
            isPlayer = true;
          else
            isPlayer = false;
    
          temp.pushBack(p[leader%4].playCard(leadingS, 0, isPlayer));
          playerTrack[3] = leader%4;

   
    
          /* Checking who has the winning card and managing points*/
          Card highest = temp[0]; //defaults
          leader = playerTrack[0];
          
          for (int i = 0; i < 4; i++)
          { //who has winning card
            if(temp[i].getSuit() == leadingS)
            {
              if(highest.getNumber() < temp[i].getNumber())
              {
                highest = temp[i];
                leader = playerTrack[i];
              }
            }
          }
    
          int totalPoints = 0; // allocating round points
          for (int i = 0; i < temp.size(); i++)
          {
            if(temp[i].getSuit() == HEART)
              totalPoints++;
            if( (temp[i].getSuit() == SPADE) && (temp[i].getNumber() == 12) )
              totalPoints = totalPoints + 13;
          }
    
          p[leader].addRoundPoints(totalPoints); //giving 'winner' their points
          p[leader].addPoints();
          cout << p[leader].getName() << " wins this round!" << endl << endl;
          leader = leader + 4;
          round++;
        } //End of Game While Loop
  
        cout << endl << endl << "FINAL SCORE" << endl;
        Player::displayInfo(p, round); //showing final score
        int topScore = 0;
        int loser = 0;
        for (int i = 0; i < 4; i++)
        {
          if(topScore < p[i].getPoints())
          {
            topScore = p[i].getPoints();
            loser = i;
          }
        }
        cout << endl << p[loser].getName() << " Lost!" << endl;
        
        //Adds Score to file
        ofstream fout;
        fout.open("Scores.txt",fstream::in|fstream::out|fstream::app);
        if (!fout.good()) throw "I/0 error";
        
        for ( int i = 0; i < 4; i ++ )
        {
          fout << p[i].getName() << "\t" << p[i].getPoints() << endl;
        }
        
        fout.close();
        
        break;
      }//End Case 1
    
      case 2:
      {
      
        AssociativeArray<string, AssociativeArray<int, int> > playerScores;
        queue <string> names;
        Vector < PriorityQueue<int> > person;
        queue <int> personScore;
        
        //for parsing an input file
        char* token;
        char buf[1000];
        const char* const tab = "\t";
        const char* const newL = "\n";
        
        //open input file
        ifstream fin;
        fin.open("Scores.txt");
        if (!fin.good()) throw "I/0 error";
        
        //read the input file
        while (fin.good())
        {
          
          //read the line
          string line;
          getline(fin, line);
          strcpy(buf, line.c_str());
          
          
          //skips blank lines
          if(buf[0] == 0) continue;
          
          
          //parse the line
          const string name(token = strtok(buf, tab));  //Reads file and inuts string into name until \t
          const string score((token = strtok(0, newL))? token : ""); //Reads file and inuts string into score until \n
          
          string mutableScore = score;
          int integerScore = stoi(mutableScore);
          
          playerScores[name][integerScore]++;
        
        }//File Closed
        
        //Puts names into queue array
        names = playerScores.keys();
        string tempName;
        
        cout << left << setw(10) << "Name" << left << setw(3)  << "|" << "Worst Three Scores Per Person" << endl;
        cout << "--------------------------------------" << endl;
        for ( int i = 0; !names.empty(); i++ )
        {
        
          cout <<left << setw(10) << names.front();
          personScore = playerScores[names.front()].keys();
          
          //Organizes Scores through priority queue
          for ( int j = 0; !personScore.empty(); j++ )
          {
            person[i].push ( personScore.front() );
            personScore.pop();
          }
          
          cout << setw(7);
          //Displays Scores
          for ( int j = 0; j < 3; j++)
          {
            cout << left << setw(3) << "|";
            cout << setw(2) << person[i].top() <<  setw(6) << " pts" <<  "( " << playerScores[names.front()][person[i].top()] << " instances of score )"<< endl;
            cout << left << setw(10) << " ";
            person[i].pop();
          }
          cout << endl;
          
          names.pop();
        }
    
        break;
      }//End Case 2
        
      case 3:
      {
        
        string rulesDescription;
        //for parsing an input file
        char* token;
        char buf[1000];
        const char* const newL = "\n";
        
        //open input file
        ifstream fin;
        fin.open("Rules.txt");
        if (!fin.good()) throw "I/0 error";
        
        
        while (fin.good())
        {
          
          //read the line
          string line;
          getline(fin, line);
          strcpy(buf, line.c_str());
          
          //skips blank lines
          if(buf[0] == 0)
            rulesDescription += "\n";
          
          else
          {
            const string sentence (token = strtok(buf, newL));
          
            rulesDescription += sentence + "\n";
          }
  
        }
        
        cout << endl;
        cout << rulesDescription << endl;;
        break;
      }//End Case 3
        
      case 4:
      {
        srand(time(0));
        
        //Creating Deck
        Vector<Card> gameDeck;
        for (int i = 1; i < 14; i++)
        {
          for (int j = 0; j < 4; j++)
          {
            
            gameDeck.pushBack( Card (i,(Suit)j ));
          }
        }
        
        Card::shuffleDeck(gameDeck); // Making sure its shuffled well.
        Card::shuffleDeck(gameDeck);
        
        string yourPlayerName = " ";
        cout << "Enter name of your player: ";
        cin >> yourPlayerName;
        
        Vector<Player> p;
        
        p[0] = Player("You", 0);
        p[1] = Player("Oscar", 0);
        p[2] = Player("Nkosi", 0);
        p[3] = Player("Jordan", 0);

        for(int i = 0; i < 13; i++) // 13 card per person
          p[0].addCard(gameDeck[i]);
        for(int i = 13; i < 26; i++)
          p[1].addCard(gameDeck[i]);
        for(int i = 26; i < 39; i++)
          p[2].addCard(gameDeck[i]);
        for(int i = 39; i < 52; i++)
          p[3].addCard(gameDeck[i]);
        
        p[0].sortHand();
        p[1].sortHand();
        p[2].sortHand();
        p[3].sortHand();
        
        int leader = 1;
        int round = 1;
        
        for (int i = 0; i < 13; i++)
        { //finding who has 2 clubs
          if(p[0].getCard(i).getSuit() == CLUB && p[0].getCard(i).getNumber() == 2)
          {
            leader = 4;
            break;
          }
          if(p[1].getCard(i).getSuit() == CLUB && p[1].getCard(i).getNumber() == 2)
          {
            leader = 5;
            break;
          }
          if(p[2].getCard(i).getSuit() == CLUB && p[2].getCard(i).getNumber() == 2)
          {
            leader = 6;
            break;
          }
          if(p[3].getCard(i).getSuit() == CLUB && p[3].getCard(i).getNumber() == 2)
          {
            leader = 7;
            break;
          }
        }
        
        /* START OF 13 ROUND GAME */
        while (true)
        {
          bool isPlayer = false;
          Suit leadingS = CLUB; //default CLUB
        //  if (leader%4 == 0)
           // isPlayer = true;
          
          cout << "Press Enter to Coninue" << endl;
          cin.get();
          
          cout << endl;
          Player::displayInfo(p, round);
          
         
          for ( int i = 0; i <4; i++)
          {
          cout << endl  << p[i].getName() << " Hand" << endl;
          cout << "---------" << endl;
          p[i].displayHand();
          cout << endl;
          cout << "Round (" << round  << ")"<< endl;
          cout << "------------" << endl;
          }
          
          
          cout << endl;
          cout << "Round (" << round  << ")"<< endl;
          cout << "------------" << endl;
          
          
          for (int i = 0; i < 4; i++) //resetting round points
            p[i].setRoundPointsZero();
          
          Vector<Card> temp; //card placement holder
          Vector<int> playerTrack;
          
          /* Making each player choose a card after leader */
          temp.pushBack(p[leader%4].playCard(leadingS, 1, isPlayer));
          leadingS = temp[0].getSuit();
          playerTrack[0] = leader%4;
          leader++;

          temp.pushBack(p[leader%4].playCard(leadingS, 0, isPlayer));
          playerTrack[1] = leader%4;
          leader++;

          temp.pushBack(p[leader%4].playCard(leadingS, 0, isPlayer));
          playerTrack[2] = leader%4;
          leader++;
          
          temp.pushBack(p[leader%4].playCard(leadingS, 0, isPlayer));
          playerTrack[3] = leader%4;
          
          /* Checking who has the winning card and managing points*/
          Card highest = temp[0]; //defaults
          leader = playerTrack[0];
          
          for (int i = 0; i < 4; i++)
          { //who has winning card
            if(temp[i].getSuit() == leadingS)
            {
              if(highest.getNumber() < temp[i].getNumber())
              {
                highest = temp[i];
                leader = playerTrack[i];
              }
            }
          }
          
          int totalPoints = 0; // allocating round points
          for (int i = 0; i < temp.size(); i++)
          {
            if(temp[i].getSuit() == HEART)
              totalPoints++;
            if( (temp[i].getSuit() == SPADE) && (temp[i].getNumber() == 12) )
              totalPoints = totalPoints + 13;
          }
          
          p[leader].addRoundPoints(totalPoints); //giving 'winner' their points
          p[leader].addPoints();
          cout << p[leader].getName() << " wins this round!" << endl << endl;
          leader = leader + 4;
          round++;
          
          if ( round >= 14)
            break;
          
        } //End of Game While Loop
        
        cout << endl << endl << "FINAL SCORE" << endl;
        Player::displayInfo(p, round); //showing final score
        int topScore = 0;
        int loser = 0;
        for (int i = 0; i < 4; i++)
        {
          if(topScore < p[i].getPoints())
          {
            topScore = p[i].getPoints();
            loser = i;
          }
        }
        cout << endl << p[loser].getName() << " Lost!" << endl;
        
        break;
      }
        
      case 5:
      {
        ofstream fout;
        fout.open("Scores.txt");
        if (!fout.good()) throw "I/0 error";
        fout.close();
        
        cout << "Success! Scores all cleared" << endl;
        break;
      }//End Case 5
        
        
    }//End Switch
    
  }//End While True
}//main end


