#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <set>

#define INT32_MAX 2147483647

using namespace std;

bool is_input_empty(string input){
     string check;
    stringstream checker(input);

    checker >> check;
    if(!check.length()) return true;
    else return false;
}

int find_weight(map<pair<int,int>, int> &weight, int left, int right){
    if(left > right) swap(left, right);
    pair<int, int> edge = make_pair(left, right);
    return weight[edge];
}

void swap(int &left, int &right){
    int temp = left;
    left = right;
    right = temp;
}

struct vertex{
    int key;
    int index;
    int parent;

    vertex() : key(0), index(-1), parent(0) {}
    vertex(int a, int b, int c) : key(a), index(b), parent(c) {}
};

int find_min_index(vector<vertex> &Q){
    
    vertex min(INT32_MAX, 0, 0);
    for(vector<vertex>::iterator iter = Q.begin(); iter != Q.end(); iter++){
        if(min.key > (*iter).key && (*iter).index != -1){
            min.index = (*iter).index;
            min.key = (*iter).key;
        }
    }
    return min.index;
}

void print_shortest_distance(map<pair<int,int>, int> &weight, int nodes){

    vector<vertex> Q;
    Q.push_back(vertex());

    for(int i = 1; i <= nodes; i++){
        vertex u(i == 1 ? 0 : INT32_MAX, i, i == 1 ? -1 : 0);
        Q.push_back(u);
    }

    for(int i = 0; i <= nodes; i++){

        int idx = find_min_index(Q);
        vertex u = Q[idx];
        Q[idx].index = -1;

        for(int i = 1; i <= nodes; i++){

            int w = find_weight(weight, u.index, i);

            if(w != 0){
                vertex v = Q[i];

                if(u.key + w < v.key){
                    Q[i].parent = u.index;
                    Q[i].key = u.key + w;
                }
            }
        }

    }

    cout << Q[nodes].key << endl;
}

int main(){

    int nodes, edges;
    string input;
    stringstream ss;
    map<pair<int, int>, int> weight;

    while(1)
    {
        weight.clear();

        getline(cin, input);

       if(is_input_empty(input)) return 0;

        ss.clear();
        ss << input;
        ss >> nodes >> edges;
        if(ss.fail()) return 0;

        for(int i = 0; i < edges; i++){
            getline(cin, input);
            ss.clear();
            ss << input;
            
            int left, right, cost;
            ss >> left >> right >> cost;
            if(ss.fail() || left > nodes || right > nodes || left == right) return 0;

            if(left > right) swap(left, right);
            pair<int, int> edge = make_pair(left, right);
            weight[edge] = cost;
        }
        
        print_shortest_distance(weight, nodes);
    }

    return 0;
}