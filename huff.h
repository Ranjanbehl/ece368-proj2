//Structures
// do I really need the usigned portions 
// A Huffman tree node 
typedef struct Node {
char ch; // the input character 
int freq; // frequency of the character
struct Node * left, *right; // left and right child of the node
}node;
// A minheap 
typedef struct MinHeap {
unsigned size; // The current size of the min heap
unsigned capacity;// of the min heap
struct Node** array; // Array of node pointers 

}minheap;

//Functions
//make the naming better
int* Load_File(char* filename);
node* newNode(char ch, unsigned freq);
minheap* create_minheap(unsigned capacity);
void swapMinHeapNode(node** a, node** b);
void minHeapify(minheap* minHeap, int index);
void insertMinHeap(minheap* minHeap,  node* minHeapNode);
node* extractMin(minheap* minHeap);
void buildMinHeap(minheap* minHeap);
minheap* createAndBuildMinHeap(char data[], int freq[], int size);
int isSizeOne(minheap* minHeap);
int Max_Height(node* root);
node* buildHuffmanTree(char data[], int freq[], int size);
int leafCount(node* root);
void gethuffcodes(node* root, int **hufftable, int * i, int j);
int ** createHuffTable(node* root);
node *HuffmanTree(char data[], int freq[], int size);
int* char_pos(int** Huffmantable,char ch,int rowsize,int colsize);
void fileheader(node* root,FILE *output);
void encode(char*filename,int **hufftable,node* root,int* ascii_array,int rowsize,int colsize);
void freetree(node* tree);
