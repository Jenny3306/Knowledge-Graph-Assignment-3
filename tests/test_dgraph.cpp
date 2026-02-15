#include "doctest/doctest.h"
#include "src/KnowledgeGraph.h"
#include "helper.h"

TEST_CASE("test_001")
{
    VertexNode<char> v1('V', charComparator, vertex2str);
    VertexNode<char> v2('O', charComparator, vertex2str);
    VertexNode<char> v3('T', charComparator, vertex2str);
    VertexNode<char> v4('I', charComparator, vertex2str);
    VertexNode<char> v5('E', charComparator, vertex2str);
    VertexNode<char> v6('N', charComparator, vertex2str);

    Edge<char> *e1 = new Edge<char>(&v1, &v2, 2.000000);
    Edge<char> *e2 = new Edge<char>(&v1, &v2, 1.000000);
    Edge<char> *e3 = new Edge<char>(&v1, &v3, 1.000000);

    CHECK(e1->equals(e2));
    CHECK(e1->equals(e3) == false);

    CHECK(Edge<char>::edgeEQ(e1, e2));
    CHECK(Edge<char>::edgeEQ(e1, e3) == false);

    CHECK(e1->toString() == "(V, O, 2.000000)");

    delete e1;
    delete e2;
    delete e3;
}

TEST_CASE("test_002")
{
    VertexNode<char> v1('V', charComparator, vertex2str);
    VertexNode<char> v2('O', charComparator, vertex2str);
    VertexNode<char> v3('T', charComparator, vertex2str);
    VertexNode<char> v4('I', charComparator, vertex2str);
    VertexNode<char> v5('E', charComparator, vertex2str);
    VertexNode<char> v6('N', charComparator, vertex2str);

    CHECK(v1.getVertex() == 'V');
    CHECK(v1.toString() == "(V, 0, 0, [])");

    v1.connect(&v2);
    v1.connect(&v3, 10.000000);
    v4.connect(&v1);

    CHECK(v1.getEdge(&v3)->toString() == "(V, T, 10.000000)");
    CHECK(v1.inDegree() == 1);
    CHECK(v1.outDegree() == 2);

    CHECK(v3.toString() == "(T, 1, 0, [(V, T, 10.000000)])");

    v1.removeTo(&v3);
    CHECK(v1.getEdge(&v3) == nullptr);
}

TEST_CASE("test_003")
{
    DGraphModel<char> model(&charComparator, &vertex2str);
    char vertices[] = {'A', 'B', 'C', 'D', 'E'};
    for (int idx = 0; idx < 5; idx++)
    {
        model.add(vertices[idx]);
    }
    stringstream output;
    model.connect('A', 'B', 8.000000);
    model.connect('B', 'D', 6.000000);
    model.connect('C', 'B', 1.000000);
    model.connect('C', 'D', 2.000000);
    model.connect('E', 'A', 3.000000);
    model.connect('E', 'B', 4.000000);
    model.connect('E', 'C', 5.000000);

    CHECK(model.toString() == "[(A, 1, 1, [(A, B, 8.000000), (E, A, 3.000000)]), (B, 3, 1, [(A, B, 8.000000), (B, D, 6.000000), (C, B, 1.000000), (E, B, 4.000000)]), (C, 1, 2, [(C, B, 1.000000), (C, D, 2.000000), (E, C, 5.000000)]), (D, 2, 0, [(B, D, 6.000000), (C, D, 2.000000)]), (E, 0, 3, [(E, A, 3.000000), (E, B, 4.000000), (E, C, 5.000000)])]");
}

TEST_CASE("test_004")
{
    DGraphModel<char> model(&charComparator, &vertex2str);
    char vertices[] = {'A', 'B', 'C', 'D', 'E'};
    for (int idx = 0; idx < 5; idx++)
    {
        model.add(vertices[idx]);
    }

    model.connect('A', 'B', 8.000000);
    model.connect('B', 'D', 6.000000);
    model.connect('C', 'B', 1.000000);
    model.connect('C', 'D', 2.000000);
    model.connect('E', 'A', 3.000000);
    model.connect('E', 'B', 4.000000);
    model.connect('E', 'C', 5.000000);

    std::ostringstream oss;
    std::streambuf *oldCout = std::cout.rdbuf(oss.rdbuf());
    vector<Edge<char> *> v = model.getOutwardEdges('E');
    for (auto edge : v)
        cout << edge->toString() << " ";
    std::cout.rdbuf(oldCout);
    std::string output = oss.str();

    CHECK(output == "(E, A, 3.000000) (E, B, 4.000000) (E, C, 5.000000) ");
}

TEST_CASE("test_005")
{
    DGraphModel<char> model(&charComparator, &vertex2str);
    char vertices[] = {'A', 'B', 'C', 'D', 'E'};
    for (int idx = 0; idx < 5; idx++)
    {
        model.add(vertices[idx]);
    }

    model.connect('A', 'C', 8.000000);
    model.connect('B', 'D', 6.000000);
    model.connect('A', 'B', 1.000000);
    model.connect('C', 'D', 1.000000);
    model.connect('A', 'E', 1.000000);

    CHECK(model.BFS('A') == "[(A, 0, 3, [(A, C, 8.000000), (A, B, 1.000000), (A, E, 1.000000)]), (C, 1, 1, [(A, C, 8.000000), (C, D, 1.000000)]), (B, 1, 1, [(B, D, 6.000000), (A, B, 1.000000)]), (E, 1, 0, [(A, E, 1.000000)]), (D, 2, 0, [(B, D, 6.000000), (C, D, 1.000000)])]");

    CHECK(model.DFS('A') == "[(A, 0, 3, [(A, C, 8.000000), (A, B, 1.000000), (A, E, 1.000000)]), (C, 1, 1, [(A, C, 8.000000), (C, D, 1.000000)]), (D, 2, 0, [(B, D, 6.000000), (C, D, 1.000000)]), (B, 1, 1, [(B, D, 6.000000), (A, B, 1.000000)]), (E, 1, 0, [(A, E, 1.000000)])]");
}

TEST_CASE("test_006")
{
    VertexNode<char> v1('V', charComparator, vertex2str2);
    VertexNode<char> v2('O', charComparator, vertex2str2);

    Edge<char> *e1 = new Edge<char>(&v1, &v2, 2.000000);

    CHECK(e1->toString() == "(V-, O-, 2.000000)");

    delete e1;
}

TEST_CASE("test_007")
{
    VertexNode<char> v1('V', charComparator, vertex2str2);
    VertexNode<char> v2('O', charComparator, vertex2str);

    Edge<char> *e1 = new Edge<char>(&v1, &v2, 2.000000);

    CHECK(e1->toString() == "(V-, O, 2.000000)");

    delete e1;
}