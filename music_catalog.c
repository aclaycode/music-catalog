/*-----------------------------------------------------------------------------
 * Programmer: AJ Clay
 * Date: 
 * Name: hw3.c
 * Description: This program implements	a simple music catalog. The program will first read a list of artist/song pairs from a text file and store them in a
                dynamically allocated array of character strings. The first line of the file specifies the number of artist song/pairs in the file. Each subsequent
                line of the file contains on artist song/pair. When the program is run, it will check to see if there are songs by a specific artist(and will tell
                you that there is at least one song by that artist)and if so, it will display those songs by that artist. The program also will also tell you what
                artist a specific song is by. If that song is not in the catalog, no artist will appear next to that song.

 *PseudoCode:   -function prototypes are initialized (and the functions to these prototypes are implemented below the main function)
                -variables are initialized in main function
                -text file is read by program (must be specified by user)
                -program reads and separates all artist and song strings and stores them into character arrays. These arrays are then stored in one larger array(songArray)
                -the program then completes a series of tasks using the functions(described above)
                -print statements are made to relay information to the user(information includes songs and artists as described in description)
                -after all tasks are completed, all allocated memory is freed

 * To run this program:  This program requires a command line argument that
 * specifies the name of the text file containing the input data for the
 * music catalog. In Code::Blocks this argument can be specified by selecting
 * the "Project" menu, then "Set Program's arguments", and then typing the name of
 * of the text file (incuding the .txt extension) in the box labeled "program's
 * arguments".
 -----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEBUFFERSIZE 256

//Function prototypes:
void getNextLine(char buffer[], int bufferSize, FILE *fptr);
void sortCatalogBySong(char *catalog[], int size);
void sortCatalogByArtist(char *catalog[], int size);
char **copyCatalog(char *catalog[], int size);
void printSongsBy(char *artist, char *catalogSortedByArtist[], int size);
int  isArtistInCatalog(char *artist,  char *catalogSortedByArtist[], int size);
char *findArtistForSong(char *song, char *catalogSortedBySong[], int size);

int main(int argc, char *argv[]) {
   FILE *songFile;
   char lineBuffer[LINEBUFFERSIZE];
   char **songArray, **songArraySortedBySong;
   int numSongs;
   char *artistTemp;
   char *songTemp;
   int i;
   char *artistArray; //initialize artist array to store artist strings
   char *musicArray; //initialize music array to store song strings

   // Name of text file containing music catalog entries must be
   // specified as a command line argument

   if(argc==1) {
      printf(" Must supply a file name as command line argument/n");
      return 0;
   }

   //Open input file for read access.  Terminate program is unsuccessful

   if((songFile = fopen(argv[1], "r")) == NULL) {
      printf ("Error opening music file.  Program terminated\n");
      return 0;
   }
   else {
          //Read first line of file which specifies number of aartist/song
          //pairs in the file.  Convert it to an integer using the atoi()
          //function (see pages 317, 318 in the text

          getNextLine(lineBuffer, LINEBUFFERSIZE, songFile);
          numSongs=atoi(lineBuffer);

         //Dynamically allocate an array of "pointers to char" to
         //hold the catalog entries.  Terminate program if unsuccessful.

         songArray = (char **) malloc(2*numSongs*sizeof(char *));
         if (songArray==NULL) {
           printf("Unable to malloc songArray.  Program terminated\n");
          return 0;
         }

         //Now read each line of the file and use the strtok() function (see pages
         // 331,336 in the text) to  break it into separate character strings
         //character strings for the artist and and song title. The pointer
         //variable artistTemp points at the artist name and songTemp points at
         //the song title.
         //The instructor-supplied function getNextLine() is used to read the
         //input file line-by-line.

         for(i=0; i<numSongs; i++) {
           getNextLine(lineBuffer, LINEBUFFERSIZE, songFile);
           artistTemp = strtok(lineBuffer,"/");
           if (artistTemp == NULL) {
             printf("Error parsing input file; Program is terminated\n");
             return 0;
           }
           songTemp = strtok(NULL ,";");
           if (songTemp == NULL) {
             printf("Error parsing input file; Program is terminated\n");
             return 0;
           }
           //Now allocate character arrays to hold the artist name and
           //song title, copy the artist name and song title into these arrays,
           // and make the appropriate elements of songArray point at
           //these strings--songArray[2*i] should point at the artist name and
           //songArray[2*i+1] should point at the song title.  If either of the
           //character arrays cannot be successfully allocated, print and error
	   	   //message and terminate the program.

            artistArray = (char *)malloc((strlen(artistTemp)+1)*sizeof(char )); //allocating memory for array to store artists
            if (artistArray==NULL)
            {
            printf("Unable to malloc artistArray.  Program terminated\n");
            return 0;
            }
            musicArray = (char *)malloc((strlen(songTemp)+1)*sizeof(char )); //allocating memory for array to store songs
            if (musicArray==NULL)
            {
            printf("Unable to malloc musicArray.  Program terminated\n");
            return 0;
            }

            strcpy(artistArray,artistTemp);    //copies artistTemp(temporary place holder for artist) to artist array
            songArray[2*i]=artistArray;        //songArray(of specific numerical element) points to artist in artist array

            strcpy(musicArray,songTemp);       //copies songTemp(temporary place holder for song) to music array
            songArray[2*i+1]=musicArray;       //songArray(of specific numerical element) points to song in song array
         }

         //At this point the catalog has been successfully entered into the songArray.
         //Now need to sort the array, primarily by artist and secondarily by song title.
         //Then make a copy of the songArray and sort it by song title. Note that you
         //will need to complete the implementation of the functions sortCatalogByArtist(),
         //copyCatalog(), and sortCatalogBySong()

         sortCatalogByArtist(songArray, numSongs);
         songArraySortedBySong=copyCatalog(songArray, numSongs);
         if (songArraySortedBySong==NULL) {
           printf("Unable to allocate songArraySOrtedBySong. Program Terminated|n");
           return 0;
         }
         sortCatalogBySong(songArraySortedBySong, numSongs);

        //You will also need to complete implementation of the functions printSongsBy(), isArtistInCatalog(),
        //and findArtistForSong() as specifed in the assignment writeup.
        //The following code provides test cases for your functions.

        //testing the isArtistInCatalog() function:

        printf("***Testing the isArtistInCatalog() function***\n");
        if (isArtistInCatalog("Pink Floyd", songArray, numSongs)) {
          printf("There is at least one Pink Floyd song in the catalog\n");
        }
        else {
         printf("There are no Pink Floyd songs in the catalog\n");
        }
        if (isArtistInCatalog("Jon Kuhl", songArray, numSongs)) {
          printf("There is at least one Jon Kuhl song in the catalog\n");
        }
        else {
         printf("There are no Jon Kuhl songs in the catalog\n");
        }

        //Testing the printSongsByArtist() function

        printf("\n***Testing the printSongsByArtist() function***\n");
        printf("Songs by Bruce Springsteen:\n");
        printSongsBy("Bruce Springsteen", songArray, numSongs);
        printf("\nSongs by U2:\n");
		    printSongsBy("U2", songArray, numSongs);
        printf("\nSongs by Jon Kuhl\n");
        printSongsBy("Jon Kuhl", songArray, numSongs);

       //Testing the findArtistForSong() function

       printf("\n***Testing the findArtistForSong() function***\n");
       artistTemp = findArtistForSong("In the Flesh", songArraySortedBySong, numSongs);
       if(artistTemp !=NULL) {
         printf("The artist for In The Flesh is: %s\n", artistTemp);
       }
       else {
         printf("The artist for In The Flesh could not be found\n");
       }
       artistTemp = findArtistForSong("Summertime Blues", songArraySortedBySong, numSongs);
       if(artistTemp != NULL && artistTemp[0] != '\0') {
         printf("The artist for Summertime Blues is: %s\n", artistTemp);
       }
       else {
         printf("The artist for Summertime Blues could not be found\n");
       }
    }
    //close the text file

    fclose(songFile);

    //Free all dynamically allocated storage--i.e. all character arrays that were
    //allocated to hold artist and song names as well as songArray[] and
    //songArraySortedBySong[].

    free(songArray);
    free(songArraySortedBySong);
    free(artistArray);
    free(musicArray);

    return 0; /* indicates successful termination */

} /* end main */

void getNextLine(char buffer[], int bufferSize, FILE *fptr) {
/***********************************************************************
* Function name: getNextLine
*Description: reads the next line of the text file pointed to by fptr and
*places it into buffer along with a terminating NULL character.
* If the length of the line exceeds buffersize the remaining characters
*in the line are read and discarded.
*inputs: buffer= character array to hold the data read from the file
*        buffersize=int=size of buffer
*        fptr= file pointer(file is assumed to be open for read access
***********************************************************************/
  char temp;
  int i = 0;
  buffer[0] = fgetc(fptr);
  while ( (!feof(fptr)) && (buffer[i] != '\n') &&  i<(bufferSize-1)) {
    i = i +1;
    buffer[i]=fgetc(fptr);
  }

  /* if loop terminated due to full buffer, purge the remaining characters up to
     the next semicolon or newline from the input stream   */
  if ((i == (bufferSize-1)) && (buffer[i] != '\n')) {
    temp = fgetc(fptr);
    while (temp != '\n') {
      temp = fgetc(fptr);
    }
  }
  buffer[i] = '\0';
}


void sortCatalogBySong(char *catalog[], int size)
/**********************************************************************
 * Function Name: sortCatalogBySong
 * Description: Sorts the catalog primarily bysong title
 * Inputs: catalog=array of pointers to char�. Each successive pair of
 *      elements point to strings containing an artist name and associated song
 *      name, respectively.
 *      size = int = number of artist/song pairs in the catalog.  Note that this is
 *      half the number of elements in the array.
 * Outputs: catalog will be sorted into ascending order, by song title
***************************************************************************/
{
 int i; //Counter
 int j; //Another counter
 char *artistKey = NULL;
 char *songKey = NULL;

 for(j=1; j < size; j++) //Insertion sort of strings
 {
   artistKey = catalog[2*j];
   songKey = catalog[2*j + 1];
   i=j-1;

   while(i >= 0 && strcmp(catalog[2 * i + 1],songKey) > 0) //sorts by song
   {
     catalog[2 * i + 2] = catalog[2 * i];
     catalog[2 * i + 3] = catalog[2 * i + 1];
      i--;
   }

   catalog[2 * i + 2] = artistKey;
   catalog[2 * i + 3] = songKey;

 }

}


void sortCatalogByArtist(char *catalog[], int size)
/**********************************************************************
 * Function Name: sortCatalogByArtist
 * Description: Sorts the catalog primarily by artist name and secondarily by
 * song title.
 * Inputs: catalog=array of pointers to char�. Each successive pair of
 *      elements point to strings containing an artist name and associated song
 *      name, respectively.
 *      size = int = number of artist/song pairs in the catalog.  Note that this is
 *      half the number of elements in the array.
 * Outputs: catalog will be sorted into ascending order, primarily by artist name and
 *          secondarily by song title.
***************************************************************************/
{

  int i; //Counter
  int j; //Another counter
  char *artistKey = NULL;
  char *songKey = NULL;

  for(j=1; j < size; j++) //Insertion sort of strings
  {
    artistKey = catalog[2*j];
    songKey = catalog[2*j + 1];
    i=j-1;

    while(i >= 0 && strcmp(catalog[2 * i],artistKey) >= 0) //Sorts by artist
    {
      if(strcmp(catalog[2 * i],artistKey) == 0 && strcmp(catalog[2*i + 1], songKey) < 0)
      {
        break; //Stops the while statement if the artists are equal, but the song in the key is greater
      }

      catalog[2 * i + 2] = catalog[2 * i];
      catalog[2 * i + 3] = catalog[2 * i + 1];
      i--;
    }

    catalog[2 * i + 2] = artistKey;
    catalog[2 * i + 3] = songKey;
  }
}



char **copyCatalog(char *catalog[], int size)
/*********************************************************************
 * Function name: copyCatalog
 * Description: allocates a new array of the same size as catalog and
 *copies the contents of catalog to the new array.  Catalog is not
 *modified.  If the new array is successfully allocated, the function
 * returns a poninter to the new array.  Otherwise it returns a Null
 * pointer.
 * Inputs: catalog=array of pointers to char�. Each successive pair of
 *      elements point to strings containing an artist name and associated song
 *      name, respectively.
 *      size = int = number of artist/song pairs in the catalog.  Note that this is
 *      half the number of elements in the array.
 * Outputs: if the new array is successfully allocated, the function returns
 *          a pointer to it.  Otherwise a NULL pointer is returned.
***************************************************************************/
{
//initializing variables
int i;
char **catalogPtr;

    catalogPtr = (char **)malloc(2*size*sizeof(char *));//allocating memory to store information in pointer array

    for(i=0;i<size;i++) //loops through catalog
    {
    catalogPtr[2*i]=catalog[2*i];     //copies artist from catalog to catalog pointer(pointer to pointer)
    catalogPtr[2*i+1]=catalog[2*i+1]; //copies artist from catalog to catalog pointer(pointer to pointer)
    }

return catalogPtr; //returns new copied catalog pointer
}



void printSongsBy(char *artist, char *catalogSortedByArtist[], int size)
/*********************************************************************
 * Function name: printSongsBy
 * Description:  prints all songs in the catalog performed by a given artist.
 * If there no songs by the artist in the catalog, a message is printed indicating
 * this fact.
 * Inputs: artist= string specifying the artist whose songs are to be printed.
 *	   catalogSortedByArtist = array of pointers to char�. Each successive pair of
 *	   elements point to strings containing an artist name and associated song
 * 	   name, respectively.  The catalog is assumed to be sorted by artist name.
 *	   size = int = number of artist/song pairs in the catalog.  Note that this is
 *	  half the number of elements in the array.
 * Outputs: none
 **********************************************************************/
{
//initialize variable
int j;

    for(j=0;j<size;j++) //loops through catalog
    {
        if(strcmp(artist,catalogSortedByArtist[2*j])==0) //identifies artist in catalog
        {
            printf("%s\n", catalogSortedByArtist[2*j+1]); //program recognizes songs by specified artist and prints these songs
        }
    }

}

int  isArtistInCatalog(char *artist,  char *catalogSortedByArtist[], int size)
/*************************************************************************
 *Function name: isArtistInCatalog
 * Description:  Searches the specified catalog to determine if it contains at least
 * one song by the specified artist.  If so, the function returns 1 (true). Otherwise,
 * the function returns 0 (false).
 * Inputs: artist= character string= artist name
 *	     catalogSortedByArtist = array of pointers to char�. Each successive pair of
 *	   elements point to strings containing an artist name and associated song
 * 	   name, respectively.  The catalog is assumed to be sorted by artist name.
 *	   size = int = number of artist/song pairs in the catalog.  Note that this is
 *	  half the number of elements in the array.
 * Outputs: The function returns an integer value of 1 if there is at least one song
 * 	       by the specified artist in the catalog, and 0 otherwise.  The parameters
 *	     are not modified.
 ***************************************************************************/
{
//initializing variables
int a=0;
int i;

    for(i=0;i<size;i++)    //loops through catalog
    {
        if(strcmp(catalogSortedByArtist[2*i],artist)==0) //identifies artist in catalog
        {
            a=1;               //if program recognizes that there is a specific artist in the catalog, this function returns true(value of 1)
        }
    }

return a;   //function returns true(value of 1) or false(value of 0)
}



char *findArtistForSong(char *song, char *catalogSortedBySong[], int size)
/*************************************************************************
 *Function name: findArtistForSong
 * Description:  Searches the specified catalog to determine the artist for a
 * specified song.  If the song is located in the library, the function returns a
 * pointer to the associated artist.  If not, the function returns  the NULL pointer.
 * The catalog is assumed to be sorted by song title.
 * Inputs: song= character string= the specified song title.
 *	     catalogSortedBySong = array of pointers to char�. Each successive pair of
 *	    elements point to strings containing an artist name and associated song
 * 	    name, respectively.  The catalog is assumed to be sorted by song title.
 *	    size = int = number of artist/song pairs in the catalog.  Note that this is
 *	   half the number of elements in the array.
 * Outputs: If the specified song is found in the catalog, the function returns a
 * pointer to the associated artist name.  Otherwise the function returns a
 * NULL pointer.
 ***************************************************************************/
{
//initializing variables
int i;
char *artistPtr;

    artistPtr =(char *)malloc(sizeof(char )); //allocating memory to store information in artistPtr(pointer to artist)

    for(i=0;i<size;i++) //loops through catalog
    {
        if(strcmp(catalogSortedBySong[2*i+1],song)==0) //identifies song in catalog
        {
            strcpy(artistPtr,catalogSortedBySong[2*i]); //if program recognizes the artist to a specific song, that artist is copied from the catalog to artistPtr
        }                                               //and the artist(artistPtr) is returned
    }

return artistPtr; //artist is returned
}