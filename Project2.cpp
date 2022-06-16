#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

const int row = 10;
const int column = 10;


bool isWrongFormat(string mail){ 
   
    int x = mail.length();  // sets x to the length of the string.
    char emailArr[x + 1];   // creates an char array
    
    strcpy(emailArr, mail.c_str());
    int counter = 0;

    for (int i = 0; i < x; ++i){

        if (isalnum(emailArr[i]) || emailArr[i] == '@' || emailArr[i] == '.'){ // allows only these characters
            if (emailArr[i] == '@' || emailArr[i] == '.'){ // counts the number of these
                ++counter;
            }
        }
        else{
            return true;
        }
    }
    
        if ((!isalnum(mail.at(0)))){ // if it doesn't start with an alphanumeric character it is invalid
            return true;
        }
        else if (mail.find('@') > x){ // if it isnt in the string it assigns the max value which is greater than the length
            return true;
        }
        else if (mail.find('.') > x){ // if it isnt in the string it assigns the max value which is greater than the length
            return true;
        }
        else if (counter != 2){ // if it has more than one @ and 1 . it is invalid
            return true;
        }
        else if (mail.find('@') > mail.find('.')){ // if the @ comes after the . it is invalid
            return true;
        }
        else if ((!isalnum(emailArr[mail.find('@') + 1]))){ // if there is not a alphanumeric character after the @ it is incorrect
            return true;
        }
        else if ((!isalnum(emailArr[mail.find('.') + 1]))){ // if there is not an alphanumeric character after the . it is incorrect
            return true;
        }
        return false;   // if it passes all of these, it is valid;
}

int** initialize(int rowF,  int colF, int either = -1){ //allows the function to return a 2d array
   int** numArr; //initializes with two pointers
   srand(time(0)); // random seeded
   numArr = new int*[rowF]; //sets up rows

   for (int i = 0; i < rowF; ++i){  //sets up columns
       numArr[i] = new int[colF];
   }
   if (either == -1){ // if the default is there, it makes the display matrix
       for (int i = 0; i < rowF; ++i){
           for (int j = 0; j < colF; ++ j){
               numArr[i][j] = -1;
           }
       }
   }
   else {
       for (int i = 0; i < rowF; ++i){ // if the default isnt it makes the numarray
           for (int j = 0; j < colF; ++ j){
               numArr[i][j] = (rand() % 20) + 1;
           }
       }
   }
   return numArr;
}

void display(int** arr, int rowF, int colF){ 
    
    for (int i = 0; i < rowF; ++i){ //allows me to manipulate the 2d array in a diff function
                for (int j = 0; j < colF; ++j){
                    cout<<arr[i][j]<<"\t";
                }
            cout<<endl;
            }
}

bool checkRepeat(int arr[], int co1, int co2, int iterate){
    for (int i = 0; i < iterate; i+= 2){ //checks if two values match the to inputs, checks by twos;
        if (arr[i] == co1 && arr[i + 1] == co2){
            return true;
        }
        
    }
    return false;
}

int main(){
    
    string email;
    int** numArray;
    int** dispArray;
    int myRow;
    int myCol;
    int points = 10;
    int revRow;
    int revCol;
    int guessRow;
    int guessCol;
    int checkArr[(row * column) * 2]; //sets the largest possib;e array size
    int iterate = 2; // use this to limit the check function's for loop;
    char quit;
    int revCount = 0;

    
    cout<<"Please enter your email."<<endl;
    cin>>email;

    while (isWrongFormat(email) == true){ // keeps asking until a valid email is input
        cout<<"Please enter a valid email"<<endl;
        cin>> email;
        isWrongFormat(email);
    }
    
    cout << "How many rows and columns?"<<endl; 
    cin>> myRow;
    cin>> myCol;
    
    while (myRow > row || myCol > column){
        cout<<"Please enter values that are less than or equal to 10."<<endl; //keeps asking until the value is less than 11.
        cin>>myRow;
        cin>>myCol;   
    }

    dispArray = initialize(myRow, myCol);
    
    numArray = initialize(myRow, myCol, 1); // the 1 tells the function to make the numArray
    
    do{ // do while loop lets this process repeat until the person inputs n to quit.


    display(dispArray, myRow, myCol);
    cout<< "Which co-ordinate would you like to reveal?"<<endl;
    cin>>revRow;
    cin>> revCol;
    
    while (checkRepeat(checkArr, revRow, revCol, iterate)){
        cout<<"You already revealed that co-ordinate.\nPlease enter a new one."<<endl; // checks if the co-ordinate is already revealed.
        cin>>revRow;
        cin>>revCol;
        while (revRow >= myRow || revCol >= myCol){ // keeps asking until they enter a valid index
            cout<<"Please enter a valid index."<<endl;
            cin>>revRow;
            cin>>revCol;
        }
    }  

     while (revRow >= myRow || revCol >= myCol){ // keeps asking until they enter a valid index
        cout<<"Please enter a valid index."<<endl;
        cin>>revRow;
        cin>>revCol;
        while (checkRepeat(checkArr, revRow, revCol, iterate)){ //checks if the co-ordinate is already revealed.
            cout<<"You already revealed that co-ordinate.\nPlease enter a new one."<<endl;
            cin>>revRow;
            cin>>revCol;
    }  
    }

    ++revCount;


    

    if (revCount >= (myRow * myCol)){
        for (int i = 0; i < myRow; ++i){
            for (int j =0; j < myCol; ++j){
                dispArray[i][j] = numArray[i][j];
            }
        }
        display(dispArray, myRow, myCol);
        cout<<"Oops, you revealed them all\nGAME OVER ;p"<<endl;
        cout<<"Your score will be emailed to you"<<endl;
        return 0;
    }
    
    
    checkArr[iterate - 2] = revRow; //// iterate also controls which index their guesses are saved on, however its minimum must be 2 for the for loop to work
    checkArr[iterate - 1] = revCol;

    

   
    dispArray[revRow][revCol] = numArray[revRow][revCol]; //displays with the revealed value
    display(dispArray, myRow, myCol);

    cout<<"Guess a co-ordinate!"<<endl;
    cin>>guessRow;
    cin>>guessCol;
    while (guessRow >= myRow || guessCol >= myCol){
        cout<<"Please enter a valid index."<<endl; //asks until they input a valid index
        cin>>guessRow;
        cin>>guessCol;
    }

    
    
    checkRepeat(checkArr, guessRow, guessCol, iterate); // checks if they already know that one

    while (checkRepeat(checkArr, guessRow, guessCol, iterate)){
        cout<<"Please guess a NEW co-ordinate"<<endl;   //asks until they enter a new guess
        cin>>guessRow;
        cin>>guessCol;
            while (guessRow >= myRow || guessCol >= myCol){
                cout<<"Please enter a valid index."<<endl;  //asks until they enter a valid index
            cin>>guessRow;
            cin>>guessCol;
            }
           checkRepeat(checkArr, guessRow, guessCol, iterate); //checks
       }
       
   
    
    if(numArray[guessRow][guessCol] == dispArray[revRow][revCol]){ //if a match is found they are alerted and their guess index is saved 
            cout<<"You found a match!"<<endl;
            points += 2;
            dispArray[guessRow][guessCol] = numArray[guessRow][guessCol];
            cout<<"Points: "<<points<<endl;
            checkArr[iterate] = guessRow; //saves index
            checkArr[iterate  + 1] = guessCol;
            iterate += 4; // adds 4 to the value that controls the loop and indexes to make sure none are overwritten and there is room for the next future loop indexes.
            
            ++revCount;
        }
        else{
            cout<< "You didn't find a match :("<<endl;
            points--;
            cout<<"Points: "<<points<<endl;

            iterate += 2; //adds only two because they did not guess a valid index.
        }
        
       
    display(dispArray, myRow, myCol);
    
    if (points < 1){ // if they're out of points, the game ends.
        cout<<"You are out of points\n"<<"GAME OVER ;p"<<endl;
        cout<<"Your score will be emailed to you."<<endl;
        delete[] dispArray;
        delete[] numArray;
        return 0;
    }
    
    
    cout<<"Would you like to continue? (Enter 'N' to quit)"<<endl; // if they enter N it quits, otherwise it continues the game.
    cin>> quit;
    }while(toupper(quit) != 'N');


cout<<"Thanks for playing!!!"<<endl; // if they decide to quit, they are told this
cout<<"You had "<<points<< " points."<<endl;
cout<<"Your score will be emailed to you."<<endl;
    delete[] dispArray;
    delete[] numArray;
    
    return 0;
}