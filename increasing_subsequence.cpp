#include <iostream>
#include <sstream>

using namespace std;

void print_LIS(string input){

    int answer_idx = 0;
    string *temp = new string[input.length()];

    for (int i = 0; i < input.length(); i++) temp[i] = "";

    for (int i = 0; i < input.length(); i++){
        int idx = -1, temp_length = 0;
        for (int j = 0; j < i; j++){
            if (input[j] < input[i]){
                if (temp_length < temp[j].length()){
                    temp_length = temp[j].length();
                    idx = j;
                }
            }
        }

        if(idx == -1){
            temp[i] = input[i];
        }
        else{
            temp[i] = temp[idx];
            temp[i].append(1, input[i]);
        }

        if (temp[i].length() > temp[answer_idx].length()){
            answer_idx = i;
        }
    }

    cout << temp[answer_idx] << endl;
    delete[] temp;
}

int main(){

    string buf, input;

    while(true) {
        input.clear();
        getline(cin, buf);
        stringstream ss(buf);
        ss >> input;

        if (input.length() > 0) {
            print_LIS(input);
        }
        else break;
    }

    return 0;
}