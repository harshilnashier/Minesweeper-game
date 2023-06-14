#include<bits/stdc++.h>
using namespace std;

#define max_mine 99

void clear(){
    // to clear the terminal after every move and show the new board

    cout<<"\33[2J\33[1;1H"<<endl;

}

bool isValid(int row,int col,int side){

    // is the row and col or the move that is made is a valid one

    return (row>=0) && (row<side) && (col>=0) && (col<side);

}

bool isMine(int row,int col,vector<vector<char> >realBoard){

    // check if the current index holds a mine in the realBoard

    if(realBoard[row][col]=='*'){

        return true;

    }else{

        return false;
        
    }
}

void printBoard(vector<vector<char> > myBoard,int side){
    
    clear();

    for(int i=0;i<side;i++){
        cout<<"\t\t\t    ";

        for(int j=0;j<side;j++){
            
            cout<<myBoard[i][j]<<" ";
        }
        cout<<" "<<i<<endl;
    }
    return;
}

void make_move(int &x,int&y,int side){
    
    cout<<"Enter your move--> row and column ->";

    int a,b;

    while(true){

        cin>>a>>b;

// constraint on the input move if not satisfied write another input

        if(a<side && b<side){

            x=a;
            y=b;
            break;

        }else{
            cout<<"INVALID MOVE \nEnter your move-->row and column";
        }
    }
}

void initialise(vector<vector<char> >&realBoard,vector<vector<char> >&myBoard,int side){

    // creating the real and the playing board

    for(int i=0;i<side;i++){

        for(int j=0;j<side;j++){

            myBoard[i][j]=realBoard[i][j]='-';

        }
    }

    return;
}

void placeBombs(vector<vector<int> >&mines,vector<vector<char> >&realBoard,int side,int mine){

// placing mines on the real board and storing their index in the mine vector

// to check that the same index is doesn't hold more than one mine hence a visited vector

    vector<bool>alreadyExists(side*side);

    for(int i=0;i<mine;i++){ //ran for the number of mines to be placed

        // generates a random number which is converted into within the board size range

        int random=rand()%(side*side);

        int x=random/side; //to generate the row
        int y=random%side; //to generate the column

        if(!alreadyExists[random]){

            realBoard[x][y]='*';

            mines[i][0]=x;

            mines[i][1]=y;

            alreadyExists[random]=true;

        }else{
            i--; // if not placed in this iteration then repeat the same iteration with another random index
        }
    }
}

// Counts the number of adjacent mines to a given block in all the 8 directions

int countAdjacent(int row,int col,vector<vector<int> >mines,vector<vector<char> >realBoard,int side){

    int count =0; 

    if(isValid(row-1,col,side)){
        if(isMine(row-1,col,realBoard)){
            count++;
        }
    }
    
    if(isValid(row+1,col,side)){
        if(isMine(row+1,col,realBoard)){
            count++;
        }
    }

    if(isValid(row,col-1,side)){
        if(isMine(row,col-1,realBoard)){
            count++;
        }
    }

    if(isValid(row,col+1,side)){
        if(isMine(row,col+1,realBoard)){
            count++;
        }
    }

    if(isValid(row-1,col+1,side)){
        if(isMine(row-1,col+1,realBoard)){
            count++;
        }
    }

    if(isValid(row+1,col+1,side)){
        if(isMine(row+1,col+1,realBoard)){
            count++;
        }
    }

    if(isValid(row-1,col-1,side)){
        if(isMine(row-1,col-1,realBoard)){
            count++;
        }
    }

    if(isValid(row+1,col-1,side)){
        if(isMine(row+1,col-1,realBoard)){
            count++;
        }
    }

    return count;
}

bool playmines(vector<vector<char> >&myBoard,vector<vector<char> >&realBoard,vector<vector<int> >mines,int row,int col,int &movesLeft,int mine,int side){

    // ensures no already explored block is taken as an input again
    if(myBoard[row][col]!='-'){

        return false;

    }
    // if a mine is encountered on the current move
    if(realBoard[row][col]=='*'){

        myBoard[row][col]='*';

    // reveal all the mines and game over
        for(int i=0;i<mine;i++){

            myBoard[mines[i][0]][mines[i][1]]='*';

        }

        printBoard(myBoard,side);

        cout<<"\n\n YOU LOST \n\n"<<endl;

        return true;

    }else{
        // count number of adjacent mines
        int count=countAdjacent(row,col,mines,realBoard,side);

        // decremented on every neighbour exploration as that move is no longer further possible
        movesLeft--;

        // change value on the playing board to the number of adjacent mines
        myBoard[row][col]=count +'0';

        // if no adjacent mines are present we move to further neighbours and explore them

        if(!count){
            if(isValid(row-1,col,side)){

                if(!isMine(row-1,col,realBoard)){
                    
                    playmines(myBoard,realBoard,mines,row-1,col,movesLeft,mine,side);

                }

            }
            
            if(isValid(row+1,col,side)){

                if(!isMine(row+1,col,realBoard)){
                    playmines(myBoard,realBoard,mines,row+1,col,movesLeft,mine,side);
                }

            }

            if(isValid(row,col-1,side)){

                if(!isMine(row,col-1,realBoard)){

                    playmines(myBoard,realBoard,mines,row,col-1,movesLeft,mine,side);

                }

            }

            if(isValid(row,col+1,side)){

                if(!isMine(row,col+1,realBoard)){

                    playmines(myBoard,realBoard,mines,row,col+1,movesLeft,mine,side);

                }

            }

            if(isValid(row-1,col+1,side)){

                if(!isMine(row-1,col+1,realBoard)){

                    playmines(myBoard,realBoard,mines,row-1,col+1,movesLeft,mine,side);

                }

            }

            if(isValid(row+1,col+1,side)){

                if(!isMine(row+1,col+1,realBoard)){

                    playmines(myBoard,realBoard,mines,row+1,col+1,movesLeft,mine,side);

                }

            }

            if(isValid(row-1,col-1,side)){

                if(!isMine(row-1,col-1,realBoard)){

                    playmines(myBoard,realBoard,mines,row-1,col-1,movesLeft,mine,side);

                }

            }

            if(isValid(row+1,col-1,side)){

                if(!isMine(row+1,col-1,realBoard)){

                    playmines(myBoard,realBoard,mines,row+1,col-1,movesLeft,mine,side);

                }

            }
        }
        return false;
    }
}

void play(int side,int mine){

    bool game=false;

    // the hidden board which contains the mines
    vector<vector<char> > realBoard(side,vector<char>(side));

    // the board on which the game is played
    vector<vector<char> > myBoard(side,vector<char>(side));

    // maximum number of moves possible 
    int movesLeft=side*side-mine;

    int x,y;

    // vector containing the indexes of all the mines to be placed on the real board
    vector<vector<int> >mines(max_mine,vector<int>(2));

    initialise(realBoard,myBoard,side);

    placeBombs(mines,realBoard,side,mine);

    int currentMoveNo=0;

    while(game==false){

        cout<<"Current Board "<<endl;

        printBoard(myBoard,side);

        make_move(x,y,side);

        currentMoveNo++;

        game=playmines(myBoard,realBoard,mines,x,y,movesLeft,mine,side);

        if(game==false && movesLeft==0){

            // indicating no further moves are possible and no mines are encountered
            cout<<"YOU WON"<<endl;

            game=true;
        }        
    }
}
void chooseDifficulty(int &side,int &mine){

    clear();

    cout<<"Choose Difficulty"<<endl;

    cout<<" a)Beginner-->1 \n b)Intermmmediate-->2\n c)Hard-->3)"<<endl;

    cout<<"Enter choice--> " ;

    int choice;

    cin>>choice;
    

    if(choice==1){

        side=9;
        mine=10;

    }else if(choice==2){

        side=16;
        mine=40;

    }else if(choice==3){

        side=24;
        mine=99;

    }else{

        cout<<"INVALID CHOICE"<<endl;
        return;
    }
    
}
int main(){
    int mine,side;

    chooseDifficulty(side,mine);

    play(side,mine);

    return 0;
}