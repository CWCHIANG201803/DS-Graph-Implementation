#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include "Graph.h"

using namespace std;

int main(){
	ifstream infile;
	infile.open("./data/graph_source3.txt");
	// graphData is a 2-D vector
	vector<vector<int>> graphData;
	// use stringstream
	stringstream ss;
	string line;

	while(getline(infile,line)){
		std::istringstream iss(line);
		vector<int> row;
		string element;
		char delimiter='\t';
		istringstream tokenStream(line);
		while (std::getline(tokenStream, element, delimiter)){
      		row.push_back(std::stoi(element));
   		}
		graphData.push_back(row);
	}
	infile.close();

	Graph g2(8);

	for(int i=0; i<graphData.size() ; i++){
		for(int j=0; j<graphData.size() ;j++){
			if(graphData[i][j]!=0)
				g2.AddEdgeList(i,j);
		}
	}

	g2.DFS(0);
    system("pause");
    return 0;
}

