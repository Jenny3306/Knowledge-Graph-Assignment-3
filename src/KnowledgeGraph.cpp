#include "KnowledgeGraph.h"

// =============================================================================
// Class Edge Implementation
// =============================================================================

template <class T>
Edge<T>::Edge(VertexNode<T> *from, VertexNode<T> *to, float weight){
    // khởi tạo các tham số chỉ định
    this->from = from;
    this->to = to;
    this->weight = weight;
}

template <class T>
string Edge<T>::toString(){
    stringstream ss;
    ss << "(";
    if (from != nullptr){
        if (from->vertex2str != nullptr)
            ss << from->vertex2str(from->vertex);
        else
            ss << from->vertex;  
    }
    ss << ", ";
    if (to != nullptr){
        if (to->vertex2str != nullptr)
            ss << to->vertex2str(to->vertex);
        else
            ss << to->vertex;  
    }
    ss << ", ";
    
    // Format float with 6 decimal places using stringstream methods
    ss.precision(6); // đặt độ chính xác là 6 chữ số thập phân
    ss.setf(std::ios::fixed, std::ios::floatfield); // sử dụng định dạng số thập phân cố định
    ss << weight; // in ra trọng số với thiết lập ở trên
    
    ss << ")";
    return ss.str();
}

// TODO: Implement other methods of Edge:
template <class T>
bool Edge<T>::equals(Edge<T> *edge){
    // so sánh cạnh hiện tại vs 1 cạnh khác, true nếu from và to giống nhau, ngược lại false
    if (edge == nullptr)
        return false;
    return (this->from == edge->from && this->to == edge->to);
}

template <class T>
bool Edge<T>::edgeEQ(Edge<T> *&edge1, Edge<T> *&edge2)
{
    if (edge1 == nullptr || edge2 == nullptr)
        return false;
    return edge1->equals(edge2);
}

// =============================================================================
// Class VertexNode Implementation
// =============================================================================
template <class T>
VertexNode<T>::VertexNode(T vertex, bool (*vertexEQ)(T &, T &), string (*vertex2str)(T &)){
    this->vertex = vertex;
    this->vertexEQ = vertexEQ;
    this->vertex2str = vertex2str;
    this->inDegree_ = 0;
    this->outDegree_ = 0;
}

template <class T>
VertexNode<T>::~VertexNode(){
    // Clean up all edges in adjacency list
    for (auto edge : adList){
        delete edge;
    }
    adList.clear();
    adListFull.clear(); // Clear full adjacency list as well (bao gồm cả incoming và outcoming edges)
}

template <class T>
T &VertexNode<T>::getVertex(){
    return this->vertex;
}

template <class T>
void VertexNode<T>::connect(VertexNode<T> *to, float weight){
    // kết nối đỉnh hiện tại vs đỉnh to bằng cách tạo 1 canh với trọng số weight (mặc định là 0)
    if (to == nullptr)
        return;

    // Check if edge already exists
    for (auto edge : adList){
        if (edge->to == to){
            edge->weight = weight; // Update weight if exists
            return;
        }
    }

    // Create new edge
    Edge<T> *newEdge = new Edge<T>(this, to, weight); // from ,to, weight
    
    // Add to outgoing edges list of 'from' node (this)
    adList.push_back(newEdge);
    adListFull.push_back(newEdge);
    this->outDegree_++;
    
    // Add to full edges list of 'to' node (incoming edge)
    to->adListFull.push_back(newEdge);
    to->inDegree_++;
}

template <class T>
Edge<T> *VertexNode<T>::getEdge(VertexNode<T> *to){
    // trả về con trỏ nối đỉnh hiện tại vs đỉnh to, nếu k có trả về nullptr
    for (auto edge : adList){
        if (edge->to == to)
            return edge;
    }
    return nullptr;
}

template <class T>
bool VertexNode<T>::equals(VertexNode<T> *node){
    if (node == nullptr)
        return false;
    if (this->vertexEQ != nullptr)
        return this->vertexEQ(this->vertex, node->vertex);
    return this->vertex == node->vertex;
}

template <class T>
void VertexNode<T>::removeTo(VertexNode<T> *to){
    // xóa cạnh nối đỉnh hiện tại vs đỉnh to
    for (auto it = adList.begin(); it != adList.end(); ++it){
        if ((*it)->to == to){
            Edge<T>* edgeToRemove = *it;
            
            // Remove from adListFull of 'from' node (this)
            for (auto it2 = this->adListFull.begin(); it2 != this->adListFull.end(); ++it2){
                if (*it2 == edgeToRemove){
                    this->adListFull.erase(it2);
                    break;
                }
            }
            
            // Remove from adListFull of 'to' node
            for (auto it2 = to->adListFull.begin(); it2 != to->adListFull.end(); ++it2){
                if (*it2 == edgeToRemove){
                    to->adListFull.erase(it2);
                    break;
                }
            }
            
            delete edgeToRemove;
            adList.erase(it);
            this->outDegree_--;
            to->inDegree_--;
            return;
        }
    }
}

template <class T>
int VertexNode<T>::inDegree(){
    return this->inDegree_;
}

template <class T>
int VertexNode<T>::outDegree(){
    return this->outDegree_;
}

template <class T>
string VertexNode<T>::toString(){
    stringstream ss;
    ss << "(";
    if (this->vertex2str != nullptr)
        ss << this->vertex2str(this->vertex);
    else
        ss << this->vertex;
    ss << ", " << this->inDegree_ << ", " << this->outDegree_ << ", [";
    
    for (size_t i = 0; i < adListFull.size(); i++){
        if (i > 0) ss << ", ";
        ss << adListFull[i]->toString();
    }
    ss << "])";
    return ss.str();
}

// =============================================================================
// Class DGraphModel Implementation
// =============================================================================
template <class T>
DGraphModel<T>::DGraphModel(bool (*vertexEQ)(T &, T &), string (*vertex2str)(T &)){
    this->vertexEQ = vertexEQ;
    this->vertex2str = vertex2str;
}

template <class T>
DGraphModel<T>::~DGraphModel(){
    // TODO: Clear all vertices and edges to avoid memory leaks
    clear();
}

template <class T>
VertexNode<T> *DGraphModel<T>::getVertexNode(T &vertex){
    // tìm kiếm và trả về con trỏ đỉnh có giá trị vertex, nếu ko tìm thấy trả về nullptr
    for (auto node : nodeList){
        if (vertexEQ != nullptr){
            if (vertexEQ(node->vertex, vertex))
                return node;
        }
        else {
            if (node->vertex == vertex)
                return node;
        }
    }
    return nullptr;
}

template <class T>
string DGraphModel<T>::vertex2Str(VertexNode<T> &node){
    // Nếu có function pointer vertex2str, dùng nó (trả về giá trị đơn giản là gtri vertex)
    if (this->vertex2str != nullptr) {
        return this->vertex2str(node.vertex);
    }
    
    // Nếu không có function pointer vertex2str, trả về format đầy đủ như toString()
    return node.toString();
}

template <class T>
string DGraphModel<T>::edge2Str(Edge<T> &edge){
    return edge.toString();
}

template <class T>
void DGraphModel<T>::add(T vertex){
    // TODO: Add a new vertex to the graph
    if (contains(vertex)) return; // Vertex already exists
    VertexNode<T> *newNode = new VertexNode<T>(vertex, this->vertexEQ, this->vertex2str);
    nodeList.push_back(newNode);
}

template <class T>
bool DGraphModel<T>::contains(T vertex){
    return getVertexNode(vertex) != nullptr;
}

template <class T>
float DGraphModel<T>::weight(T from, T to){
    // trả về trọng số của cạnh nối đỉnh from vs đỉnh to
    VertexNode<T> *fromNode = getVertexNode(from);
    if (fromNode == nullptr){
        throw VertexNotFoundException();
    }

    VertexNode<T> *toNode = getVertexNode(to);
    if (toNode == nullptr){
        throw VertexNotFoundException();
    }

    Edge<T> *edge = fromNode->getEdge(toNode);
    if (edge == nullptr){
        throw EdgeNotFoundException();
    }

    return edge->weight;
}

template <class T>
vector<Edge<T> *> DGraphModel<T>::getOutwardEdges(T from){
    // trả về danh sách các cạnh đi ra từ đỉnh from
    VertexNode<T> *fromNode = getVertexNode(from);
    if (fromNode == nullptr){
        throw VertexNotFoundException();
    }
    return fromNode->adList;
}

template <class T>
void DGraphModel<T>::connect(T from, T to, float weight){
    VertexNode<T> *fromNode = getVertexNode(from);
    if (fromNode == nullptr){
        throw VertexNotFoundException();
    }

    VertexNode<T> *toNode = getVertexNode(to);
    if (toNode == nullptr){
        throw VertexNotFoundException();
    }

    fromNode->connect(toNode, weight);
}

template <class T>
void DGraphModel<T>::disconnect(T from, T to){
    VertexNode<T> *fromNode = getVertexNode(from);
    if (fromNode == nullptr){
        throw VertexNotFoundException();
    }

    VertexNode<T> *toNode = getVertexNode(to);
    if (toNode == nullptr){
        throw VertexNotFoundException();
    }

    fromNode->removeTo(toNode); // disconnect nghĩa là xóa cạnh nối từ 'from' đến 'to'
}

template <class T>
bool DGraphModel<T>::connected(T from, T to){
    // kiểm tra xem có cạnh nối đỉnh from vs đỉnh to hay ko
    VertexNode<T> *fromNode = getVertexNode(from);
    if (fromNode == nullptr){
        throw VertexNotFoundException();
    }

    VertexNode<T> *toNode = getVertexNode(to);
    if (toNode == nullptr){
        throw VertexNotFoundException();
    }

    return (fromNode->getEdge(toNode) != nullptr);
}

template <class T>
int DGraphModel<T>::size(){
    return nodeList.size(); // trả về số đỉnh trong đồ thị
}

template <class T>
bool DGraphModel<T>::empty(){
    return nodeList.empty(); // kiểm tra đồ thị có rỗng hay ko
}

template <class T>
void DGraphModel<T>::clear(){
    // xóa tất cả các cạnh và node trong đồ thị (bắt buộc phải xóa cạnh trước nếu ko sẽ bị rò rỉ bộ nhớ)
    for (auto node : nodeList){
        for (auto edge : node->adList){
            delete edge;
        }
        node->adList.clear();
        node->adListFull.clear();
        delete node;
    }
    nodeList.clear();
}

template <class T>
int DGraphModel<T>::inDegree(T vertex){
    VertexNode<T> *node = getVertexNode(vertex);
    if (node == nullptr){
        throw VertexNotFoundException();
    }
    return node->inDegree();
}

template <class T>
int DGraphModel<T>::outDegree(T vertex){
    VertexNode<T> *node = getVertexNode(vertex);
    if (node == nullptr){
        throw VertexNotFoundException();
    }
    return node->outDegree();
}

template <class T>
vector<T> DGraphModel<T>::vertices(){
    // trả về danh sách tất cả các đỉnh trong đồ thị
    vector<T> result;
    for (auto node : nodeList){
        result.push_back(node->vertex);
    }
    return result;
}

template <class T>
string DGraphModel<T>::toString(){
    // trả về chuỗi biểu diễn toàn bộ đồ thị, bao gồm danh sách các đỉnh theo đúng thứ tự trong nodeList và các cạnh của chúng
    // mỗi đỉnh dc in bằng phương thức toString() của VertexNode
    stringstream ss;
    ss << "[";
    
    for (size_t i = 0; i < nodeList.size(); i++){
        if (i > 0) ss << ", ";
        ss << nodeList[i]->toString();
    }
    
    ss << "]";
    return ss.str();
}

// TODO: BFS use Queue and DFS use stack
template <class T>
class Queue
{
private:
    vector<T> data;
    int frontIndex;
    int rearIndex;

public:
    Queue() : frontIndex(0), rearIndex(-1) {}

    // TODO
    void enqueue(T item){
        data.push_back(item);
        rearIndex++;
    }

    T dequeue(){
        return data[frontIndex++];
    }

    bool isEmpty(){
        return frontIndex > rearIndex;
    }
};

template <class T>
class Stack
{
private:
    vector<T> data;

public:
    Stack() = default;

    void push(T item){
        data.push_back(item);
    }

    T pop(){
        T item = data.back();
        data.pop_back();
        return item;
    }

    bool isEmpty(){
        return data.empty();
    }
};

template <class T>
string DGraphModel<T>::BFS(T start){
    // Bước 1: ktra đỉnh bắt đầu có tồn tại ko 
    VertexNode<T> *startNode = getVertexNode(start);
    if (startNode == nullptr){
        throw VertexNotFoundException();
    }

    // Bước 2: Khởi tạo cấu trúc dữ liệu cần thiết cho BFS
    vector<bool> visited(nodeList.size(), false);       // theo dõi và đánh dấu đỉnh đã thăm
    vector<VertexNode<T>*> visitOrder;                  // lưu thứ tự các đỉnh được thăm
    Queue<VertexNode<T> *> queue;                       // hàng đợi để hỗ trợ quá trình duyệt BFS

    // Bước 3: Tìm chỉ số của đỉnh bắt đầu trong nodeList
    int startIdx = -1;
    for (size_t i = 0; i < nodeList.size(); i++){
        if (nodeList[i] == startNode){
            startIdx = i;
            break;
        }
    }

    // Bước 4: Bắt đầu quá trình duyệt BFS - thêm đỉnh bắt đầu vào hàng đợi và đánh dấu là đã thăm
    queue.enqueue(startNode);
    visited[startIdx] = true;

    // Bước 5: Thực hiện duyệt BFS
    while (!queue.isEmpty()){
        // Lấy đỉnh hiện tại từ hàng đợi
        VertexNode<T> *current = queue.dequeue();
        visitOrder.push_back(current);

        // Duyệt qua tất cả các đỉnh kề (outward neighbors) của đỉnh hiện tại
        for (auto edge : current->adList){
            VertexNode<T> *neighbor = edge->to;
            // Tìm chỉ số của đỉnh kề trong nodeList
            for (size_t i = 0; i < nodeList.size(); i++) {
                if (nodeList[i] == neighbor && !visited[i]) {
                    visited[i] = true;
                    queue.enqueue(neighbor);
                    break;
                }
            }
        }
    }

    // Tạo chuỗi kết quả
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < visitOrder.size(); i++){
        if (i > 0) ss << ", ";
        ss << vertex2Str(*visitOrder[i]); // LUÔN dùng vertex2Str
    }
    ss << "]";
    return ss.str();
}

template <class T>
string DGraphModel<T>::DFS(T start){
    VertexNode<T> *startNode = getVertexNode(start);
    if (startNode == nullptr){
        throw VertexNotFoundException();
    }

    vector<bool> visited(nodeList.size(), false);
    vector<VertexNode<T>*> visitOrder;
    Stack<VertexNode<T> *> stack;

    int startIdx = -1;
    for (size_t i = 0; i < nodeList.size(); i++){
        if (nodeList[i] == startNode){
            startIdx = i;
            break;
        }
    }

    stack.push(startNode);
    
    while (!stack.isEmpty()){
        VertexNode<T> *current = stack.pop();
        
        int currentIdx = -1;
        for (size_t i = 0; i < nodeList.size(); i++){
            if (nodeList[i] == current){
                currentIdx = i;
                break;
            }
        }
        
        if (visited[currentIdx]) continue;
        visited[currentIdx] = true;
        visitOrder.push_back(current);
        
        for (int i = current->adList.size() - 1; i >= 0; i--){
            VertexNode<T> *neighbor = current->adList[i]->to;
            int neighborIdx = -1;
            for (size_t j = 0; j < nodeList.size(); j++){
                if (nodeList[j] == neighbor){
                    neighborIdx = j;
                    break;
                }
            }
            if (neighborIdx != -1 && !visited[neighborIdx]){
                stack.push(neighbor);
            }
        }
    }
    
    // Tạo chuỗi kết quả
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < visitOrder.size(); i++){
        if (i > 0) ss << ", ";
        ss << vertex2Str(*visitOrder[i]); // LUÔN dùng vertex2Str
    }
    ss << "]";
    return ss.str();
}

// =============================================================================
// Class KnowledgeGraph Implementation
// =============================================================================
// Helper function for string comparison
bool KnowledgeGraph::stringEQ(string &lhs, string &rhs) {
    // So sánh hai chuỗi lhs và rhs, trả về true nếu chúng bằng nhau, ngược lại false
    return lhs == rhs;
}

KnowledgeGraph::KnowledgeGraph() : graph(&stringEQ, nullptr) {
    // Khởi tạo đồ thị tri thức với hàm so sánh chuỗi và hàm chuyển đổi chuỗi
    // Truyền nullptr để vertex2Str() gọi toString() cho BFS/DFS
}

void KnowledgeGraph::addEntity(string entity) {
    // TODO: Add a new entity to the Knowledge Graph (thêm thực thể mới vào đồ thị)
    if (graph.contains(entity)) {
        throw EntityExistsException();
    }
    graph.add(entity);
    entities.push_back(entity);
}

void KnowledgeGraph::addRelation(string from, string to, float weight) {
    // TODO: Add a directed relation from 'from' entity to 'to' entity with the specified weight
    if (!graph.contains(from)) {
        throw EntityNotFoundException();
    }
    if (!graph.contains(to)) {
        throw EntityNotFoundException();
    }
    graph.connect(from, to, weight);
}

vector<string> KnowledgeGraph::getAllEntities() {
    return entities;
}

vector<string> KnowledgeGraph::getNeighbors(string entity) {
    if (!graph.contains(entity)) {
        throw EntityNotFoundException();
    }
    // Lấy tất cả các đỉnh kề (outward neighbors) của thực thể đã cho
    vector<Edge<string>*> edges = graph.getOutwardEdges(entity);
    vector<string> neighbors;
    for (auto edge : edges) {
        VertexNode<string>* toNode = edge->getTo();
        neighbors.push_back(toNode->getVertex());
    }
    return neighbors;
}

string KnowledgeGraph::bfs(string start) {
    if (!graph.contains(start)) {
        throw EntityNotFoundException();
    }
    return graph.BFS(start);
}

string KnowledgeGraph::dfs(string start) {
    if (!graph.contains(start)) {
        throw EntityNotFoundException();
    }
    return graph.DFS(start);
}

bool KnowledgeGraph::isReachable(string from, string to) {
    if (!graph.contains(from)) {
        throw EntityNotFoundException();
    }
    if (!graph.contains(to)) {
        throw EntityNotFoundException();
    }
    
    // Use BFS to check reachability
    vector<bool> visited(entities.size(), false);
    Queue<string> queue;
    
    // Find index of 'from' entity
    int fromIdx = -1;
    for (size_t i = 0; i < entities.size(); i++) {
        if (entities[i] == from) {
            fromIdx = i;
            break;
        }
    }
    
    queue.enqueue(from);
    visited[fromIdx] = true;
    
    while (!queue.isEmpty()) {
        string current = queue.dequeue();
        
        if (current == to) {
            return true;
        }
        // Explore neighbors - outward edges of current entity
        vector<Edge<string>*> edges = graph.getOutwardEdges(current);
        for (auto edge : edges) {
            VertexNode<string>* toNode = edge->getTo();
            string neighbor = toNode->getVertex();
            for (size_t i = 0; i < entities.size(); i++) {
                if (entities[i] == neighbor && !visited[i]) {
                    visited[i] = true;
                    queue.enqueue(neighbor);
                    break;
                }
            }
        }
    }
    
    return false;
}

string KnowledgeGraph::toString() {
    return graph.toString();
}

vector<string> KnowledgeGraph::getRelatedEntities(string entity, int depth) {
    // TODO: Return all entities related to the given entity within the specified depth (use BFS)
    if (!graph.contains(entity)) {
        throw EntityNotFoundException();
    }
    
    vector<string> result; // to store related entities
    vector<bool> visited(entities.size(), false); // to track visited entities
    Queue<pair<string, int>> queue; // queue to perform BFS, storing pairs of (entity, current depth)
    
    // Find index of entity
    int entityIdx = -1;
    for (size_t i = 0; i < entities.size(); i++) {
        if (entities[i] == entity) {
            entityIdx = i;
            break;
        }
    }
    // Start BFS (khởi tạo)
    queue.enqueue(make_pair(entity, 0)); // enqueue starting entity with depth 0
    visited[entityIdx] = true; // mark starting entity as visited
    // BFS loop
    while (!queue.isEmpty()) {
        pair<string, int> current = queue.dequeue();
        string currentEntity = current.first; // current entity
        int currentDepth = current.second; // current depth
        // If current depth reached the specified depth, skip further exploration
        if (currentDepth >= depth) {
            continue;
        }
        
        vector<Edge<string>*> edges = graph.getOutwardEdges(currentEntity);
        for (auto edge : edges) {
            VertexNode<string>* toNode = edge->getTo();
            string neighbor = toNode->getVertex();
            int neighborIdx = -1;
            for (size_t i = 0; i < entities.size(); i++) {
                if (entities[i] == neighbor) {
                    neighborIdx = i;
                    break;
                }
            }
            
            if (neighborIdx != -1 && !visited[neighborIdx]) {
                visited[neighborIdx] = true;
                result.push_back(neighbor);
                queue.enqueue(make_pair(neighbor, currentDepth + 1));
            }
        }
    }
    
    return result;
}

string KnowledgeGraph::findCommonAncestors(string entity1, string entity2) {
    if (!graph.contains(entity1)) {
        throw EntityNotFoundException();
    }
    if (!graph.contains(entity2)) {
        throw EntityNotFoundException();
    }
    
    // Special case: same entity
    if (entity1 == entity2) {
        return entity1;
    }
    
    // Check if entity1 is ancestor of entity2
    if (isReachable(entity1, entity2)) {
        return entity1;
    }
    
    // Check if entity2 is ancestor of entity1
    if (isReachable(entity2, entity1)) {
        return entity2;
    }
    
    // Helper function to get index of entity
    auto getIndex = [&](const string& entity) -> int {
        for (size_t i = 0; i < entities.size(); i++) {
            if (entities[i] == entity) {
                return i;
            }
        }
        return -1;
    };
    
    // Helper function to compute shortest weighted distance
    auto getShortestDistance = [&](const string& from, const string& to) -> float {
        int n = entities.size();
        vector<float> dist(n, 1e9); // khoảng cách tới mỗi đỉnh ban đầu vô hạn
        vector<bool> visited(n, false);
        
        int fromIdx = getIndex(from);
        int toIdx = getIndex(to);
        
        if (fromIdx == -1 || toIdx == -1) return 1e9;
        
        dist[fromIdx] = 0; // khoảng cách từ đỉnh nguồn tới chính nó là 0
        
        // Dijkstra's algorithm
        for (int i = 0; i < n; i++) {
            // Find unvisited node with minimum distance
            int u = -1;
            float minDist = 1e9;
            for (int j = 0; j < n; j++) {
                if (!visited[j] && dist[j] < minDist) {
                    minDist = dist[j];
                    u = j;
                }
            }
            
            if (u == -1 || minDist == 1e9) break;
            visited[u] = true;
            
            if (u == toIdx) break; // Reached destination
            
            // Get outward edges from current node => cập nhật khoảng cách cho các đỉnh kề
            vector<Edge<string>*> edges = graph.getOutwardEdges(entities[u]);
            for (auto edge : edges) {
                string neighbor = edge->getTo()->getVertex();
                int vIdx = getIndex(neighbor);
                if (vIdx != -1) {
                    float weight = edge->getWeight();
                    if (dist[u] + weight < dist[vIdx]) {
                        dist[vIdx] = dist[u] + weight;
                    }
                }
            }
        }
        
        return dist[toIdx];
    };
    
    // Find all common ancestors with their total weighted distances
    string lca = "";
    float minTotalDist = 1e9;
    
    for (const string& candidate : entities) {
        if (candidate == entity1 || candidate == entity2) continue;
        
        // Check if candidate can reach both entities
        if (isReachable(candidate, entity1) && isReachable(candidate, entity2)) {
            float dist1 = getShortestDistance(candidate, entity1);
            float dist2 = getShortestDistance(candidate, entity2);
            
            if (dist1 < 1e9 && dist2 < 1e9) {
                float totalDist = dist1 + dist2;
                
                // Choose candidate with smaller total distance
                // Or if equal, keep the later one (iterate through entities in order)
                if (totalDist <= minTotalDist) {
                    minTotalDist = totalDist;
                    lca = candidate;
                }
            }
        }
    }
    
    if (lca.empty()) {
        return "No common ancestor";
    }
    
    return lca;
}

// =============================================================================
// Explicit Template Instantiation
// =============================================================================
template class Edge<string>;
template class Edge<int>;
template class Edge<float>;
template class Edge<char>;

template class VertexNode<string>;
template class VertexNode<int>;
template class VertexNode<float>;
template class VertexNode<char>;

template class DGraphModel<string>;
template class DGraphModel<int>;
template class DGraphModel<float>;
template class DGraphModel<char>;