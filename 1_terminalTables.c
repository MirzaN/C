/****************************************************
    By   Mirza Nezirovic
    On   Apr 4th 2013
    For  Bicom Systems
    Purpose: programming test #1 "Terminal tables"  
*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parseLines(char *currentLine, char *nextLine);

int main(int argc, char *argv[])
{
    FILE *fileHandle;
    char nextLine[1024] = "";
    char currentLine[1024] = "";


    if (argv[1])  //Verify that CLI parameter exists.
    {
    
        if( fileHandle = fopen(argv[1],"r") ) //Verify input file handle.
        {

            while (fgets (nextLine, 1024, fileHandle)!=NULL) //Read line by line until EOF
            {
                parseLines(currentLine, nextLine);   //Send current and next line to print first line characters followed by border between current and the next line.
                strcpy(currentLine, nextLine);       //Copy next line into current before reading new next line.
            }

            parseLines(currentLine, nextLine);   //Send the very last line for printing.

            fclose(fileHandle);
        }
        else
        {
            printf("\n Unable to open input file \"%s\"!!!\n\n", argv[1]);
            return 2;
        }
    }
    else
    {
        printf("\n No input file specified!  -->%s  <filename>\n Please provide name of the input file.\n\n", argv[0]);
        return 1;
    }

    return 0;
}


int parseLines(char *currentLine, char *nextLine)
{
    int currentLineLength = strlen(currentLine)-1; //Adjust length for EOL character
    int nextLineLength    = strlen(nextLine)-1;    //Adjust length for EOL character
    int borderLength      = currentLineLength;
    int i = 0;

    //Print line of characters.
    for (i = 0; i < currentLineLength; i += 2)
    {
        if ( currentLine[i] != ' ' )   //Filled cell.
        {
            printf ("| %c ", currentLine[i]);
            if (i == currentLineLength-1 || i == currentLineLength-2) //If filled cell is at the end of the line, adding final right side border.
                printf ("|");
        }
        else if (currentLine[i] == ' ' && i != 0 && currentLine[i-2] != ' ') //Empty cell following a filled cell. Create right side border for the filled cell.
            printf ("|   ");
        else
            printf ("    ");
    }
    printf ("\n");

    
    //Print border between current row and the next row.
    if (nextLineLength > currentLineLength)  //Adjust border length if next line is longer then current line.
        borderLength = nextLineLength;

    for (i = 0; i < borderLength; i += 2)
    {
      if ( (currentLine[i] != ' ' && i < currentLineLength) || (nextLine[i] != ' ' && i < nextLineLength))  //Filled cell on current line OR on next line.
        {
            printf("+---");
            if (i == borderLength-1 || i == borderLength-2) //If filled cell is at the end of the line, adding final right side border.
                printf("+");
        }
        else if (  (currentLine[i] == ' ' && i != 0 && currentLine[i-2] != ' ' && i < currentLineLength ) //An empty cell following a filled cell on the current line. Creating right side border for the filled cell.
                || (currentLine[i] != ' ' && i == currentLineLength+1) //Handle case where current line is longer then the next line.
                || (nextLine[i] == ' ' && i != 0 && nextLine[i-2] != ' ' && i < nextLineLength) //An empty cell following a filled cell on the next line. Creating right side border for the filled cell.
                || (nextLine[i] != ' ' && i == nextLineLength+1) )//Handle case where next line is longer then the current line.
            printf("+   ");
        else
            printf("    ");
    }
    printf("\n");    

    return 0;
}

