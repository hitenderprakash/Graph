/*
 * Directed graph
 * This implementation generate directed graph from the given edges
 * edges are provided as a vector of pair
 * {b,a} represent directed edge from a to b (i.e b is dependent on a)
 * Helpful in writing programs like build dependency 
 * Graph is created as unordered_map<int,unordered_set<int>> , i.e node(int) is ey and unordered_set<int> contains other nodes which has edge from the key node
 * 
 * Hitender Prakash
 * 
 */
 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <utility>
using namespace std;

//prototypes
void generateDirectedGraph(vector<pair<int, int>>& prerequisites,unordered_map<int,unordered_set<int>> &graph);
void displayGraph(unordered_map<int,unordered_set<int>> &graph);
vector<int> topologicalSort(unordered_map<int,unordered_set<int>> &graph);
void recursiveTSHelper(unordered_map<int,unordered_set<int>> ::iterator it,unordered_map<int,unordered_set<int>> &graph,unordered_set<int> &visited,stack<int> &resultStack);
vector<vector<int>> levelOrder(vector<int> &vec,unordered_map<int,unordered_set<int>> &graph);
void removeCycles(unordered_map<int,unordered_set<int>> &graph);
bool detectCycle(unordered_map<int,unordered_set<int>> &graph, unordered_set<int> &loop);
bool detectCycle_dfs(int cur,unordered_set<int> &explored,unordered_map<int,int> onPath,unordered_map<int,unordered_set<int>> &graph,unordered_set<int> &loop,int depth);


//main function for testing the functions
int main(){
	//driver code
	vector<pair<int, int>>edges ={ {3,1},{3,2},{4,2},{5,3},{6,4},{7,6},{1,5},{4,7} };
	unordered_map<int,unordered_set<int>> graph;
	generateDirectedGraph(edges,graph);
	cout<<"\nThe graph is:";
	displayGraph(graph);
	
	unordered_set<int> loop;
	
	//will detect only one cycle and return as find one
	bool hasCycle=detectCycle(graph, loop);
	if(hasCycle){
		cout<<"\nThe following nodes are in a loop: ";
		for(auto i =loop.begin();i!=loop.end();i++){
			cout<<" "<<*i;
		}
	}
	else{
		cout<<"\nGaph has no loop";
	}
	
	if(hasCycle){
		cout<<"\nremoving cycles from the graph";
		
		//detect and remove all cycles, does not print the cycle on console
		removeCycles(graph);
		cout<<"\nThe graph after removing cycles";
		displayGraph(graph);
	}
	vector<int> ts = topologicalSort(graph);
	vector<vector<int>> levelTS = levelOrder(ts,graph);
	//printing level order topological sort
	cout<<"\nLevel order topological sort of graph";
	for(int i=0;i<levelTS.size();i++){
		cout<<"\n";
		for(int j=0;j<levelTS[i].size();j++){
			cout<<levelTS[i][j]<<" ";
		}
	}
	cout<<"\n";
	return 0;	
}

//method to generate the directed graph from given vector of edges
//input is a vector of pairs like [ [b,a],[d,c]] , pair [b,a] represent edge a->b
//also require a reference of unordered_map<int,unordered_set<int>> which stores the graph
void generateDirectedGraph(vector<pair<int, int>>& prerequisites,unordered_map<int,unordered_set<int>> &graph){
	for(int i=0;i<prerequisites.size();i++){
		graph[prerequisites[i].second].insert(prerequisites[i].first);
		if(graph.find(prerequisites[i].first)==graph.end()){
			unordered_set<int> temp;
			graph.insert({prerequisites[i].first,temp});

		}
	}       
}
  
//method to display graph   
void displayGraph(unordered_map<int,unordered_set<int>> &graph){
	for(auto it=graph.begin();it!=graph.end();it++){
		cout<<"\n"<<it->first<<":->";
		for(auto i=it->second.begin();i!=it->second.end();i++){
			cout<<" "<<*i;
		}
	}
	cout<<"\n";
}
    
//topological sort of graph ( require directed acyclic graph, if graph has cycle then result may be unpredictible)    
vector<int> topologicalSort(unordered_map<int,unordered_set<int>> &graph){
	unordered_set<int> visited;
	stack<int> resultStack;
	vector<int> result;
	for(auto it=graph.begin();it!=graph.end();it++){
		recursiveTSHelper(it, graph, visited, resultStack);
	}
	while(!resultStack.empty()){ 
		result.push_back(resultStack.top());
		resultStack.pop();
	}
	return result;
	
}
//helper function used in topological sort method	
void recursiveTSHelper(unordered_map<int,unordered_set<int>> ::iterator it,unordered_map<int,unordered_set<int>> &graph,unordered_set<int> &visited,stack<int> &resultStack){
	if(visited.find(it->first)!=visited.end()){return;}
	visited.insert(it->first);
	for(auto i=it->second.begin();i!=it->second.end();i++){
		auto itr=graph.find(*i);
		if(itr!=graph.end()){
			recursiveTSHelper(itr,graph,visited,resultStack);
		}
	}
	resultStack.push(it->first);
}
 
//method to give level order of toological sort
//require output of topological sort as input  
vector<vector<int>> levelOrder(vector<int> &vec,unordered_map<int,unordered_set<int>> &graph){
	unordered_map<int,int> mp;
	for(int i=0;i<vec.size();i++){
		mp[vec[i]]=1;
	}
	int mx=0;
	for(int i=0;i<vec.size();i++){
		int val=mp[vec[i]];
		mx=max(mx,val);
		auto it=graph.find(vec[i]);
		if(it!=graph.end()){
			for(auto i=it->second.begin();i!=it->second.end();i++){
				mp[*i]=max(mp[*i],val+1);
				mx=max(mx,mp[*i]);
			}
		}
	}
	vector<vector<int>> resultvec(mx);
	for(auto i=mp.begin();i!=mp.end();i++){
		resultvec[i->second-1].push_back(i->first);
	}	
	return 	resultvec;
}


//detect cycle in graph and store the nodes in loop, in a set
//will return as it finds any loop
bool detectCycle(unordered_map<int,unordered_set<int>> &graph, unordered_set<int> &loop){
	unordered_set<int> explored;
	
	unordered_map<int,int> onPath;
	for(auto it=graph.begin();it!=graph.end();it++){
		if(explored.find(it->first)!=explored.end()){continue;}
		bool hasCycle=detectCycle_dfs(it->first,explored,onPath,graph,loop,1);
		if(hasCycle){break;}	
	}
	if(loop.size()==0){return false;}	
	else{
		for(auto i=loop.begin();i!=loop.end();i++){
			graph.erase(graph.find(*i));
		}
		for(auto i=loop.begin();i!=loop.end();i++){
			for(auto j=graph.begin();j!=graph.end();j++){
				auto temp=j->second.find(*i);
				if(temp!=j->second.end()){j->second.erase(temp);}
			}
		}
		return true;
	}
}

//remove cycles from the graph
//i.e delete all nodes which are involved in loop
void removeCycles(unordered_map<int,unordered_set<int>> &graph){
	unordered_set<int> explored;
	while(1){
		unordered_set<int> loop;
		unordered_map<int,int> onPath;
		for(auto it=graph.begin();it!=graph.end();it++){
			if(explored.find(it->first)!=explored.end()){continue;}
			bool hasCycle=detectCycle_dfs(it->first,explored,onPath,graph,loop,1);
			if(hasCycle){break;}	
		}
		if(loop.size()==0){break;}	
		else{
			for(auto i=loop.begin();i!=loop.end();i++){
				graph.erase(graph.find(*i));
			}
			for(auto i=loop.begin();i!=loop.end();i++){
				for(auto j=graph.begin();j!=graph.end();j++){
					auto temp=j->second.find(*i);
					if(temp!=j->second.end()){j->second.erase(temp);}
				}
			}
		}	
	}
}

//detect cycle in graph and stores the nodes involved in loop in a set which is passed by reference to the method
bool detectCycle_dfs(int cur,unordered_set<int> &explored,unordered_map<int,int> onPath,unordered_map<int,unordered_set<int>> &graph,unordered_set<int> &loop,int depth){
	if(explored.find(cur)!=explored.end()){return false;}
	auto it=graph.find(cur);
	onPath[cur]=depth++;
	for(auto i=it->second.begin();i!=it->second.end();i++){
		if(onPath[*i]){
			for(auto j=onPath.begin();j!=onPath.end();j++){
				if(j->second >= onPath[*i]){loop.insert(j->first);}
			}
			return true;
		}
		bool temp=detectCycle_dfs(*i,explored, onPath, graph, loop, depth);
		if(temp){return true;}
	}
	explored.insert(cur);
	return false;
}
