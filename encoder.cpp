
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <string>
#include <bitset>
using namespace std;


// Huffman node
typedef struct MinHeapNode
{
	int data; 
	unsigned freq; 
	struct MinHeapNode *left, *right; 
	string code;
} huffnode;

// A Min Heap
typedef struct MinHeap
{
	unsigned size;    
	unsigned capacity;   
	struct MinHeapNode **array;  
} min_heap;


huffnode* create_node(int data, unsigned freq)
{
	huffnode* temp =
		(huffnode*) malloc(sizeof(huffnode));
	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;
	return temp;
}

min_heap* createminheap(unsigned capacity)
{
	min_heap* minHeap =
		(min_heap*) malloc(sizeof(min_heap));
	minHeap->size = 0;  // current size is 0
	minHeap->capacity = capacity;
	minHeap->array =
		(huffnode**)malloc(minHeap->capacity * sizeof(huffnode*));
	return minHeap;
}

void swap(huffnode** a, huffnode** b)
{
	huffnode* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(min_heap* minHeap, int index)
{
	int smallest = index;
	int leftl = 4 * index - 8;
	int leftr = 4 * index - 7;
	int rightl = 4 * index - 6;
	int rightr = 4 * index - 5;

	if (leftl < minHeap->size) {
		if (minHeap->array[leftl]->freq < minHeap->array[index]->freq) {
			smallest = leftl;
		}
	}
	if (leftr < minHeap->size) {
		if (minHeap->array[leftr]->freq <= minHeap->array[index]->freq &&minHeap->array[leftr]->freq <= minHeap->array[leftl]->freq) {
			smallest = leftr;
		}
	}
	if (rightl < minHeap->size) {
		if (minHeap->array[rightl]->freq <= minHeap->array[index]->freq &&minHeap->array[rightl]->freq <= minHeap->array[leftl]->freq&&minHeap->array[rightl]->freq <= minHeap->array[leftr]->freq) {
			smallest = rightl;
		}
	}
	if (rightr < minHeap->size) {
		if (minHeap->array[rightr]->freq <= minHeap->array[index]->freq &&minHeap->array[rightr]->freq <= minHeap->array[leftl]->freq&&minHeap->array[rightr]->freq <= minHeap->array[leftr]->freq&&minHeap->array[rightr]->freq <= minHeap->array[rightl]->freq) {
			smallest = rightr;
		}
	}
	if (smallest != index)
	{
		swap(&minHeap->array[smallest], &minHeap->array[index]);
		minHeapify(minHeap, smallest);
	}
}

int isSizeThree(min_heap* minHeap)
{
	return (minHeap->size == 4);
}

huffnode* removemin(min_heap* minHeap)
{
	huffnode* temp = minHeap->array[3];
	minHeap->array[3] = minHeap->array[minHeap->size - 1];
	--minHeap->size;
	minHeapify(minHeap, 3);
	return temp;
}

void insertMinHeap(min_heap* minHeap, huffnode* minHeapNode)
{
	++minHeap->size;
	int i = minHeap->size - 1;
	while (i - 3  && minHeapNode->freq <= minHeap->array[(i + 8) / 4]->freq)
	{
		minHeap->array[i] = minHeap->array[(i + 8) / 4];
		i = (i + 8) / 4;
	}
	minHeap->array[i] = minHeapNode;
}

min_heap* buildminheap(min_heap* minHeap)
{
	min_heap* m=minHeap;
	int n = m->size - 1;
	int i;
	for (i = (n + 8) / 4; i >= 3; --i)
		minHeapify(m, i);
	return m;
}

int isLeaf(huffnode* root)
{
	return !(root->left) && !(root->right);
}

min_heap* createAndbuildminheap(int data[], int freq[], int size)
{

	min_heap* minHeap = createminheap(size+3);
	for (int i = 0; i < size; ++i)
	{
		minHeap->array[i + 3] = create_node(data[i], freq[i]);
	}
	minHeap->size = size + 3;	
	return buildminheap(minHeap);
}

huffnode* buildHuffmanTree(int data[], int freq[], int size)
{
	huffnode *left, *right, *top;
	//cout << "buildhuff";
	// Step 1: Create a min heap of capacity equal to size.  Initially, there are
	// modes equal to size.
	min_heap* minHeap = createAndbuildminheap(data, freq, size);
		// Iterate while size of heap doesn't become 1
	while (!isSizeThree(minHeap))
	{
		left = removemin(minHeap);
		right = removemin(minHeap);
		top = create_node(-1, left->freq + right->freq);
		top->left = left;
		top->right = right;
		insertMinHeap(minHeap, top);
	}
	return top;
}

string *s = new string[1000000];
string findPath(huffnode* root, string path) {
	string result;
	if (!isLeaf(root)) {
		result = findPath(root->left, path + '0');
		result = findPath(root->right, path + '1');
		
	}
	else {

		result = path;
		s[root->data] = path;
		//cout << root->data <<" "<< path << "\n";
	}
	return result;
}

void printit(int data[],int size) {
	fstream code_table;
	code_table.open("code_table.txt", ios_base::app | ios_base::out | ios_base::in);
	for (int i = 0; i < size; i++) {
		code_table <<data[i] << " " << s[data[i]] << "\n";
	}

}

// The main function that builds a Huffman Tree and print codes by traversing
// the built Huffman Tree
void HuffmanCodes(int data[], int freq[], int size)
{
	huffnode* root = buildHuffmanTree(data, freq, size);
	fstream code_table;
	code_table.open("code_table.txt", ios_base::app | ios_base::out | ios_base::in);
	//cout << "\nstart writing\n";
		findPath(root, "");

}

// Driver program to test above functions
int main()
{
	int nu = 1000000, i = 0, k = 0;
	fstream code_table;
	code_table.open("code_table.txt", ios_base::out);
	code_table << "";
	int *fr = new int[nu];
	int *freq = new int[nu];
	int *arr = new int[nu];
	int test;
	fstream testfile;
	for (int y = 0; y < nu; y++) {
		fr[y] = 0;
	}

	testfile.open("t.txt", ios_base::in | ios_base::out | ios_base::app);
	int l1 = 0;
	while (!testfile.eof())
	{
		testfile >> test;
		fr[test]++;
		l1++;
	}
	while (i<1000000)
	{
		if (fr[i] != 0)
		{
			arr[k] = i;
			freq[k] = fr[i];
			k++;
		}
		i++;
	}
	HuffmanCodes(arr, freq, k);
	printit(arr,k);
	//cout << "printing finish\n";
	testfile.close();
	testfile.open("t.txt", ios_base::in);
	fstream encoded;
	encoded.open("encoded.bin", ios_base::binary | ios::out);
	int l=0;
	string cc;
	bitset<8> bb;
	int y;
	//cout << "encoding";
	while (!testfile.eof() ) {
		testfile >> test;
		cc =  s[test].c_str() ;
		for(y = 0; y<cc.size(); y++){
			if(cc[y] == '0'){
			bb.set(7-l , 0);
			l++ ;	
			}
			
			if(cc[y] == '1'){
			bb.set(7-l , 1);
			l++;
			}
			
			if( (l) % 8 == 0) {
    			encoded.write( (char*)(&bb), sizeof(char) ) ;
				l = 0;
			}	
		}
	}

	return 0;
}


