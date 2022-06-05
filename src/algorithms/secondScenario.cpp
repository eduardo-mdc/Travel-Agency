//
// Created by Eduardo Correia on 09/04/2022.
//


#include <stack>
#include "secondScenario.h"
#include <bits/stdc++.h>
#include <limits>
#define FAILED_FLAG -1000



secondScenario::secondScenario(const map<int, vector<Route>> &nodes) : abstractAlgorithm(nodes) {
    int source = 0;
    Vertex current_vertex;

    //copy elements from nodes vector and insert them into vertices
    int counter = 0;
    for(const auto& node : safe_nodes){
        Vertex vertex;
        vertex.index = counter;
        vertex.linked_vertex = node;
        safe_vertices.push_back(vertex);
        counter++;
    }
    //adding final node;
    current_vertex.index = counter;
    safe_vertices.push_back(current_vertex);
}

void secondScenario::compute() {
    int state;
    printOptions();
    cin >> state;
    if(run(state)){
        cout << "Finished Computing Scenario 2_" << state << "." << endl;
    }
    else{
        cout << "Exiting to main menu." << endl;
    }
}

void secondScenario::printOptions(){
    cout << "-*-------------  Scenario 2  --------------------------*-" << endl;
    cout << " |--> Computing" << endl;
    cout << " |        1 - Compute Scenario 2.1 " << endl;
    cout << " |        2 - Compute Scenario 2.2"  << endl;
    cout << " |        3 - Compute Scenario 2.3 " << endl;
    cout << " |        4 - Compute Scenario 2.4"  << endl;
    cout << " |        5 - Compute Scenario 2.5 " << endl;
    cout << " |--> Exit " << endl;
    cout << " |        0 - Exit Scenario "<< endl;
    cout << "-*----------------------------------------------------*-" << endl;
}

bool secondScenario::run(int state) {
    switch (state) {
        case 1:
            compute_2_1();
            return true;
        case 2:
            compute_2_2();
            return true;
        case 3:
            compute_2_3();
            return true;
        case 4:
            compute_2_4();
            return true;
        case 5:
            compute_2_5();
            return true;
        default:
            return false;
    }
}

void secondScenario::compute_2_1() {
    int groupSize,buffer,counter = 1;
    vector<vector<Route>> nodes = safe_nodes;
    vector<vector<int>> paths;
    vector<int> buffers;

    cout << "Group Size: " << endl;
    cin >> groupSize;
    buffer = groupSize;

    while(buffer > 0){
        stack<int> path = findPathLazy(buffer, nodes);
        if(!path.empty()){
            vector<int> vectorPath = stackIntoVector(path);
            paths.push_back(vectorPath);
            buffers.push_back(buffer);
            blockPath(nodes, vectorPath, buffer);
            groupSize -= buffer;
            buffer = groupSize;
            counter++;
        }
        else{
            buffer--;
        }
    }

    if(groupSize > 0){
        cout << "Could not find a path for the given group size" << endl;
    }
    else{
        int counter_b = 0;
        for(const auto& path : paths){
            cout << "Found path for subgroup [" << counter_b+1 << "] with size [" << buffers.at(counter_b) <<"]"<< endl;
            printPath(path);
            counter_b++;
        }
    }
}

void secondScenario::compute_2_2() {

    int groupSize,buffer,counter = 1, mincap;
    vector<vector<Route>> nodes = safe_nodes;
    vector<vector<int>> paths;
    vector<int> buffers;
    stack<int> path2;

    cout << "Group Size: " << endl;
    cin >> groupSize;
    buffer = groupSize;

    while(buffer > 0){
        stack<int> path = findPathLazy(buffer, nodes);
        if(!path.empty()){
            vector<int> vectorPath = stackIntoVector(path);
            paths.push_back(vectorPath);
            buffers.push_back(buffer);
            blockPath(nodes, vectorPath, buffer);
            groupSize -= buffer;
            buffer = groupSize;
            counter++;
        }
        else{
            buffer--;
        }
    }

    if(groupSize > 0){
        cout << "Could not find a path for the given group size" << endl;
    }
    else{
            int counter_b = 0;
            for(const auto& path : paths){
                cout << "Found path for subgroup [" << counter_b+1 << "] with size [" << buffers.at(counter_b) <<"]"<< endl;
                printPath(path);
                counter_b++;
            }
    }
    // THIS IS WHERE 2.2 is
    cout << "2.2 Would you like to add more people ? 1-Yes 2-No"<< endl;
    cin >> groupSize ;
    if (groupSize ==1){
        cout << "How many people would you like to add ? " << endl;
        cin >> groupSize;

        //check possible

        for (int i=0; i < paths.size(); i++){
            cout << "0" << endl;
            mincap =getMinimumCapacityOG(nodes, paths[i]);
            cout << "1" << endl;
            if ( mincap > 0 ){
                if (mincap >= groupSize){
                    buffers[i]+= groupSize; //buffer
                    blockPath(nodes, paths[i], groupSize);
                    groupSize =0;
                    //add all the people in groupsize
                }
                else{
                    buffers[i]+=mincap; //buffer
                    blockPath(nodes, paths[i], mincap);
                    groupSize -= mincap;
                }

            }
            if (groupSize <=0) break;
        }

        if (groupSize <=0) {
            int counter_b =0;
            for(const auto& path : paths){
                cout << "Found path for subgroup [" << counter_b+1 << "] with size [" << buffers.at(counter_b) <<"]"<< endl;
            printPath(path);
            counter_b++;
            }
        }

        else{
            cout << endl <<"No existing path found, looking for new direction...."<< endl;
            buffer = groupSize;

            while(buffer > 0){
                path2.empty();
                path2 = findPathLazy(buffer, nodes); //findAlternativePathLazy(buffer, nodes,)
                if(!path2.empty()){
                    vector<int> vectorPath2 = stackIntoVector(path2);
                    paths.push_back(vectorPath2);
                    buffers.push_back(buffer);
                    blockPath(nodes, vectorPath2, buffer); //verify group size
                    groupSize -= buffer;
                    buffer = groupSize;
                    counter++;
                }
                else{
                    buffer--;
                }
            }

            if(groupSize > 0){
                cout << "Could not find a path for the given group size" << endl;
            }
            else{
                int counter_b = 0;
                for(const auto& path : paths){
                    cout << "Found path for subgroup [" << counter_b+1 << "] with size [" << buffers.at(counter_b) <<"]"<< endl;
                    printPath(path);
                    counter_b++;
                }
            }
        }
    }
    else{
        cout << "Thank You!" << endl;
    }
}

void secondScenario::compute_2_3() {
    int source = 0;
    int sink = finalNode;
    int maxGroup = 0;
    int minimumCapacity;
    vector<pair<vector<Vertex>,int>> paths;
    vector<Vertex> vertices = safe_vertices;
    Vertex current_vertex;


    while(!vertices.empty()){
        vector<Vertex> shortest_path;
        //get shortest path from source to sink for all nodes
        vertices = dijkstra(vertices, sink, source);

        //If last node is unreachable, break;
        if(vertices.at(sink).distance == numeric_limits<int>::max()){
            break;
        }

        //insert shortest path from source to sink into a vector
        current_vertex = vertices.at(sink);
        while(true){
            shortest_path.push_back(current_vertex);
            if(current_vertex.index == source) break;
            current_vertex = vertices.at(current_vertex.source);
        }
        reverse(shortest_path.begin(),shortest_path.end());

        //Gets minimum capacity for given path
        minimumCapacity = getMinimumCapacity(shortest_path);
        //Increases the flow value by the given amount
        vertices = increaseFlow(vertices,shortest_path,minimumCapacity);

        //Setting output variables
        maxGroup += minimumCapacity;
        pair<vector<Vertex>,int> output;
        output.first = shortest_path;
        output.second = minimumCapacity;
        paths.push_back(output);
    }

    //Print Results
    cout << "Found a path for a divisible group with the maximum size of [" << maxGroup << "]" << endl;
    int counter = 1;
    for(const auto& pair : paths){
        cout << "Group " << counter << " with size [" << pair.second << "] :" << endl;
        printPath(pair.first);
        counter++;
    }

}

void secondScenario::compute_2_4() {

}

void secondScenario::compute_2_5() {

}

stack<int> secondScenario::findPathLazy(int groupSize, vector<vector<Route>> nodes) {
    stack<int> path;
    int node_index = 0;
    int route_index;

    //insert first node into stack
    path.push(node_index);
    //if stack is empty, there is no solution, loops breaks when exit node enters stack.
    while(!path.empty()){
        node_index = path.top();
        if(node_index != finalNode){
            route_index = checkNode(groupSize, nodes.at(node_index));
            if(route_index != FAILED_FLAG){
                path.push(route_index);
            }
            else{
                path.pop();
            }
        }
        else{
            //Found final node
            break;
        }
    }

    return path;
}

int secondScenario::checkNode(int groupSize, vector<Route> &node) {
    for(auto & route : node){
        if(groupSize <= route.capacity && !route.visited){
            route.visited = true;
            return route.destination;
        }
    }
    return FAILED_FLAG;
}

void secondScenario::printPath(vector<int> path){
    cout << "(";
    for(int i = 0; i < path.size(); i++){
        cout << path.at(i);
        if(i < path.size()-1) cout << "->";
    }
    cout << ")" << endl;
}

void secondScenario::printPath(const vector<Vertex>& path) {
    cout << "(";
    for(int i = 0; i < path.size(); i++){
        cout << path.at(i).index;
        if(i < path.size()-1) cout << "->";
    }
    cout << ")" << endl;
}

vector<int> secondScenario::stackIntoVector(stack<int> stack) {
    vector<int> vector;
    while(!stack.empty()) {
        vector.push_back(stack.top());
        stack.pop();
    }
    reverse(vector.begin(), vector.end());
    return vector;
}

void secondScenario::blockPath(vector<vector<Route>> &nodes, const vector<int> &path, int groupSize) {
    int source,destination = 0,index;
    for(int i = 0; destination != finalNode; i++){
        source = path.at(i);
        destination = path.at(i+1);
        index = checkIfDestination(nodes.at(source),destination);
        if(index != FAILED_FLAG){
            nodes.at(source).at(index).capacity -= groupSize;
        }
    }
}

int secondScenario::checkIfDestination(const vector<Route>& node, int destination){
    for(int i = 0; i < node.size(); i++){
        if(destination == node.at(i).destination){
            return i;
        }
    }
    return FAILED_FLAG;
}

vector<Vertex> secondScenario::dijkstra(const vector<Vertex> &safe_vertices, int final, int source) {
    vector<Vertex> vertices = safe_vertices;
    vector<int> visited;
    Vertex current_vertex;

    //Compare Function used for the prio queue, sorts elements by distance
    auto compare = [](Vertex &vertex1, Vertex &vertex2) { return vertex1.distance > vertex2.distance;};
    priority_queue<Vertex,vector<Vertex>, decltype(compare) > priorityQueue(compare);

    for(auto & elem : vertices){
        elem.distance = numeric_limits<int>::max();
        elem.source = -1;
    }

    vertices.at(source).distance = 0;

    priorityQueue.push(vertices.at(source));
    visited.push_back(source);

    while (!priorityQueue.empty()){
        current_vertex = priorityQueue.top();
        priorityQueue.pop();
        int alt = current_vertex.distance + 1;
        if(current_vertex.index != final){
            for(auto route : current_vertex.linked_vertex){
                //Verify if route still has flow left.
                if(route.capacity > 0){
                    int destination = route.destination;
                    if(alt < vertices.at(destination).distance){
                        vertices.at(destination).distance = alt;
                        vertices.at(destination).source = current_vertex.index;
                        if(vectorContains(visited,vertices.at(destination).index) == FAILED_FLAG){
                            visited.push_back(vertices.at(destination).index);
                            priorityQueue.push(vertices.at(destination));
                        }
                    }
                }
            }
        }
    }



    return vertices;
}

int secondScenario::vectorContains(vector<int> vector, int value) {
    int counter = 0;
    for(auto elem : vector){
        if (elem == value) return counter;
        counter++;
    }
    return FAILED_FLAG;
}

int secondScenario::getMinimumCapacity(const vector<Vertex> &path) {
    Vertex node, nextNode;
    int min = numeric_limits<int>::max();
    for(int i = 0; i < path.size()-1; i++){
        node = path.at(i);
        nextNode = path.at(i+1);
        for(const auto& route : node.linked_vertex){
            if(route.destination == nextNode.index && route.capacity < min) min = route.capacity;
        }
    }
    return min;
}


int secondScenario::getMinimumCapacityOG(const vector<vector<Route>> &nodes, const vector<int> &path) {
    int index, node, nextNode;
    int min = numeric_limits<int>::max();
    for(int i = 0; i < path.size()-1; i++){
        node = path.at(i);
        nextNode = path.at(i+1);
        for(const auto& route : nodes[node]){
            if(route.destination == nextNode && route.capacity < min) min = route.capacity;
        }
    }
    return min;
}

vector<Vertex> secondScenario::increaseFlow(const vector<Vertex> & vertices_input, const vector<Vertex> &path, int value) {
    vector<Vertex> vertices = vertices_input;
    Vertex node, nextNode;
    for(int i = 0; i < path.size()-1; i++){
        node = path.at(i);
        nextNode = path.at(i+1);
        int counter = 0;
        for(auto route : node.linked_vertex){
            if(route.destination == nextNode.index){
                vertices.at(node.index).linked_vertex.at(counter).capacity -= value;
                break;
            }
            counter++;
        }
    }
    return vertices;
}


