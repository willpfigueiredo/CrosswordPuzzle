/*
	Crossword puzzle solver
	
	It takes a crossword char matrix, a list of words and fit the words into the word spaces into the matrix
	
	Author:William P. D. Figueiredo

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Copies the colth column from **matrix into *target	
crossword_count: size of the square puzzle matrix and target string
*/
void vert2hor(char *target, char **matrix, int col, int crossword_count){
	int i;

	for (i = 0; i < crossword_count; i++){
		target[i] = matrix[i][col];
	}
}

/*
	Replaces the colth column from **matrix with *source
	crossword_count: size of the square puzzle matrix and source string
*/
void hor2vert(char *source, char **matrix, int col, int crossword_count){
	int i;

	for (i = 0; i < crossword_count; i++){
		matrix[i][col] = source[i];
	}
}

/*
Prints the square matrix char **Puzzle of size crossword_count
*/
void printPuzzle(char **Puzzle, int crossword_count)
{
	int i;
	
	for(i = 0; i < crossword_count; i++)
	{
		puts(Puzzle[i]);

	}
}


/*
Tries to vertically fit the word in **words indexed by windex into the **cpuzzle matrix

*/

int tryHorizontal(int windex, char **words, char **cpuzzle, int crossword_count)
{
	int i,j,l,slen;
	char temp[crossword_count+1];
	
	slen = strlen(words[windex]);
	
	
	for(i = 0; i < crossword_count; i++)
	{
		l = 0;
		strcpy(temp,cpuzzle[i]);
		
		for (j = 0; j <crossword_count; j++)
		{
			
			if((cpuzzle[i][j] == '-' || cpuzzle[i][j] == words[windex][l]) && words[windex][l] != '\0')
			{
				cpuzzle[i][j] = words[windex][l];
				l++;
			}
			else if (l == slen && j < crossword_count && cpuzzle[i][j+1]!= '-') return 1;
			//reached the end of the word, the next spot is not a letter spot (the space is the size of the word) and the line is valid: success
			else 
			{
				
				l = 0;//resets l
				strcpy(cpuzzle[i],temp); //restores line to try to fit the word in the remaining line spots
			}
			
		}
		if (l == slen ) return 1;
		strcpy(cpuzzle[i],temp);//restores the line in which the functions tried to fit a word
		
	}
		

	
		
	
	
	return 0;//fail

	
}

/*
Tries to vertically fit the word in **words indexed by windex into the **cpuzzle matrix
*/

int tryVertical(int windex, char **words, char **cpuzzle, int crossword_count)
{
	int i,j,l,slen;
	char temp[crossword_count];
	
	slen = strlen(words[windex]);
	
	
	for(j = 0; j < crossword_count; j++)
	{
		l = 0;
		
		//copies a column of the corssword matrix into temp
		vert2hor(temp,cpuzzle, j, crossword_count);
		
		
		for (i = 0; i <crossword_count; i++)
		{
			
			
			if((cpuzzle[i][j] == '-' || cpuzzle[i][j] == words[windex][l]) && words[windex][l] != '\0')
			{
				//found a place to a letter from the source word
				cpuzzle[i][j] = words[windex][l];
				l++;
			}
			else if (l == slen && i < crossword_count) return 1;//
			else 
			{
				
				l = 0;
				hor2vert(temp,cpuzzle, j, crossword_count);
			}
			
		}
		if (l == slen ) return 1;
		hor2vert(temp,cpuzzle, j, crossword_count);//restores the column in which the function tried to fit a word
		
	}
		

	
		
	
	
	return 0;//fail

	
}

/*
prints the words from **words
*/
void printWords(char **words, int nwords)
{
	int i;
	printf("Words list:\n");
	for(i=0; i<nwords; i++){
		printf("%d: %s\n", i, words[i]);
	}
}

/*
	Sorts the words in **words in decreasing size order
	
	nwords: number of words in **words
*/
void wordOrder(char **words, int nwords)
{
	int i,j,x;
	char *temp;

	for(i=0; i<nwords-1; i++)
	{
		for(j=i+1;j<nwords; j++)
		{
		
		 if(strlen(words[i])< strlen(words[j]))
		 {
		 	temp = words[i];
		 	words[i] = words[j];
		 	words[j] = temp;
		 	
		 	
		 	
		 	
		 }
		}
	}
	
	
	
}

void rebuildWords(char **words, int reIndex, int nwords)
{
	char *temp;
	
	temp = words[reIndex];
	words[reIndex] = words[reIndex +1];
	words[reIndex +1] = temp;
	wordOrder(words, nwords);
	
	
	
}

/*
 Copies a crossword_count size square char matrix source into the target matrix
*/
void cpyMtrx(char  **target, char  **source, int crossword_count)
{
	int i;
	
	for(i=0; i<crossword_count; i++){
		strcpy(target[i], source[i]);
	}
}

/*
	fits the words in **words into the **cpuzzle matrix
	nwords: number of words to fit
	**cpuzzle: pointer to the puzzle matrix
	**words: pointer to word list
	crossword_count size of the square puzzle matrix
	
	return char **:  address of the solved crosswordpuzzle matrix 
	
*/

char** solvePuzzle (int nwords, char **cpuzzle, char **words, int crossword_count)
{
	int i,r;
	int reIndex = 0;
	char **tempmatrix = malloc(sizeof(char*)* crossword_count);
	
	for(i=0; i<crossword_count; i++)
	{
		tempmatrix[i] = (char *)malloc(sizeof(char)*(crossword_count+1));
	}
	
	cpyMtrx(tempmatrix,cpuzzle, crossword_count);

	
	
	for( i = 0; i < nwords; i++){
		r = tryHorizontal(i, words, tempmatrix, crossword_count);
		
		
		if(r==0)
		{
			
		    r=tryVertical(i, words, tempmatrix, crossword_count);
		    
		}
		
		if(r==0 && reIndex < nwords-1)
		{
		   //puts("Remaking all");	   
		   rebuildWords(words, reIndex, nwords);
		   cpyMtrx(tempmatrix,cpuzzle, crossword_count);
		   i=(-1);	
		   reIndex++;
		   if(reIndex == nwords-1) 
		   	reIndex = 0;
		}
		
	}
	

	return tempmatrix;
	
}


/*
	Solves a crossword puzzle fitting the semiconlon separated words in char * words into the char** crossword matrix
	- indicates a place for a letter
	. indicates no letter
	crossword_count: size of the square crossword matrix
	
	returns **char :crossword matrix with the words 
*/
char** crosswordPuzzle(int crossword_count, char** crossword, char* words) 
{
	int nwords, j,x;
	char *swords[crossword_count];
	char buffer[crossword_count];
	char **SolvedPuzzle;
	j=0;
	nwords=0;
	x=0;

	do//separate the words and storing them in an array of char arrays
	{
		
		if(words[x] != ';')
		{
			buffer[j] = words[x];
			j++;
		}
		
		
		
		else
		{
			buffer[j] = '\0';
			swords[nwords] = (char*)malloc(sizeof(char) * (strlen(buffer)+1));
			strcpy(swords[nwords],buffer);
			nwords++;
			j=0;
		}
		
		if(words[x+1] == '\0')
		{
			buffer[j] = '\0';
			swords[nwords] = (char*)malloc(sizeof(char) * (strlen(buffer)+1));
			strcpy(swords[nwords],buffer);
			nwords++;
			j=0;
		}
		
	
		x++;
	}while(words[x] != '\0');
	
	
	

	wordOrder(swords, nwords);
	
	
	
	return(solvePuzzle(nwords, crossword, swords,crossword_count ));
	
	
	
}


int main ()
{
	char *cpuzzle[]={ ".-----....",
              		  ".....-....",
			  		  ".....-....",
              		  ".....-..-.",
			  		  "........-.",
			  		  ".....-..-.",
              		  ".-----..-.",
			  		  ".....-..-.",
			  		  ".....-..--",
			  		  "........-."  };


	char  words[] = { "palio;outra;mala;ouro;rastape;pe"};
	
	
	
	
    int nwords;
	
	int result_count;

	int crossword_count= 10;
	
	
	printPuzzle(crosswordPuzzle(crossword_count, cpuzzle, words),crossword_count);
	  
	
	return 0;
}
