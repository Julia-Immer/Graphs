#include "Graph.h"

#include <iostream>
#include <sstream>

using namespace std;

// fwd declarations
string make_dot(Graph* g);
string what(int& v);

Graph::Graph() {
  // DONE FOR YOU
  directed = false; // graphs are undirected by default
}

Graph::~Graph() {
  // "DONE" FOR YOU
  // no implementation needed
}

vector<shared_ptr<Node>> Graph::getNodes() {
  // DONE FOR YOU
  return nodes;
}

vector<shared_ptr<Edge>> Graph::getEdges() {
  // DONE FOR YOU
  return edges;
}

int Graph::getClock() {
  // DONE FOR YOU
  return clock;
}

void Graph::setClock(int ctime) {
  clock = ctime;
}

void Graph::addNode(shared_ptr<Node> n) {
  // DONE FOR YOU
  nodes.push_back(n);
}

void Graph::addEdge(shared_ptr<Edge> e) {
  // DONE FOR YOU
  edges.push_back(e);
}
 
void Graph::removeNode(shared_ptr<Node> n) {
  // DONE FOR YOU
  for (vector<shared_ptr<Node>>::iterator it = nodes.begin(); it != nodes.end(); it++) {
    if (n == *it) {
      nodes.erase(it);
      break;
    }
  }
}
 
void Graph::removeEdge(shared_ptr<Edge> e) {
  // DONE FOR YOU
  for (vector<shared_ptr<Edge>>::iterator it = edges.begin();
       it != edges.end(); 
       it++) {
    if (e == *it) {
      edges.erase(it);
      break;
    }
  }
}

void Graph::setDirected(bool val) {
  // DONE FOR YOU
  directed = val;
}

bool Graph::isDirected() {
  // DONE FOR YOU
  return directed;
}

set<shared_ptr<Edge>> Graph::getAdjacentEdges(shared_ptr<Node> n) {
  // DONE FOR YOU
  set<shared_ptr<Edge>> ret;
  for (vector<shared_ptr<Edge>>::iterator it = edges.begin(); it != edges.end(); it++) {
    shared_ptr<Edge> edge = *it;
    if (edge->getStart() == n) {
      ret.insert(edge);
    }
    if (!directed && (edge->getEnd() == n)) {
      ret.insert(edge);
    }
  }
  return ret;
}

//done
void Graph::clear() {
  //call clear() to reset all node's color to white, times and rank to -1
  for (auto n: nodes) {
    n->clear();
  }
  setClock(0); //reset clock time to zero
  //reset all edges to undiscovered edge
  for (auto e: edges) {
    e->setType(9); //UNDISCOVERED_EDGE type
  }
}

void Graph::tick(string message) {
  // DONE FOR YOU
  //
  // optional debugging function, disabled with if(false) to prevent
  // unused var warning. Change this however you want.
  //
  // recommended use: call it just after incrementing the clock.
  if (false) {
    cout << "// " << message << endl << make_dot(this) << endl;
  }
}

void Graph::dfs(shared_ptr<Node> start) {
  //use getClock setClock and getAdjacentEdges
  start->setColor(GRAY, getClock()); //set current node to gray since we are exploring it now
  setClock(getClock()+1); //advance the clock

  set<shared_ptr<Edge>> adjacent_edges = getAdjacentEdges(start);
  int end_color, end_disco_time, end_finish_time, end_bfs;
  shared_ptr<Node> end;

  //visit the node at the end of every edge and classify
  for (auto edge: adjacent_edges) {
    //if edge->end is white, TREE edge and 
    //set Predecessor to current start node
    end = edge->getEnd();
    end->getDiscoveryInformation(end_color, end_disco_time, end_finish_time, end_bfs);
    if (end_color == WHITE) {
      end->setPredecessor(start);
      edge->setType(TREE_EDGE);
      dfs(end);
    }
    //if end was discovered before start, but end is still being explored
    //i.e. is grey, then BACK edge
    else if (end_color == GRAY) {
      edge->setType(BACK_EDGE);
    }
    //if edge->end is BLACK and start is ancestor of edge->end
    //it's a FORWARD edge
    else if ((end_color == BLACK)&&(end->isAncestor(start) == true)) {
      edge->setType(FORWARD_EDGE);
    }
    //edge->end is BLACK and start is not an ancestor of c
    //label CROSS edge
    else {
      edge->setType(CROSS_EDGE);
    }
  }
  //all edges fully explored, we change node to black
  start->setColor(BLACK, getClock()); 
  setClock(getClock()+1); //advance the clock
}

void Graph::bfs(shared_ptr<Node> start) {
  shared_ptr<Node> unreachable_target(new Node);
  unreachable_target->clear(); //clear for very small chance memory has values that would match a node in graph

  //call first bfs function with unreachable node so entire graph is searched
  bfs(start, unreachable_target);
}

void Graph::bfs(shared_ptr<Node> start, shared_ptr<Node> finish) {
  queue<shared_ptr<Node>> q_nodes;
  shared_ptr<Node> curr, next_curr; //future current node and the one to be examined after that
  int color, disco_time, finish_time, rank;
  start->setRank(0); //set rank of current node
  q_nodes.push(start); //add start node to the queue to start search
  start->setColor(GRAY, 0);//mark start node

  while (q_nodes.size() > 0) {
    curr = q_nodes.front();

    q_nodes.pop(); //remove curr node from queue
    curr->setColor(BLACK, 0);

    if (curr == finish) { //check to see if we found our target
      return;
    }
    //check out all the nodes related to current node
    for(auto edge: getAdjacentEdges(curr)) {
      if (edge->getEnd() != curr) {//whether it's at the beginning or end of edge doesn't matter as graph is undirected
        next_curr = edge->getEnd();
      }
      else {
        next_curr = edge->getStart();
      }
      //find out if we've discovered this node and added it yet or not
      next_curr->getDiscoveryInformation(color, disco_time, finish_time, rank);
      if(color == WHITE) { //unadded nodes will be white
        next_curr->setColor(GRAY, 0);
        next_curr->setRank(curr->getRank() +1);
        q_nodes.push(next_curr);
      }
    }
  }
}


// overloading operator << lets you put a Graph object into an output
// stream.
ostream &operator << (ostream& out, Graph graph) {
  // DONE FOR YOU
  out << graph.nodes.size() << " Nodes:" << endl;
  out << "[";
  for (vector<shared_ptr<Node>>::iterator it = graph.nodes.begin(); it != graph.nodes.end(); it++) {
    shared_ptr<Node> n = *it;
    out << *n << ", ";
  }
  out << "]" << endl;
  out << graph.edges.size() << " Edges:" << endl;
  out << "[";
  for (vector<shared_ptr<Edge>>::iterator it = graph.edges.begin(); it != graph.edges.end(); it++) {
    shared_ptr<Edge> e = *it;
    out << *e << ", ";
  }
  out << "]";
  return out;
}

// what is a helper function that turns a constant (e.g. WHITE or
// FORWARD_EDGE) into a string for debugging goodness. 
string what(int& v) {
  // DONE FOR YOU
  string ret = "Unknown";
  if (v == WHITE) {
    ret = "white";
  } else if (v == GRAY) {
    ret = "gray";
  } else if (v == BLACK) {
    ret = "black";
  } else if (v == UNDISCOVERED_EDGE) {
    ret = "undiscovered";
  } else if (v == TREE_EDGE) {
    ret = "tree";
  } else if (v == BACK_EDGE) {
    ret = "back";
  } else if (v == FORWARD_EDGE) {
    ret = "forward";
  } else if (v == CROSS_EDGE) {
    ret = "cross";
  }
  return ret;
}

// make_dot generates a dotfile string for viewing your graph. Have
// tick() print out the results of this function, and then use
// http://www.webgraphviz.com/ (or get a copy of GraphViz) to view the
// result. If you're stuck, this can help you get un-stuck.
string make_dot(Graph* g) {
  // DONE FOR YOU
  stringstream ss;
  vector<shared_ptr<Node>> nodes = g->getNodes();
  vector<shared_ptr<Edge>> edges = g->getEdges();
  string gt = "graph";
  string con = "--";
  if (g->isDirected()) {
    con = "->";
    gt = "digraph";
  }
  ss << gt << " homework {" << endl;
  int c, dt, ft, r;
  string textColor = "black";
  for (auto it=nodes.begin(); it != nodes.end(); ++it) {
    shared_ptr<Node> n = *it;
    n->getDiscoveryInformation(c, dt, ft, r);
    if (c == BLACK) {
      textColor = "white";
    } else {
      textColor = "black";
    }
    ss << "  " << n->getData() << " [ style=\"filled\" fontcolor=\"" << textColor << "\" fillcolor=\"" << what(c) << "\"" << " ]" << endl;
  }
  
  string edgeColor = "black";
  for (auto it=edges.begin(); it != edges.end(); ++it) {
    shared_ptr<Edge> e = *it;
    if (e->getType() == TREE_EDGE) {
      edgeColor = "black";
    } else if (e->getType() == FORWARD_EDGE) {
      edgeColor = "purple";
    } else if (e->getType() == BACK_EDGE) {
      edgeColor = "blue";
    } else if (e->getType() == CROSS_EDGE) {
      edgeColor = "green";
    } else {
      edgeColor = "gray";
    }
    ss << "  " << e->getStart()->getData() << con << e->getEnd()->getData() << " [color=\"" << edgeColor << "\"]" << endl;
  }
  ss << "}" << endl;
  return ss.str();
}