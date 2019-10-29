#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "unhuff.h"

//Create a new node with the given char value
node* createnode(char ch)
{
	node* Node = malloc(sizeof(Node));
	Node -> ch = ch;
	Node -> left = NULL;
	Node -> right = NULL;
	return Node;
}

//Destroy a tree to free the allocated nodes including all sub-children. 
void freenode(node* tree)
{
	if (tree == NULL)
	{
		return;
	}
	freenode(tree -> left);
	freenode(tree -> right);
	free(tree);
}
//Read the header from file
node* readHeader(FILE * input, int *readFlag,char size)
{	
    int cnt = 0;
    char ch;
	if (*readFlag == 1 && cnt < size)	
    fread(&ch, 1, 1, input);
	if (ch == 0)
	{
		*readFlag = 0;
		exit(0);
	}
	if (ch == '1')
	{	cnt++;
		char ch2;
		fread(&ch2, 1, 1, input);
		return createnode(ch2);
	}
	else
	{
		node*  left = readHeader(input, readFlag,size);
		node*  right = readHeader(input, readFlag,size);
		node* newnode = createnode(0);
		newnode->left = left;
		newnode->right = right;
		return newnode;
	}
    
}

// the header is correct thank god 
/*
void printheader(node* currNode)
{

   if(currNode->left == NULL && currNode->right == NULL)
    {
        char val = '1';
        printf("%c",val);
        val = currNode->ch;
        printf("%c",val);
    }
    else
    {
        char val = '0';
        printf("%c",val);
        printheader(currNode->left);
        printheader(currNode->right);
    }
}
*/
//Decodes the given char
char findpos(node* Tree,FILE*input)
{
	node* Node;
	Node = Tree;
	while(Node->left != NULL || Node->right != NULL)
	{
		if(readbit(input)){
			Node = Node->right;
		}
		else
		{
			Node = Node->left;
		}
	}
	return Node->ch;
}
//Read a bit from the input file
//YAY IT WORKS FINALLY
int readbit(FILE* input){
	  /* buffer holding raw bits and size of MSB filled */
    static int bits = 0, bitcount = 0;
    int nextbit;
    
    if(bitcount == 0)
    {
        bits = fgetc(input);
        bitcount = (1 << 7);
    }
    
    nextbit = bits / bitcount;
    bits %= bitcount;
    bitcount /= 2;
    
    return nextbit;
}

//Read HuffMan header and decompress file
void deCompressFile(char * filename)
{
	long k = 0;
	char c;
	long filesize;
    FILE * input = fopen(filename, "rb");
	strcat(filename, ".unhuff");
    FILE * output = fopen(filename,"w");
	if(input ==  NULL)
	{
		printf("Error opening file %s\n", filename);
		return;
	}
	char size;
    fread(&size,sizeof(char),1,input);
	int readFlag = 1;
	node* huffTree = readHeader(input, &readFlag,size);
	node* currNode = huffTree;
    //printheader(currNode);
    fread(&filesize,sizeof(filesize),1,input);
	while(k < filesize){
	  k++;
	  c = findpos(currNode,input);
	//  printf("\nThe char being written is %c",c);
	  fputc(c,output);
	}
	freenode(huffTree);
	fclose(input);
	fclose(output);
}

// Main function to send the input file to the decoder function
int main(int argc, char**argv)
{
	if (argc != 2)	
	{
		printf("Invalid number of arguments\n");
		return -1;
	}
	deCompressFile(argv[1]);
	return 0;
}
