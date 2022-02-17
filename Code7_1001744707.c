//Huy Nguyen
//1001744707
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ROWS 9
#define MAX_COLS 9
#define TICKET_LIMIT 4

void FillMovieTheater(char MovieTheater[MAX_ROWS][MAX_COLS], int number_of_row, int number_of_column, char movie[MAX_ROWS*MAX_COLS])
{
    int k =0;
    for (int i=0; i< number_of_row; i++)
    {
        for (int j=0; j < number_of_column; j++)
        {
            MovieTheater[i][j] = movie[k];
            k++;
        }
    }
}

void PrintSeatMap(char MovieTheater[MAX_ROWS][MAX_COLS], int number_of_row, int number_of_column)
{
    printf("        ");
    for( int i=1; i<=number_of_column; i++)
    {
        printf("Seat %d ",i);
    }
    printf("\n");
    for (int i=0; i < number_of_row; i++)
    {
        printf("Row %c   %c", 65 + i,MovieTheater[i][0]);
        for (int j=1; j < number_of_column; j++)
        {
            printf("%7c", MovieTheater[i][j]);
        }
        printf("\n");
    }
}

int IsSeatSold(char MovieTheater[MAX_ROWS][MAX_COLS], int array_row, int array_column)
{
    int check;
    if (MovieTheater[array_row][array_column] == 'X')
    {
        check = 1;
    }
    else 
    {
        MovieTheater[array_row][array_column] = 'X';
        check = 0;
    }
    return check;
}

void WriteMovieTheater(char MovieTheater[MAX_ROWS][MAX_COLS], int number_of_row, int number_of_column)
{
	/* declare a char array to hold the output filename */
    char output_filename[20]={};
	/* declare a file handle for the output file and set it to NULL */
    FILE *WROUT = NULL;
	/* prompt for and store the output filename */
    printf("Enter output name:");
    scanf("%s", output_filename);
	/* open the output filename with "w+" */
    WROUT = fopen(output_filename,"w+");
	/* If the file did not open, print message shown in sample output and exit */
    if (WROUT == NULL)
    {
        printf("The file did not open. Exiting...");
        exit(0);
    }
	/* use fprintf() to print the rows and seats to the 1st line of the file */
    fprintf(WROUT, "%d %d \n", number_of_row, number_of_column);
	/* used a nested for loops with fprintf() to print the 2D array to the output file */
    for (int i=0; i< number_of_row; i++)
    {
        for (int j=0; j < number_of_column; j++)
        {
            fprintf(WROUT,"%c", MovieTheater[i][j]);
        }
    }
	/* close the file */
    fclose(WROUT);
}


int main(void)
{
    int purchased_ticket=0;
    int sold_ticket=0;
    int array_row;
    int array_column;
    int number_of_row;
    int number_of_column;
    char user_row;
    int user_seat;
    char MovieTheater[MAX_ROWS][MAX_COLS];
	
	/* declare a file handle and set it to NULL */
    FILE *USERFILE = NULL;
	/* declare a char array to hold the user input file name */
    char user_filename[20] = {};
	/* declare a char array of size MAX_ROWS*MAX_COLS - DO NOT HARDCODE THESE VALUES */
    char movie[MAX_ROWS*MAX_COLS]={};
	/* prompt for and store the Movie Theater file name */
    printf("Enter the name of your movie theater file:");
    scanf("%s", user_filename);
	/* Open the file */
    USERFILE = fopen(user_filename,"r+");
	/* If the file did not open, print message shown in sample output and exit */
    if (USERFILE == NULL)
    {
        printf("The file did not open. Exiting...");
        exit(0);
    }
	/* Read the first line of the file to get the number of rows and seats - use fscanf() */
	fscanf(USERFILE, "%d %d \n", &number_of_row, &number_of_column);
	/* Use fgets() to read the 2nd line of the file */
    fgets(movie, sizeof(movie)-1, USERFILE);
	/* close the file */
	fclose(USERFILE);
	/* call FillMovieTheater - pass in 2nd line read from file */
    FillMovieTheater(MovieTheater, number_of_row, number_of_column, movie);
	/* prompt for number of tickets to purchase as shown in sample output */
    printf("How many ticket would you like to purchase?");
    scanf("%d", &purchased_ticket);

	while (purchased_ticket < 0 || purchased_ticket > TICKET_LIMIT)
    {
        printf("This is a special showing - limit of %d ticket per purchase\n", TICKET_LIMIT);
        printf("How many ticket would you like to purchase?");
        scanf("%d", &purchased_ticket);
    }
    
    if (purchased_ticket == 0)
    {
        printf("No movie for you!\n");
    }
    else
    {
        while ( sold_ticket < purchased_ticket)
        {
            PrintSeatMap(MovieTheater, number_of_row, number_of_column);
            printf("Enter seat choice by entering the row and seat\nPlease pick a seat\n");
            scanf(" %c %d", &user_row, &user_seat );
            array_row = toupper(user_row);
            array_column = user_seat;
            
            array_row = array_row - 65;
            array_column = array_column - 1;
            if (/*ArrayRow or ArrayCol is out of range*/ (array_row>=number_of_row|| array_row<0 || array_column>=number_of_column||array_column < 0 ))
            {
                printf("That seat is not in this theater\n");
            }
            else if (IsSeatSold(MovieTheater, array_row, array_column))
            {
                printf("Seat %c%d is already sold. Pick a different seat\n",toupper(user_row), user_seat);
            }
            else
            {
                sold_ticket++;
            }
        }
        printf("Please find your way to your seats using this map...\n");
        PrintSeatMap(MovieTheater, number_of_row, number_of_column);
        printf("Enjoy your movie!\n");
    }
	/* Call WriteMovieTheater */
    WriteMovieTheater(MovieTheater, number_of_row, number_of_column);
}
