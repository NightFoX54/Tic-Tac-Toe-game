#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void pRules(); //prints the game rules

void gBoard(int arr[3][3]); //prints the game board

void gMove(int arr[3][3],int pl,int y); //implements the player's move to the board

int hardAiMove(int arr[3][3]);

void moveCheck(int arr[3][3],int *y);  //checks wether the move is correct or not

void moveCheckAi(int arr[3][3], int *y); //checks the ai's move

int gOver(int arr[3][3]); //checks wether the board is full or not

int winningCondition(int arr[3][3], int p, int comp); //checks the winning conditions to find the winner.


int main(){
    int arr[3][3] = {}; //declaring a multidimentional array for the gameboard
    int y;
    int player = 0;
    int difficulty=0;
    srand(time(NULL)); //random number generater for ai in singleplayer

    pRules();

    while(player != 1 && player != 2){ //while loop just in case in player presses anything other than 1 or 2
        cout<<"\nPress 1 for singleplayer, Press 2 for multiplayer : ";
        cin>> player; //getting input from user for singleplayer or multiplayer
    
        switch(player){ //using switch case to seperate singleplayer and multiplayer
            case 1: //codes for singleplayer
                while(difficulty != 1 && difficulty != 2){
                    cout << "\n|DIFFICULTY|\n1) Easy\n2) Hard\nChoose a difficulty to start:  ";
                    cin >> difficulty;

                    switch(difficulty){
                        case 1:
                            while(1){  //looping the game around the players until someone wins
                                cout<<"\nPlayer's turn";
                                gBoard(arr);
                                cout << "Choose a cell to play: ";
                                y = getchar();
                                cout << endl;
                                moveCheck(arr,&y);
                                gMove(arr,1,y);
                                if(winningCondition(arr,1,0)) //if winningCondition returns 1 breaks out of the loop
                                    break;
                                if(gOver(arr)) //if gameOver returns 1 breaks out of the loop
                                    break;
            
        
                                cout << "\nComputer's turn\n";
                                y = rand() % 9 + 1; //creating random number for the ai move
                                moveCheckAi(arr,&y);
                                cout << "Computer chose cell " << y << ".\n";
                                cout << endl;
                                gMove(arr,2,y);
                                if(winningCondition(arr,2,1)) 
                                    break;
                                if(gOver(arr)) 
                                    break;
                            }
                        break;
                        
                        case 2:
                            while(1){
                                cout << "\nComputer's turn\n";
                                y = hardAiMove(arr);
                                moveCheckAi(arr,&y);
                                cout << "Computer chose cell " << y << ".\n";
                                cout << endl;
                                gMove(arr,2,y);
                                if(winningCondition(arr,2,1)) 
                                    break;
                                if(gOver(arr)) 
                                    break;

                                cout<<"\nPlayer's turn";
                                gBoard(arr);
                                cout << "Choose a cell to play: ";
                                y = getchar();
                                cout << endl;
                                moveCheck(arr,&y);
                                gMove(arr,1,y);
                                if(winningCondition(arr,1,0)) //if winningCondition returns 1 breaks out of the loop
                                    break;
                                if(gOver(arr)) //if gameOver returns 1 breaks out of the loop
                                    break;
                            }
                        break;

                        default:
                            cout << "\nIncorrect input, try again.\n";
                    }
                }
                break;
                 
            case 2: //codes for multiplayer.
                while(1){ 
                    cout << "\nPlayer 1's turn";
                    gBoard(arr);
                    cout << "Choose a cell to play: ";
                    y = getchar(); 
                    cout << endl;
                    moveCheck(arr,&y);
                    gMove(arr,1,y);
                    if(winningCondition(arr,1,0)) 
                        break;
                    if(gOver(arr)) 
                        break;
            
        
                    cout << "\nPlayer 2's turn";
                    gBoard(arr);
                    cout << "Choose a cell to play: ";
                    y = getchar();
                    cout << endl;
                    moveCheck(arr,&y);
                    gMove(arr,2,y);
                    if(winningCondition(arr,2,0)) 
                        break;
                    if(gOver(arr)) 
                        break;
                }
            break;

            default:
                cout << "\nIncorrect input, try again.\n";
        }
    }
    

    cout << "\nGame is finished.";
    gBoard(arr);

    return 0;
}

void pRules(){
    cout<<"======================== RULES ====================================\n";
    cout<<"1) Players must connect 3 of the same sign in a row to win.\n";
    cout<<"2) Only one sign is played at a time.\n";
    cout<<"3) Players can be on the offensive or defensive.\n";
    cout<<"4) The game ends when there is a 3-in-a-row or a stalemate.\n";
    cout<<"-------------------------------------------------------------------\n";
}

void gBoard(int arr[3][3]){
    cout<< endl;
    cout<<" -------------------\n"; //prints the gameboard's top line
     for(int i = 0; i < 3; i++){ //prints the gameboard
        cout<<" |"; //prints "|" at the beginning to make it look like a board
        for(int j = 0; j < 3; j++){
            if(arr[i][j] == 0)
                cout << "   |" << (3*i)+j+1 << "|"; //if there are no input at the current character prints space
            else
                if(arr[i][j]==1)
                cout<<" X |" << (3*i)+j+1 <<"|"; //if there is an input prints the character.

                else
                cout<<" O |" << (3*i)+j+1 <<"|"; //if there is an input prints the character.
        }
        if(i<3)
            cout<<"\n -------------------\n"; //prints this between lines.
    }
    cout<<endl;
}

void gMove(int arr[3][3],int pl,int y){
    arr[(y-1)/3][(y-1)%3]=pl;
    
}

int hardAiMove(int arr[3][3]){
    int x;
    for(x=0;x<3;x++){
        if(arr[0][x]==2 && arr[2][x]==2 && arr[1][x]==0) // checks vertical winning posibility for middle cell
            return x+4;
        else if(arr[x][0]==2 && arr[x][2]==2 && arr[x][1]==0) // checks horizontal winning posbility for middle cell
            return 3*x+2;
        else if(arr[0][2]==2 && arr[2][0]==2 && arr[1][1]==0) // checks diagonal winning posbility from top right to bottom left for middle cell
            return 5;
        else if(arr[0][0]==2 && arr[2][2]==2 && arr[1][1]==0) // checks diagonal winning posbility from top left to bottom right for middle cell
            return 5;
        else if(arr[2][0]==2 && arr[1][1]==2 && arr[0][2]==0) // diognal top right winning
            return 3;
        else if(arr[0][2]==2 && arr[1][1]==2 && arr[2][0]==0) // diognal bot left winning
            return 7;
        else if(arr[0][0]==2 && arr[1][1]==2 && arr[2][2]==0) // diognal bot right winning
            return 9;
        else if(arr[2][2]==2 && arr[1][1]==2 && arr[0][0]==0) // diognal top left winning
            return 3;
        else if(arr[0][x]==2 && arr[1][x]==2 && arr[2][x]==0)//vertical bottom side winning
            return x+7;
        else if(arr[2][x]==2 && arr[1][x]==2 && arr[0][x]==0)//vertical top side winning
            return x+1;
        else if(arr[x][0]==2 && arr[x][1]==2 && arr[x][2]==0)//horizontal right side winning
            return 3*x+3;
        else if(arr[x][2]==2 && arr[x][1]==2 && arr[x][0]==0)//horizontal left side winning
            return 3*x+1;
    }

    for(x=0;x<3;x++){
        if(arr[0][x]==1 && arr[2][x]==1 && arr[1][x]==0) // checks vertical winning posibility for middle cell
            return x+4;
        else if(arr[x][0]==1 && arr[x][2]==1 && arr[x][1]==0) // checks horizontal winning posbility for middle cell
            return 3*x+2;
        else if(arr[0][2]==1 && arr[2][0]==1 && arr[1][1]==0) // checks diagonal winning posbility from top right to bottom left for middle cell
            return 5;
        else if(arr[0][0]==1 && arr[2][2]==1 && arr[1][1]==0) // checks diagonal winning posbility from top left to bottom right for middle cell
            return 5;
        else if(arr[2][0]==1 && arr[1][1]==1 && arr[0][2]==0) // diognal top right winning
            return 3;
        else if(arr[0][2]==1 && arr[1][1]==1 && arr[2][0]==0) // diognal bot left winning
            return 7;
        else if(arr[0][0]==1 && arr[1][1]==1 && arr[2][2]==0) // diognal bot right winning
            return 9;
        else if(arr[2][2]==1 && arr[1][1]==1 && arr[0][0]==0) // diognal top left winning
            return 3;    
        else if(arr[0][x]==1 && arr[1][x]==1 && arr[2][x]==0)//vertical bottom side winning
            return x+7;
        else if(arr[2][x]==1 && arr[1][x]==1 && arr[0][x]==0)//vertical top side winning
            return x+1;
        else if(arr[x][0]==1 && arr[x][1]==1 && arr[x][2]==0)//horizontal right side winning
            return 3*x+3;
        else if(arr[x][2]==1 && arr[x][1]==1 && arr[x][0]==0)//horizontal left side winning
            return 3*x+1;
    }
    return rand() % 9 + 1;
    
}

void moveCheck(int arr[3][3],int *y){
   while(arr[(*y-1)/3][(*y-1)%3] != 0 || *y < 1 || *y > 9){
        if(arr[(*y-1)/3][(*y-1)%3] != 0 && !(*y < 1 || *y > 9)){
            cout << "This cell is full!"<< endl << "Choose another cell: ";
            cin >> *y;
        }
        else{
            cout << "You have to choose a number between 1 and 9: ";
            cin >> *y;
        }

    }
}

void moveCheckAi(int arr[3][3], int *y){
    while(arr[(*y-1)/3][(*y-1)%3] > 0){ //checks wether the row that ai chose is full or not.
        *y = rand() % 9 + 1; //if the row is full generates another number.
    }
}

int gOver(int arr[3][3]){
    int emptyCellCount = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
        if(arr[i][j] == 0)
            emptyCellCount++; //increases the emptyCellCount if the cell is empty.
        }
    }
    if(emptyCellCount == 0){
        cout << "\nNo empty spaces left!"; //if the emptyCellCount remains 0 prints this.
        return 1; //returns 1 to end the game
    }
    else
        return 0; //returns 0 to continue the game
}

int winningCondition(int arr[3][3], int p, int comp){
    int y = 0;
    int x = 0;
    for(x = 0; x < 3; x++){ //checks horizontal wins
            if(arr[x][y] == p && arr[x][y+1] == p && arr[x][y+2] == p)
            {
                if(comp == 1)
                    cout << "\nComputer won!";

                else
                    cout << "\nPlayer "<< p << " won!";
                return 1; //returns 1 to end the game
            }
        
    }

    x=0;

        for(int y = 0; y < 3; y++){ //checks vertical wins
            if(arr[x][y] == p && arr[x+1][y] == p && arr[x+2][y] == p)
            {
                if(comp == 1)
                    cout << "\nComputer won!";

                else
                    cout << "\nPlayer "<< p << " won!";
                return 1;
            }
        }
    
    y=0;

    //checks diagonal wins from top left to bottom right   
        if(arr[x][y] == p && arr[x+1][y+1] == p && arr[x+2][y+2] == p){
                if(comp == 1)
                    cout << "\nComputer won!";

                else
                    cout << "\nPlayer " << p << " won!";
                return 1;
        }
       
    y=2;

     //checks diagonal wins from top right to bottom left
            if(arr[x][y] == p && arr[x+1][y-1] == p && arr[x+2][y-2] == p)
            {
                if(comp == 1)
                    cout << "\nComputer won!";

                else
                    cout << "\nPlayer " << p <<" won!";
                return 1;
            }

    return 0; //returns 0 to continue the game
}