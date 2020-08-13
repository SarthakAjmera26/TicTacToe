using namespace std;
#include<bits/stdc++.h>
#define int long long
#define pb push_back 
#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)

vector<vector<int>>winTriplets = { {0,1,2}, 
                                {3,4,5},
                                {6,7,8},
                                {0,3,6},
                                {1,4,7},
                                {2,5,8},
                                {0,4,8},
                                {2,4,6}   
                                        }  ;

string BoardString = "         ";
int winner;

map<pair<string,int>,int>memoise;
map<pair<string,int>,int>visited;

void DisplayBoard()
{
    for (int i=0; i<9; i+=3)
    {
        for (int j=i; j<=i+2; j++)
        {
            if ( BoardString[j]==' ' )
                cout<<"_";
            else
                if (BoardString[j]=='1')
                    cout<<"O";
                else
                    cout<<"X";
        }
        cout<<endl;
    }
}

bool Tied(string &current)
{
    bool space = false;

    for (auto it:current)
        if ( it==' ' )
            space = true;

    if (space)
        return false;
    else
        return true;
}

bool FoundWinner(string current)
{
    for (int i=0; i<8; i++)
    {
        set<char>values;
        for (int j=0; j<3; j++)
            values.insert( current[ winTriplets[i][j] ] );

        if ( values.size()==1 && *values.begin()!=' ')
        {
            winner = *values.begin() - '0';
            return true;
        }
    }

    return false;
}

int dfs(string &current,int turn)
{
    
    int &ans = memoise[{current,turn}];

    if (visited[{current,turn}])
        return ans;
    ans = -1;
    visited[{current,turn}] = 1;

    int complement = turn;

    if (turn==1)
        complement++;
    else
        complement--;

    if ( FoundWinner(current) )
    {
        ans = winner;
        return winner;
    }

    if ( Tied(current) )
    {
        ans = 0;
        return 0;
    }

    for (int i=0; i<9; i++)
    {
        if ( current[i]!=' ' )
            continue;

        string temp = current;
        temp[i] = '0' + turn;

        if ( dfs(temp,complement)==turn )
        {
            ans = turn;
            break;
        }

        if ( dfs(temp,complement)==0 )
        {
            ans = 0;
            continue;
        }
    }
    if (ans==-1)
        ans = complement;

    return ans;
}

bool PlayerMove(int pos)
{

    if ( BoardString[pos]!=' ' )
    {
        cout<<"Invalid Move, try again "<<endl;
        return false;
    }

    BoardString[pos] = '2';
}

void ComputerMove()
{

    int best;
    for (int i=0; i<9; i++)
    {
        if ( BoardString[i]==' ' )
        {
            string temp = BoardString;
            temp[i] = '1';

            if ( dfs(temp,2)==1 )
            {
                best = i;
                break;
            }

            if ( !dfs(temp,2) )
                best = i;
        }
    }

    BoardString[ best ] = '1'; 

}


signed main()
{
    IOS;

    BoardString = "         ";
    char mode;
    int turnOf;


    cout<<"Press Y if you want to initialize the board, however if you want to start a fresh game press N"<<endl;

    while(true)
    {
        cin>>mode;

        if (mode=='Y' || mode=='N')
            break;
        cout<<"Invalid input, please enter Y or N"<<endl;
    }

    if (mode=='Y')
    {

        int p = 0;
        int e = 0;


        while(true)
        {
            set<char>tempSet;

            cout<<"Input a 3x3 matrix filled with moves, represent your move by X and enemies move by Y, represnt empty cell by and underscore ( _ ) space"<<endl;
            for (int i=0; i<9; i++)
            {
                cin>>BoardString[i];
                tempSet.insert(BoardString[i]);
                e+=(BoardString[i]=='O');
                p+=(BoardString[i]=='X');
            }

            if ( abs(e-p)>=1 )
            {
                cout<<"Invalid state of board"<<endl;
                continue;
            }

            if (tempSet.find('_')!=tempSet.end())
                tempSet.erase(tempSet.find('_'));
            
            if (tempSet.find('O')!=tempSet.end())
                tempSet.erase(tempSet.find('O'));

            if (tempSet.find('X')!=tempSet.end())
                tempSet.erase(tempSet.find('X'));
            
            if (tempSet.size())
            {
                cout<<"Please enter valid characters only"<<endl;
                continue;
            }
            break;
        }

        if (p==e)
        {
            cout<<"Choose the player who moves first, type 2 if you want to move first, else type 1"<<endl;
            while(true)
            {
                cin>>turnOf;
                if (turnOf!=1 && turnOf!=2)
                    cout<<"Please enter valid characters only"<<endl;
                else
                    break;
            }

        }
        else
            if ( p>e )
                turnOf = 2;
            else
                turnOf = 1;
    }

    else
    {
        cout<<"Press 1 if you want computer to move first, 2 if you want to go firtst" <<endl;
        
        while(true)
            {
                cin>>turnOf;
                if (turnOf!=1 && turnOf!=2)
                    cout<<"Please enter valid characters only"<<endl;
                else
                    break;
            }
    }


    cout<<"Your move on the board will be represented by X"<<endl;

    for (int i=0; i<9; i++)
        if (BoardString[i]=='O')
            BoardString[i]='1';
        else if (BoardString[i]=='X')
            BoardString[i]='2';
        else 
            BoardString[i]=' ';

    while(true)
    {

        if ( turnOf==1 )
        {
            ComputerMove();
        }

        else 
        {
            DisplayBoard();
            int pos;
            while(true)
            {
                cout<<endl<<"Make a move"<<endl;
                int x,y;

                while(true)
                {
                    cin>>x>>y;
                    x--;
                    y--;
                    if (x<0 || y<0 || x>2 || y>2)
                        cout<<"Invalid Move, try again "<<endl;
                    else
                        break;
                }
                pos = x*3 + y;

                if ( PlayerMove(pos) )
                    break;
            }
            
            BoardString[pos] = '2';
        }

        if (Tied(BoardString))
        {
            cout<<"Tied!"<<endl;
            break;
        }

        if (FoundWinner(BoardString))
        {
            DisplayBoard();
            cout<<"Computer won the game!"<<endl;
            break;
        }

        if (turnOf==2)
            turnOf = 1;
        else
            turnOf = 2;
    }
       

}
