/* Driver code for testing Graph API
 * Hitender Prakash
 */


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
	cout<<"\n================\n";
	directedGraph city;
	cout<<"\nTest: Adding isolated edges======";
	city.addNode("shimla");
	city.addNode("delhi");
	city.displayGraphNodes();
	
	cout<<"\nTest: edgeExist API======";
	if(!city.edgeExists("shimla","delhi")){cout<<"\nThe edge between shimla and delhi does not exists";}
	
	cout<<"\nTest: Adding edges======";
	int temp=city.addEdge("shimla","delhi");
	if(temp==0){cout<<"\nAdded edge shimla->delhi successfully";}
	cout<<"\nTest: shimla ->delhi edges again after creation";
	if(city.edgeExists("shimla","delhi")){cout<<"\nNow edge between shimla and delhi exists";}
	
	cout<<"\nTest:Total nodes in graph";
	cout<<"\nSize of graph: "<<city.nodeCount();

	//test creation/modification of graph by edge list
	cout<<"\nTest: Adding more nodes and edges from edge list";
	cout<<"\nAdding few more edges and nodes";
	vector<pair<string,string>> citylinks={ {"shimla","delhi"},{"newyork", "indiana"},{"indiana","chicago"},{"chicago","ohio"}};
	city.generateDirectedGraphWithEdges(citylinks);
	city.displayGraph();
	//test cycles
	cout<<"\nTest: if graph has cycle";
	bool cycle = city.hasCycle();
	if(cycle){
		cout<<"\nThe following nodes are in a loop: ";
		vector<graphNode> res=city.getNodesInCycle();
		for(int i =res.size();i<res.size();i++){
			cout<<" "<<res[i];
		}
	}
	else{
		cout<<"\nGaph has no loop";
	}
	
	cout<<"\nTest: topological sort\n";
	vector<graphNode> res=city.topologicalSort();
	for(int i=0;i<res.size();i++){
		cout<<res[i]<<" ";
	}
	cout<<"\nTest: level order topological sort\n";
	vector<vector<graphNode>>lres= city.levelOrder(res);
	for(int i=0;i<lres.size();i++){
		cout<<"\n";
		for(int j=0;j<lres[i].size();j++){
			cout<<lres[i][j]<<" ";
		}
	}
	//test cycle removal
	
	//city.removeAllCycles();
	
	//test displaying graph structure
	//city.displayGraph();
	cout<<"\n================\n";
	return 0;	
}
