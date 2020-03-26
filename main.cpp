#include <iostream>
#include <fstream>
using namespace std;

/**
* Read in the map layout for level
**/
void init_map(int level){
	char ch;
	int num_row = 4;
	int num_col = 4; 
	int map[num_row][num_col] = {0};

	string filename = "level" + to_string(level) + ".txt";
	ifstream file{filename};

	if(!file.is_open()){
		cout << "not valid " << endl;
	}
	
	else{
		for(int i=0; i <num_row; i++){
			for(int j=0; j <num_col; j++){
				file >> map[i][j];
			}
		}
		for(int i=0; i <num_row; i++){
			for(int j = 0; j <num_col; j++){
				cout << map[i][j];
			}
			cout<< endl;
		}

	}

	file.close();

}
int main(){
	int level = 1;
	init_map(level);
	return 0;
}