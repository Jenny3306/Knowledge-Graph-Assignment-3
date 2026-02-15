#include "doctest/doctest.h"
#include "src/KnowledgeGraph.h"
#include "helper.h"

// =============================================================================
// TEST CASES FOR STRING-BASED KNOWLEDGE GRAPH
// =============================================================================

TEST_CASE("test_143")
{
    KnowledgeGraph kg;

    kg.addEntity("D");
    kg.addEntity("A");
    kg.addEntity("B");
    kg.addEntity("C");
    kg.addEntity("E");

    kg.addRelation("A", "B");
    kg.addRelation("A", "C", -2);
    kg.addRelation("B", "A", 2);
    kg.addRelation("D", "A", 4);

    CHECK(kg.getAllEntities() == vector<string>{"D", "A", "B", "C", "E"});

    CHECK(kg.toString() == "[(D, 0, 1, [(D, A, 4.000000)]), (A, 2, 2, [(A, B, 1.000000), (A, C, -2.000000), (B, A, 2.000000), (D, A, 4.000000)]), (B, 1, 1, [(A, B, 1.000000), (B, A, 2.000000)]), (C, 1, 0, [(A, C, -2.000000)]), (E, 0, 0, [])]");
}

TEST_CASE("test_154")
{
    KnowledgeGraph kg;

    const char *names[10] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    for (int i = 0; i < 10; i++)
    {
        kg.addEntity(names[i]);
    }

    kg.addRelation("A", "B");
    kg.addRelation("A", "C");
    kg.addRelation("B", "D");
    kg.addRelation("B", "E");
    kg.addRelation("C", "F");
    kg.addRelation("C", "G");
    kg.addRelation("D", "H");
    kg.addRelation("E", "I");
    kg.addRelation("F", "J");

    CHECK(kg.getRelatedEntities("A", 2) == vector<string>{"B", "C", "D", "E", "F", "G"});
    CHECK(kg.getRelatedEntities("A") == vector<string>{"B", "C", "D", "E", "F", "G"});
    CHECK(kg.getRelatedEntities("C", 1.000000) == vector<string>{"F", "G"});
    CHECK(kg.findCommonAncestors("H", "I") == "B");
    CHECK(kg.findCommonAncestors("H", "J") == "A");
    CHECK(kg.findCommonAncestors("F", "G") == "C");
}

TEST_CASE("test_157")
{
    KnowledgeGraph kg;

    const char *names[10] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    for (int i = 0; i < 10; i++)
    {
        kg.addEntity(names[i]);
    }

    kg.addRelation("D", "A");
    kg.addRelation("D", "B");
    kg.addRelation("C", "A");
    kg.addRelation("C", "B", 2);

    CHECK(kg.findCommonAncestors("A", "B") == "D"); // tổng trọng số đương đi 2 thằng là nhỏ nhất

    kg.addRelation("D", "B", 5);
    CHECK(kg.findCommonAncestors("A", "B") == "C");

    kg.addRelation("C", "A", 3);
    kg.addRelation("E", "A");
    kg.addRelation("F", "B");
    kg.addRelation("G", "E");
    kg.addRelation("G", "F");

    CHECK(kg.findCommonAncestors("A", "B") == "G");
}