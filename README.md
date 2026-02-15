# Knowledge Graph Assignment 3

A C++ implementation of a Knowledge Graph data structure for Assignment 3 of the Data Structures and Algorithms (DSA) course at Ho Chi Minh City University of Technology (HCMUT).

## 🚀 Quick Start

```bash
# Clone the repository
git clone https://github.com/Jenny3306/Knowledge-Graph-Assignment-3.git
cd Knowledge-Graph-Assignment-3

# Download doctest header
mkdir -p doctest
curl -o doctest/doctest.h https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h

# Compile the project
g++ -std=c++11 -o main main.cpp src/KnowledgeGraph.cpp tests/helper.cpp \
    tests/test_knowledgegraph.cpp tests/test_dgraph.cpp tests/test_LMS.cpp \
    -I. -DTESTING

# Run tests
./main
```

## 📋 Table of Contents

- [Quick Start](#quick-start)
- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Prerequisites](#prerequisites)
- [Building the Project](#building-the-project)
- [Running Tests](#running-tests)
- [Usage Examples](#usage-examples)
- [Implementation Details](#implementation-details)
- [Assignment Context](#assignment-context)

## 🔍 Overview

This project implements a **Knowledge Graph** using a directed graph data structure. A knowledge graph represents entities and the relationships between them, enabling complex querying and traversal operations. The implementation uses C++ templates for flexibility and includes comprehensive test coverage.

### Key Components

- **DGraphModel**: A generic directed graph implementation using adjacency lists
- **KnowledgeGraph**: A specialized graph for storing and querying knowledge entities and their relationships
- **Edge & VertexNode**: Core building blocks for the graph structure

## ✨ Features

- **Entity Management**: Add and manage entities in the knowledge graph
- **Relationship Management**: Create weighted relationships between entities
- **Graph Traversal**: BFS (Breadth-First Search) and DFS (Depth-First Search) algorithms
- **Reachability Analysis**: Check if one entity is reachable from another
- **Neighbor Discovery**: Find all entities directly connected to a given entity
- **Related Entities**: Discover entities within a specified depth from a target entity
- **Common Ancestors**: Find common ancestors between two entities
- **Template-Based Design**: Generic graph implementation supporting various data types
- **Exception Handling**: Robust error handling for vertex and edge operations

## 📁 Project Structure

```
Knowledge-Graph-Assignment-3/
├── src/
│   ├── KnowledgeGraph.h      # Knowledge graph class definition
│   ├── KnowledgeGraph.cpp    # Knowledge graph implementation
│   ├── main.h                # Common headers and exception definitions
│   └── utils.h               # Utility classes (Point, etc.)
├── tests/
│   ├── test_knowledgegraph.cpp  # Knowledge graph unit tests
│   ├── test_dgraph.cpp          # Directed graph unit tests
│   ├── test_LMS.cpp             # Learning management system tests
│   ├── helper.h                 # Test helper functions
│   └── helper.cpp               # Test helper implementations
├── main.cpp                  # Main test runner
├── README.md                 # This file
└── _251_CO2003___DSA__Assignment_3_VI_v1.1.pdf  # Assignment specification
```

## 🔧 Prerequisites

Before building this project, ensure you have the following installed:

- **C++ Compiler**: GCC 7.0+ or Clang 5.0+ with C++11 support
- **Git**: For version control
- **Make** (optional): For automated building

### Required C++ Standard

This project requires C++11 or later due to the use of:
- Template features
- Lambda functions
- `nullptr` keyword
- Range-based for loops
- Smart pointers

### Setting Up doctest

This project uses [doctest](https://github.com/doctest/doctest) for unit testing. You need to download the doctest header file before building:

```bash
# Create doctest directory
mkdir -p doctest

# Download doctest header (single-header library)
curl -o doctest/doctest.h https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h

# Alternative: using wget
# wget -O doctest/doctest.h https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h
```

Or manually download `doctest.h` from the [doctest releases](https://github.com/doctest/doctest/releases) and place it in a `doctest/` directory in the project root.

## 🏗️ Building the Project

### Compile with G++

To compile the project with all source files:

```bash
# Compile all source and test files
g++ -std=c++11 -o main main.cpp src/KnowledgeGraph.cpp tests/helper.cpp \
    tests/test_knowledgegraph.cpp tests/test_dgraph.cpp tests/test_LMS.cpp \
    -I. -DTESTING

# Run the compiled executable
./main
```

### Compile Individual Components

To compile and test individual components:

```bash
# Compile only knowledge graph tests
g++ -std=c++11 -o test_kg main.cpp src/KnowledgeGraph.cpp tests/helper.cpp \
    tests/test_knowledgegraph.cpp -I. -DTESTING
./test_kg

# Compile only directed graph tests
g++ -std=c++11 -o test_dg main.cpp src/KnowledgeGraph.cpp tests/helper.cpp \
    tests/test_dgraph.cpp -I. -DTESTING
./test_dg
```

### Build with Debug Symbols

For debugging:

```bash
g++ -std=c++11 -g -o main_debug main.cpp src/KnowledgeGraph.cpp tests/helper.cpp \
    tests/test_knowledgegraph.cpp tests/test_dgraph.cpp tests/test_LMS.cpp \
    -I. -DTESTING
```

## 🧪 Running Tests

This project uses [doctest](https://github.com/doctest/doctest) for unit testing.

### Run All Tests

```bash
./main
```

### Run Specific Test Cases

Use doctest command-line options:

```bash
# Run tests matching a pattern
./main -tc="test_143"

# Run with verbose output
./main -s

# List all test cases
./main -ltc
```

### Test Coverage

The test suite includes:
- Entity and relationship management tests
- Graph traversal (BFS/DFS) tests
- Reachability and connectivity tests
- Related entities discovery tests
- Common ancestor finding tests
- Edge case and exception handling tests

## 📚 Assignment Context

This project is part of **Assignment 3** for the Data Structures and Algorithms course (CO2003) at Ho Chi Minh City University of Technology (HCMUT). The assignment focuses on:

- Implementing directed graph data structures
- Understanding and applying graph traversal algorithms
- Building practical applications of graphs (Knowledge Graphs)
- Writing comprehensive unit tests
- Managing complex data relationships

For detailed assignment requirements, refer to `_251_CO2003___DSA__Assignment_3_VI_v1.1.pdf`.

## 👥 Contributing

This is an academic assignment project. If you're a student working on a similar assignment:
- Use this as a reference for understanding concepts
- Do not copy code directly - academic integrity is important
- Focus on understanding the algorithms and data structures
- Implement your own solution based on the concepts learned

## 📝 Notes

- The implementation uses function pointers for custom equality and string conversion operations
- The `TESTING` macro is used to expose private members to test helper classes
- All graph operations maintain consistency of in-degree and out-degree counts
- The knowledge graph is specialized for string-based entities but the underlying graph is generic

## 🐛 Known Issues

- Make sure to compile with `-DTESTING` flag when running tests to enable test helper access
- Ensure proper exception handling when accessing vertices or edges that may not exist

## 📄 License

This project is created for educational purposes as part of a university assignment at HCMUT.

---

**Course**: CO2003 - Data Structures and Algorithms  
**Institution**: Ho Chi Minh City University of Technology (HCMUT)  
**Assignment**: Assignment 3 - Knowledge Graphs
