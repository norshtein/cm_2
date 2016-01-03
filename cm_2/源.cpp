#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<string>
#include<fstream>

using namespace std;

map<char, int> charOccorTimes;
string text;

//huffman
struct HTNode
{
	char character;
	int parent, lChild, rChild, weight;
};
map<char, string> hashTable;
HTNode* huffmanTree;
const int Infinity = 2100000000;


void readData()
{
	char c;
	while (cin >> c)
	{
		if (c == '\n')
			continue;
		charOccorTimes[c]++;
		text.append(1, c);
	}
}
void initHuffmanTree()
{
	int charNum = charOccorTimes.size();
	int treeSize = charNum * 2 - 1;
	huffmanTree = new HTNode[treeSize];
	int i;
	map<char, int>::iterator itor;
	for (i = 0, itor = charOccorTimes.begin(); itor != charOccorTimes.end(); itor++, i++)
	{
		huffmanTree[i].parent = -1;
		huffmanTree[i].character = itor->first;
		huffmanTree[i].weight = itor->second;
		huffmanTree[i].lChild = huffmanTree[i].rChild = -1;
	}
	for (int i = 0; i < treeSize; i++)
		huffmanTree[i].parent = -1;
}
void buildHuffmanTree()
{
	int charNum = charOccorTimes.size();
	int treeSize = charNum * 2 - 1;
	for (int i = 0; i < charNum - 1; i++)
	{
		int minIndex = -1, secondMinIndex = -1;
		int minValue = Infinity, secondMinValue = Infinity;
		for (int j = 0; j < charNum + i; j++)
		{
			if (huffmanTree[j].parent == -1 && huffmanTree[j].weight < minValue)
			{
				secondMinValue = minValue;
				secondMinIndex = minIndex;
				minValue = huffmanTree[j].weight;
				minIndex = j;
			}
			else if (huffmanTree[j].parent == -1 && huffmanTree[j].weight < secondMinValue)
			{
				secondMinValue = huffmanTree[j].weight;
				secondMinIndex = j;
			}
		}
		huffmanTree[charNum + i].weight = minValue + secondMinValue;
		huffmanTree[charNum + i].lChild = minIndex;
		huffmanTree[charNum + i].rChild = secondMinIndex;
		huffmanTree[minIndex].parent = huffmanTree[secondMinIndex].parent = charNum + i;
	}
}
void getHuffmanCode()
{
	int charNum = charOccorTimes.size();
	int treeSize = 2 * charNum - 1;
	//开的数组比较松
	char* temp = new char[treeSize];
	for (int i = 0; i < charNum; i++)
	{
		int now = i;
		int parent = huffmanTree[now].parent;
		int startPosition = treeSize - 1;
		while (parent != -1)
		{
			if (huffmanTree[parent].lChild == now)
				temp[startPosition--] = '0';
			else
				temp[startPosition--] = '1';
			now = parent;
			parent = huffmanTree[parent].parent;
		}
		hashTable[huffmanTree[i].character] = string(temp + startPosition + 1, temp + treeSize);
	}
}
void writeDocumentHuffmanVersion(char* fileName)
{
	ofstream of(fileName);
	for (int i = 0; i < text.size(); i++)
		of << hashTable[text[i]];
}
void decodeHuffmanCode(char* inFileName,char* outFileName)
{
	int charNum = charOccorTimes.size();
	int treeSize = 2 * charNum - 1;

	ifstream input(inFileName);
	ofstream output(outFileName);
	string s;
	input >> s;
	
	for (int i = 0; i < s.size(); )
	{
		int nowPosition = treeSize - 1;
		while (huffmanTree[nowPosition].lChild != -1 && huffmanTree[nowPosition].rChild != -1)
		{
			if (s[i] == '0')
				nowPosition = huffmanTree[nowPosition].lChild;
			else
				nowPosition = huffmanTree[nowPosition].rChild;
			i++;
		}
		output << huffmanTree[nowPosition].character;
	}
}

//lzw
string* lzwArray;
void printLZWCode(ofstream& output, int num, int bit = 8)
{
	char* bits = new char[bit];
	for (int i = bit - 1; i >= 0; i++)
	{
		if (num & 1)
			bits[i] = '1';
		else
			bits[i] = '0';
		num <<= 1;
	}
	for (int i = 0; i < bit; i++)
		output << bits[i];
}
void getAndOutputLZWCode(char* fileName)
{
	int charNum = 0;
	for (int i = 0; i < text.size(); i++)
	{
		if (charOccorTimes.count(text[i]) && charOccorTimes[text[i]] != 0)
		{
			lzwArray[charNum++] = string(1, text[i]);
			charOccorTimes[text[i]] = 0;
		}
	}

	ofstream output = ofstream(fileName,std::ios::binary);
	string preString = "";
	string nowString;
	for (int i = 0; i < text.size(); i++)
	{
		nowString = preString + string(1, text[i]);
		bool exist = false;

		for (int j = 0; j < charNum; j++)
		if (lzwArray[j] == nowString)
		{
			exist = true;
			break;
		}

		if (exist)
			preString = nowString;
		else
		{
			lzwArray[charNum++] = nowString;
			preString = text[i];
			string prefix = nowString.erase(nowString.size() - 1,1);
			for (int j = 0; j < charNum;j++)
			if (lzwArray[j] == prefix)
			{
				printLZWCode(output, j);
				break;
			}
		}
	}
	for (int i = 0; i < charNum; i++)
	if (lzwArray[i] == preString)
	{
		printLZWCode(output, i);
		break;
	}
}
void decodeLZWCode(char* inFileName, char* outFileName,int bit = 8)
{
	ifstream input = ifstream(inFileName);
	ofstream output = ofstream(outFileName);

	
}
int main()
{
	/*
	readData();
	initHuffmanTree();
	buildHuffmanTree();
	getHuffmanCode();
	writeDocumentHuffmanVersion("huf.bin");
	decodeHuffmanCode("huf.bin", "out.txt");
	*/

	return 0;
}