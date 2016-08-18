#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;

class Players
{
	public:
		string name;
		void AddHands(int color){hands[color]++;};
	private:
		int hands[7];
};
void shuffle(int *cards, int cards_MAX)
{
	cards_MAX-=1;
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
int main()
{
	int player_num,cards[77], cards_MAX;
	//0=Orange, 1=Yellow, 2=Pink, 3=Gray, 4=Green, 5=Brown, 6=Blue, 7=Rainbow, 8=+2Card, 10=End Card
	string colors[7]={"Orange", "Yellow", "Pink", "Gray", "Green", "Brown", "Blue"};
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
	cout << cards_MAX << endl;
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

	bool GameEnd = false;
	/*do
	{
		int *lamp = new int[player_num];
		bool TurnEnd = false;
		do
		{
			for(int i=0; i<player_num; i++)
			{
				
			}
		}while(TurnEnd);
	}while(GameEnd);*/
	system("PAUSE");
	return 0;
}
