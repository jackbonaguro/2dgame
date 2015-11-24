#include <stdlib.h>
#include <stdio.h>
#include <iostream>

int main(){
	int val = 1;
	int row = 0;
	int col = 0;

	int a[25][6];

	while(val < 100){
		a[row][col] = val;
		val++;
		if((row == 0) || (col == 5)){
			row = row + col + 1;
			col = 0;
		}else{
			col++;
			row--;
		}
	}

	std::string s;
	for(int r = 0; r < 15; r++){
		for(int c = 0; c < 6; c++){
			s = s + std::to_string(a[r][c]) + " ";
		}
		s = s + "\n";
	}
	std::cout << s;
	std::cout << "\n" + std::to_string(val) + " at " + std::to_string(row) + ", " + std::to_string(col) + "\n";
	return 0;
}