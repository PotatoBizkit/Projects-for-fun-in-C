#include <stdio.h>
#include <string.h>

typedef struct ani_tracker
{
    char aname[100];
    int total_eps;
    int watched_eps;
} ant;

void add_new_anime(ant *new_ani){
    FILE *f = NULL;
    f = fopen("ani_data.csv", "a");
    printf("\nEnter anime name:\n");
    fgets(new_ani->aname, sizeof(new_ani->aname), stdin);
    new_ani->aname[strcspn(new_ani->aname, "\n")] = '\0';

    printf("\nEnter total anime episodes:\n");
    scanf("%d", &new_ani->total_eps);
    while (getchar() != '\n');

    printf("\nEnter number of anime episodes watched:\n");
    scanf("%d", &new_ani->watched_eps);
    while (getchar() != '\n');

    fprintf(f, "\"%s\",%d,%d\n", new_ani->aname, new_ani->total_eps, new_ani->watched_eps);

    fclose(f);

    printf("\nNew anime has been added to the list!\n");
}

void show_all(){
    int col2, col3, i=1;
    char t[100], s[100];

    FILE *f = NULL;
    f = fopen("ani_data.csv", "r");

    if (f == NULL)
    {
        printf("\nNo anime has yet been added to the list!\n\n");
        return;
    }
    
    printf("\n");
    while (fgets(t, sizeof(t), f))
    {
        sscanf(t, "\"%[^\"]\", %d, %d", s, &col2, &col3);
        printf("%d. %s: %d/%d\n", i++, s, col3, col2);
    }
    fclose(f);
    printf("\n");    
}

void update(){
    printf("\nLoading...\n");

    int col2, col3, count=0, row, choice;
    char t[100], s[100];

    FILE *f = NULL;
    f = fopen("ani_data.csv", "r");

    if (f == NULL)
    {
        printf("\nNo anime has yet been added to the list!\n\n");
        return;
    }

    while (fgets(t, sizeof(t), f)){
        count++;
    }

    rewind(f);
    ant arr[count];

    for (int i = 0; i < count; i++)
    {
        fgets(t, sizeof(t), f);
        sscanf(t, "\"%[^\"]\", %d, %d", s, &col2, &col3);
        strcpy(arr[i].aname, s);
        arr[i].total_eps = col2;
        arr[i].watched_eps = col3;
    }

    fclose(f);
    
    printf("\nValues of which row do you want to update?\n");
    scanf("%d", &row);
    while (getchar() != '\n');
    printf("\nWhich field do you want to update?\n1. Anime name\n2. Total episodes\n3. Watched Episodes\n");
    scanf("%d", &choice);
    while (getchar() != '\n');

    switch (choice)
    {
    case 1:{
        printf("\nRe-enter anime name:\n");
        fgets(arr[row-1].aname, sizeof(arr[row-1].aname), stdin);
        arr[row-1].aname[strcspn(arr[row-1].aname, "\n")] = '\0';
        break;
    }
    case 2:{
        printf("\nRe-enter total anime episodes:\n");
        scanf("%d", &arr[row-1].total_eps);
        while (getchar() != '\n');
        break;
    }
    case 3:{
        printf("\nRe-enter total watched episodes:\n");
        scanf("%d", &arr[row-1].watched_eps);
        while (getchar() != '\n');
        break;
    }
    default:
        break;
    }

    f = fopen("ani_data.csv", "w");
    for (int i = 0; i < count; i++)
    {
        fprintf(f, "\"%s\",%d,%d\n", arr[i].aname, arr[i].total_eps, arr[i].watched_eps);
    }
    fclose(f);
}

void delete(){
    printf("\nLoading...\n");

    int col2, col3, count=0, row, choice;
    char t[100], s[100];

    FILE *f = NULL;
    f = fopen("ani_data.csv", "r");

    if (f == NULL)
    {
        printf("\nNo anime has yet been added to the list!\n\n");
        return;
    }

    while (fgets(t, sizeof(t), f)){
        count++;
    }

    rewind(f);
    ant arr[count];

    for (int i = 0; i < count; i++)
    {
        fgets(t, sizeof(t), f);
        sscanf(t, "\"%[^\"]\", %d, %d", s, &col2, &col3);
        strcpy(arr[i].aname, s);
        arr[i].total_eps = col2;
        arr[i].watched_eps = col3;
    }

    fclose(f);

    printf("\nEnter row number you want to delete:\n");
    scanf("%d", &row);
    while (getchar() != '\n');

    f = fopen("ani_data.csv", "w");
    for (int i = 0; i < count; i++)
    {
        if (i == row-1)
        {
            continue;
        }
        fprintf(f, "\"%s\",%d,%d\n", arr[i].aname, arr[i].total_eps, arr[i].watched_eps);
    }
    fclose(f);
}

int main(){
    int start_choice, w = 1;

    printf("******************** Welcome to Anime Tracker ********************\n");
    while (w){
        printf("\nWhat would you like to do?\n");
        printf("\n1. Add an anime\n2. Show all anime\n3. Update\n4. Delete an anime\n5. Exit\n\n");
        scanf("%d", &start_choice);
        while (getchar() != '\n');

        switch (start_choice)
        {
        case 1:{
            ant new;
            add_new_anime(&new);
            break;
        }
        case 2:{
            show_all();
            break;
        }
        case 3:{
            update();
            break;
        }
        case 4:{
            delete();
            break;
        }
        case 5:{
            w = 0;
            printf("\nThank You!\n");
            break;
        }
        default:
            break;
        }
    }
    return 0;
}