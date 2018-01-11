#ifndef _DIRECTED_GRAPH
#define _DIRECTED_GRAPH

#include <string>
#include <unordered_map>
#include <unordered_set>
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
	public:
	//add single node
	void addNode(graphNode node);
	void addNode(string nodename);
	//check if node exists
	bool nodeExists(graphNode node);
	bool nodeExists(string nodename);
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
	
};
#endif
