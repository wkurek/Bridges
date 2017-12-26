#ifndef AISDI_BRIDGES
#define AISDI_BRIDGES

#include <list>

struct Vertex {
  unsigned int id;
  std::list<unsigned int> adjatency;

  Vertex(unsigned int id=0) {
    this->id = id;
  }

  void addNeigbour(unsigned int v) {
    adjatency.push_back(v);
  }
};

class Graph {
  std::size_t v;
  Vertex *vertices;

public:
  Graph(std::size_t v) {
    this->v = v;
    this->vertices = new Vertex[this->v];

    for(unsigned int i = 0; i < this->v; ++i) {
      this->vertices[i].id = i;
    }
  }

  Graph(const Graph &other) {
    this->v = other.v;
    this->vertices = new Vertex[this->v];

    for(int i = 0; i < this->v; ++i) {
      this->vertices[i].id = i;

      std::list<unsigned int>::iterator it = other.vertices[i].adjatency.begin();
      for(;it != other.vertices[i].adjatency.end(); ++it) {
        this->vertices[i].addNeigbour(*it);
      }
    }
  }

  void addEdge(unsigned int u, unsigned int w) {
    vertices[w].adjatency.push_back(u);
    vertices[u].adjatency.push_back(w);
  }

  void deleteVertex(unsigned int u) {
    Vertex *tmp = vertices;
    this->vertices = new Vertex[this->v-1];

    unsigned int i, j;
    for(i = 0, j = 0; i < this->v; ++i) {
      if(tmp[i].id == u) continue;
      this->vertices[j].id = tmp[i].id;

      std::list<unsigned int>::iterator it = tmp[i].adjatency.begin();
      for(;it != tmp[i].adjatency.end(); ++it) {
        if(*it != u) this->vertices[j].addNeigbour(*it);
      }
      ++j;
    }

    --this->v;
    delete[] tmp;
  }

  bool isConnected() {
    bool visited[v];

      dfs(0, visited);

    for(int i = 0; i < v; ++i) {
      if(!visited[i]) return false;
    }
    return true;
  }

  void print() {
    for(unsigned int i = 0; i < this->v; ++i) {
      std::cout<<"["<<vertices[i].id<<"]\t";
      std::list<unsigned int>::iterator it = vertices[i].adjatency.begin();
      for(;it != vertices[i].adjatency.end(); ++it) {
        std::cout<<*it<<" ";
      }
      std::cout<<std::endl;
    }
  }

  ~Graph() {
    delete[] this->vertices;
  }

private:
  void dfs(unsigned int u, bool visited[]) {
    visited[u] = true;

      std::list<unsigned int>::iterator it = vertices[u].adjatency.begin();
      for(;it != vertices[u].adjatency.end(); ++it) {
        if(!visited[getVertexIndex(*it)]) dfs(getVertexIndex(*it), visited);
      }
  }

  int getVertexIndex(unsigned int u) {
    for(int i = 0; i < this->v; ++i) {
      if(vertices[i].id == u) return i;
    }
  }

};
#endif
