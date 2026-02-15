#include "doctest/doctest.h"
#include "src/KnowledgeGraph.h"
#include "helper.h"

void tc_001()
{
    cout << "Test Edge basic functionality" << endl;

    DGraphModel<string> graph;

    auto vertexEQ = [](string &a, string &b) -> bool
    { return a == b; };
    auto vertex2str = [](string &s) -> string
    { return s; };

    DGraphModel<string> g(vertexEQ, vertex2str);
    g.add("A");
    g.add("B");
    g.connect("A", "B", 5.0f);

    cout << "Edge connection successful" << endl;
}

void tc_002()
{
    cout << "Test VertexNode basic functionality" << endl;

    // Create function pointers
    auto vertexEQ = [](string &a, string &b) -> bool
    { return a == b; };
    auto vertex2str = [](string &s) -> string
    { return s; };

    // Create vertex nodes
    VertexNode<string> node1("Node1", vertexEQ, vertex2str);
    VertexNode<string> node2("Node2", vertexEQ, vertex2str);

    cout << "Node1 vertex: " << node1.getVertex() << endl;
    cout << "Initial inDegree: " << node1.inDegree() << endl;
    cout << "Initial outDegree: " << node1.outDegree() << endl;
}

void tc_003()
{
    cout << "Test VertexNode basic functionality" << endl;

    // Create function pointers
    auto vertexEQ = [](string &a, string &b) -> bool
    { return a == b; };
    auto vertex2str = [](string &s) -> string
    { return s; };

    // Create vertex nodes
    VertexNode<string> node1("Node1", vertexEQ, vertex2str);
    VertexNode<string> node2("Node2", vertexEQ, vertex2str);

    node1.connect(&node2, 2.5f);
    cout << "After connection - outDegree: " << node1.outDegree() << endl;
    cout << "After connection - inDegree: " << node2.inDegree() << endl;
}

void tc_004()
{
    cout << "Test DGraphModel basic functionality" << endl;

    // Define function pointers
    auto vertexEQ = [](string &a, string &b) -> bool
    { return a == b; };
    auto vertex2str = [](string &s) -> string
    { return s; };

    DGraphModel<string> graph(vertexEQ, vertex2str);

    // Test add and contains
    graph.add("X");
    graph.add("Y");
    graph.add("Z");

    cout << "Graph size: " << graph.size() << endl;
    cout << "Contains X: " << (graph.contains("X") ? "true" : "false") << endl;
    cout << "Empty: " << (graph.empty() ? "true" : "false") << endl;

    // Test connection
    cout << "Connected X to Y: " << (graph.connected("X", "Y") ? "true" : "false") << endl;
}

void tc_005()
{
    cout << "Test toString methods of Edge, VertexNode, and DGraphModel" << endl;

    // Define function pointers
    auto vertexEQ = [](string &a, string &b) -> bool
    { return a == b; };
    auto vertex2str = [](string &s) -> string
    { return s; };

    DGraphModel<string> graph(vertexEQ, vertex2str);

    // Add vertices
    graph.add("A");
    graph.add("B");
    graph.add("C");

    // Add connections
    graph.connect("A", "B", 2.5f);
    graph.connect("B", "C", 3.0f);
    graph.connect("A", "C", 1.0f);

    // Test DGraphModel toString (which internally uses VertexNode toString and Edge toString)
    cout << "DGraphModel toString:" << endl;
    string graphString = graph.toString();
    cout << graphString << endl;

    // Test individual VertexNode toString by getting vertex and checking outward edges
    cout << "Testing individual components:" << endl;
    vector<Edge<string> *> outwardEdges = graph.getOutwardEdges("A");
    cout << "Vertex A has " << outwardEdges.size() << " outward edges" << endl;
}

void tc_006()
{
    cout << "Test KnowledgeGraph basic functionality" << endl;

    KnowledgeGraph kg;

    // Test entity management
    kg.addEntity("Entity1");
    kg.addEntity("Entity2");
    kg.addEntity("Entity3");

    vector<string> entities = kg.getAllEntities();
    cout << "Number of entities: " << entities.size() << endl;

    kg.addRelation("Entity1", "Entity2", 1.0f);
    kg.addRelation("Entity2", "Entity3", 1.0f);

    vector<string> neighbors = kg.getNeighbors("Entity1");
    cout << "Entity1 has " << neighbors.size() << " neighbor(s)" << endl;
}

TEST_CASE("tc_000")
{
    std::ostringstream oss;
    std::streambuf *oldCout = std::cout.rdbuf(oss.rdbuf());
    tc_001();
    cout << "======================" << endl;
    tc_002();
    cout << "======================" << endl;
    tc_003();
    cout << "======================" << endl;
    tc_004();
    cout << "======================" << endl;
    tc_005();
    cout << "======================" << endl;
    tc_006();
    std::cout.rdbuf(oldCout);
    std::string output = oss.str();

    CHECK(output ==
          "Test Edge basic functionality\n"
          "Edge connection successful\n"
          "======================\n"
          "Test VertexNode basic functionality\n"
          "Node1 vertex: Node1\n"
          "Initial inDegree: 0\n"
          "Initial outDegree: 0\n"
          "======================\n"
          "Test VertexNode basic functionality\n"
          "After connection - outDegree: 1\n"
          "After connection - inDegree: 1\n"
          "======================\n"
          "Test DGraphModel basic functionality\n"
          "Graph size: 3\n"
          "Contains X: true\n"
          "Empty: false\n"
          "Connected X to Y: false\n"
          "======================\n"
          "Test toString methods of Edge, VertexNode, and DGraphModel\n"
          "DGraphModel toString:\n"
          "[(A, 0, 2, [(A, B, 2.500000), (A, C, 1.000000)]), (B, 1, 1, [(A, B, 2.500000), (B, C, 3.000000)]), (C, 2, 0, [(B, C, 3.000000), (A, C, 1.000000)])]\n"
          "Testing individual components:\n"
          "Vertex A has 2 outward edges\n"
          "======================\n"
          "Test KnowledgeGraph basic functionality\n"
          "Number of entities: 3\n"
          "Entity1 has 1 neighbor(s)\n");
}