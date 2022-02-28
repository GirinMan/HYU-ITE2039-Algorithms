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

void print_min_connect_cost(map<pair<int,int>,int> &weight, int cities){

    vector<vertex> Q;
    Q.push_back(vertex());

    for(int i = 1; i <= cities; i++){
        vertex u(i == 1 ? 0 : INT32_MAX, i, i == 1 ? -1 : 0);
        Q.push_back(u);
    }

    for(int i = 0; i < cities; i++){

        int idx = find_min_index(Q);
        vertex u = Q[idx];
        Q[idx].index = -1;

        for(int i = 1; i <= cities; i++){

            int w = find_weight(weight, u.index, i);

            if(w != 0){
                vertex v = Q[i];

                if(v.index != -1 && w < v.key){
                    Q[i].parent = u.index;
                    Q[i].key = w;
                }
            }
        }
    }

    int cost = 0;
    for (int i = 1; i < Q.size(); i++){
        for(int j = 1; j < Q.size(); j++){
            if(Q[j].parent == i){
                cost += find_weight(weight, i, j);
            }
        }
    }
    cout << cost << endl;
}

int main(){

    int cities, city_pairs;
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
        ss >> cities >> city_pairs;
        if(ss.fail()) return 0;

        for(int i = 0; i < city_pairs; i++){
            getline(cin, input);
            ss.clear();
            ss << input;
            
            int left, right, cost;
            ss >> left >> right >> cost;
            if(ss.fail() || left > cities || right > cities || left == right) return 0;

            if(left > right) swap(left, right);
            pair<int, int> edge = make_pair(left, right);
            weight[edge] = cost;
        }
        
        print_min_connect_cost(weight, cities);
    }

    return 0;
}