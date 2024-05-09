#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define USER_MAX 50
#define BUS_MAX 30

//Regular text
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

//Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

//Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

//Regular background
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

//High intensty background 
#define BLKHB "\e[0;100m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define BLUHB "\e[0;104m"
#define MAGHB "\e[0;105m"
#define CYNHB "\e[0;106m"
#define WHTHB "\e[0;107m"

//High intensty text
#define HBLK "\e[0;90m"
#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HBLU "\e[0;94m"
#define HMAG "\e[0;95m"
#define HCYN "\e[0;96m"
#define HWHT "\e[0;97m"

//Bold high intensity text
#define BHBLK "\e[1;90m"
#define BHRED "\e[1;91m"
#define BHGRN "\e[1;92m"
#define BHYEL "\e[1;93m"
#define BHBLU "\e[1;94m"
#define BHMAG "\e[1;95m"
#define BHCYN "\e[1;96m"
#define BHWHT "\e[1;97m"

#define SLOW_BLINKING_RED  "\e[1;5;31m"
#define SLOW_BLINKING_CYAN  "\e[1;5;36m"

//Reset
#define reset "\e[0m"
#define CRESET "\e[0m"
#define COLOR_RESET "\e[0m"

#define hideCursor "\e[?25l"
#define defaultCursor "\e[?25h"

//Spacing 
#define busSpacing "                       " // for animated bus only

typedef struct user user;
typedef struct bus bus;

struct user {
    char fullName[30];
    char userName[20];
    char userPass[20];
    bool userGender; // 0 for men, 1 fo female
    int userAge;
    int userRole; // 1 for customer, 2 for executive, 3 for admin
    int userId;
};

//User Management
user id[USER_MAX] = { 
    {"Admin", "admin", "pass", false, 22, 3, 1},
    {"Hasib Hasnain", "hasib", "hasib", false, 22, 2, 2},
    {"Atikur Rahman", "rajib", "rajib", false, 22, 1, 3},
    {"Sarowar Mahfuz", "suman", "suman", false, 22, 1, 4}
};
int countUser = 4;
int $myUserId = 0;


//Bus Section
struct bus {
    char busName[20];
    char boardingPoint[20];
    char droppingPoint[20];
    char boardingTime[10];
    int seatNumber;
    bool coachType; // 0 non ac, 1 ac
    int ticketPrice;
    int coachId;
    int seatList[99];
};

//Bus Management
bus coach[BUS_MAX] = {
    {"Safar", "Dhaka", "Rajshahi", "8:00am", 57, 0, 700, 1, {0}}, 
    {"Jatra", "Dhaka", "Khulna", "9:00am", 41, 1, 1600, 2, {0}},
    {"Zatri", "Dhaka", "Chattagram", "9:00am", 41, 1, 1800, 3, {0}},
    {"Pother Sur","Dhaka", "Shylet", "10:00am", 41, 0, 1300, 4, {0}},
    {"Meghdut","Dhaka", "Chapai", "10:00am", 41, 0, 1000, 5, {0}},
    {"Pother Sathi","Dhaka", "Srimangal", "10:330am", 41, 1, 1150, 6, {0}},
    {"POtho Bondhhu","Dhaka", "Dinajpur", "11:00am", 41, 1, 900, 7, {0}},
    {"Mridu Goti","Dhaka", "Rajshahi", "10:30am", 41, 0, 400, 8, {0}},
    {"Shongi","Chapai", "Dhaka", "7:00pm", 41, 1, 900, 9, {0}},
    {"Akashpoth","Feni", "Bogura", "12:00pm", 41, 1, 700, 10, {0}},
    {"Shopnopothe","Rajshahi", "Rangpur", "11:30am", 41, 1, 1250, 11, {0}},
    {"Meghmala","Magura", "Naogoan", "8:00pm", 41, 0, 700, 12, {0}},
    {"Oronnopoth","Dhaka", "Pabna", "08:30pm", 41, 0, 400, 13, {0}},
    {"Gotidhara","Rajshahi", "Barishal", "09:00pm", 41, 1, 1400, 14, {0}},
    {"Songjogpoth","Dhaka", "Cumilla", "09:30pm", 41, 0, 900, 15, {0}},
    {"Choltipoth","Rajshahi", "Cox's Bazar", "10:00pm", 41, 1, 1600, 16, {0}},
    {"Chokro","Dhaka", "Jashore", "10:00am", 41, 0, 1000, 17, {0}},
    {"Prantore","Dhaka", "Narail", "10:20am", 41, 0, 550, 18, {0}},
    {"Panthopothe","Dhaka", "Magura", "11:45am", 41, 0, 1100, 19, {0}},
    {"Vromon","Bogura", "Feni", "10:00am", 41, 0, 1400, 20, {0}},
};
 
int countCoach = 20;
char getBusDepartFrom[20];
char getBusDestiTo[20];

//Default Home variables
bool lang = 0; // 0 for non english. 1 for bangla.


//Functions
void welcomeMsg();
void nonLogged_Menu();
void searchBus();
void ourBranches();
void contactUs();
void userManual();
void login();
void createAccount();
void customerMenu();
void executiveMenu();
void adminMenu();
void setBusSchedule();
void updateBusScedule();
void updateBusTicket();
void showBusSummary(); 
void cancelSeat();
void createNewProfiles(); 
void updateOtherProfiles(); 
void removeExistingProfiles(); 
void updateOwnProfile();
void logout();
void myBookedSeat();
void busDepartFrom();
void busDestiTo();
void busSchedule();
void buyTicket(int n);
int availableSeat(int s);
void seatPlan(int n);
void ifExit();
void forgetPassword();
void busAnimation();
void busLogo();
void returnToMenu();
const char* showGender(bool gender);
const char* showRole(int role);
const char* showCoachType(bool icoachType);
const char* showSeatStatus(int iseatStatus);


int main() {
    if($myUserId == 0) {
        nonLogged_Menu();
    } else {
        printf("Something went wrong!\n");
        exit(0);
    }
}

void busAnimation() {
    int i, j;
    int width = 5; // Width
    int steps = 10; // Number of steps
    printf(hideCursor);

    for (i = steps; i >= 0; i--) {
        // Clear the screen
        printf("\033[H\033[J");
        printf("\n\n\n");
        
        // Print the ASCII art with appropriate spacing for movement
        for (j = 0; j < i % width; j++) {
            printf(" ");
        }
        printf(busSpacing YEL "         _________________\n");
        for (j = 0; j < i % width; j++) {
            printf(" ");
        }
        printf(busSpacing "       /" BHBLK "|[][][][][][][][]" YEL " | " BHBLK "- -\n");
        for (j = 0; j < i % width; j++) {
            printf(" ");
        }
        printf(busSpacing YEL "      (    " BHYEL "DURNIBAR BUS" YEL "   | " BHBLK "- -\n");
        for (j = 0; j < i % width; j++) {
            printf(" ");
        }
        printf(busSpacing YEL "      =---" BHBLK "OO" YEL "---------" BHBLK "OO" YEL "---=" BHBLK "@@@\n\n" COLOR_RESET);
        
        // Sleep for a short duration to control the speed of movement
        usleep(200000); // 200 milliseconds
    }
    printf(defaultCursor);

}

void busLogo() {
    //10,8,7,7 spaces
    printf("\n\n\n\n");
    printf(YEL "         _________________\n");
    printf("       /" BHBLK "|[][][][][][][][]" YEL " | " BHBLK "- -\n");
    printf(YEL "      (    " BHYEL "DURNIBAR BUS" YEL "   | " BHBLK "- -\n");
    printf(YEL "      =---" BHBLK "OO" YEL "---------" BHBLK "OO" YEL "---=" BHBLK "@@@\n\n" COLOR_RESET);
}

void welcomeMsg() {
    if($myUserId == 0) {
        printf(BHWHT "            Hello User!\n");
        printf("        Welcome to our system!\n" COLOR_RESET);
    } else {
        printf(BHYEL "     Hello " BHGRN "%s, " BHYEL "an %s!\n", id[$myUserId-1].userName, showRole(id[$myUserId-1].userRole));
        printf(BHYEL "           Welcome Dear!\n" COLOR_RESET);
    }
}

void nonLogged_Menu() {
    busAnimation();
    system("cls");
    busLogo();
    welcomeMsg();
    int n;
    printf(WHTHB "\n            Main Menu             "reset);
    printf("\n");
    printf(HBLK "        [Choose an option]\n\n");
    printf(BHCYN "  1. Search Bus " SLOW_BLINKING_RED "FAST!\n" COLOR_RESET);
    printf(BHCYN "  2. Bus Schedule\n\n");
    printf("  3. Our Branches\n");
    printf("  4. Contact Us\n");
    printf("  5. User Manual\n\n");
    printf("  6. Login\n");
    printf("  7. Forget Password\n");
    printf("  8. Create an account " SLOW_BLINKING_RED "JOIN!\n\n" reset);
    printf(BHCYN "  [0] Exit\n" reset);
    printf("\n");
    printf(BHYEL "Choose a option: " COLOR_RESET);
    scanf("%d", &n);

    switch(n) {
        case 0: 
            ifExit();
        case 1: 
            searchBus();
            break;
        case 2: 
            busSchedule();
            break;
        case 3: 
            ourBranches();
            break;
        case 4: 
            contactUs();
            break;
        case 5: 
            userManual();
            break;
        case 6: 
            login();
            break;
        case 7: 
            forgetPassword();
            break;
        case 8:
            createAccount();
            break;
        default: 
            printf(BHRED "\n\nPlease try again\n\n" COLOR_RESET);
            system("pause");
            nonLogged_Menu();
            break;
    }
}

void login() {
    busAnimation();
    system("cls");
    char currName[20];
    char currPass[20];
    printf(WHTHB BHBLK "\n             Login Page             \n" COLOR_RESET);
    printf(HBLK"   [Write Username and Password]\n\n");
    printf(BHCYN "  Username: " COLOR_RESET);
    scanf("%s", currName);
    printf(BHCYN "  Password: " COLOR_RESET);
    scanf("%s", currPass);
    
    for(int i = 0; i < countUser; i++) {
        bool nameMatching = strcmp(currName, id[i].userName);

        if(nameMatching == 0){
            bool passMatching = strcmp(currPass, id[i].userPass);
            if(passMatching == 0) {
                printf(BHGRN "\n     Login Successfull!\n\n" COLOR_RESET);
                system("pause");
                $myUserId = i+1;
                if(id[i].userRole == 1) {
                    customerMenu();
                    break;
                } else if(id[i].userRole == 2) {
                    executiveMenu();
                    break;
                } else if(id[i].userRole == 3) {
                    adminMenu();
                    break;
                } else {
                    printf("\nThere is a problem with role\n\n");
                    break;
                }
            } 
            else {
                printf(BHRED "\nIncorrect Username or Password.\n\n" COLOR_RESET);
                int p;
                
                printf(BHWHT "Now what?\n");
                printf(BHCYN "1. Forget Password\n");
                printf("2. Create Account\n");
                printf("3. Return to Main Menu\n");
                printf("4. Try to login again\n\n" COLOR_RESET);
                printf(BHYEL "Choose an option: " COLOR_RESET);
                scanf("%d", &p);
                switch(p) {
                    case 1:
                        forgetPassword();
                        break;
                    case 2:
                        createAccount();
                        break;
                    case 3:
                        nonLogged_Menu();
                        break;
                    case 4: 
                        login();
                        break;
                    default:
                        printf(BHRED "\n\nWrong Keyword. Try again\n\n" COLOR_RESET);
                        system("pause");
                        login();
                        break;
                }
            }
        } 
        if (i == countUser-1) {
            printf(BHRED "\nIncorrect Username or Password. Try again\n\n" COLOR_RESET); 
            int q;
            printf(BHWHT "Now What? \n");
            printf(BHCYN "1. Forget Password\n");
            printf("2. Create Account\n");
            printf("3. Return to Main Menu\n");
            printf("4. Try again\n\n");
            printf(BHYEL "Choose an option: " COLOR_RESET);
            scanf("%d", &q);
            switch(q) {
                case 1:
                    forgetPassword();
                    break;
                case 2:
                    createAccount();
                    break;
                case 3:
                    nonLogged_Menu();
                    break;
                case 4: 
                    login();
                    break;
                default:
                    printf(BHRED "\n\nWrong Keyword. Try again\n\n" COLOR_RESET);
                    system("pause");
                    login();
                    break;
            }
        }
    }
}

void forgetPassword() {
    system("cls");
    printf("\n" WHTHB "            Main Menu             "reset);
    printf("\n\n");
    char stemp;
    int itemp;
    int store;
    int verify = 0;
    char currName[20];
    printf(BHCYN "  Username: " COLOR_RESET);
    scanf("%c", &stemp);
    scanf("%[^\n]", currName);
    for(int i = 0; i < countUser; i++) {
        bool nameMatching = strcmp(currName, id[i].userName);
        if(nameMatching == 0) {
            store = i + 1;
            verify++;
        }  
    }

    printf(BHCYN "  Fullname: " COLOR_RESET);
    scanf("%c", &stemp);
    scanf("%[^\n]", currName);
    bool nameMatching = strcmp(currName, id[store-1].fullName);
    if(nameMatching == 0) {
        verify++;
    }  

    printf(BHCYN "  Age: " COLOR_RESET);
    scanf("%d", &itemp);
    if(itemp == id[store-1].userAge) {
        verify++;
    }  

    if(verify == 3 && id[store-1].userRole == 1) {
        $myUserId = store;
        printf("\n\nYour provided informations are correct.\n");
        printf("\nYou are eligible for changing password.\n\n");
        printf("\n\nWrite new password: ");
        scanf("%c", &stemp);
        scanf("%[^\n]", id[$myUserId-1].userPass);
        printf("Password has been changed\n");
        printf("Please login now!\n");
        system("pause");
        login();
    } else {
        printf("\n\nSorry. Password can not be changed. Maybe your informations are wrong or you are trying to access admin panel in a wrong way...\n");
        system("pause");
        returnToMenu();
    }
}

void createAccount() {
    busAnimation();
    system("cls");
    char currName[20];
    char ctemp;
    bool nameMatching;
    printf(WHTHB BHBLK "             Create an account            \n" COLOR_RESET);
    printf(HBLK"     [Submit Correct Informantions]\n\n");
    countUser++;
    printf(BHCYN "Fullname: " COLOR_RESET);
    //scanf("%s", id[countUser-1].fullName);
    scanf("%c", &ctemp);
    scanf("%[^\n]", id[countUser-1].fullName);
    //fgets(id[countUser-1].fullName, 30, stdin);

    do{
        printf(BHCYN "Username (no space allowed): " COLOR_RESET);
        scanf("%s", currName);
        for(int i = 0; i < countUser; i++) {
            nameMatching = strcmp(currName, id[i].userName);

            if(nameMatching == 0){
                printf(BHRED "\n\n  Username isn't available!\n       Try Another one.\n\n" COLOR_RESET); 
                system("pause"); 
                break;          
            }
        }
    } while(nameMatching == 0);

    strcpy(id[countUser-1].userName, currName);
    printf(BHGRN "Username is available.\n" COLOR_RESET);
    printf(BHCYN "Password: " COLOR_RESET);
    scanf("%s", id[countUser-1].userPass);
    printf(BHCYN "Gender (0 for men, 1 for women): " COLOR_RESET);
    scanf("%d", &id[countUser-1].userGender);
    printf(BHCYN "Age: " COLOR_RESET);
    scanf("%d", &id[countUser-1].userAge);

    id[countUser-1].userRole = 1;
    id[countUser-1].userId = countUser;

    printf("\n\n");
    system("pause");
    system("cls");
    printf(BHGRN "\nAccount has been created!\n\n" COLOR_RESET);
    printf(BHYEL "Your Informations: \n");
    printf(BHCYN "Full name: %s \n", id[countUser-1].fullName);
    printf("Username: %s \n", id[countUser-1].userName);
    printf("Password: %s \n", id[countUser-1].userPass);
    printf("Gender: %s \n", showGender(id[countUser-1].userGender));
    printf("Age: %d \n", id[countUser-1].userAge);
    printf("Role: %s \n", showRole(id[countUser-1].userRole));
    printf("User ID: %d \n" COLOR_RESET, id[countUser-1].userId);

    printf(BHYEL "\nPlease login now.\n" COLOR_RESET);
    system("pause");
    login();
}

void updateOwnProfile() {
    system("cls");
    printf("\n== My Profile ==\n");
    printf("1. Full Name: %s\n", id[$myUserId-1].fullName);
    printf("2. Username: %s\n", id[$myUserId-1].userName);
    printf("3. Password: %s\n", id[$myUserId-1].userPass);
    printf("4. Gender: %s\n", showGender(id[$myUserId-1].userGender));
    printf("5. Age: %d\n", id[$myUserId-1].userAge);
    printf("Role: %s\n", showRole(id[$myUserId-1].userRole));
    printf("User ID: %d\n\n", id[$myUserId-1].userId);

    printf("Want to change profile? (yes = 1, no = 0): ");
    int n;
    scanf("%d", &n);
    
    system("pause");
}

void logout() {
    $myUserId = 0;
    printf( BHGRN "\nYou have logged out successfully...\n\n" COLOR_RESET);
    system("pause");
    system("cls");
    nonLogged_Menu();
}

void searchBus() {
    busAnimation();
    system("cls");
    printf(WHTHB BHBLK "           Bus Schedule           \n" COLOR_RESET);
    busDepartFrom();
    busDestiTo();
    printf(WHTHB BHBLK "           Bus Schedule           \n" COLOR_RESET);
    int temp = 0;
    printf(BHCYN "\n From: " YEL " %s " BHCYN " \tTo: " YEL " %s\n\n", getBusDepartFrom, getBusDestiTo);
    for(int i = 0; i < BUS_MAX; i++) {
        if(strcmp(coach[i].boardingPoint, getBusDepartFrom) == 0) {
            if(strcmp(coach[i].droppingPoint, getBusDestiTo) == 0) {
                printf(BHCYN "  Bus Name         :    " WHT "%-15s\n" COLOR_RESET, coach[i].busName);
                printf(BHCYN "  Boarding Point   :    " WHT "%-15s\n" COLOR_RESET, coach[i].boardingPoint);
                printf(BHCYN "  Dropping Point   :    " WHT "%-15s\n" COLOR_RESET, coach[i].droppingPoint);
                printf(BHCYN "  Boarding Time    :    " WHT "%-15s\n" COLOR_RESET, coach[i].boardingTime);
                printf(BHCYN "  Total Seat Num   :    " WHT "%-15d\n" COLOR_RESET, coach[i].seatNumber);
                printf(BHGRN "  Available Seat   :    %-15d\n" COLOR_RESET, availableSeat(coach[i].coachId));
                printf(BHCYN "  Coach Type       :    " WHT "%-15s\n" COLOR_RESET, showCoachType(coach[i].coachType));
                printf(BHRED "  Coach ID         :    %-15d\n" COLOR_RESET, coach[i].coachId);
                printf(CYN "  Ticket Price     :    " WHT "%-15d\n\n" COLOR_RESET, coach[i].ticketPrice);
                temp++;
            }
        }
    }
    if(temp==0) {
        printf( BHRED "\nSorry, we have no bus in this route :(\n\n" COLOR_RESET );
        system("pause");
        searchBus();
    }
    int n;
    printf( BHWHT "Enter Coach ID to buy a ticket.\n" BHRED "* Place '0' to go back.\n\n" COLOR_RESET);
    printf(BHYEL "Enter your choice: " COLOR_RESET);
    scanf("%d", &n);
    if(n == 0) {
        returnToMenu();
        return;
    }
    buyTicket(n);
}

void busDepartFrom() {

    struct busDepart {
        char busDepart[20];
    } busDepartFromTemp[BUS_MAX];

    printf(BHYEL "\n\nDeparture From: \n");
    int countUnique = 0;
    for(int i=0; i<countCoach; i++) {
        bool isUnique = 1;
        for(int j=0; j<i; j++) {
            if(strcmp(coach[i].boardingPoint, coach[j].boardingPoint) == 0) {
                isUnique = 0;
                break;
            }
        }
        if(isUnique) {
            countUnique++;
            printf(BHCYN "%d. %s\n" COLOR_RESET, countUnique, coach[i].boardingPoint);
            strcpy(busDepartFromTemp[countUnique-1].busDepart, coach[i].boardingPoint);
        }
    }   
    printf(BHRED "\n\n0. Back to Main Menu\n");
    printf(YEL "\nEnter your choice: " COLOR_RESET);
    int n;
    scanf("%d", &n);
    if(n == 0) {
        returnToMenu();
        return;
    }
    strcpy(getBusDepartFrom, busDepartFromTemp[n-1].busDepart);
    printf(BHGRN "\nYou are going from %s\n\n" COLOR_RESET, getBusDepartFrom);
    system("pause");
}

void busDestiTo() {
    struct busDesti {
    char busDesti[20];
    } busDestiToTemp[BUS_MAX];

    printf(BHYEL "\n\nDestination To:\n");
    int countUnique = 0;
    for(int i=0; i<countCoach; i++) {
        bool isUnique = 1;
        for(int j=0; j<i; j++) {
            if(strcmp(coach[i].droppingPoint, coach[j].droppingPoint) == 0) {
                isUnique = 0;
                break;
            }
        }
        if(isUnique) {
            countUnique++;
            printf(BHCYN "%d. %s\n" COLOR_RESET, countUnique, coach[i].droppingPoint);
            strcpy(busDestiToTemp[countUnique-1].busDesti, coach[i].droppingPoint);
        }
    }
    printf(BHRED "\n\n0. Main Menu\n");

    printf(YEL "\nEnter your choice: " COLOR_RESET);
    int n;
    scanf("%d", &n);
    if(n == 0) {
        returnToMenu();
    }
    strcpy(getBusDestiTo, busDestiToTemp[n-1].busDesti);
    printf(BHGRN "\nYou have choosen to go %s\n\n" COLOR_RESET, getBusDestiTo);
    system("pause");
    system("cls");
}

int availableSeat(int s) {
    int emptySeat = 0;
    for(int i=0; i<coach[s-1].seatNumber; i++) {
        if(coach[s-1].seatList[i] == 0) {
            emptySeat++;
        }
    }
    return emptySeat;
}

void busSchedule() {
    busAnimation();
    system("cls");
    printf("\n\n\n                                     ");
    printf(WHTHB BHBLK"                 Bus Schedule                 \n" COLOR_RESET);
    printf("\n                                  ");
    printf(HBLK "[Currently this routes and buses are available only.]\n\n");
    printf(BLUHB BLKHB "\nBus Name        From            Destination      Time          Seat           Coach Type        Price        Coach ID   " COLOR_RESET);
    printf("\n");
    for(int i=0; i<countCoach; i++) {
        if(i%2 == 0) {
            printf(MAGB);
        } else {
            printf(BLUB);
        }
        printf("%-15s %-15s %-15s %-15s %-15d %-15s %-15d %-8d" reset, coach[i].busName, coach[i].boardingPoint, coach[i].droppingPoint, coach[i].boardingTime, coach[i].seatNumber, showCoachType(coach[i].coachType), coach[i].ticketPrice, coach[i].coachId);
        printf("\n");
    }
    printf(BHYEL "\n\n\n                               Now What?\n");
    printf(BHCYN "                                 1. Search Bus\n");
    printf( "                                 2. Go back\n");
    int n;
    printf(BHYEL "                               Enter your choice: " COLOR_RESET);
    scanf("%d", &n);
    switch(n){
        case 1:
            searchBus();
            break;
        case 2:
            returnToMenu();
        default:
            printf(BHRED "\n\n                                  Wrong input!\n\n" COLOR_RESET);
            system("pause");
            busSchedule();
    }
}

void buyTicket(int n) {
    busAnimation();
    system("cls");
    printf(WHTHB BHBLK"                                Buy Ticket                                " COLOR_RESET);
    seatPlan(n);

    //Ticketing

    if($myUserId==0){
        printf(BHRED "\n\n\n                    Please Login for buying a ticket.\n\n" COLOR_RESET);
        system("pause");
        int p;
        do {
            printf(BHYEL "\nChoose an option:\n");
            printf(BHCYN " 1. Login\n");
            printf(" 2. Forgotten Password\n");
            printf(" 3. Create an account\n");
            printf(" 4. Search Bus\n");
            printf(" 5. Main Menu\n\n");
            printf(BHYEL "Enter your choice: "COLOR_RESET);
            scanf("%d", &p);
            switch(p) {
                case 1: 
                    login();
                    return;
                case 2:
                    forgetPassword();
                    return;
                case 3:
                    createAccount();
                    return;
                case 4:
                    searchBus();
                    return;
                case 5:
                    returnToMenu();
                    return;
                default:
                    printf(BHRED "Invalid Insertion!\n" COLOR_RESET);
            } 
        } while(p>5 || p<1);
    } 

    int choice;
    int genderMatch;
    int x = 0;

    do {
        printf(BHWHT "\n\nEnter Seat number to buy a ticket " BHRED " (Put 0 to return): " COLOR_RESET );
        scanf("%d", &choice);
        if(choice == 0) {
            searchBus();
            return;
        }
        if(choice > coach[n-1].seatNumber || choice < 1) {
            printf(BHRED "\n\nWrong Seat Number\n");
            continue;
        }

        if(coach[n-1].seatList[choice-1] == 0) {
            printf(BHWHT "\nTicket owner's gender (1 for men, 2 for women):" COLOR_RESET);
            scanf("%d", &genderMatch);
        
            if(choice == 1 || (choice-1)%4 == 0) {
                if(coach[n-1].seatList[choice] == genderMatch || coach[n-1].seatList[choice] == 0) {
                    coach[n-1].seatList[choice-1] = genderMatch;
                    printf(BHGRN "\n\nHurray! Seat booking successfull!\n\n" COLOR_RESET);
                    x = 1;
                    system("pause");
            } else {
                    printf(BHRED "\nSorry! You cann't seat beside your unknown opposite gender.\n\n" COLOR_RESET);
                    system("pause");
                }
            } else if(choice == 2 || (choice-2)%4 == 0) {
                if(coach[n-1].seatList[choice-2] == genderMatch || coach[n-1].seatList[choice-2] == 0) {
                    coach[n-1].seatList[choice-1] = genderMatch;
                    printf(BHGRN "\n\nHurray! Seat booking successfull!\n\n" COLOR_RESET);
                    system("pause");
                    x = 1;
                } else {
                    printf(BHRED "\n\nSorry! You cann't seat beside your unknown opposite gender.\n\n" COLOR_RESET);
                    system("pause");
                }   
            } else if((choice+1)%4 == 0) {
                if(coach[n-1].seatList[choice] == genderMatch || coach[n-1].seatList[choice] == 0) {
                    coach[n-1].seatList[choice-1] = genderMatch;
                    printf(BHGRN "\n\nHurray! Seat booking successfull!\n\n" COLOR_RESET);
                    x = 1;
                    system("pause");
                } else {
                    printf(BHRED "\n\nSorry! You cann't seat beside your unknown opposite gender.\n\n" COLOR_RESET);
                    system("pause");
                }
            } else if(choice%4 == 0) {
                if(coach[n-1].seatList[choice-2] == genderMatch || coach[n-1].seatList[choice-2] == 0) {
                    coach[n-1].seatList[choice-1] = genderMatch;
                    printf(BHGRN "\n\nHurray! Seat booking successfull!\n\n" COLOR_RESET);
                    x = 1;
                    system("pause");
                } else {
                    printf(BHRED "\n\nSorry! You cann't seat beside your unknown opposite gender.\n\n" COLOR_RESET);
                    system("pause");
                }
            }
        } else {
            printf(BHRED "\nSorry! The seat has been already booked!\n" COLOR_RESET);
            system("pause");
            searchBus();
            return;
        }
    } while (x == 0);

    system("cls");
    busAnimation();
    printf(WHTHB BHBLK"                                Updated Seat Plan                                " COLOR_RESET);
    seatPlan(n);

    int q;
    do {
        printf(BHYEL "\n\nChoose an option:\n");
        printf(BHWHT" 1. Search Bus\n");
        printf(" 2. Buy Ticket Again\n");
        printf(" 3. Main Menu\n\n");
        printf(BHYEL "Enter your choice: "COLOR_RESET);
        scanf("%d", &q);
        switch(q) {
            case  1:
                searchBus();
                return;
            case  2:
                buyTicket(n);
                return;
            case 3:
                returnToMenu();
                return;
            default:
                printf(BHRED "Invalid Insertion!\n" COLOR_RESET);
            } 
        } while(q>3 || q<1);
}

void seatPlan(int n) {
    printf("\n\n");
    printf(BHCYN"                         Bus name    : " HYEL "%-10s\n", coach[n-1].busName);
    printf(BHCYN"                         Bus ID      : " HYEL "%-10d\n", coach[n-1].coachId);
    printf(BHCYN"                         From        : " HYEL "%-10s\n", coach[n-1].boardingPoint);
    printf(BHCYN"                         To          : " HYEL "%-10s\n\n", coach[n-1].droppingPoint);
    printf(BLKHB BHWHT"                                Seat Plan                                " COLOR_RESET);
    printf("\n\n");
    int tabtemp = 0;
    int lastrowtemp = 0;
    for(int i=0; i<coach[n-1].seatNumber; i++) {
        if(i+5 >= coach[n-1].seatNumber) {
            if(tabtemp==2) {
                printf("\n");
                tabtemp = 0;
            }
            printf("%d. %s \t", i+1, showSeatStatus(coach[n-1].seatList[i]));
            continue;
        } else {
            if((i+1)%4==1 && (i+1)>=4) {
                printf("\n");
            }
            printf("%d. %s \t", i+1, showSeatStatus(coach[n-1].seatList[i]));
            tabtemp++;
            if(tabtemp == 2 && i+6 < coach[n-1].seatNumber) {
                printf("\t\t");
                tabtemp = 0;
            }
        }
    }
}

void myBookedSeat() {

}

void cancelSeat() {

}

void customerMenu() {
    busAnimation();
    system("cls");
    welcomeMsg();
    int n;
    
    printf(WHTHB BHBLK "\n         Customer Menu         \n" COLOR_RESET);
    printf(HBLK "       [Choose an option] \n\n");
    printf(BHCYN"  1. Search Bus\n");
    printf("  2. Bus Schedule\n\n");
    printf("  3. Update Own Profile\n");
    printf("  4. My Booked Seat\n");
    printf("  5. Cancel Seat\n\n");
    printf("  6. User Manual\n");        
    printf("  7. Our Branches\n");
    printf("  8. Contact Us\n\n");
    printf("  9. Logout " COLOR_RESET "(Logged as %s)\n\n", id[$myUserId-1].userName);
    printf(BHRED "         [0] Exit\n\n" COLOR_RESET);
    printf(BHYEL "Choose an option: " COLOR_RESET);
    scanf("%d", &n);

    switch(n) {
        case 0:
            ifExit();
        case 1:
            searchBus();
            break;
        case 2:
            busSchedule();
            break;
        case 3:
            updateOwnProfile();
            break;
        case 4:
            myBookedSeat();
            break;    
        case 5:
            cancelSeat();
            break;
        case 6:
            userManual();
            break;
        case 7:
            ourBranches();
            break;
        case 8:
            contactUs();
            break;
        case 9:
            logout();
            break;
        default:
            printf(BHRED "   \n\nSomething went wrong, plz try again!\n\n" COLOR_RESET);
            system("pause");
            customerMenu();
            return;
    }
}

void executiveMenu() {
    busAnimation();
    system("cls");
    welcomeMsg();
    printf(WHTHB BHBLK"\n             Executive Menu              \n" COLOR_RESET);
    printf(HBLK "         [Choose an option] \n\n");
    printf(BHCYN "  1. Search Bus\n");
    printf("  2. Bus Schedule\n");
    printf("  3. Show bus summary\n");
    printf("  4. Cancel Seat\n\n");
    printf("  5. Update Own Profile\n");
    printf("  6. Logout " COLOR_RESET "(Logged as %s)\n\n", id[$myUserId-1].userName);
    printf(BHRED "            [0] Exit\n\n");
    printf(BHYEL "\nChoose an option: " COLOR_RESET);

    int n;
    scanf("%d", &n);

    switch(n) {
        case 1:
            searchBus();
            break;
        case 2:
            busSchedule();
            break;
        case 3:
            showBusSummary();
            break;
        case 4:
            cancelSeat();
            break;    
        case 5:
            updateOwnProfile();
            break;
        case 6:
            logout();
            break;
        case 0:
            ifExit();
            break;
        default:
            printf(BHRED "\n\nSomething went wrong, plz try again!\n\n" COLOR_RESET);
            system("pause");
            executiveMenu();
    }
}

//ADMIN MENU

void adminMenu() {
    busAnimation();
    system("cls");
    welcomeMsg();
    printf(WHTHB BHBLK "\n             Admin Menu             \n" COLOR_RESET);
    printf(HBLK "         [Choose an option] \n\n");
    printf(BHCYN "  1. Search Bus\n");
    printf("  2. View Bus Schedule\n\n");

    printf(BHYEL "  Exclusive Admin Features: \n");
    printf(BHBLU "  3. Add New Bus & Route\n");
    printf("  4. Update Bus & Route\n");
    printf("  5. Update ticket Price\n");
    printf("  6. Show bus summary\n");
    printf("  7. Cancel any Seat\n");
    printf("  8. Create new Profiles\n");
    printf("  9. Update other Profiles\n");
    printf("  10. Remove existing Profiles\n\n");
    printf(BHCYN "  11. Update Own Profile\n");
    printf("  12. Logout " COLOR_RESET "(Logged as %s)\n\n", id[$myUserId-1].userName);
    printf(BHRED "         [0] Exit\n\n" COLOR_RESET);

    printf(BHYEL "\n  Choose an option: " COLOR_RESET);

    int n;
    scanf("%d", &n);

    switch(n) {
        case 1: 
            searchBus();
            break;
        case 2: 
            busSchedule();
            break;
        case 3:
            setBusSchedule();
            break;
        case 4:
            updateBusScedule();
            break;
        case 5:
            updateBusTicket();
            break;
        case 6:
            showBusSummary();
            break;
        case 7:
            cancelSeat();
            break;
        case 8:
            createNewProfiles();
            break;
        case 9:
            updateOtherProfiles();
            break;
        case 10:
            removeExistingProfiles();
            break;
        case 11:
            updateOwnProfile();
            break;
        case 12:
            logout();
            break;
        case 0:
            ifExit();
            break;
        default:
            printf(BHRED "\n\n   Something went wrong, plz try again!\n\n" COLOR_RESET);
            system("pause");
            adminMenu();
    }
}

void setBusSchedule() {
    system("cls");
    busAnimation();
    printf(WHTHB BHBLK "\n             Create Bus Schedule             \n" COLOR_RESET);
    char ctemp;
    countCoach++;
    printf("Bus Name: ");
    scanf("%c", &ctemp);
    scanf("%[^\n]", coach[countCoach-1].busName);
    printf("Boarding Point: ");
    scanf("%s", coach[countCoach-1].boardingPoint);
    printf("Dropping Point: ");
    scanf("%s", coach[countCoach-1].droppingPoint);
    printf("Boarding Time: ");
    scanf("%c", &ctemp);
    scanf("%[^\n]", coach[countCoach-1].boardingTime);
    printf("Seat Number: (41,45,49,53,57): ");
    scanf("%d", &coach[countCoach-1].seatNumber);
    printf("Coach Type: (1 for ac, 0 for non ac)");
    scanf("%d", &coach[countCoach-1].coachType);
    printf("Ticket Price: ");
    scanf("%d", &coach[countCoach-1].ticketPrice);
    
    coach[countCoach-1].coachId = countCoach;
    for(int i=0; i<60; i++) {
        coach[countCoach-1].seatList[i] = 0;
    }

    printf("New bus and route has been inserted\n");
    searchBus();
}

void updateBusScedule() {
    
}

void updateBusTicket() {

}

void showBusSummary() {

} 

void createNewProfiles() {

} 

void updateOtherProfiles() {

}

void removeExistingProfiles() {

}

void ifExit() {
    busAnimation();
    system("cls");
    printf( BHGRN "\n\n\n       Have a good Day, TaTa!\n\n\n" COLOR_RESET);
    system("pause");
    system("cls");
    exit(0);
}

void returnToMenu() {
    if($myUserId == 0) {
        nonLogged_Menu();
        return;
    } else {
        if(id[$myUserId-1].userRole == 1) {
            customerMenu();
            return;
        } else if(id[$myUserId-1].userRole == 2) {
            executiveMenu();
            return;
        } else if(id[$myUserId-1].userRole == 3){
            adminMenu();
            return;
        }
    }
}

const char* showGender(bool gender) {
    if(gender == 1) {
        return "Female";
    } else if(gender == 0) {
        return "Male";
    } else {
        return "Undefined";
    }
}

const char* showRole(int role) {
    if(role == 3) {
        return "Admin";
    } else if(role == 2) {
        return "Executive";
    } else if(role == 1){
        return "Customer";
    }
}

const char* showCoachType(bool icoachType) {
    if(icoachType == 1) {
        return "AC";
    } else {
        return "Non AC";
    }
}

const char* showSeatStatus(int iseatStatus) {
    if(iseatStatus == 0) {
        return "\033[1;32mEmpty\033[1;0m";
    } else if(iseatStatus == 1) {
        return "\033[1;34mMale\033[1;0m";
    } else if(iseatStatus == 2){
        return "\033[1;31mFemale\033[1;0m";
    }
}

void ourBranches() {

}

void contactUs() {

}

void userManual() {

}
