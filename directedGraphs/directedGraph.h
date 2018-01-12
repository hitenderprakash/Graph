/* Interface for directed graph
 * Hitender Prakash
 */
 
#ifndef _DIRECTED_GRAPH
#define _DIRECTED_GRAPH

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "graph.h"
using namespace std;

namespace std {
    template <> struct hash<graphNode> {
        size_t operator()(const graphNode & x) const {
            std::hash<std::string> h;
            return h(x.node_name);
        }
    };   
}

class directedGraph{	
	private:
	unordered_map<graphNode,unordered_set<graphNode>> graph;
	bool detectCycle_dfs(graphNode cur,unordered_set<graphNode> &explored,unordered_map<graphNode,int> onPath,unordered_set<graphNode> &loop,int depth);
	bool getNodesSetInCycle(unordered_set<graphNode> &loop);
	void recursiveTSHelper(unordered_map<graphNode,unordered_set<graphNode>> ::iterator it,unordered_set<graphNode> &visited,stack<graphNode> &resultStack);
	
	public:
	
	//check if node exists
	bool nodeExists(graphNode node);
	bool nodeExists(string nodename);
	
	//add single node
	void addNode(graphNode node);
	void addNode(string nodename);
	
	//display graph nodes
	void displayGraphNodes();
	
	//find total number of nodes in graph
	int nodeCount();
	
	//add edge 
	int addEdge(graphNode sourceNode, graphNode destNode);	
	int addEdge(string sourceNodeName, string destNodeName);
	
	//check if node exists
	bool edgeExists(graphNode sourceNode, graphNode destNode);
	bool edgeExists(string sourceNodeName, string destNodeName);
	
	//display graph structure
	void displayGraph();
	
	//cycle detection in graph
	bool hasCycle();
	vector<graphNode> getNodesInCycle();
	
	//remove all cycles
	void removeAllCycles();
	
	//topological sort
	vector<graphNode> topologicalSort();
	
	//level order traversal
	vector<vector<graphNode>> levelOrder(vector<graphNode> &vec);
	
	//generate graph from given directed edge list
	void generateDirectedGraphWithEdges(vector<pair<string,string>>& edges);
	
};


#endif
