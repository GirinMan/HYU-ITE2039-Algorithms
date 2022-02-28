#include <iostream>
#include <sstream>
#include <vector>

unsigned int **cost;
unsigned int **mark;

void order(int i, int j, const std::vector<int> &vec){
    
    int k;
    if (i == j){
        std::cout << vec[i];
    }
    else{
        k = mark[i][j];
        std::cout << "(";
        order(i, k, vec);
        std::cout << ",";
        order(k + 1, j, vec);
        std::cout << ")";
    }
}

void print_min_cost_with_seq(const std::vector<int> &vec){
    size_t size = vec.size();
    cost = new unsigned int*[size];
    mark = new unsigned int*[size];  
    
    for (int i = 0; i < size; i++){
        cost[i] = new unsigned int[size];
        mark[i] = new unsigned int[size];
    }
    
    for (int d = 0; d < size; d++){
        for (int i = 0; i < size - d; i++){
            int j = i + d;
            
            if (i == j){
                cost[i][j] = 0;
            }
            else{
                int sum = 0;
                for (int k = i; k <= j; k++){
                    sum += vec[k];
                }

                cost[i][j] = 0xffffffff;

                for (int k = i; k < j; k++){
                    if (cost[i][j] > cost[i][k] + cost[k+1][j] + sum){
                        cost[i][j] = cost[i][k] + cost[k+1][j] + sum;
                        mark[i][j] = k;
                    }
                }
            }
        }
    }
    
    std::cout << cost[0][size-1] << " ";
    if (size > 1) order(0, size-1, vec);
    std::cout << std::endl;
    
    for (int i = 0; i < size; i++){
        delete[] mark[i];
        delete[] cost[i];
    }
    delete[] mark;
    delete[] cost;
}

int main(){
	
    int num;
    std::string buf;
    std::vector<int> vec;
    
    while(true) {
        vec.clear();
        std::getline(std::cin, buf);
        
        std::stringstream ss(buf);
        while ( ss >> num ) vec.push_back(num);
        
        if (vec.size() > 0) print_min_cost_with_seq(vec);
        else break;
    }
    return 0;
}
