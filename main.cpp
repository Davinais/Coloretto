#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;

class Players
{
	public:
      string name;
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
	cout << "Please enter the number of the players:" << endl;
	cin >> player_num;
	Players *player = new Players[player_num];
	for(int i=0; i<player_num; i++)
	{
		cout << "Enter Player " << i+1 << "'s name:";
  cin >> player[i].name;
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
		cards_MAX=77;
		for(int i=0; i<8; i++)
			cards[6*8+3+10+i] = 6; //7 colors when players > 3.
	}
	else
		cards_MAX=68;
	//Shuffle the deck.
	shuffle(cards, cards_MAX);
	for(int i=0; i<cards_MAX; i++)
		cout << cards[i] << endl;
	system("PAUSE");
	return 0;
}
