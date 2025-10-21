#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void pRules(); //prints the game rules

void gBoard(int arr[3][3]); //prints the game board

void gMove(int arr[3][3],int pl,int y); //implements the player's move to the board

void moveCheck(int arr[3][3],int *y);  //checks wether the move is correct or not

void moveCheckAi(int arr[3][3], int *y); //checks the ai's move

int gOver(int arr[3][3]); //checks wether the board is full or not

int winningCondition(int arr[3][3], int p, int comp); //checks the winning conditions to find the winner.

int inputCheck(string input);

int hardAi(int arr[3][3]);

int returnDifferent(int arr[3][3], int x, int y, int z, int player);


int main(){
    int arr[3][3] = {}; //declaring a multidimentional array for the gameboard
    int y;
    int player = 0;
    int difficulty=0;
    string input;
    srand(time(NULL)); //random number generater for ai in singleplayer

    pRules();

    while(player != 1 && player != 2){ //while loop just in case in player presses anything other than 1 or 2
        cout<<"\nPress 1 for singleplayer, Press 2 for multiplayer : ";
        getline(cin, input); //getting input from user for singleplayer or multiplayer
        player = inputCheck(input);
    
        switch(player){ //using switch case to seperate singleplayer and multiplayer
            case 1: //codes for singleplayer
                while(difficulty != 1 && difficulty != 2){
                    cout << "\n|DIFFICULTY|\n1) Easy\n2) Hard\nChoose a difficulty to start:  ";
                    getline(cin, input);
                    difficulty = inputCheck(input);

                    switch(difficulty){
                        case 1:
                            while(1){  //looping the game around the players until someone wins
                                cout<<"\nPlayer's turn";
                                gBoard(arr);
                                cout << "Choose a cell to play: ";
                                getline(cin, input);
                                y = inputCheck(input);
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
                                y = hardAi(arr);
                                if(y == 0)
                                    y = rand() % 9 + 1; //creating random number for the ai move
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
                                getline(cin, input);
                                y = inputCheck(input);
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
                    getline(cin, input);
                    y = inputCheck(input);
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
                    getline(cin, input);
                    y = inputCheck(input);
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
    getline(cin, input);
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

void moveCheck(int arr[3][3],int *y){
    string input;
    while(arr[(*y-1)/3][(*y-1)%3] != 0 || *y < 1 || *y > 9){
        if(arr[(*y-1)/3][(*y-1)%3] != 0 && !(*y < 1 || *y > 9)){
            cout << "This cell is full!"<< endl << "Choose another cell: ";
            getline(cin, input);
            *y = inputCheck(input);
        }
        else{
            cout << "You have to choose a number between 1 and 9: ";
            getline(cin, input);
            *y = inputCheck(input);
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

int inputCheck(string input){
    char c = input[0];
    while(c < '1' && c > '9'){
        cout << "Incorrect input. Please type a number between 1 and 9 : ";
        getline(cin, input);
        c = input[0];
    }
    return (c - '0');
}


int hardAi(int arr[3][3]){
    int x;
    int out = 0;
    for(x=0;x<3;x++){
        if(out = returnDifferent(arr, 3*x + 1, 3*x + 2, 3*x + 3, 2))
            return out;
        if(out = returnDifferent(arr, x + 1, x + 4, x + 7, 2))
            return out;
    }
    if(out = returnDifferent(arr, 1, 5, 9, 2))
        return out;
    if(out = returnDifferent(arr, 3, 5, 7, 2))
        return out;    

    for(x=0;x<3;x++){
        if(out = returnDifferent(arr, 3*x + 1, 3*x + 2, 3*x + 3, 1))
            return out;
        if(out = returnDifferent(arr, x + 1, x + 4, x + 7, 1))
            return out;
    }
    if(out = returnDifferent(arr, 1, 5, 9, 1))
        return out;
    if(out = returnDifferent(arr, 3, 5, 7, 1))
        return out;    
    return rand() % 9 + 1;
}

int returnDifferent(int arr[3][3], int x, int y, int z, int player){
    if(arr[(x-1)/3][(x-1)%3] == player && arr[(y-1)/3][(y-1)%3] == player && arr[(z-1)/3][(z-1)%3] == 0)
        return z;
    if(arr[(z-1)/3][(z-1)%3] == player && arr[(y-1)/3][(y-1)%3] == player && arr[(x-1)/3][(x-1)%3] == 0)
        return x;
    if(arr[(x-1)/3][(x-1)%3] == player && arr[(z-1)/3][(z-1)%3] == player && arr[(y-1)/3][(y-1)%3] == 0)
        return y;
    return 0;
}
