//Structures
// HuffTree Structure
typedef struct Node {
char ch; // the input character 
struct Node * left, *right; // left and right child of the node
}node;

//Functions
node* newNode(char ch);
void freetree(node* tree);
void printheader(node* currNode);
node* readHeader(FILE * fpr, int *readFlag,char size);
int readbit(FILE* input);
char findpos(node* Tree,FILE*input);
void deCompressFile(char * filename);
node* readHeader(FILE * fpr, int *readFlag,char size);
void printheader(node* );

