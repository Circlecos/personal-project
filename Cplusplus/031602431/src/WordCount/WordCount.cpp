#define _CRT_SECURE_NO_WARNINGS 

// 统计文本文件中的字符数、单词数和单词频率最高的十个单词
//


#include <iostream>
#include "Tools.h"
#include "ArgParser.h"
#include <fstream>
#include <cstdio>
#include "Scanner.h"
#include "ScanProcesser.h"

using namespace std;

int showResults(struct Top10Words tp, int charNum, int lineNum, int wordNum);

int main(int argc, char* argv[]){
	
	// make sure the arg valid
	ArgParser argParser(argc,argv);
	string filename = argParser.getFileName();
	if (filename.empty()){
		argParser.helpDoc();
		return 1;
	}
	
	// for test
	//string filename = "A MIDSUMMER-NIGHT'S DREAM.txt";

	map<string, int>* strMap = new map<string, int>();
	ScanProcesser* scanProcesser = new ScanProcesser(strMap);
	Scanner* scanner = new Scanner(filename.c_str(), scanProcesser);
	scanner->scan();
	scanProcesser->processTop10Words();

	struct Top10Words tp = scanProcesser->getTop10words();


	int charNum = scanProcesser->getCharNum();
	int lineNum = scanProcesser->getLineNum();
	int wordNum = scanProcesser->getWordNumTotal();


	showResults(tp, charNum, lineNum, wordNum);


	return 0;


}


int showResults(struct Top10Words tp, int charNum, int lineNum, int wordNum) {
	FILE* outfile = NULL;
	outfile = fopen("result.txt", "w+");
	fprintf(outfile,"characters: %d\n", charNum);
	fprintf(outfile, "words: %d\n", wordNum);
	fprintf(outfile, "lines: %d", lineNum);


	cout << "characters: " << charNum << endl;
	cout << "words: " << wordNum << endl;
	cout << "lines: " << lineNum;
	for (int i = 0; i < 10 && i < wordNum;i++) {
		if (!(tp.str[i].empty())) {
			cout << endl << "<" << tp.str[i] << ">: " << tp.count[i];
			fprintf(outfile, "\n<%s>: %d", tp.str[i].c_str(), tp.count[i]);
		}
	}
	fclose(outfile);
	return 0;
}