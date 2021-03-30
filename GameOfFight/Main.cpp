#include <fstream>
using namespace std;
int main() {
	ofstream fout("test.out");
	fout << "hi";
	fout.close();
	return 0;
}