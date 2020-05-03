#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Mac {
	string mac;
	string vlan;
	bool ignore = false;
	Mac(string m, string vl) : mac(m), vlan(vl) {}
};

int main(int argc, char** argv) {
	cout << "Mac Duplicate Finder Server v 1.1" << endl;
	cout << "Written by DevilishSkull" << endl;
	cout << "Modded by Gamania" << endl;
	vector<Mac> macs;
	vector<string> ex;

	ifstream fin("GotIt.txt");
	while (!fin.eof()) {
		string mac, vlan;
		fin >> mac >> vlan;
		macs.push_back(Mac(mac, vlan));
	}
	fin.close();

	ifstream fex("exceptions.txt");
	while (!fex.eof()) {
		string mac;
		fex >> mac;
		ex.push_back(mac);
	}
	fex.close();

	vector<int> ind;
	for (int i = 1; i < macs.size(); i++) {
		bool cont = false;
		for (auto& j : ex) {
			if (macs[i].mac == j) {
				cont = true;
				break;
			}
		}
		if (cont) continue;

		bool b = false;
		for (int j = i + 1; j < macs.size(); j++) {
			if (macs[i].mac == macs[j].mac && !macs[j].ignore) {
				if (!b) {
					ind.push_back(i);
					b = true;
				}
				ind.push_back(j);
				macs[j].ignore = true;
			}
		}
	}

	ofstream fout("output.txt");
	for (auto& i : ind) {
		fout << macs[i].mac << " " << macs[i].vlan << endl;
	}
	fout.close();

	return 0;
}