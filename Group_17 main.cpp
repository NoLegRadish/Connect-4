#include <bits/stdc++.h>
#include <conio.h>
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 0x0d
using namespace std;
bool gamestatus,enable=false;
bool ailose[7]={false},aiwin[7]={false},aihelp[7]={false};
int spa,turn=0;
char arr[6][7];
string winningname="";

//class that stores player information
class Player{
	friend istream& operator>>(istream&,Player&);
	friend void control();
	private:
		string name;
		char symbol;
	public:
		Player():name(""),symbol(' '){}
		~Player(){name=""; symbol=' ';}
		void checkWin(int,int);
		char getSymbol(){
			return symbol;
		}
		string getName(){
			return name;
		}
};

//operator overloading
istream& operator>>(istream& input,Player& user){
	static int x=1;
	if(x>2) x=2;
	cout<<"Input player "<<x<<"'s name: ";
    input>>user.name;
    cout<<"Input player "<<x<<"'s symbol (one character): ";
    input>>user.symbol;
    input.ignore(numeric_limits<streamsize>::max(),'\n');
    x++;
    return input;
}

//check winning condition
void Player::checkWin(int x,int y){
    int coutx=0,couty=0,couts=0,coutw=0;
	
    int X=x;
    int Y=y;
    if(x==-1) return;
    while(x<6&&coutx!=4){
        if(arr[x][y]==symbol){
            coutx++;
            x++;
		}
        else{
            break;
        }
    }
    x=X;
    coutx--;
    while(x>-1&&coutx!=4){
        if(arr[x][y]==symbol){
            coutx++;
            x--;
        }
        else{
            break;
        }
    }
    x=X;
    while(y<7&&couty!=4){
        if(arr[x][y]==symbol){
            couty++;
            y++;
        }
        else{
            break;
        }
    }
    y=Y;
    couty--;
    while(y>-1&&couty!=4){
        if(arr[x][y]==symbol){
            couty++;
            y--;
        }
        else{
            break;
        }
    }
    y=Y;
    while(x<6&&y<7&&couts!=4){
        if(arr[x][y]==symbol){
            couts++;
            x++;
            y++;
        }
        else{
            break;
        }
    }
    x=X;
    y=Y;
    couts--;
    while(x>-1&&y>-1&&couts!=4){
        if(arr[x][y]==symbol){
            couts++;
            x--;
            y--;
        }
        else{
            break;
        }
    }
    x=X;
    y=Y;
    while(x>-1&&y<7&&coutw!=4){
        if(arr[x][y]==symbol){
            coutw++;
            x--;
            y++;
        }
        else{
            break;
        }
    }
    x=X;
    y=Y;
    coutw--;
    while(x<6&&y>-1&&coutw!=4){
        if(arr[x][y]==symbol){
            coutw++;
            x++;
            y--;
        }
        else{
            break;
        }
    }

    if(coutx==4||couty==4||couts==4||coutw==4){
        gamestatus=false;
        winningname=name;
    }
    
}

//initialize array
void Initialize(){
	for(int i=0;i<6;i++){
		for(int j=0;j<7;j++)
			arr[i][j]=' ';
	}
}

//restart the game
void Restart(Player player[]){
	char willing;
	cout<<"Do you want to restart (Y/N): ";
	cin>>willing;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
	if(willing=='Y'){
		Initialize();
		winningname="";
		gamestatus=true;
		cout<<player[turn%2].getName()<<" first!\n";
		cout<<"Press any key to restart the game...\n";
		if(player[turn%2].getName()=="AI")
		getch();
	}
}

//check if it is full
void checkFull(){
	bool isFull=true;
	for(int h=0;h<7;h++){
		if(arr[0][h]==' ')
			isFull=false;
	}

	if(isFull==true&&winningname==""){
		cout<<"No player wins!\n";
		cout<<"Press any key to continue the game...\n";
		getch();
		gamestatus=false;
	}
}

//AI will lose
void AIplayer1Win(Player player[]){
	for(int u=0;u<7;u++) ailose[u]=false;
	for(int v=0;v<7;v++){
		for(int h=5;h>=0;h--){
		if(arr[h][v]!=' ') 
		continue;
		else{
			arr[h][v]=player[0].getSymbol();
			player[0].checkWin(h,v);
			ailose[v]=(!gamestatus);
			gamestatus=true;
			arr[h][v]=' ';
			winningname="";
			break;
			}
		}
	}
}

//AI can win
void AIcanWin(Player player[]){
	for(int u=0;u<7;u++) aiwin[u]=false;
	for(int v=0;v<7;v++){
		for(int h=5;h>=0;h--){
		if(arr[h][v]!=' ') 
		continue;
		else{
			arr[h][v]=player[1].getSymbol();
			player[1].checkWin(h,v);
			aiwin[v]=(!gamestatus);
			gamestatus=true;
			arr[h][v]=' ';
			winningname="";
			break;
			}
		}
	}
}

//AI help win
void AIhelpWin(Player player[]){
	for(int u=0;u<7;u++) aihelp[u]=false;
	for(int v=0;v<7;v++){
		for(int h=5;h>=0;h--){
		if(arr[h][v]!=' ') 
		continue;
		else{
			if(h-1>=0){
					arr[h-1][v]=player[0].getSymbol();
					player[0].checkWin(h-1,v);
					aihelp[v]=(!gamestatus);
					gamestatus=true;
					arr[h-1][v]=' ';
					winningname="";
					break;
				}	
			}
		}
	}
}

//AI
int AI(Player player[]){
	int y,g;
	int flag=0;
	srand(time(0));
	AIcanWin(player);
	AIplayer1Win(player);
	AIhelpWin(player);
	
	for(int k=0;k<=6;k++){
		if(aiwin[k]==true){ 
		return k;
		} 
	}
	
	for(int l=0;l<=6;l++){
		if(ailose[l]==true){ 
		return l;
		} 
	}

	int nomorestep;
	do{
		flag=0;
		nomorestep=-1;
		g=(rand()%30);
		if(g==0&&aihelp[0]==false) y=0;
		else if (g>=1&&g<=3&&aihelp[1]==false) y=1;
		else if (g>=4&&g<=9&&aihelp[2]==false) y=2;
		else if (g>=10&&g<=19&&aihelp[3]==false) y=3;
		else if (g>=20&&g<=25&&aihelp[4]==false) y=4; 
		else if (g>=26&&g<=28&&aihelp[5]==false) y=5;
		else if (g==29&&aihelp[6]==false) y=6;
		else{
			for(int h=0;h<7;h++){
				if(aihelp[h]==true||arr[0][h]!=' '){
					nomorestep=1;
				} 
				else{
					nomorestep=0;
					break;
				}
			}		
			if(nomorestep==1)
				y=rand()%7;
			else 
				flag=-1;
		}
	}while(arr[0][y]!=' '||flag==-1);
	return y;
}

//get input position from player
int Control(Player player[]){
    int c=0;
    switch(c=getch()) {
    case KEY_LEFT:
    	if(spa<=0) spa=0;
    	else spa--;
    	break;
	case KEY_RIGHT:
    	if(spa>=6) spa=6;
    	else spa++;
        break;
    case KEY_ENTER:
		if(enable==true){
			if(arr[0][spa]!=' '){
				cout<<"This column is Full!\n";
				cout<<"Press any key to continue the game...\n";
				getch();
				break;
			}

			for(int w=5;w>=0;w--){
				if(arr[w][spa]!=' ')
				continue;
				else{
					arr[w][spa]=player[turn%2].getSymbol();
					turn++;
					return w;
					break;
				}
			}
        }
        break;
    default:
        break;
    }
    return -1;
}

//print and check array
void UserUI(Player player[]){
	int x; int y;
	if(player[1].getName()!="AI"||turn%2==0){
		x=Control(player);
		y=spa;
	}
	else if(turn%2==1){
		y=AI(player);
		for(int w=5;w>=0;w--){
			if(arr[w][y]!=' ')
			continue;
			else{
				arr[w][y]=player[1].getSymbol();
				turn++;
				x=w;
				break;
			}
		}
	}
	system("cls");
	cout<<"  ";
	for(int h=0;h<spa;h++){
		cout<<"    ";
	}

	cout<<"Y"<<endl;
	cout<<"  1  ";

	for(int z=2;z<=7;z++){
		cout<<" "<<z<<"  ";
	}

	cout<<endl;
	for(int i=0;i<6;i++){
		for(int k=0;k<13;k++){
			cout<<"-+";
		}
	cout<<"-+-"<<endl;
	cout<<"|";

		for(int g=0;g<7;g++){
			cout<<" "<<arr[i][g]<<" "<<"|";
		}
	cout<<endl;
	}
	for(int k=0;k<13;k++){
		cout<<"-+";
	}
	cout<<"-+-"<<endl;
	cout<<player[turn%2].getName()<<"'s turn."<<endl;
	
	player[(turn-1)%2].checkWin(x,y);
	checkFull();
}

int main(){
	cout<<"---------------------------\n";
	cout<<"| Welcome to Connect Four |\n";
	cout<<"---------------------------\n\n";
	cout<<"Input AI in player 2 to start AI.\n\n";
	Initialize();
	gamestatus=true;
	//initialize
	Player player[2];
	cin>>player[0]>>player[1];
	//input player
	while(player[0].getSymbol()==player[1].getSymbol()||player[0].getName()==player[1].getName()){
		cout<<"Repeated. Input again!\n";
		cin>>player[1];
	}
	//check validation
	cout<<"Press any key to start the game...\n";
	
	do{
		UserUI(player);
		enable=true;
		if(gamestatus==false){
			if(winningname!="")
			cout<<winningname<<" win!\n";
			
			Restart(player);
			enable=false;
		}
	}while(gamestatus==true);
	//gaming while loop
	cout<<"Thanks for playing!"<<endl;
	return 0;
}
