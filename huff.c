
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "huff.h"

#define FAKE_EOF 256 
//Function to load the input file
int* Load_File(char* filename){
    FILE *input;
    int cnt = 0;
    long filesize = 0;
    int i, j,c;
    int* arr = malloc(256 * sizeof(int));// making it 257 to inculde fake EOF
    input = fopen(filename,"r");
    if(input == NULL){
        return 0;
    }
    // finding the size of the file
    fseek(input,0,SEEK_END);
    filesize = ftell(input);
    rewind(input);
   for (i = 0; i < 256; i++){
       for(j = 0; j < filesize; j++){
           c = fgetc(input);
           if(i == c){
               cnt++;
           }
       }
       rewind(input); // have to reset the file pointer
       arr[i] = cnt;
       cnt = 0; // have to reset the count
   }
    //arr[256] = 256;
   fclose(input);
   return arr;
}
// Function to create a new node with the given character and frequency
node* newNode(char ch, unsigned freq){ 
    node* temp = (node*)malloc(sizeof(node)); 
    temp->left = temp->right = NULL; 
    temp->ch = ch; 
    temp->freq = freq; 
    return temp; 
} 
//Function to create a min heap 
minheap* create_minheap(unsigned capacity)
{ 
    minheap* minHeap   = (minheap*)malloc(sizeof(minheap)); 
  
    // current size is 0 
    minHeap->size = 0; 
  
    minHeap->capacity = capacity; 
  
    minHeap->array  = (node**)malloc(minHeap-> capacity * sizeof(node*)); 
    return minHeap; 
} 
// Function to  swap two nodes
void swapMinHeapNode(node** a, node** b) 
{ 
    node* t = *a; 
    *a = *b; 
    *b = t; 
} 
// The minheapify function that is required to make sure the heap properties are not violated
void minHeapify(minheap* minHeap, int idx) 
{ 
    int smallest = idx; 
    int left = 2 * idx + 1; 
    int right = 2 * idx + 2; 
  
    if (left < minHeap->size && minHeap->array[left]-> 
freq < minHeap->array[smallest]->freq) 
        smallest = left; 
  
    if (right < minHeap->size && minHeap->array[right]-> 
freq < minHeap->array[smallest]->freq) 
        smallest = right; 
  
    if (smallest != idx) { 
        swapMinHeapNode(&minHeap->array[smallest], 
                        &minHeap->array[idx]); 
        minHeapify(minHeap, smallest); 
    } 
} 
// Function to insert a new node into the minheap
void insertMinHeap(minheap* minHeap,  node* minHeapNode) 
{ 
    ++minHeap->size; 
    int i = minHeap->size - 1; 
  
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) { 
  
        minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
        i = (i - 1) / 2; 
    } 
  
    minHeap->array[i] = minHeapNode; 
} 
// Function to extract the min value node(which is the first node) in the heap
node* extractMin(minheap* minHeap) 
{ 
    node* temp = minHeap->array[0]; 
    minHeap->array[0] = minHeap->array[minHeap->size - 1]; 
    --minHeap->size; 
    minHeapify(minHeap, 0); 
    return temp; 
} 
// A standard function to build min heap 
void buildMinHeap(minheap* minHeap) 
{ 
    int n = minHeap->size - 1; 
    int i; 
  
    for (i = (n - 1) / 2; i >= 0; --i) 
        minHeapify(minHeap, i); 
} 
// Function to create the minHeap for the given data 
minheap* createAndBuildMinHeap(char data[], int freq[], int size) // this function is fine
{ 
   minheap* minHeap = create_minheap(size); 
  
    for (int i = 0; i < size; ++i) 
        minHeap->array[i] = newNode(data[i], freq[i]); 

    minHeap->size = size; 
    buildMinHeap(minHeap); 
    return minHeap; 
} 
// The following are functions for the huffman tree
// Function to check if size of heap is 1 or not 
int isSizeOne(minheap* minHeap) 
{ 
    return (minHeap->size == 1); 
} 
// Function to find the height of the tree
int Max_Height(node* root){
    if(root==NULL)  
       return 0; 
   else 
   { 
       /* compute the depth of each subtree */
       int leftdepth = Max_Height(root->left); 
       int rightdepth= Max_Height(root->right); 
  
       /* use the larger one */
       if (leftdepth > rightdepth) 
        {
           return(leftdepth + 1); 
           }
       else 
       return(rightdepth +1); 
   } 
}

// The main function that builds Huffman tree 
node* buildHuffmanTree(char data[], int freq[], int size) 
{ 
    node *left, *right, *top; 
  
    // Step 1: Create a min heap of capacity 
    // equal to size.  Initially, there are 
    // modes equal to size. 
    minheap* minHeap = createAndBuildMinHeap(data, freq, size); 
  
    // Iterate while size of heap doesn't become 1 
    while (!isSizeOne(minHeap)) { 
  
        // Step 2: Extract the two minimum 
        // freq items from min heap 
        left = extractMin(minHeap); 
       //printf("\n%d  and %c are extracted for left node",left->freq, left->ch);
        right = extractMin(minHeap); 
        //printf("\n%d and %c are extracted for right node",right->freq,right->ch);
       // printf("\n");
        
        // Step 3:  Create a new internal 
        // node with frequency equal to the 
        // sum of the two nodes frequencies. 
        // Make the two extracted node as 
        // left and right children of this new node. 
        // Add this node to the min heap 
        // '$' is a special value for internal nodes, not used 
        top = newNode('$', left->freq + right->freq); 
  
        top->left = left; 
        top->right = right; 
  
        insertMinHeap(minHeap, top); 
    } 
  
    // Step 4: The remaining node is the 
    // root node and the tree is complete. 
    return extractMin(minHeap); 
} 
// Function to get the leaf count of the tree
int getLeafNodesCount(node* root)
{
	if(root== NULL)	return 0;
	if(root->left == NULL && root->right==NULL)	return 1;            
	return getLeafNodesCount(root->left) + getLeafNodesCount(root->right);      
}
// helper functions to create the huffman code table
void calcHuffCodesHelper(node* root, int **hufftable, int * i, int j)
{
	if (root == NULL)	return;

	if((root->left == NULL) && (root->right == NULL))
	{
		hufftable[*i][0] = root->ch;
		(*i)++;
		return;
	}
	
	if(root->left != NULL)
	{
		int numRow = getLeafNodesCount(root->left);
		int k;
 		for(k = *i; k < (*i) + numRow; k++)
		{
			hufftable[k][j] = 0;
		}
		calcHuffCodesHelper(root->left, hufftable, i, j+1);
    	}
	
	if(root->right != NULL)
	{
		int numRow = getLeafNodesCount(root->right);
		int k;
 		for(k = *i; k < (*i) + numRow; k++)
		{
			hufftable[k][j] = 1;
		}
		calcHuffCodesHelper(root->right, hufftable, i, j+1);
    	}
}
void calcHuffCodes(node* root, int ** hufftable)
{
  int i = 0;
  calcHuffCodesHelper(root, hufftable, &i, 1);
}
int ** createHuffTable(node* root)
{
	int tree_height = Max_Height(root);
	int leaf_nodes = getLeafNodesCount(root);
  	int ** hufftable = malloc(sizeof(int*) * leaf_nodes);
	int i, j;
	for(i = 0; i < leaf_nodes; i++)
	{
		hufftable[i] = malloc(sizeof(int) * (tree_height + 1));
		for(j = 0; j < tree_height + 1; j++)
		{
			hufftable[i][j] = -1;
		}
	}
	calcHuffCodes(root, hufftable);
	return hufftable;
}
// call the tree builter function and assign it to a node called tree
node *HuffmanTree(char data[], int freq[], int size) 
{ 
    // Construct Huffman Tree 
    node* tree = buildHuffmanTree(data, freq, size); 
  return tree;
} 

// The following functions are meant to write the encoded data to the output file
// write the tree to the output file as a header
// works correctly atm however its is not good enough as its char so try the bit header
void fileheader(node* root,FILE *output)
{
    if(root->left == NULL && root->right == NULL)
    {
        char val = '1';
        fwrite(&val,sizeof(char),1,output);
        val = root->ch;
        fwrite(&val,sizeof(char),1,output);
    }
    else
    {
        char val = '0';
        fwrite(&val,sizeof(char),1,output);
        fileheader(root->left,output);
        fileheader(root->right,output);
    }
}
/*
void write_bit_char(FILE * fphuff, char data)
{//write an ASCII character to the file 1 bit at a time
	unsigned int newdata = (unsigned int) data;
	//1000 0000
	unsigned char mask = 0x80;

	while (mask > 0)
	{//loop 8 times for the 8 bits
		if ((mask & newdata) == mask)
		{//if the furthest left bit is 1, pack a 1
			write_bit(fphuff, 1);
		} else
		{//if the furthest left bit is 0, pack a 0
			write_bit(fphuff, 0);
		}//shift mask to the right
		mask >>= 1;
	}
	return;
}
*/
/*
void write_bit(FILE * fphuff, unsigned char bit)
{//packs 1 bit at a time and writes to the file when a byte has been filled up
	if(!bitspot)
	{//if we just wrote a byte to the file, reset the buffer byte
		currentbyte = 0;
	}
	//shift the bit to write to the next unoccupied location, then add it to the buffer byte
	unsigned char temp = bit << (7 - bitspot);
	currentbyte |= temp;

	if (bitspot == 7)
	{//if we have filled out byte, write it to the file
		fwrite(&currentbyte, sizeof(unsigned char), 1, fphuff);
	}
	//if we just wrote a full byte to the file, reset the next bit position
	bitspot = (bitspot + 1) % 8;
	return;
}
*/
int* char_pos(int** Huffmantable,char ch,int rowsize,int colsize){
    int* posarray = malloc(sizeof(int) * 2);
    int j = 1;
    for(int i = 0; i < rowsize; i++){
        if(ch == Huffmantable[i][0]){
            posarray[0] = i;
        }
    }
    while(j < colsize  && Huffmantable[posarray[0]][j] != -1){
        j++;
    }
    posarray[1] = j -1; // It was creating a extra col bc j starts at one
    return posarray;
}
// encode the input file and write the encoded data to a output file
 void encode(char*filename,int **hufftable,node* root,int * ascii_array,int rowsize,int colsize)
 {
   FILE* input= fopen(filename,"r");
    //strcpy(filename,input); // is this correct?
    strcat(filename,".huff");
    FILE* output = fopen(filename,"wb");
    long filesize;
    char c = 0;
    uint8_t buffer = 0x00;
    int bufflen = 0; 
    bool check = false;
    int* posarray;
    //find the filesize
    fseek(input,0,SEEK_END);
    filesize = ftell(input);
    rewind(input);
    //write header
    char size = 0;// write how many leaf nodes r in the tree
    size = (char)rowsize;
   fwrite(&size,sizeof(size),1,output);
    //write the file header
   fileheader(root,output);
    //write the filesize
   fwrite(&filesize,sizeof(filesize),1,output);
 
 while(check == false)
 {
     c = fgetc(input);
    // printf("\nThe read char is %c",c); //the char is read correctly
     
        if(c == EOF)
        {
            check = true;
        }
        else
        {   check = false;
            posarray = char_pos(hufftable,c,rowsize,colsize);
           //printf("\nThe pos values r %d, %d",posarray[0],posarray[1]);
            for(int i = 1; i <= posarray[1]; i++)
            {
                    buffer = buffer | hufftable[posarray[0]][i] << (7 - bufflen); 
                   // printf("\nbuffer value after adding the bit is %d",buffer);
                        bufflen++; 
                    if(bufflen == 8) 
                    {
                    // printf("\nbuffer value atm is %d",buffer);
                     fwrite(&buffer,sizeof(buffer),1,output);
                      buffer = 0x00;
                      bufflen = 0;
                   }
                   
            }
            free(posarray); 
           }
 }
    //EOF dont work so not doing it atm
    if(check == true)
    {
        while(bufflen < 8) //used to make sure that full bytes are written to the file aka padding
        {
            buffer = buffer | 0 << (7 - bufflen);
            bufflen++;
        }
        if(bufflen == 8) 
                    {
                     // printf("\nbuffer value atm is %d",buffer);
                      fwrite(&buffer,sizeof(buffer),1,output);
                      buffer =  0;
                      bufflen = 0;
                    }
    }
  
}
//Main function to handle file calls
int main(int argc, char **argv)
{
   if (argc < 2) {
    fprintf(stderr, "No input file given\n");
    return EXIT_FAILURE;
  } 
  else if (argc > 2) {
    fprintf(stderr, "Too many input arguments\n");
    return EXIT_FAILURE;
  }
    int* ascii_array; 
    int** hufftable;
    node* tree;
    int i,k = 0,j =0, cnt = 0;
    int height;
    ascii_array =  Load_File(argv[1]);
    for(i = 0; i < 256; i++){
        if(ascii_array[i] != 0){
            cnt++;
        }
    }
   
    int freqarray[cnt];
    char chararray[cnt];

    for(i = 0; i < 256; i++){
        if(ascii_array[i] != 0){
            chararray[k++] = (char)i;
            freqarray[j++] = ascii_array[i];
        }
    } 
    //adding the fake EOF into the min heap node nope didnt work
    tree = HuffmanTree(chararray,freqarray,cnt);
    height = Max_Height(tree);
    hufftable = createHuffTable(tree);
  /* for(i = 0; i < cnt; i++){
      printf("\nThe char is %c",hufftable[i][0]);
       for(k = 0; k < height; k++)
        {
            printf("\n The Bit value is %d",hufftable[i][k]);
        }

    }
    */
    encode(argv[1],hufftable,tree,ascii_array,cnt,height); // works but overall huff is super slow
   return 0;
}
