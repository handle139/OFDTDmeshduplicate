#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<sstream>
#include<vector>
using namespace std;

int main() {
	//open file
	fstream ifs;
	ifs.open("MS.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "Error" << endl;
		return EXIT_FAILURE;
	}
	fstream ofs;
	ofs.open("Copy.txt", ios::out);
	if (!ofs.is_open()) {
		cout << "Error" << endl;
		return EXIT_FAILURE;
	}
	double bx1, bx2, by1, by2;

	cout << "Box x1 :" << flush;
	cin >> bx1;
	cout << "Box x2 :" << flush;
	cin >> bx2;
	cout << "Box y1 :" << flush;
	cin >> by1;
	cout << "Box y2 :" << flush;
	cin >> by2;

	double maxx, maxy, minx, miny;
	cout << "Maximum x :" << flush;
	cin >> maxx;
	cout << "Minimum x :" << flush;
	cin >> minx;
	cout << "Maximum y :" << flush;
	cin >> maxy;
	cout << "Minimum y :" << flush;
	cin >> miny;

	double spx, spy;
	cout << "Move x :" << flush;
	cin >> spx;
	cout << "Move y :" << flush;
	cin >> spy;

	int maxcx, maxcy, mincx, mincy;
	// count x(unsigned)
	if (bx1 < bx2) {
		maxcx = (bx2 - maxx) / spx;
		if (maxcx < 0) { maxcx = maxcx * -1; }
		mincx = (bx1 - minx) / spx;
		if (mincx < 0) { mincx = mincx * -1; }
	}
	else {
		maxcx = (bx1 - maxx) / spx;
		if (maxcx < 0) { maxcx = maxcx * -1; }
		mincx = (bx2 - minx) / spx;
		if (mincx < 0) { mincx = mincx * -1; }
	}
	// count y(unsigned)
	if (by1 < by2) {
		maxcy = (by2 - maxy) / spy;
		if (maxcy < 0) { maxcy = maxcy * -1; }
		mincy = (by1 - miny) / spy;
		if (mincy < 0) { mincy = mincy * -1; }
	}
	else {
		maxcy = (by1 - maxy) / spy;
		if (maxcy < 0) { maxcy = maxcy * -1; }
		mincy = (by2 - miny) / spy;
		if (mincy < 0) { mincy = mincy * -1; }
	}

	string str = "";
	int i = 0;
	int j = 0;
	int cnt = 0;
	//Number of duplicates
	int nod = (maxcx * maxcy) + (maxcx * mincy) + (mincx * maxcy) + (mincx * mincy) + maxcx + mincx + maxcy + mincy;
	cout << maxcx << maxcy << mincx << mincy << endl;
	while (getline(ifs, str)) {
		string tmp = "";
		istringstream stream(str);
		int fs = 0;
		vector<string> stack(100);
		
		while (getline(stream, tmp, ' ')) {
			if (j == 0) {
				fs = tmp.find("geometry");
				if (fs != -1) { 
					for (int k = 0; k < nod; k++) {
						stack[k] += "geometry = ";
					}
				}
				j++;
				continue;
			}
			if (j == 1) {
				j++;
				continue;
			}
			if (fs != -1) {
				cnt = 0;
				istringstream ss;
				ss = istringstream(tmp);
				double num = stod(tmp.c_str());
				int inum = stoi(tmp.c_str());
				if (cnt < nod) {
					if (j == 4 || j == 5) {
						//coordinate (+,+)
						for (int a = 0; a <= maxcx; a++) {
							for (int b = 0; b <= maxcy; b++) {
								if (b == 0 && a == 0) { b++; }
								stack[cnt] += to_string(num + (spx * a));
								stack[cnt] += ' ';
								cnt++;
							}
						}
						//(+,-)
						for (int c = 0; c <= maxcx; c++) {
							for (int d = 1; d <= mincy; d++) {
								stack[cnt] += to_string(num + (spx * c));
								stack[cnt] += ' ';
								cnt++;
								
							}
						}
						//(-,+)
						for (int e = 1; e <= mincx; e++) {
							for (int f = 0; f <= maxcy; f++) {
								stack[cnt] += to_string(num - (spx * e));
								stack[cnt] += ' ';
								cnt++;
							}
						}
						//(-,-)
						for (int g = 1; g <= mincx; g++) {
							for (int h = 1; h <= mincy; h++) {
								stack[cnt] += to_string(num - (spx * g));
								stack[cnt] += ' ';
								++cnt;
								
							}
						}
					}
					else
						if (j == 6 || j == 7) {
							//coordinate (+,+)
							for (int a = 0; a <= maxcx; a++) {
								for (int b = 0; b <= maxcy; b++) {
									if (b == 0 && a == 0) { b++; }
									stack[cnt] += to_string(num + (spy * b));
									stack[cnt] += ' ';
									cnt++;
									
								}
							}
							//(+,-)
							for (int c = 0; c <= maxcx; c++) {
								for (int d = 1; d <= mincy; d++) {
									stack[cnt] += to_string(num - (spy * d));
									stack[cnt] += ' ';
									cnt++;
									
								}
							}
							//(-,+)
							for (int e = 1; e <= mincx; e++) {
								for (int f = 0; f <= maxcy; f++) {
									stack[cnt] += to_string(num + (spy * f));
									stack[cnt] += ' ';
									cnt++;
									
								}
							}
							//(-,-)
							for (int g = 1; g <= mincx; g++) {
								for (int h = 1; h <= mincy; h++) {
									stack[cnt] += to_string(num - (spy * h));
									stack[cnt] += ' ';
									cnt++;
									
								}
							}
						}
						else
						{
							for (int a = 0; a < nod; a++) {
								stack[a] += to_string(inum);
								stack[a] += ' ';
							}
						}
				}

			}
			j++;
		}
		if (j == 10) {
			for (int f = 0; f < nod; f++) {
				ofs << stack[f] << endl;
			}
		}
		j = 0;
	}

	//close file
	ifs.close();
	ofs.close();
	return 0;
}

