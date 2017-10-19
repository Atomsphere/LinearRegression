#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;



struct Mpg {
	double y;
	double x[5];
};

Mpg uLimit, lLimit;
const float ALPHA = .01;

void printTest(vector<Mpg> vec) {
	for (int i = 0; i < vec.size(); ++i) {
		cout << vec[i].y << " - ";
		for (int j = 0; j < 5; ++j) {
			cout << vec[i].x[j] << " - ";
		}
		cout << endl;
	}
}

//********************************
//normalize: normalizes the data using feature scaling
//returns a copy of the data vector with normalized data
//******************************
vector<Mpg> normalize(vector<Mpg> vec) {
	for (int i = 0; i < vec.size(); ++i) {
		vec[i].y = (vec[i].y - lLimit.y) / (uLimit.y - lLimit.y);
		for (int j = 0; j < 5; ++j) {
			vec[i].x[j] = (vec[i].x[j] - lLimit.x[j]) / (uLimit.x[j] - lLimit.x[j]);
		}
	}
	return vec;
}

//****************
//bounds: finds the lower and upper bounds
//returns a call to normalize
//*******************
vector<Mpg> bounds(vector<Mpg> vec) {
	
	lLimit.y = DBL_MAX;
	uLimit.y = 0;
	for (int i = 0; i < 5; ++i) {
		lLimit.x[i] = DBL_MAX;
		uLimit.x[i] = 0;
	}

	for (int i = 0; i < vec.size(); ++i) {
		if (lLimit.y > vec[i].y)
			lLimit.y = vec[i].y;
		for (int j = 0; j < 5; ++j) {
			if (lLimit.x[j] > vec[i].x[j])
				lLimit.x[j] = vec[i].x[j];
		}

		if (uLimit.y < vec[i].y)
			uLimit.y = vec[i].y;
		for (int j = 0; j < 5; ++j) {
			if (uLimit.x[j] < vec[i].x[j])
				uLimit.x[j] = vec[i].x[j];
		}
	}
		return normalize(vec);
}


void gradient(vector<Mpg> vec, double theta[5]) {
	while (1) {

	}
}

int main() {
	vector<Mpg> data;
	vector<Mpg> nData; 
	vector<Mpg> test;
	vector<Mpg> nTest;
	ifstream inFile;
	Mpg temp;
	string line;
	string temp1;
	double theta[5] = { 0, 0, 0, 0, 0 };

	inFile.open("linear_regression_data-1.txt");

	while (getline(inFile, line)) {
		
		if (line.empty()) {
			break;
		}

		istringstream iss(line);

		if (line.at(0) == '?') {
			getline(iss, temp1, '\t');
			temp.y = -1;
			for (int i = 0; i < 4; ++i) {
				getline(iss, temp1, '\t');
				temp.x[i] = stod(temp1);
			}
			getline(iss, temp1);
			temp.x[4] = stod(temp1);

			test.push_back(temp);
		}
		else {
			getline(iss, temp1, '\t');
			temp.y = stod(temp1);
			for (int i = 0; i < 4; ++i) {
				getline(iss, temp1, '\t');
				temp.x[i] = stod(temp1);
			}
			getline(iss, temp1);
			temp.x[4] = stod(temp1);
			
			data.push_back(temp);
		}
	}
	


	nData = bounds(data);
	nTest = normalize(test); 	
	cout << endl;
	printTest(nTest);
	cout << endl << endl;
	printTest(nData);
	return 0;

}