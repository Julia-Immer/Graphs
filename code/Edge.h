#ifndef EDGE_H__
#define EDGE_H__

#include <memory>
#include "Node.h"

using namespace std;

class Edge {
private:
  shared_ptr<Node> a;  // start node
  shared_ptr<Node> b;  // end node
  int type; // one of the edge types defined in graph.hpp
public:
  Edge(shared_ptr<Node> n1, shared_ptr<Node> n2);
  ~Edge();
  int getType();
  shared_ptr<Node> getStart();
  shared_ptr<Node> getEnd();
  void setWeight(float val);
  friend std::ostream &operator << (std::ostream& out, Edge edge);

  // Set the edge type to the given value (see edge type #define
  // statements).
  void setType(int edge_type);
  
};

#endif  // EDGE