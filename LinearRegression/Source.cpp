//********************
//Mark Maupin
//CS 4328V
//10/18/2017
//Homework 2, problem 3
//Linear Regression using Gradient Descent
//***********************************

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

struct Mpg {
	double y;
	double x[6];
};

Mpg uLimit, lLimit;
const float ALPHA = .05;

void print(Mpg vec) {
	for (int j = 1; j < 6; ++j) {
		cout << vec.x[j] << " ";
	}
	cout << endl << endl;
}

//********************************
//normalize: normalizes the data using feature scaling
//returns a copy of the data vector with normalized data
//******************************
vector<Mpg> normalize(vector<Mpg> vec) {
	for (int i = 0; i < vec.size(); ++i) {
		vec[i].y = (vec[i].y - lLimit.y) / (uLimit.y - lLimit.y);
		for (int j = 1; j < 6; ++j) {
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
	for (int i = 1; i < 6; ++i) {
		lLimit.x[i] = DBL_MAX;
		uLimit.x[i] = 0;
	}

	for (int i = 0; i < vec.size(); ++i) {
		if (lLimit.y > vec[i].y)
			lLimit.y = vec[i].y;
		for (int j = 1; j < 6; ++j) {
			if (lLimit.x[j] > vec[i].x[j])
				lLimit.x[j] = vec[i].x[j];
		}

		if (uLimit.y < vec[i].y)
			uLimit.y = vec[i].y;
		for (int j = 1; j < 6; ++j) {
			if (uLimit.x[j] < vec[i].x[j])
				uLimit.x[j] = vec[i].x[j];
		}
	}
	return normalize(vec);
}

//**********
//returns crossproduct of the vectors 
//theta and x
//*******************
double hofx(Mpg x, double theta[6]) {
	double temp = 0;

	for (int i = 0; i < 6; ++i) {
		temp += (x.x[i] * theta[i]);
	}
	return temp;
}

//***************************
//Implementation of Gradien Descent
//calls hofx
//*********************
void gradient(vector<Mpg> vec, double theta[6]) {
	double temp[6];
	bool flag[6];
	for (int i = 0; i < 6; ++i) {
		flag[i] = false;
	}
	while (!flag[0] || !flag[1] || !flag[2] || !flag[3] || !flag[4] || !flag[5]) {
		for (int j = 0; j < 6; ++j) {
			//if (!flag[j]) {
				for (int i = 0; i < vec.size(); ++i) {
					temp[j] = (vec[i].y - hofx(vec[i], theta))*vec[i].x[j];
				}
				temp[j] = theta[j] + ALPHA * temp[j];
			//}
		}
		for (int j = 0; j < 6; ++j) {
			if (ALPHA > abs(temp[j]- theta[j]))
				flag[j] = true;
			theta[j] = temp[j];
		}
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
	double prediction1, prediction2, prediction3;

	double theta[6] = { 0, 0, 0, 0, 0, 0 };

	inFile.open("linear_regression_data-1.txt");

	while (getline(inFile, line)) {
		
		if (line.empty()) {
			break;
		}

		istringstream iss(line);

		if (line.at(0) == '?') {
			getline(iss, temp1, '\t');
			temp.y = -1;
			temp.x[0] = 1;
			for (int i = 1; i < 5; ++i) {
				getline(iss, temp1, '\t');
				temp.x[i] = stod(temp1);
			}
			getline(iss, temp1);
			temp.x[5] = stod(temp1);

			test.push_back(temp);
		}
		else {
			getline(iss, temp1, '\t');
			temp.y = stod(temp1);
			temp.x[0] = 1;
			for (int i = 1; i < 5; ++i) {
				getline(iss, temp1, '\t');
				temp.x[i] = stod(temp1);
			}
			getline(iss, temp1);
			temp.x[5] = stod(temp1);
			
			data.push_back(temp);
		}
	}
	

	
	nData = bounds(data);
	gradient(nData, theta);

	prediction1 = hofx(test[0], theta);
	prediction2 = hofx(test[1], theta);
	prediction3 = hofx(test[2], theta);

	cout << "Test value: ";
	print(test[0]);
	cout << "Prediction: " << prediction1 << endl << endl;
	cout << "Test value: ";
	print(test[1]);
	cout << "Prediction: " << prediction2 << endl << endl;
	cout << "Test value: ";
	print(test[2]);
	cout << "Prediction: " << prediction3;

	return 0;

}