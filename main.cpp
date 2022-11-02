#include <iostream>
#include <string>
#include <windows.h>

std::string card[13] =
        {"2","3","4","5","6","7","8","9","10","J","Q","K","A"},
        simbol[4] = {"\u2665","\u2666","\u2660","\u2663"},
        dealers_hand[10][4], players_hand[10][4],
        space = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n",
        rules ="Rules:\nTry to get as close to 21 without going over.\nKings, Queens, and Jacks are worth 10 points.\nAces are worth 1 or 11 points.\nCards 2 through 10 are worth their face value.\n(H)it to take another card.\n(S)tand to stop taking cards.\nOn your first play, you can (D)ouble down to increase your bet\nbut must hit exactly one more time before standing.\nIn case of a tie, the bet is returned to the player.\nThe dealer stops hitting at 17.",
        back_side[4] = {
        " ___  ",
        "|## | ",
        "|###| ",
        "|_##| "},
        choice;

int dealers_num[10], players_num[10],
cards, rows = 4, dd = 1,
players_cards = 2, dealers_cards = 2,
players_count = 0, dealers_count = 0;

double players_money = 0, bet = 0;

void deposit(){
    std::cout<<"How much would you like to deposit?"<<std::endl;
    std::cout<<"$ ";
    std::cin>>players_money;
}

void game_bet(){
    std::cout<<"Bet: ";
    std::cin>>bet;
    players_money -= bet;
}

void dealers_hit(){
    while(17>=dealers_count){
        std::cout << space;
        std::cout << rules << std::endl;
        dealers_count = 0;
        for (int u = 0; dealers_cards > u; u++) {
            dealers_count += dealers_num[u];
        }
        for (int p = 0; rows > p; p++) {
            std::cout << "\n";
            for (int a = 0; dealers_cards > a; a++) {
                std::cout << dealers_hand[a][p];
            }
        }
        std::cout << "\nDealers hand >> " << dealers_count << std::endl;
        dealers_cards++;

        for (int s = 0; rows > s; s++) {
            std::cout << "\n";
            for (int f = 0; players_cards > f; f++) {
                std::cout << players_hand[f][s];
            }
        }
        std::cout << "\n\nPlayers hand >> " << players_count << std::endl;
        std::cout << "\nPress to continue >> ";
        std::cin.ignore(1);
        std::cin.get();
    }
    if(dealers_count>players_count && dealers_count<=21){
        std::cout<<"Dealer wins!"<<std::endl;
    }
    else if(dealers_count==players_count){
        if(dealers_count<=21 && players_count<=21){
            std::cout<<"Push!"<<std::endl;
            players_money += bet;
        }
        else{
            std::cout<<"House wins!"<<std::endl;
        }
    }
    else if(21<players_count){
        std::cout<<"You busted!"<<std::endl;
    }
    else{
        std::cout<<"You win!"<<std::endl;
        players_money += (bet*2);
    }
}

void players_hit(){
    std::cout << space;
    std::cout<<rules<<std::endl;
    cards = 1;
    for (int e = 0; rows > e; e++) {
        std::cout << "\n";
        dealers_count = +dealers_num[0];
        for (int r = 0; cards > r; r++) {
            std::cout << dealers_hand[r++][e] << back_side[e];
        }
    }
    std::cout << "\nDealers hand >> " << dealers_count << std::endl;
    players_count = 0;

    for(int y=0; players_cards>y; y++){
        players_count += players_num[y];
    }
    for (int q = 0; rows > q; q++) {
        std::cout << "\n";
        for (int w = 0; players_cards > w; w++) {
            std::cout << players_hand[w][q];
        }
    }
    std::cout << "\n\nPlayers hand >> " << players_count << std::endl;

    if(players_count == 21 && players_cards == 2){
        std::cout << "Blackjack!" << std::endl;
        dealers_hit();
    }
    else if(players_count > 21){
        dealers_hit();
    }
    else{
        if(dd == 0){
                dealers_hit();
        }
        else if(dd == 1){
            std::cout << "\n(H)it, (S)tand, (D)ouble down >> ";
            std::cin >> choice;

            if (choice == "H" || choice == "h"){
                dd++;
                players_cards++;
                players_hit();
            }
            else if (choice == "D" || choice == "d"){
                dd--;
                players_money -= bet;
                2*bet;
                players_cards++;
                players_hit();
            }
            else {
                dealers_hit();
            }
        }
        else{
            std::cout << "\n(H)it, (S)tand >> ";
            std::cin >> choice;

            if (choice == "H" || choice == "h"){
                players_cards++;
                players_hit();
            }
        }
    }
}

void blackjack(){
    game_bet();

    for(int i=0; 10>i; i++){
        std::string num = card[rand() % 13];
        if(num == "J" || num == "Q" || num == "K"){
            dealers_num[i] = 10;
        }
        else if(num == "A"){
            dealers_num[i] = 11;
        }
        else{
            dealers_num[i] = std::stoi(num);
        }
        if (num == "10"){
            dealers_hand[i][0] = " ___  ";
            dealers_hand[i][1] = "|"+num+" | ";
            dealers_hand[i][2] = "| "+simbol[rand() % 4]+" | ";
            dealers_hand[i][3] = "|_"+num+"| ";
        }
        else {
            dealers_hand[i][0] = " ___  ";
            dealers_hand[i][1] = "|" + num + "  | ";
            dealers_hand[i][2] = "| " + simbol[rand() % 4] + " | ";
            dealers_hand[i][3] = "|__" + num + "| ";
        }
    }

    for(int x=0; 10>x; x++){
        std::string num = card[rand() % 13];
        if(num == "J" || num == "Q" || num == "K"){
            players_num[x] = 10;
        }
        else if(num == "A"){
            players_num[x] = 11;
        }
        else{
            players_num[x] = std::stoi(num);
        }
        if (num == "10") {
            players_hand[x][0] = " ___  ";
            players_hand[x][1] = "|" + num + " | ";
            players_hand[x][2] = "| " + simbol[rand() % 4] + " | ";
            players_hand[x][3] = "|_" + num + "| ";
        }
        else{
            players_hand[x][0] = " ___  ";
            players_hand[x][1] = "|" + num + "  | ";
            players_hand[x][2] = "| " + simbol[rand() % 4] + " | ";
            players_hand[x][3] = "|__" + num + "| ";
        }
    }

    players_hit();
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));
    std::cout << "Welcome to the Casino++!" << std::endl;
    deposit();
    std::cout << "We will play blackjack today!" << std::endl;
    do{ blackjack();
        std::cout << '\n' << "Casino account >> " << players_money << "$" << "\nPress (q)uit to exit or anything else to continue >> ";
    } while (std::cin.get() != 'q');

    return 0;
}
