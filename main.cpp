
#include <iostream>
#include <string>
#include <vector>

int* transformToBasic(std::vector<std::int16_t> playerHand);
void printPointer(int* ptr);

int main()
{
    // Set up and initialize a few presets
    std::string people[6] = {"Mr. Green", "Professor Plum", "Ms. Scarlet", "Mrs. White", "Mrs. Peacock", "Colonel Mustard"};
    std::string weapons1[6] = {"Candlestick", "Rope", "Knife", "Wrench", "Lead Pipe", "Revolver"};
    std::string locations1[9] = {"Kitchen", "Dining Room", "Hall", "Study", "Lounge", "Library", "Billiard Room", "Conservatory", "Ballroom"};
    std::string weapons2[6] = { "Candlestick", "Rope", "Knife", "Poison", "Pistol", "Dumbbell" };
    std::string locations2[9] = { "Kitchen", "Dining Room", "Hall", "Patio", "Observatory", "Living Room", "Theater", "Spa", "Guest House" };
    std::int8_t preset = 0;

    // Get information from user
    std::cout << "Welcome to your Clue helper! Before I can help you, I need some information. How many players are there excluding yourself?\n";
    std::string inputLine;
    getline(std::cin, inputLine);
    std::int8_t numPlayers = stoi(inputLine);
    if (numPlayers < 2 || numPlayers > 5) {
        inputLine = "";
        std::cout << "Invalid number of players. Please re-enter the number of players:\n";
        getline(std::cin, inputLine);
        numPlayers = stoi(inputLine);
    }
    std::vector<std::string> players;
    std::vector<std::int8_t> numCards;
    std::cout << "Please enter the players in the order they are seated after you. ";
    for (int i = 1; i < numPlayers+1; i++) {
        inputLine = "";
        std::cout << "What is the name of player " << i << "?\n";
        getline(std::cin, inputLine);
        players.push_back(inputLine);
        std::cout << "How many cards does " << inputLine << " have?\n";
        inputLine = "";
        getline(std::cin, inputLine);
        std::int8_t cards = stoi(inputLine);
        numCards.push_back(cards);
        //std::cout << inputLine << std::endl;
    }
    std::int8_t isDone = 0;
    std::cout << "Which preset would you like to use? Classic(0) or Ours(1)? Enter the number for the corresponding preset.\n";
    inputLine = "";
    getline(std::cin, inputLine);
    // Prints out the options for the card preset the user chose
    std::int16_t itemNumber = 0;
    if (stoi(inputLine) == 0) {
        for (int i = 0; i < 6; i++) {
            std::cout << weapons1[i] << " : " << itemNumber << std::endl;
            itemNumber++;
        }
        for (int i = 0; i < 9; i++) {
            std::cout << locations1[i] << " : " << itemNumber << std::endl;
            itemNumber++;
        }
    }
    else {
        preset = 1;
        for (int i = 0; i < 6; i++) {
            std::cout << weapons2[i] << " : " << itemNumber << std::endl;
            itemNumber++;
        }
        for (int i = 0; i < 9; i++) {
            std::cout << locations2[i] << " : " << itemNumber << std::endl;
            itemNumber++;
        }
    }
    for (int i = 0; i < 6; i++) {
        std::cout << people[i] << " : " << itemNumber << std::endl;
        itemNumber++;
    }
    // Gathers the player's hand information
    std::vector<std::int16_t> playerHand;
    std::cout << "Enter your hand one card at a time. Type the number corresponding to a card you have, and then hit enter between each card. When finished, type \"Done\" then enter\n";
    while (isDone != 1) {
        inputLine = "";
        getline(std::cin, inputLine);
        if (inputLine != "Done" && inputLine != "Done " && inputLine != "done" && inputLine != "done " && inputLine != "") {
            // 1 for they have it, 0 they don't have it, -1 for we don't know. 
            std::int16_t itemNum = stoi(inputLine);
            playerHand.push_back(itemNum);
        }
        else {
            isDone = 1;
        }
    }
    int* ptr = transformToBasic(playerHand);
    // Print out the matrix to see if everything was put in correctly
    printPointer(ptr);


    // Now the main loop to gather turn information or queries
    std::int16_t finished = 0;
    while (finished == 0) {
        std::cout << "\nChoose an option: \n 0: Input information from a suggestion \n 1: Ask for a suggestion\n";
        inputLine = "";
        getline(std::cin, inputLine);
        int option = stoi(inputLine);
        if (option == 1) {
            std::cout << "Formulating a good suggestion...\n";
            // TODO: Run Joel's function
            // TODO: Print out the suggestion from his function
            continue;
        } else {
            std::cout << "Which cards were suggested? Enter them one at a time like before.\n";
            int num = 0;
            int items[3];
            while (num < 3) {
                inputLine = "";
                getline(std::cin, inputLine);
                int tempNum = stoi(inputLine);
                if (tempNum < 0 || tempNum > 20) {
                    std::cout << "Invalid card number. Try again.\n";
                    continue;
                }
                items[num] = tempNum;
                num++;
            }
            std::cout << "Did you give the suggestion?\n";
            inputLine = "";
            getline(std::cin, inputLine);
            // This top section is for the player suggestion
            if (inputLine == "yes" || inputLine == "Yes") {
                std::cout << "Who showed you a card? (Enter \"None\" if no one helped)\n";
                inputLine = "";
                getline(std::cin, inputLine);
                int i = 0;
                // This is for a player helping them
                if (inputLine != "None" && inputLine != "none") {
                    for (; i < players.size(); i++) {
                        if (players[i] == inputLine) {
                            break;
                        }
                    }
                    if (i == players.size()) {
                        std::cout << "Could not find player. Try again.\n";
                        continue;
                    }
                    std::cout << "Which card was it?\n";
                    inputLine = "";
                    getline(std::cin, inputLine);
                    int card = stoi(inputLine);
                    std::cout << i << std::endl;
                    for (int j = 0; j < i; j++) {
                        ptr[(items[0] * 6) + j + 1] = 0;
                        ptr[(items[1] * 6) + j + 1] = 0;
                        ptr[(items[2] * 6) + j + 1] = 0;
                    }
                    for (int j = 0; j < 5; j++) {
                        if (j == i) {
                            ptr[(card * 6) + i + 1] = 1;
                        }
                        else {
                            ptr[(card * 6) + (j + 1)] = 0;
                        }
                    }
                }
                // This is for no one helping them.
                else {
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 5; j++) {
                            ptr[(items[i] * 6) + j + 1] = 0;
                        }
                    }
                }
            }
            // This section is for if another player gives a suggestion
            else {
                std::cout << "Which player gave the suggestion?\n";
                inputLine = "";
                getline(std::cin, inputLine);
                int sugPlayer = 0;
                for (; sugPlayer < players.size(); sugPlayer++) {
                    if (players[sugPlayer] == inputLine) {
                        break;
                    }
                }
                if (sugPlayer == players.size()) {
                    std::cout << "Could not find player. Try again.\n";
                    continue;
                }
                std::cout << "Who gave a card? (Enter \"None\" if no one helped)\n";
                inputLine = "";
                getline(std::cin, inputLine);
                // This is someone (including the player) helping the other player's suggestion
                if (inputLine != "None" && inputLine != "none") {
                    int cardPlayer = 0;
                    for (; cardPlayer < players.size(); cardPlayer++) {
                        if (players[cardPlayer] == inputLine) {
                            break;
                        }
                    }
                    if (inputLine == "me" || inputLine == "Me") {
                        cardPlayer = -1;
                    }
                    if (cardPlayer == players.size()) {
                        std::cout << "Could not find player. Try again.\n";
                        continue;
                    }
                    for (int j = 1; j < 5; j++) {
                        int playerNum = sugPlayer + j;
                        if (sugPlayer + j > numPlayers) {
                            playerNum = (sugPlayer + j) - numPlayers;
                        }
                        if (playerNum == cardPlayer) {
                            break;
                        }
                        ptr[(items[0] * 6) + playerNum] = 0;
                        ptr[(items[1] * 6) + playerNum] = 0;
                        ptr[(items[2] * 6) + playerNum] = 0;
                    }
                    // Nothing else cause just mark the cards that people do not have
                }
                // This if for if no one helps that one player
                else {
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 5; j++) {
                            if (ptr[(items[i] * 6) + j + 1] != 1) {
                                ptr[(items[i] * 6) + j + 1] = 0;
                            }
                        }
                    }
                }
            }
            std::cout << "Recorded.\n";
            printPointer(ptr);
        }
        
        std::cout << "If you are finished with the game, type \"Done\". If not, hit enter.\n";
        inputLine = "";
        getline(std::cin, inputLine);
        if (inputLine == "Done" || inputLine == "done") {
            finished = 1;
        }
    }
    
    // End program
    std::cout << "Did you win?\n";
    inputLine = "";
    getline(std::cin, inputLine);
    if (inputLine == "Yes" || inputLine == "yes") {
        std::cout << "Congratulations!";
    }
    else {
        std::cout << "Try Again Next Time";
    }
}

// This function fills out the clue card with what the player has and initiallizes the unkown card rows
int* transformToBasic(std::vector<std::int16_t> playerHand) {
    static int basic[21][6];
    for (int i = 0; i < playerHand.size(); i++) {
        //std::cout << "Has row: " << playerHand[i] << std::endl;
        basic[playerHand[i]][0] = 1;
        basic[playerHand[i]][1] = 0;
        basic[playerHand[i]][2] = 0;
        basic[playerHand[i]][3] = 0;
        basic[playerHand[i]][4] = 0;
        basic[playerHand[i]][5] = 0;
    }
    int i = 0;
    while (i < 21) {
        if (basic[i][0] != 1) {
            //std::cout << "Doesn't have row: " << i << std::endl;
            basic[i][0] = 0;
            basic[i][1] = -1;
            basic[i][2] = -1;
            basic[i][3] = -1;
            basic[i][4] = -1;
            basic[i][5] = -1;
        }
        i++;
    }
    // For printing out
    /*for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 6; j++) {
            std::cout << basic[i][j] << " ";
        }
        std::cout << std::endl;
    }*/
    return *basic;
}

// Prints out the matrix from the pointer reference we have
void printPointer(int* ptr) {
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 6; j++) {
            std::cout << ptr[(i * 6) + j] << " ";
        }
        std::cout << std::endl;
    }
}