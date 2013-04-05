/****************************************************
    By   Mirza N.
    On   Apr 4th 2013
    For  Bicom Systems
    Purpose: programming test #2 "IP Address Range"   
*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void spliIpIntoOctets (int *, char *, char *);
void convertIPToBinary(char *, int *);
void clearString (char *string, int length);


int main(int argc, char *argv[])
{
    FILE *fileHandle;
    int  i=0;
    int  ipAddress[4]={0,0,0,0};
    int  ipRange[5]  ={0,0,0,0,0} ;
    char nextLine[50]="";
    char binaryIpRange[50]="";
    char binaryIpAddress[50]="";


    if (argv[1] && argv[2] && argv[3])  //Verify that all CLI parameter vere provided.
    {
        spliIpIntoOctets(ipAddress, argv[3], "."); //Split provided IP address string into integer octets. 
        
        convertIPToBinary(binaryIpAddress, ipAddress); //Convert IP Address into binary format for comparison.
         
        if( fileHandle = fopen(argv[2],"r") ) //Verify input file handle.
        {

            while (fgets (nextLine, 50, fileHandle)!=NULL)
            {
                spliIpIntoOctets(ipRange, nextLine, "./"); //Split provided IP address string into integer octets. 
                
                convertIPToBinary(binaryIpRange, ipRange); //Convert IP Address into binary format for comparison.
                
                if(! strncmp(binaryIpAddress, binaryIpRange, ipRange[4]) ) //Compare binary format of Network ID segment of IP address and the IP Range. 
                {
                   printf("%s\n", nextLine); 
                }
                clearString(nextLine, 50); //Clear string from previously red characters.
            }
            
            fclose(fileHandle);
        }
        else
        {
            printf("\n Unable to open input file \"%s\"!!!\n\n", argv[2]);
            return 2;
        }
    }
    else
    {
        printf("\n  Missing paramater!\n  >%s  <--database or --file> <input file> <IP address>\n  Please provide all three parameters.\n\n", argv[0]);
        return 1;
    }

    return 0;
}


void spliIpIntoOctets(int *ipAddress, char *ipString, char *delimiters)
{
    int  i=0;
    char *subString = NULL, tempString[50]="";
    
    strcpy(tempString, ipString);  //Copy passed string and search the copy since "strtok" alters searched string by inserting null in place of a detected delimiter.
    
    subString = strtok( tempString, delimiters ); //Search the copy.
    while( subString != NULL ) 
    {
        ipAddress[i++] = atoi(subString);       //Convert octet from string into integer.
        subString = strtok( NULL, delimiters );
    }
}


void convertIPToBinary(char *binaryIpAddress, int *ipAddress)
{
    int i=0, c=0, octet=0, twoToPowerOf[8] = { 1, 2, 4, 8, 16, 32, 64, 128};
     
    strcpy(binaryIpAddress, "\0"); //Ensure string is clean so that strcat() starts from the beginning.
    
    for(i=0; i<4; i++)
    {
        octet = ipAddress[i];
        
        for(c=7; c>=0; c-=1)
        {
            if(octet >= twoToPowerOf[c])
            {
                strcat(binaryIpAddress, "1");
                octet -= twoToPowerOf[c];  
            }
            else
            {
                strcat(binaryIpAddress, "0");
            }
        }
    }    
}


void clearString (char *string, int length)
{
    int i;

    for( i=0; i<length; i++)
        string[i] = 0;
}
