#include <iostream>
#include <utility>
#include <list>
#include "graph.h"

using namespace std;

list<pair<unsigned int, unsigned int> > edges;

Graph readGraph() {
  std::size_t v;
    cin>>v;
  Graph graph(v);

  unsigned int u, w;
  while(cin>>u>>w) {
    graph.addEdge(u, w);
    edges.push_back(make_pair(u, w));
  }

  return graph;
}

int main() {
  Graph graph(readGraph());

  list<pair<unsigned int, unsigned int> >::iterator it = edges.begin();
  for(;it != edges.end(); ++it) {
    Graph tmp(graph);
    tmp.deleteVertex(it->first);
    tmp.deleteVertex(it->second);
    if(!tmp.isConnected()) cout<<it->first<<" "<<it->second<<endl;
  }

  return 0;
}
