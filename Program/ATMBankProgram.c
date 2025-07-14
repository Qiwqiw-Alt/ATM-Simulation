#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    long long acc_number;
    int pin;
    long long balance;
} Bank_ABD;

typedef struct {
    long long acc_number;
    long long balance;
} other_Bank;

Bank_ABD ABD [] = {
    {2662095984, 51273, 1000000}, {4989309257, 62739, 500000},  {6472506749, 34857, 750000},
    {2464710477, 38025, 550000}, {6685147553, 15649, 1500000}, {2677761013, 90416, 600000},
    {6685147553, 73264, 700000}, {2677761013, 51928, 720000}, {7081537032, 84197, 980000}
};

other_Bank OHIO [] = {
    {1012421956, 1000000}, {1164126826, 1500000}, {7339036500, 735000},
    {940546860, 1250000}, {5733839894, 1000000}, {8360084590, 800000},
    {6203428904, 2000000}, {9451316769, 900000}, {1451471948, 1700000} 
};

other_Bank BSS [] = {
    {1131605022, 1000000}, {9396006086, 500000}, {6883288403, 750000},
    {1145789910, 550000}, {1145789910, 1500000}, {8517780672, 600000},
    {1172682446, 700000}, {3021533963, 720000}, {1035581044, 900000}
};

other_Bank BCD [] = {
    {3069517149, 1000000}, {5474727503, 1500000}, {6486962259, 735000},
    {8738544965, 765000}, {5404953180, 125000}, {3427836322, 100000},
    {7992174082, 800000}, {8963187799, 900000}, {6945792397, 2000000},
};

other_Bank BII [] = {
    {2670841659, 100000}, {3217959896, 500000}, {1763918290, 750000},
    {9151626329, 550000}, {3016684703, 150000}, {9881700983, 600000},
    {8688908526, 700000}, {9918244045, 720000}, {1972438485, 980000},
};

other_Bank AirBank [] = {
    {5757435103, 1000000}, {6590952392, 1500000}, {6693575415, 735000},
    {5181295103, 765000}, {7199363140, 125000}, {5104542019, 100000},
    {4925221703, 800000}, {7348708837, 900000}, {9138263532, 2000000}
};

int size = sizeof(ABD) / sizeof(ABD[0]);
int active_account_idx = -1;
int login_chance = 3;

void login();
void menu();
void cashWithdrawal();
void balanceInquiry();
void fundsTransfer();
void transferOtherBank();
void transferOtherBankHelper(other_Bank Bank[], const char* bank_name, int transfer_fee);
void cashDeposit();
char* current_time();
void printHeader(const char* bank_name);
void waiting_time(int seconds);
void thanks();

void thanks(){
    printf("===================================================================================================================\n");
    printf("=                                       THANKS FOR USING ABD BANK SERVICE                                         =\n");                                                                                                                                                                                                                                                                                                                            
    printf("===================================================================================================================\n");
    Sleep(3000);
    system("cls");
}

void printHeader(const char* bank_name) {
    int total_width = 119;
    char middle[100];

    sprintf(middle, "Transfer to %s", bank_name);

    int len = strlen(middle);
    int padding = (total_width - 2 - len) / 2; 

    printf("===================================================================================================================\n");
    printf("= %*s%-*s =\n", padding, "", total_width - 2 - padding, middle);
    printf("===================================================================================================================\n");
}

char* current_time(){
    time_t current_time;
    struct tm *time_info;
    static char time_str[100];

    time(&current_time);

    time_info = localtime(&current_time);

    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);

    return time_str;
}

void waiting_time(int seconds){
    if(seconds <= 0) {
        return;
    }
    printf("You can try to login agan after %d seconds n \n", seconds - 1);
    Sleep(1000);   
    waiting_time(seconds - 1);
}

void login(){
    long long acc_number_active;
    int pin_active;
    bool verification = false;

    do {
        printf("===================================================================================================================\n");
        printf("=                                              WELCOME TO ABD BANK                                                =\n");                                                                                                                                                                                                                                                                                                                            
        printf("===================================================================================================================\n");
        
        printf("\nInput account number: "); scanf("%lld", &acc_number_active);
        printf("Input account pin   : "); scanf("%d", &pin_active);

        printf("===================================================================================================================\n");

        for(int i = 0; i < size; i++){
            if(acc_number_active == ABD[i].acc_number && pin_active == ABD[i].pin){
                verification = true;
                active_account_idx = i;
                system("cls");
                menu();
                break;
            }
        }

        printf("\nPlease input the correct account number and pin, you have %d chance again before we give you penalty", --login_chance);
        Sleep(3000);
        system("cls");
        if(login_chance == 0){
            waiting_time(60);
            login_chance = 3;
            system("cls");
        }
    } while (!verification);
}

void menu(){
    int choice;

    do {
        printf("===================================================================================================================\n");
        printf("=                                                   MENU                                                          =\n");
        printf("===================================================================================================================\n");
        printf("= 1. Cash Withdrawal                                                                                              =\n");
        printf("= 2. Balance Inquiry                                                                                              =\n");
        printf("= 3. Funds Trnasfer                                                                                               =\n");
        printf("= 4. Transfer to Other Bank                                                                                       =\n");
        printf("= 5. Cash Deposit                                                                                                 =\n");
        printf("= 6. Logout                                                                                                       =\n");
        printf("===================================================================================================================\n");
        printf("\nInput the menu number you want use: "); scanf("%d", &choice);

        switch (choice){
            case 1: system("cls"); cashWithdrawal(); break;
            case 2: system("cls"); balanceInquiry(); break;
            case 3: system("cls"); fundsTransfer(); break;
            case 4: system("cls"); transferOtherBank(); break;
            case 5: system("cls"); cashDeposit(); break;
            case 6: system("cls"); thanks(); login(); break;
            default:
                printf("\n The menu number is not found, please input the correct number");
                Sleep(3000);
                system("cls");
                break;
        }
    } while(choice < 1 || choice > 5);
}

void cashWithdrawal(){
    char verification;
    int choice;
    int cash;

    do {
        printf("===================================================================================================================\n");
        printf("=                                             Cash Withdrawal                                                     =\n");
        printf("===================================================================================================================\n");
        printf("= 1. Rp 100.000                                                                                                   =\n");
        printf("= 2. Rp 500.000                                                                                                   =\n");
        printf("= 3. Rp 1.000.000                                                                                                 =\n");
        printf("= 4. Rp 1.500.000                                                                                                 =\n");
        printf("= 5. Rp 2.000.000                                                                                                 =\n");
        printf("= 6. Rp 2.500.000                                                                                                 =\n");
        printf("= 7. Cancel                                                                                                       =\n");
        printf("===================================================================================================================\n");
        printf("\nInput the menu number you want use: "); scanf("%d", &choice);

        switch (choice){
            case 1: cash = 100000; break;
            case 2: cash = 500000; break;
            case 3: cash = 1000000; break;
            case 4: cash = 1500000; break;
            case 5: cash = 2000000; break;
            case 6: cash = 2500000; break;
            case 7: system("cls"); menu(); break;
            default:
                printf("\n The menu number is not found, please input the correct number\n");
                Sleep(3000);
                system("cls");
                break;
        }
    }while(choice < 1 || choice > 7);

    if(ABD[active_account_idx].balance < cash) {
        printf("Your balance is not enough, your balance is Rp %lld", ABD[active_account_idx].balance);
        do {
            printf("Do you want try another transaction (Y/N)?: "); scanf(" %c", &verification);

            if(verification == 'Y' || verification == 'y'){
                system("cls");
                menu();
            }
            else if(verification == 'N' || verification == 'n'){
                system("cls");
                thanks();
                login();
            }
            else {
                printf("Please input the correct answer (Y/N)!\n");
                Sleep(3000);
                system("cls");
            }
        } while(verification != 'Y' && verification != 'y' && verification != 'N' && verification != 'n');
    }
    else {
        ABD[active_account_idx].balance -= cash;
        printf("Withdrawal succes, your balance now is Rp %lld", ABD[active_account_idx].balance);
        do {
            printf("\nDo you want try another transaction (Y/N)?: "); scanf(" %c", &verification);

            if(verification == 'Y' || verification == 'y'){
                system("cls");
                menu();
            }
            else if(verification == 'N' || verification == 'n'){
                system("cls");
                thanks();
                login();
            }
            else {
                printf("Please input the correct answer (Y/N)!\n");
                Sleep(3000);
                system("cls");
            }
        } while(verification != 'Y' && verification != 'y' && verification != 'N' && verification != 'n');
    }
}

void balanceInquiry(){
    char time_now[100]; strcpy(time_now, current_time());
    char verification;
    do {
        printf("===================================================================================================================\n");
        printf("=                                             Balance Inquiry                                                     =\n");
        printf("===================================================================================================================\n");
        printf("Time acces: %s\n", time_now);
        printf("===================================================================================================================\n");
        printf("Your balance is: Rp %lld\n", ABD[active_account_idx].balance);
        printf("===================================================================================================================\n");

        printf("\nDo you want to back to menu (Y/N)?: "); scanf(" %c", &verification);
        
        if(verification == 'Y' || verification == 'y'){
            system("cls");
            menu();
        }
        else if(verification == 'N' || verification == 'n'){
            system("cls");
            thanks();
            login();
        }
        else {
            printf("Please input the correct answer (Y/N)!\n");
            Sleep(3000);
            system("cls");
        }
    } while(verification != 'Y' && verification != 'y' && verification != 'N' && verification != 'n');
}

void fundsTransfer(){
    long long d_account_number;
    long long amount_of_money;
    int account_active_pin;
    int d_account_idx;
    bool d_account_verif = false;
    bool acc_active_pin_verif = false;
    char verification;

    do {
        d_account_verif = false;
        acc_active_pin_verif = false;

        printf("===================================================================================================================\n");
        printf("=                                             Funds Transfer                                                      =\n");
        printf("===================================================================================================================\n");
        printf("\nPlease enter destination account number: "); scanf("%lld", &d_account_number);

        for(int i = 0; i < size; i++){
            if(d_account_number == ABD[i].acc_number){
                d_account_verif = true;
                d_account_idx = i;
                break;
            }
        }

        printf("Please enter amount of money: "); scanf("%lld", &amount_of_money);
        printf("Enter your pin: "); scanf("%d", &account_active_pin);

        if(account_active_pin == ABD[active_account_idx].pin) {
            acc_active_pin_verif = true;
        }

        if(acc_active_pin_verif && d_account_verif){
            if(ABD[active_account_idx].balance < amount_of_money){
                printf("Your balance is not enough, your balance is Rp %lld\n", ABD[active_account_idx].balance);
                do {
                    printf("\nDo you want try another transaction (Y/N)?: "); scanf(" %c", &verification);

                    if(verification == 'Y' || verification == 'y'){
                        system("cls");
                        menu();
                    }
                    else if(verification == 'N' || verification == 'n'){
                        system("cls");
                        thanks();
                        login();
                    }
                    else {
                        printf("Please input the correct answer (Y/N)!\n");
                        Sleep(3000);
                        system("cls");
                    }
                } while(verification != 'Y' && verification != 'y' && verification != 'N' && verification != 'n');
            }
            else {
                ABD[d_account_idx].balance += amount_of_money;
                ABD[active_account_idx].balance -= amount_of_money;
                printf("Transfer succes, your balance now is Rp %lld\n", ABD[active_account_idx].balance);
                do {
                    printf("Do you want to back to menu (Y/N)?: "); scanf(" %c", &verification);

                    if(verification == 'Y' || verification == 'y'){
                        system("cls");
                        menu();
                    }
                    else if(verification == 'N' || verification == 'n'){
                        system("cls");
                        thanks();
                        login();
                    }
                    else {
                        printf("Please input the correct answer (Y/N)!\n");
                        Sleep(3000);
                        system("cls");
                    }
                } while (verification != 'Y' && verification != 'y' && verification != 'N' && verification != 'n');
            }
        }
        else {
            if(!d_account_verif){
                printf("Your destination account number is not found, please input the correct account number\n");
            }
            else if(!acc_active_pin_verif){
                printf("Your pin is incorrect, please input the correct pin\n");
            }
            else {
                printf("Your destination account number is not found and your pin is incorrect, please input the correct account number and pin\n");
            }
            Sleep(3000);
            system("cls");
        }
    } while(!d_account_verif || !acc_active_pin_verif);
}

void transferOtherBank(){
    int choice;
    do {
        printf("===================================================================================================================\n");
        printf("=                                        Transfer to Another Bank                                                 =\n");
        printf("===================================================================================================================\n");
        printf("= 1. OHIO Bank (Tarnsfer fee: Rp 2500)                                                                            =\n");
        printf("= 2. BSS Bank  (Tarnsfer fee: Rp 5000)                                                                            =\n");
        printf("= 3. BCD Bank  (Tarnsfer fee: Rp 7500)                                                                            =\n");
        printf("= 4. BII Bank  (Tarnsfer fee: Rp 10000)                                                                           =\n");
        printf("= 5. AirBank   (Tarnsfer fee: Rp 5000)                                                                            =\n");
        printf("= 6. Cancel                                                                                                       =\n");
        printf("===================================================================================================================\n");
        printf("\nInput the bank number you want to transfer: "); scanf("%d", &choice);

        switch (choice) {
            case 1: system("cls"); transferOtherBankHelper(OHIO, "Ohio Bank", 2500); break;
            case 2: system("cls"); transferOtherBankHelper(BSS, "BSS Bank", 5000); break;
            case 3: system("cls"); transferOtherBankHelper(BCD, "BCD Bank", 7500); break;
            case 4: system("cls"); transferOtherBankHelper(BII, "BII Bank", 10000); break;
            case 5: system("cls"); transferOtherBankHelper(AirBank, "AirBank", 5000); break;
            case 6: login(); break;
            default:
                printf("\n The menu number is not found, please input the correct number\n");
                system("cls");
                break;
        }
    } while(choice < 1 || choice > 6);
}

void transferOtherBankHelper(other_Bank Bank[], const char* bank_name, int transfer_fee){
    long long d_account_number;
    long long amount_of_money;
    int account_active_pin;
    int d_account_idx;
    bool d_account_verif = false;
    bool acc_active_pin_verif = false;
    char verification;

    do {
        d_account_verif = false;
        acc_active_pin_verif = false;

        printHeader(bank_name);
        printf("Please enter destination account number: "); scanf("%lld", &d_account_number);

        for(int i = 0; i < size; i++){
            if(d_account_number == Bank[i].acc_number){
                d_account_verif = true;
                d_account_idx = i;
                break;
            }
        }

        printf("Please enter amount of money: "); scanf("%lld", &amount_of_money);
        printf("Enter your pin: "); scanf("%d", &account_active_pin);

        if(account_active_pin == ABD[active_account_idx].pin) {
            acc_active_pin_verif = true;
        }

        if(acc_active_pin_verif && d_account_verif){
            if(ABD[active_account_idx].balance < (amount_of_money + transfer_fee)){
                printf("Your balance is not enough, your balance is Rp %lld\n", ABD[active_account_idx].balance);
                do {
                    printf("\nDo you want try another transaction (Y/N)?: "); scanf(" %c", &verification);

                    if(verification == 'Y' || verification == 'y'){
                        system("cls");
                        menu();
                    }
                    else if(verification == 'N' || verification == 'n'){
                        system("cls");
                        thanks();
                        login();
                    }
                    else {
                        printf("Please input the correct answer (Y/N)!\n");
                        Sleep(3000);
                        system("cls");
                    }
                } while(verification != 'Y' && verification != 'y' && verification != 'N' && verification != 'n');
            }
            else {
                Bank[d_account_idx].balance += amount_of_money;
                ABD[active_account_idx].balance -= (amount_of_money + transfer_fee);
                printf("Transfer succes, your balance now is Rp %lld\n", ABD[active_account_idx].balance);
                do {
                     printf("Do you want to back to menu (Y/N)?: "); scanf(" %c", &verification);

                     if(verification == 'Y' || verification == 'y'){
                        system("cls");
                        menu();
                    }
                    else if(verification == 'N' || verification == 'n'){
                        system("cls");
                        thanks();
                        login();
                    }
                    else {
                        printf("Please input the correct answer (Y/N)!\n");
                        Sleep(3000);
                        system("cls");
                    }
                } while (verification != 'Y' && verification != 'y' && verification != 'N' && verification != 'n');
            }
        }
        else {
            if(!d_account_verif){
                printf("Your destination account number is not found, please input the correct account number\n");
            }
            else if(!acc_active_pin_verif){
                printf("Your pin is incorrect, please input the correct pin\n");
            }
            else {
                printf("Your destination account number is not found and your pin is incorrect, please input the correct account number and pin\n");
            }
            Sleep(3000);
            system("cls");
        }
    } while(!d_account_verif || !acc_active_pin_verif);
}

void cashDeposit(){
    char verification;
    long long amount_of_money;

    do {
        printf("===================================================================================================================\n");
        printf("=                                                 Cash Deposit                                                    =\n");
        printf("===================================================================================================================\n");
        printf("Input amount of money you want to deposit: "); scanf("%lld", &amount_of_money);
        ABD[active_account_idx].balance += amount_of_money;
        printf("====================================================================================================================\n");
        printf("Your balanace now is: Rp %lld\n", ABD[active_account_idx].balance);
        printf("====================================================================================================================\n");

        printf("\nDo you want to back to menu (Y/N)?: "); scanf(" %c", &verification);
        
        if(verification == 'Y' || verification == 'y'){
            system("cls");
            menu();
        }
        else if(verification == 'N' || verification == 'n'){
            system("cls");
            thanks();
            login();
        }
        else {
            printf("Please input the correct answer (Y/N)!\n");
            Sleep(3000);
            system("cls");
        }
    } while(verification != 'Y' && verification != 'y' && verification != 'N' && verification != 'n');
}

int main(){
    login();
    return 0;
}