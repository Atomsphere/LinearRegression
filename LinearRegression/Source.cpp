#include <vector>

using namespace std;



struct Mpg {
	double mpg;
	double cyl;
	double dis;
	double hp;
	double w;
	double a;
};

//********************************
//normalize: normalizes the data using feature scaling
//returns a copy of the data vector with normalized data
//******************************
vector<Mpg> normalize(vector<Mpg> vec, Mpg uLimit, Mpg lLimit) {
	for (int i = 0; i < vec.size(); ++i) {
		vec[i].mpg = (vec[i].mpg - lLimit.mpg) / (uLimit.mpg - lLimit.mpg);
		vec[i].cyl = (vec[i].cyl - lLimit.cyl) / (uLimit.cyl - lLimit.cyl);
		vec[i].dis = (vec[i].dis - lLimit.dis) / (uLimit.dis - lLimit.dis);
		vec[i].hp = (vec[i].hp - lLimit.hp) / (uLimit.hp - lLimit.hp);
		vec[i].w = (vec[i].w - lLimit.w) / (uLimit.w - lLimit.w);
		vec[i].a = (vec[i].a - lLimit.a) / (uLimit.a - lLimit.a);
	}
	return vec;
}

//****************
//bounds: finds the lower and upper bounds
//returns a call to normalize
//*******************
vector<Mpg> bounds(vector<Mpg> vec) {
	Mpg uLimit, lLimit;
	
	lLimit.mpg = DBL_MAX;
	lLimit.cyl = DBL_MAX;
	lLimit.dis = DBL_MAX;
	lLimit.hp = DBL_MAX;
	lLimit.w = DBL_MAX;
	lLimit.a = DBL_MAX;

	uLimit.mpg = 0;
	uLimit.cyl = 0;
	uLimit.dis = 0;
	uLimit.hp = 0;
	uLimit.w = 0;
	uLimit.a = 0;


	for (int i = 0; i < vec.size(); ++i) {
		if (lLimit.mpg > vec[i].mpg)
			lLimit.mpg = vec[i].mpg;
		if (lLimit.cyl > vec[i].cyl)
			lLimit.cyl = vec[i].cyl;
		if (lLimit.dis > vec[i].dis)
			lLimit.dis = vec[i].dis;
		if (lLimit.hp > vec[i].hp)
			lLimit.hp = vec[i].hp;
		if (lLimit.w > vec[i].w)
			lLimit.w = vec[i].w;
		if (lLimit.a > vec[i].a)
			lLimit.a = vec[i].a;

		if (uLimit.mpg < vec[i].mpg)
			uLimit.mpg = vec[i].mpg;
		if (uLimit.cyl < vec[i].cyl)
			uLimit.cyl = vec[i].cyl;
		if (uLimit.dis < vec[i].dis)
			uLimit.dis = vec[i].dis;
		if (uLimit.hp < vec[i].hp)
			uLimit.hp = vec[i].hp;
		if (uLimit.w < vec[i].w)
			uLimit.w = vec[i].w;
		if (uLimit.a < vec[i].a)
			uLimit.a = vec[i].a;
	}
	return normalize(vec, uLimit, lLimit);
}


int main() {
	vector<Mpg> data;
	vector<Mpg> nData; 






}