#include<iostream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;

class Players
{
	public:
		string name;
		Players();
		void AddHands(int color){hands[color]++;};
		bool CheckValid(){return have_taken;};
		void setTakenStatus(bool value){have_taken = value;};
	private:
		int hands[7];
		bool have_taken;
};
Players::Players()
{
	for(int cnum=0; cnum<7; cnum++)
		hands[cnum] = 0;
	have_taken = false;
}
void shuffle(int *cards, int cards_MAX)
{
	cards_MAX-=1;
	srand((unsigned)time(NULL));
	for(int i=0; i<cards_MAX; i++)
	{
		int random = rand() % cards_MAX;
		int temp = cards[i];
		cards[i] = cards[random];
		cards[random] = temp;
	}
	cards[cards_MAX] = cards[cards_MAX-15];
	cards[cards_MAX-15] = 10;
}
void draw(int *cards, int *nowDraw, string *name, bool *GameEnd)
{
	if(cards[*nowDraw] == 10)
	{
		cout << "You get the End Game Card." << endl
			 << "The game will end when this turn end." << endl
			 << "Since you can't put the End Game Card, draw a card again." << endl;
		*GameEnd = true;
		*nowDraw++;
		draw(cards, nowDraw, name, GameEnd);
	}
	else
		cout << "You get a card: " << setw(8) << name[cards[*nowDraw]] << endl;
}
int main()
{
	int player_num,cards[77], cards_MAX;
	//0=Orange, 1=Yellow, 2=Pink, 3=Gray, 4=Green, 5=Brown, 6=Blue, 7=Rainbow, 8=+2Card, 10=End Card
	string colors[]={"Orange", "Yellow", "Pink", "Gray", "Green", "Brown", "Blue", "Rainbow", "+2 Card"};
	bool color_be_selected[7] = {false, false, false, false, false, false, false};
	cout << "Coloretto!" << endl
		 << "Players: 3 to 5 people" << endl
		 << "Please enter the number of the players:";
	cin >> player_num;
	system("CLS");
	Players *player = new Players[player_num];
	for(int i=0; i<player_num; i++)
	{
		cout << "Enter Player " << i+1 << "'s name:";
		cin >> player[i].name;
		cout << "Please choose the starting color:" << endl;
		for(int j=0; j<((player_num!=3)?7:6); j++)
		{
			if(!color_be_selected[j])
				cout << "<" << j+1 << "> " << colors[j] << endl;
		}
		int choice;
		cin >> choice;
		choice--;
		player[i].AddHands(choice);
		color_be_selected[choice] = true;
	}
	//Initial the deck.
	for(int i=0; i<6; i++)
	{
		for(int j=0; j<8; j++)
			cards[i*8+j] = i;
	}
	for(int i=0; i<3; i++)
		cards[6*8+i] = 7;
	for(int i=0; i<10; i++)
		cards[6*8+3+i] = 8;
	if(player_num != 3)
	{
		cards_MAX=77-player_num;
		for(int i=0; i<8; i++)
			cards[6*8+3+10+i] = 6; //7 colors when players > 3.
	}
	else
		cards_MAX=68-player_num;
	for(int i=0,j=0; i<6; i++)
	{
		if(!color_be_selected[i])
		{
			cards[cards_MAX-1-player_num+j] = i; //Minus end card and the reserve space.
			j++;
		}
	}
	//Shuffle the deck.
	shuffle(cards, cards_MAX);
	/*for(int i=0; i<cards_MAX; i++)
		cout << cards[i] << endl;*/

	int lamp[5][3], nowDraw=0;
	bool GameEnd = false;
	do
	{
		system("CLS");
		int taken_player = 0;
		bool TurnEnd = false, isValidOffLamp[5] = {false, false, false, false, false}, isValidPlaceLamp[5] = {true, true, true, true, true};
		for(int lp=0; lp<5; lp++)
		{
			for(int lk=0; lk<3; lk++)
				lamp[lp][lk]=11; //11:No cards in the lamp.
		}
		if(player_num < 5)
		{
			isValidPlaceLamp[4] = false;
			if(player_num < 4)
				isValidPlaceLamp[3] = false;
		}
		for(int va=0; va<player_num; va++)
			player[va].setTakenStatus(false);
		do
		{
			for(int i=0; i<player_num; i++)
			{
				for(int j=0; j<player_num; j++)
				{
					cout << "Lamp " << j+1 << ": ";
					for(int k=0; k<3; k++)
					{
						if(lamp[j][k] == 12)
						{
							cout << setw(16) << "Be Turned off";
							break;
						}
						if(lamp[j][k] != 11)
							cout << setw(8) << colors[lamp[j][k]] << " ";
					}
					cout << endl << endl;
				}
				if(!player[i].CheckValid())
				{
					cout << "[" << i+1 << ". " << player[i].name << "] Please enter your action:" << endl;
					if(isValidPlaceLamp[0] || isValidPlaceLamp[1] || isValidPlaceLamp[2] || isValidPlaceLamp[3] || isValidPlaceLamp[4])
						cout << "<1> Draw a card." << endl;
					if(isValidOffLamp[0] || isValidOffLamp[1] || isValidOffLamp[2] || isValidOffLamp[3] || isValidOffLamp[4])
						cout << "<2> Turn off a lamp." << endl;
					int action;
					cin >> action;
					if(action == 1)
					{
						draw(cards, &nowDraw, colors, &GameEnd);
						cout << "Please choose a lamp to place the card:" << endl;
						for(int lnum=0; lnum<player_num; lnum++)
						{
							if(isValidPlaceLamp[lnum])
								cout << "<" << lnum+1 << "> Lamp " << lnum+1 << endl;
						}
						int lampChoice;
						cin >> lampChoice;
						lampChoice--;
						for(int roll=0; roll<3; roll++)
						{
							if(lamp[lampChoice][roll] == 11)
							{
								lamp[lampChoice][roll] = cards[nowDraw];
								if(roll == 2)
									isValidPlaceLamp[lampChoice] = false;
								break;
							}
						}
						isValidOffLamp[lampChoice] = true;
						nowDraw++;
					}
					else if(action == 2)
					{
						cout << "Please choose a lamp to turn off:" << endl;
						for(int lnum=0; lnum<player_num; lnum++)
						{
							if(isValidOffLamp[lnum])
								cout << "<" << lnum+1 << "> Lamp " << lnum+1 << endl;
						}
						int lampChoice;
						cin >> lampChoice;
						lampChoice--;
						for(int roll=0; roll<3; roll++)
						{
							if(lamp[lampChoice][roll] != 11)
								player[i].AddHands(lamp[lampChoice][roll]);
							lamp[lampChoice][roll] = 12;
						}
						player[i].setTakenStatus(true);
						isValidPlaceLamp[lampChoice] = false;
						isValidOffLamp[lampChoice] = false;
						taken_player++;
					}
				}
				else
				{
					cout << "[" << i+1 << ". " << player[i].name << "] Since you have turn off the lamp, pass." << endl;
					system("PAUSE");
				}
				if(taken_player == player_num)
				{
					cout << "All of the lamp are off, start a new turn." << endl;
					TurnEnd = true;
					system("PAUSE");
					break;
				}
				//system("PAUSE");
				system("CLS");
			}
		}while(!TurnEnd);
	}while(!GameEnd);
	system("PAUSE");
	return 0;
}
