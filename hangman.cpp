// #include <stdio.h>
// #include <stdbool.h>
// #include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <ctime>

// Testing Github right now woooo why is this so difficult and annoying to learn

// Functions
int main(); // main function
void startGame(); // opens file and starts game if user selects to  play (calls menu)
void menu(); // gets users choice between instructions, quit, and play
void pauseProgram(); // asks for a char input to pause the program
void welcome(); // welcome message
void instructions(); // instructions
void goodbye(); // goodbye message
bool isPresent(char, char[]); // checks to see if the char argument is present in the char[] argument
void play(); // repeatedly gets user guesses and either reveals letters or removes lives (playing the game)
int addToGuessed(char letter, char guessedLetters[]); // returns the next free index in guessedLetters to add a new letter to guessedLetters
bool isRoundWon(char word[], char guessedLetters[], int length); // Checks if the word has been fullyguessed

void settingsAccess();

// Variables
// bool gameOn = true;

// Main function
int main(){

    
    welcome(); // Welcome message
    startGame(); // Starts the game by creating the file pointer and sending user to the menu

    return 0;
}

// Purpose: Setup the answer file and send the user to the menu
void startGame(){

    // Variables
    //char word[13] = {0}; // This will hold the word in the game

    //allows for new random numbers every execution
    srand(time(0));

    //FILE *words = fopen("D:\\words.txt", "r"); // Creating the pointer for the file
    //std::ofstream ReadFile("words.txt");

    //Checking to see if file open was a success, if not, output error
    // if (words == NULL){
    //     std::cout << "ERROR OPENING FILE" << std::endl;
    // }

    menu(); // Continue to the main menu
    
}

// Purpose: Check if the password is correct or not
int accessGranted(char password[]){
    int count = 0;
    char storedPass [8] = "test";


    for (int i = 0 ; i < 8 ; i++){

        if (password[i] == '1'){
            count++;
        }
    }
    if (count == 8){
        return 2;
    }

    for (int i = 0 ; i < 8 ; i++){

        if (password[i] != storedPass[i]){
            return 0;
        }
    }
    return 1;
}

// Purpose: the admin page
void settings(){
    system("cls");
    std::cout << "Settings" << std::endl;
    pauseProgram();
}

// Purpose: the password input loop after choosing to go to settings from main menu
void settingsAccess(){
    char choice;
    // bool accessGranted = false;
    char password[8];
    
    pauseProgram();
    system("cls");

    while (choice != 'b' || choice != 'B'){

        std::cout << "This is a password protected admin page, please enter what you would like to do." << std::endl;
        std::cout << "[B]ack to Menu - [E]nter admin password" << std::endl;
        
        choice = getch();
        fflush(stdin);
        if (choice == 'B' || choice == 'b'){
            break;
        }
        else if (choice == 'E' || choice == 'e'){

            while (accessGranted(password) == 0){
                system("cls");
                std::cout << "Enter all 1's to return to main menu." << std::endl;
                std::cout << "Enter Password: " << std::endl;
                
                std::cin >> password;
                fflush(stdin);

                if (accessGranted(password) == 0){
                    std::cout << "Invalid password, please try again, or enter 11111111 to return to the menu" << std::endl;
                    pauseProgram();
                }
                // printf("\n", '\n');
                // printf("password: %8s", password);
            }
            if (accessGranted(password) != 0){
                    break;
            }
        } 
    }
    if (accessGranted(password) == 1){
        settings();
    }
}

// Purpose: Actual Gameplay. Gets user input, processes guesses, and outputs gameplay to the user
void play(){

    // Variables
    int lives = 20;
    int length = 0; // The length of the current word being guessed
    char guess; // The users input
    char guessedLetters[26] = {0}; // Array which stores all the guessed letters

    
    while (lives != 0){

        // Clear guessedLetters and sets word length to 0 if its not the first time here and there are chars stored 
        // (necessary if the user passed the first word)
        length = 0;
        for (int i = 0 ; i < 26 ; i++){
            guessedLetters[i] = 0;
        }

        // CLear screen if user chooses to play 
        std::string filename = "words.txt";
        char word[13];
        int wordNum = rand() % 1000;
        std::ifstream file(filename);

        system("cls");
        for (int i = 0 ; i < wordNum ; i++){
            word[13] = {NULL};
            file >> word;
        }
        fflush(stdin);
        // std::cout << wordNum << std::endl;
        // std::cout << rand() % 1000 << std::endl;
        // std::cout << rand() % 1000 << std::endl;
        // std::cout << rand() % 1000 << std::endl;
        // std::cout << "word: " << word; //debugging
        // std::cout << "--" << std::endl; //debugginh
        //fgets(word, 13, words); // get the next word from the file
        //printf("word: %s-", word);
        
        // Traverses through the first 13 characters of word
        for (int i = 0 ; i < 13 ; i++){

            // If word isnt any letter in the alphabet, upper or lower case, it will stop adding length to the word, meaning the word is finished
            if ( !((word[i] >= 65 && word[i] <= 90) || (word[i] >= 97 && word[i] <= 122)) ){
                break;
            }
            length++;
            word[i] = word[i]-32;
        }
        // std::cout << "length: " << length << std::endl;
        // std::cout << "wordREAL: " << word << std::endl;
        
        // Actual gameplay with guessing and output
        do{

            // Printing the word with non guessed letters hidden
            for (int i = 0 ; i < length ; i++){
                // std::cout << "word[i]: " << word[i] << std::endl;
                // If the letter in word[] is already guessed, output the letter instead of a star
                if (isPresent(word[i], guessedLetters)){
                    std::cout << word[i];
                }
                else {
                    std::cout << "*";
                }
            }

            // Printing out what the player has already guessed and the lives
            std::cout << "\nGuessed: ";
            for (int i = 0 ; i < 26 ; i++){

                // If there is a non default entry in guessedletters, it must be a letter which was guessed
                if (guessedLetters[i] != 0){    
                    
                    // If its the first letter that was guessed, dont add a coma, otherwise add one to keep a clean look
                    if (i == 0){
                        std::cout << guessedLetters[i];
                    }
                    else{
                        std::cout << ", " << guessedLetters[i];
                    }
                }
            }

            // Printing the users total lives
            std::cout << "\nLives: " << lives << std::endl;
            std::cout << "" << std::endl;
            
            // User guessing
            std::cout << "Please enter your letter guess: " << std::endl;
            guess = getch();
            fflush(stdin);

            // If the guess was lower case, subtract 32 to make its ascii value the equivalent upper case letter
            if (guess > 90){
                guess -=32;
            }

            // Checking if the guess is already present in guessed letters
            if (isPresent(guess, guessedLetters)){
                std::cout << "You already guessed that! Try again :D" << std::endl;
            }
            else{

                // Adds letter guess to guesedletters
                guessedLetters[addToGuessed(guess, guessedLetters)] = guess;

                // If the guess is present in the word, or not
                // std::cout << "guess: " << guess << std::endl;
                // std::cout << "WORD: " << word << std::endl;
                if (!isPresent(guess,word)){
                    lives--;
                    std::cout << "Incorrect" << std::endl;
                }
                else{
                    std::cout << "Correct" << std::endl;
                }
            }

            // Stopping the program to let the user see the correct or incorrect message
            //pauseProgram(); 
            system("cls");

            // If the user guessed all the letters in the word
            if (isRoundWon(word, guessedLetters, length)){
                std::cout << "CONGRATS" << std::endl;
                pauseProgram();

                std::cout << "Enter 'N' to stop. Enter anything else to continue playing." << std::endl;
                guess = getch();
                fflush(stdin);

                if (guess == 'N' || guess == 'n'){
                    lives = 0;
                }
            }
        }
        while( (lives != 0) && !isRoundWon(word,guessedLetters,length));
    }

    // close and open the file to restart at the beginning if the user is kicked from the game loops
    // (meaning the user lost all lives, or purposefully chose to restart)
    //fclose(words);
    //fopen("words.txt","r");
}

// Purpose: Returns true if the word has been fully guessed, false if otherwise
bool isRoundWon(char word[], char guessedLetters[], int length){

    // Variables
    int count = 0; // Indicates how many correctly guessed letters are in the word

    // Traverses through the length of the word
    for (int i = 0 ; i < length ; i++){

        // Traverses through the guessedletters array to see if word[i] is guessed or not
        for (int j = 0 ; j < 26 ; j++){

            // If the letter in word has been guessed, add 1 to the count of correct letters, and break the inner loop
            if (word[i] == guessedLetters[j]){
                count++; // counts how many letters in word are already guessed
                break; // break out of loop
            }
        }
    }

    // If the length of the word = the amount of correct guesses, game wins, otherwise returns false
    if (count == length){ 
        return true;
    }
    return false;
}

// Purpose: returns the next free index of guessedletters to add letters to the array in the play function
int addToGuessed(char letter, char guessedLetters[]){
    // Variables
    int index = 0; // The next free index

    // Traverse through the guessedleters array
    for (int i = 0 ; i < 26 ; i++){
        
        // If index i of guessedletters is the default value, set the index to return as i, and break the loop
        if (guessedLetters[i] == 0){
            index = i;
            break;
        }
    }

    return index;
}

// Purpose: Checks to see if the char 'letter' passed in is found in the array 'guessesOrWord' passed in
bool isPresent(char letter, char guessesOrWord[]){ // guessesOrWord array can either hold the guessed letters array, or the words array
    // variables
    //bool guessed = false; // Shows whether it was guessed or not
    //std::cout << "word: " << guessesOrWord; //debugging
    //std::cout << "Letter: " << letter << std::endl; //debugging
    // Traverse through the guessesOrWord array
    for (int i = 0 ; i < 25 ; i++){

        // If the letter is found in the array, return true
        //std::cout << "word CHAR: " << guessesOrWord[i] << "," << std::endl; //debugging
        //std::cout << "Letter CHAR: " << letter << std::endl;
        if (guessesOrWord[i] == NULL){
            return false;
        }
        if (letter == guessesOrWord[i]){
            return true;
        }
    }
    //std::cout << "nope" << std::endl; // debugging
    return false;
}

// Purpose: Act as the menu for the player. Gives options on what to do, like play, quit, and instructions.
//          Correctly gets user input and sends the user to where they chose
void menu(){
    // Variables
    char guess; // The users input on what to do

    // While the guess is not q or Q, aka: while the user does not want to quit
    while (guess != 'Q' && guess != 'q'){
        system("cls"); // MUST REMOVE THIS FOR DEBUGGING. IT MAY HIDE USEFUL ERRORS IF NOT COMMENTED
        std::cout << "Enter [I]nstructions - Enter [Q]uit - Enter [P]lay - Enter [S]ettings" << std::endl;
        std::cout << "Please enter what you wish to do: " << std::endl;

        guess = getch();
        fflush(stdin);
        
        // If statement to determine where to send the user, either sends user to a function, or breaks the menu loop
        if (guess == 'I' || guess == 'i'){
            instructions();
        }
        else if (guess == 'Q' || guess == 'q'){
            break;
        }
        else if (guess == 'P' || guess == 'p'){
            play();
        }
        else if (guess == 'S' || guess == 's'){
            settingsAccess();
        }
        else{
            std::cout << "Invalid input!!! Try again." << std::endl;
            pauseProgram();
        }
    }
    // If the user wanted to quit, the loop will break and goodbye() will trigger
    goodbye();
}

// Purpose: Outputs the instructions of the game to the user
void instructions(){
    system("cls");
    std::cout << "Instructions: " << std::endl;
    std::cout << "\n\t1. You will have to guess letters to try and complete the word hidden under the stars." << std::endl;
    std::cout << "\n\t2. If there are multiple instances of the same letter, they all are revealed upon guessing." << std::endl;
    std::cout << "\n\t3. Any incorrect guess deducts a life, once all lives are depleted, the game ends." << std::endl;
    std::cout << "\n\t4. If you guess the word before losing all your lives, you can move to a new word with your remaining lives.\n" << std::endl;
    pauseProgram(); // pauses the program so the user can control when they wish to continue back the menu
}

// Purpose: Pauses the entire program by asking for user input to continue
void pauseProgram(){
    char click;

    std::cout << "Enter any key to continue!" << std::endl;
    click = getch();
    fflush(stdin);
}

// Purpose: Outputs welcome message and asks to continue
void welcome(){

    std::cout << "Welcome to Binary Hangman!!!" << std::endl;
    pauseProgram();
}

// Purpose: Outputs goodbye message
void goodbye(){
    system("cls");
    std::cout << "Goodbye! We hope you had fun!!!" << std::endl;
}