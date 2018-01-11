#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <utility>
#include "directedGraph.h"
using namespace std;

int main(){
	directedGraph city;
	
	city.addNode("shimla");
	city.addNode("delhi");
	if(!city.edgeExists("shimla","delhi")){cout<<"\nThe edge between shimla and delhi does not exists";}
	int temp=city.addEdge("shimla","delhi");
	if(temp==0){cout<<"\nedge creating....";}
	if(city.edgeExists("shimla","delhi")){cout<<"\nNow edge between shimla and delhi does  exists";}
	cout<<"\nSize of graph: "<<city.nodeCount();
	city.displayGraph();
	if(city.nodeExists("Manipur")){cout<<"\nyeah";}
	city.displayGraphNodes();
	return 0;	
}
