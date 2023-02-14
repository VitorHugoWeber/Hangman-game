// Vitor Hugo Behlau Weber
// Hangman Game

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>
#include <algorithm>

using namespace std;

void clearScreen(){
    system("CLS");
}

string returnRandomWord(){
    string words[10] = {"AIRPLANE", "COMPUTER", "PICTURE", "HORIZON", "MUSIC", "FLOWER", "WHEEL", "ICE", "TABLE", "MOUNTAINS"};
    int randomIndex = rand() % 10;
    return words[randomIndex];
}

string returnWordWithMask(string word, int wordSize){
    int counter = 0;
    string wordWithMask;
    while(counter < wordSize){
        wordWithMask += "_";
        counter++;
    }
    return wordWithMask;
}

void displayStatus(string wordWithMask, int wordSize, int remainingAttempts, string triedLetters, string message){
    cout << message;
    cout << "Word: " << wordWithMask << " (Size: " << wordSize << ")";
    cout << "\n\nRemaining attempts: " << remainingAttempts;
    int counter;
    cout << "\nTried letters: ";
    for(counter = 0; counter < triedLetters.size();counter++){
        cout << triedLetters[counter] << ", ";
    }
}

int play(int numberOfPlayers){

    string word;
    if(numberOfPlayers == 1){
        word = returnRandomWord();
    }else{
        cout << "\nPlease, type a word: ";
        cin >> word;
        transform(word.begin(), word.end(),word.begin(), ::toupper);
    }

    int wordSize = word.size();
    string wordWithMask = returnWordWithMask(word, wordSize);
    int attempts = 0, maximumAttempts = 10;
    int counter = 0;
    char letter;
    int option;
    string triedLetters;
    string message = "Lets play!\n\n";
    string triedWord;
    bool letterTyped = false, letterCorrect = false;

    while(word != wordWithMask && maximumAttempts - attempts > 0){
        clearScreen();
        displayStatus(wordWithMask, wordSize, maximumAttempts - attempts, triedLetters,message);
        cout << "\n\nType a letter or type 1 to try the complete word: ";
        cin >> letter;
        letter = toupper(letter);

        if(letter == '1'){
            cout << "Try the complete word: ";
            cin >> triedWord;
            transform(triedWord.begin(), triedWord.end(),triedWord.begin(), ::toupper);
            if(triedWord == word){
                 wordWithMask = triedWord;
            }else{
                 attempts = maximumAttempts;
            }
        }

        for(counter = 0; counter < attempts; counter++){
            if(triedLetters[counter] == letter){
                message = "This letter has already been typed.\n\n";
                letterTyped = true;
            }
        }

        if(letterTyped == false){
            triedLetters += toupper(letter);
            for(counter = 0; counter < wordSize; counter++){
                if(word[counter] == toupper(letter)){
                    wordWithMask[counter] = word[counter];
                    letterCorrect = true;
                }
            }

        if(letterCorrect == false){
            message = "Wrong letter!\n\n";
        }else{
            message = "Right letter!\n\n";
        }
        attempts++;
        }
        letterTyped = false;
        letterCorrect = false;
    }

    if(word == wordWithMask){
        cout << "\nWell done! You won!";
        cout << "\nThe word was: " << word;
        cout << "\n\nDo you want to play again?";
        cout << "\n1 - Yes";
        cout << "\n2 - No\n\n";
        cin >> option;
        return option;
    }else{
        cout << "\nWasted!";
        cout << "\nThe word was: " << word;
        cout << "\n\nDo you want to play again?";
        cout << "\n1 - Yes";
        cout << "\n2 - No\n\n";
        cin >> option;
        return option;
    }
}

void menu(){
    int option = 0;
    while(option < 1 || option > 3){
        clearScreen();
        cout << "Welcome to the Handman Game!\n";
        cout << "Type the number of the option that you want and click ENTER:\n\n";
        cout << "1 - Single Player\n";
        cout << "2 - Multiplayer\n";
        cout << "3 - Exit\n\n";
        cin >> option;

        switch(option){

            case 1:
                if(play(1) == 1){
                    menu();
                }
                break;

            case 2:
                if(play(2) == 1){
                    menu();
                }
                break;

            case 3:
                break;
        }
    }
}

int main(){
    srand((unsigned)time(NULL));
    menu();
    cout << "I hope you had a great time!\n";
    cout << "Goodbye!\n";
    return 0;
}
