#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "time.h"
#include <string.h>

#define MAX_Menu 100
#define MAX_History_Order 500

typedef struct {
    char Name[30];
    int Price;
} S_Menu;

typedef struct {
    char Date[30], Time[20], Eat[10];
    int Money;
} S_History;

S_Menu Menu[MAX_Menu];
S_History History[MAX_History_Order];

int i, j;

int choice, menu, row_drink;

void Display_Menu();

void User();

int Discount(int *total, int money);

int Read_History();

void Save_History(int money, char *eat);

void Admin();

void Income();

void Month_Income(int list);

void Week_Income(int list);

void Edit();

void Change_data();

void Delete_data();

void Add_data();

void Read_Menu();

void Save_Menu();

char *now(char *dt);

int main() {
    int choice;
    Start:
    system("cls");
    printf("\n\n----------------------------------- W E L C O M E  T O  J U L Y ' S C A F E -----------------------------------\n\n");

    printf("\n\tYou are User or Admin.\n");
    printf("\t0.Close\n");
    printf("\t1.User\n");
    printf("\t2.Admin\n");
    printf("\tPlease select choice 1 or 2 : ");
    scanf("%d", &choice);

    if (choice == 0) {
        exit(1);
    } else if (choice == 1) {
        User();
    } else if (choice == 2) {
        char id[] = "admin", pass[] = "admin";
        char idIn[10], passIn[10];
        for (;;) {
            system("cls");
            printf("\n\n------------------------------------------- A D M I N  S Y S T E M  -------------------------------------------\n\n");
            printf("   Login :              \n\n");
            printf("   Enter ID       : ");
            scanf("%s", idIn);
            printf("\n");
            printf("   Enter Password : ");
            scanf("%s", passIn);
            system("cls");


            if (strcmp(id, idIn) == 0 && strcmp(pass, passIn) == 0) {
                Admin();
                break;
            } else {
                printf("\n    Password incorrect       \n");
                continue;
            }
        }
    }
    goto Start;
}

void Display_Menu() {
    printf("\n\n                                             Menu July's Cafe                                             \n\n");
    printf("_______________________________________________________________________________________________________________________\n\n");
    printf("     Drinks\n");
    for (i = 0; i < row_drink; i++) {
        printf("           [%2d]%25s                                                %3d  \n", i + 1, Menu[i].Name,
               Menu[i].Price);
    }
    printf("\n\n     Dessert\n");
    for (j = row_drink; j < menu; j++) {
        printf("           [%2d]%25s                                                %3d  \n", j + 1, Menu[j].Name,
               Menu[j].Price);
    }
    printf("                                                Exit with order[0]                                                         \n");
}

void User() {
    char Eat_Take[10];
    menu = 0, row_drink = 0;
    User:
    Read_Menu();
    system("cls");
    printf("\n\n----------------------------------- W E L C O M E  T O  J U L Y ' S C A F E -----------------------------------\n\n");
    printf("\n\tThere are two types.\n");
    printf("\t1.Eat here\n");
    printf("\t2.Take away\n");
    printf("\tPlease select choice 1 or 2 : ");
    scanf("%d", &choice);

    if (choice == 1) {
        strcpy(Eat_Take, "Eat_here");
    } else {
        strcpy(Eat_Take, "Take away");
    }
    system("cls");
    Display_Menu(menu, row_drink);

    int n, sum, count = 0;

    Unconfirm:
    n = 1, sum = 0;
    for (;;) {
        Wrong_item:
        printf("\tPlease insert order : ");
        scanf("%d", &n);

        if (n == 0) {
            break;
        }

        if (n > menu) {
            printf("\tTry again\n");
            goto User;
        }

        printf("Selected : [%d] %s %d Bath\n\n", n, Menu[n - 1].Name, Menu[n - 1].Price);
        sum += Menu[n - 1].Price;
        count++;
    }

    if (count == 0) {
        goto END;
    }
    //variable
    char choose;
    //choose
    printf("\n\t Confirm order[y/n]: ");
    choose = getch(); //เพือให้หน้าจอค้างไว้ ไม่ปิดเอง
    printf("%c\n", choose);
    int total, discout, payment, change;
    int *p_total = &total;
    //choose 'y'
    if (choose == 'y') {
        system("cls");
        discout = Discount(p_total, sum);
        printf("\n\tTotal : %d\n", sum);
        printf("\tDiscount : %d\n", discout);
        printf("\n\n");

        printf("\tNet Total : %d\n", total);
        printf("\tPayment :");
        scanf("%d", &payment);

        change = payment - total;
        printf("\nChange : %d", change);

    } else {
        goto Unconfirm;
    }

    Save_History(total, Eat_Take);
    END:
    printf("\n\nThank you...Goodbye!\n\n");
    printf("Press any key to continue...");
    getch();
}

int Discount(int *total, int money) {
    int discount;
    int array_discount[] = {5, 10, 5, 10, 5, 10, 10, 5, 5, 10};
    int array_table[10];

    srand(time(NULL));

    for (i = 0; i < 9; i++) {
        array_table[i] = array_discount[rand() % 10];
    }
    printf("\t\t--------------\n");
    printf("\t\t| 7 |  8 |  9|\n");
    printf("\t\t--------------\n");
    printf("\t\t| 4 |  5 |  6|\n");
    printf("\t\t--------------\n");
    printf("\t\t| 1 |  2 |  3|\n");
    printf("\t\t--------------\n");

    printf("Choose Number 1-9 : ");
    scanf("%d", &choice);

    system("cls");
    printf("\t\t--------------\n");
    printf("\t\t%2d%% | %2d%% | %2d%%\n", array_table[6], array_table[7], array_table[8]);
    printf("\t\t--------------\n");
    printf("\t\t%2d%% | %2d%% | %2d%%\n", array_table[3], array_table[4], array_table[5]);
    printf("\t\t--------------\n");
    printf("\t\t%2d%% | %2d%% | %2d%%\n", array_table[0], array_table[1], array_table[2]);
    printf("\t\t--------------\n");

    printf("You get %d%% discount!!", array_table[choice - 1]);

    *total = money - money * array_table[choice - 1] / 100;
    discount = money - *total;
    return discount;


}

void Read_Menu() {
    menu = 0, row_drink = 0;
    FILE *drink = fopen("Drink.txt", "r");
    FILE *desert = fopen("Desert.txt", "r");

    while (!feof(drink)) {
        printf("%d\n", menu);
        fscanf(drink, "%s %d", Menu[menu].Name, &Menu[menu].Price);
        printf("%d\n", menu);
        menu++;
        printf("%d\n", menu);
    }

    row_drink = menu;
    while (!feof(desert)) {
        fscanf(desert, "%s %d", Menu[menu].Name, &Menu[menu].Price);
        menu++;
    }

    fclose(drink);
    fclose(desert);
}

void Admin() {
    for (;;) {
        Read_Menu();
        system("cls");
        printf("\n\n------------------------------------------- A D M I N  S Y S T E M  -------------------------------------------\n\n");
        printf("\n\tAdmin Menu\n");
        printf("\t0.Exit\n");
        printf("\t1.Income\n");
        printf("\t2.Edit\n");

        printf("\tPlease select choice 0 1 or 2 : ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                return;
            case 1:
                Income();
                break;
            case 2:
                Edit();
                break;
        }
    }
}

void Income() {
    int choice, list;
    for(;;) {
    	list = Read_History();
        system("cls");
        printf("\n\n------------------------------------------- A D M I N  S Y S T E M  -------------------------------------------\n\n");
        printf("\n\tIncome Menu\n");
        printf("\t0.Exit\n");
        printf("\t1.Week\n");
        printf("\t2.Month\n");

        printf("\tPlease select choice 1 or 2 : ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                return;
            case 1:
                Week_Income(list);
                break;
            case 2:
                Month_Income(list);
                break;
        }
    }
}

void Month_Income(int list) {
    int Month[13] = {0}, month;
    char *token;
    char mon[3];
    for (i = 0; i < list; i++) {
        token = strtok(History[i].Date, "/");
        strcpy(mon, token);
        month = strtod(mon, NULL);
        Month[month-1] += History[i].Money;
    }
    system("cls");
    printf("\n\n------------------------------------------- M O N T H  I N C O M E  -------------------------------------------\n\n");
    printf("\tMonth's Income :\n\n");
    for (i = 0; i < 12; i++) {
        printf("\tMonth [%2d] = %6d Bath\n", i + 1, Month[i]);
    }

    printf("\tPress any key to continue...");
    getch();
}

void Week_Income(int list) {
    int Week[32] = {0}, day, today,income;
    char day_str[3], str[10];
    char *token;

    for (i = 0; i < list; i++) {

        token = strtok(History[i].Date, "/");
        token = strtok(NULL, "/");
        strcpy(day_str, token);
        day = strtod(day_str, NULL);

        Week[day-1] += History[i].Money;

    }

    token = strtok(now(str), "/");
    token = strtok(NULL, "/");
    strcpy(day_str, token);
    today = strtod(day_str, NULL);
    system("cls");
    printf("\n\n-------------------------------------------  W E E K  I N C O M E  --------------------------------------------\n\n");
    printf("\tWeek's Income :\n\n");
    // -5
    int day7 = today-6,total=0;
    for (i = 0; i < 7; i++) {
        if(day7+i > 0){
            printf("\tDay [%d] = %6d Bath\n", day7+i, Week[day7+i-1]);
            total += Week[day7+i-1];
        }
    }
    printf("\n\tTotal Income = %d",total);
    printf("\n\tPress any key to continue");
    getch();
}

int Read_History() {
    int row_his = 0;
    FILE *history = fopen("History.txt", "r");
    while (!feof(history)) {
        fscanf(history, "%s %s %d %s", History[row_his].Date, History[row_his].Time, &History[row_his].Money,
               History[row_his].Eat);
        row_his++;
    }
    return row_his - 1;
}

void Save_History(int money, char *eat) {
    char date[20];
    FILE *history = fopen("History.txt", "a");
    fprintf(history, "%s %d %s\n", now(date), money, eat);
    fclose(history);
}

void Edit() {
    int choice;
    for (;;) {
        Read_Menu();
        system("cls");
        printf("\n\n------------------------------------------- A D M I N  S Y S T E M  -------------------------------------------\n\n");
        printf("\n\tEdit Menu.\n");
        printf("\t0.Exit\n");
        printf("\t1.Change Data\n");
        printf("\t2.Delete Data\n");
        printf("\t3.Add    Data\n");
        printf("\tPlease select choice 0 1 2 or 3: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                return;
            case 1:
                Change_data();
                break;
            case 2:
                Delete_data();
                break;
            case 3:
                Save_Menu();
                Add_data();
                break;
        }
    }


}

void Change_data() {
    system("cls");
    printf("\n\n------------------------------------------- A D M I N  S Y S T E M  -------------------------------------------\n\n");
    Display_Menu();

    int N;
    printf("\tEnter Number of menu to edit : ");
    scanf("%d", &N);

    if (N == 0) {
        goto END;
    }
    system("cls");
    printf("\n\t         Edit           \n");
    printf("\n\t======================= \n");
    printf("\tOld Data [%d]:\n\n", N);
    printf("\tName     : %s\n\n", Menu[N - 1].Name);
    printf("\tPrice    : %d\n\n", Menu[N - 1].Price);

    printf("\n");
	printf("\tWarnning : Don't Use Spacebar!\n\n");
    printf("\tNew Data [%d]:\n\n", N);
    printf("\tName     : ");
    scanf("%s", Menu[N - 1].Name);
    printf("\n");
    printf("\tPrice    : ");
    scanf("%d", &Menu[N - 1].Price);
    printf("\n");

    printf("\n\tNew Data Saved\n");
    printf("\tPress Any key to continue...");
    getch();
    END:
    system("cls");
    Save_Menu();

}

void Delete_data() {
    system("cls");
    printf("\n\n------------------------------------------- D E L E T E  S Y S T E M -------------------------------------------\n\n");
    Display_Menu(menu, row_drink);
    int N;
    Delete:
    printf("\tEnter Number of Menu to Delete : ");
    scanf("%d", &N);
    if (N == 0) {
        return;
    }
    char choose;
    //choose
    printf("\n\t Confirm order[y/n]: ");
    choose = getch();
    printf("\t%c\n", choose);
    if (choose == 'y' || choose == 'Y') {
        strcpy(Menu[N - 1].Name, "None");
    } else {
        goto Delete;
    }
    Save_Menu();
    printf("\n\tMenu Deleted\n");
    printf("\tPress Any key to continue...");
    getch();

}

void Add_data() {
    int choice, price;
    char name[30];
    system("cls");
    printf("\n\n--------------------------------------------- A D D  S Y S T E M  ---------------------------------------------\n\n");
    printf("\n\tDrink or Desert.\n");
    printf("\t0.Exit\n");
    printf("\t1.Drink\n");
    printf("\t2.Desert\n");
    printf("\tPlease select choice 0 1 or 2 : ");
    scanf("%d", &choice);
	printf("\n\n");
    if (choice == 0) {
        return;
    }

    if (choice == 1) {
		printf("\tWarnning : Don't Use Spacebar!\n\n");
        printf("\tNew Data \n");
        printf("\tName     : ");
        scanf("%s", name);
        printf("\n");
        printf("\tPrice    : ");
        scanf("%d", &price);
        printf("\n");

        FILE *f = fopen("Drink.txt", "a");
        fprintf(f, "\n%s %d", name, price);
        fclose(f);
        row_drink++;


    } else if (choice == 2) {
		printf("\tWarnning : Don't Use Spacebar!\n\n");
        printf("\tNew Data \n");
        printf("\tName     : ");
        scanf("%s", name);
        printf("\n");
        printf("\tPrice    : ");
        scanf("%d", &price);
        printf("\n");

        FILE *f = fopen("Desert.txt", "a");
        fprintf(f, "\n%s %d", name, price);
        fclose(f);
    }
    printf("\n\tMenu Added\n");
    printf("\tPress Any key to continue...");
    getch();
    menu++;
}

void Save_Menu() {
    char space[2] = "\n";

    FILE *f1 = fopen("Drink.txt", "w");
    FILE *f2 = fopen("Desert.txt", "w");
    for (i = 0; i < row_drink; i++) {
        if (i == row_drink - 1) {
            strcpy(space, "");
        } else if (i == row_drink - 2 && strcmp(Menu[i + 1].Name, "None") == 0) {
            strcpy(space, "");
        }
        if (strcmp(Menu[i].Name, "None") != 0)
            fprintf(f1, "%s %d%s", Menu[i].Name, Menu[i].Price, space);
        strcpy(space, "\n");
    }

    strcpy(space, "\n");
    for (j = row_drink; j < menu; j++) {
        if (j == menu - 1) {
            strcpy(space, "");
        } else if (j == menu - 2 && strcmp(Menu[j + 1].Name, "None") == 0) {
            strcpy(space, "");
        }
        if (strcmp(Menu[j].Name, "None") != 0)
            fprintf(f2, "%s %d%s", Menu[j].Name, Menu[j].Price, space);
        strcpy(space, "\n");
    }
    fclose(f1);
    fclose(f2);
}

char *now(char *dt) {
    time_t current = time(NULL);
    struct tm *info = localtime(&current);
    strftime(dt, 40, "%c", info);
    return dt;
}
