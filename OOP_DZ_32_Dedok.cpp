#include <iostream>
#include <fstream>
using namespace std;
class Fraction {
private:
	int numerator;
	int denominator;
public:
	Fraction() : numerator(0), denominator(1) {}
    Fraction(int num, int den) : numerator(num), denominator(den) {}
	void print() const {
		cout << numerator << "/" << denominator;
	}
	friend ostream& operator<<(ostream& out, const Fraction& f);
	friend istream& operator>>(std::istream& in, Fraction& f);
};
ostream& operator<<(ostream& out, const Fraction& f) {
	out.write(reinterpret_cast<const char*>(&f), sizeof(Fraction));
	return out;
}
istream& operator>>(istream& in, Fraction& f) {
	in.read(reinterpret_cast<char*>(&f), sizeof(Fraction));
	return in;
}
int main()
{
	//Task 1
	Fraction fractions[4] = {
		Fraction(1, 2),
		Fraction(3, 4),
		Fraction(5, 6),
		Fraction(7, 8)
	};
	ofstream outFile("fractions.bin", ios::binary);
	for (const auto& fraction : fractions) {
		outFile << fraction;
	}
	outFile.close();
	Fraction fractionsFromFile[4];
	ifstream inFile("fractions.bin", ios::binary);
	for (auto& fraction : fractionsFromFile) {
		inFile >> fraction;
	}
	inFile.close();
	for (const auto& fraction : fractionsFromFile) {
		fraction.print();
	}
	cout << endl;
	//Task 2
	Fraction fractions_1[4] = {
		Fraction(9, 10),
		Fraction(11, 12),
		Fraction(13, 14),
		Fraction(15, 16)
	};
	ofstream outFile_1("fractions_1.bin", ios::binary);
	for (const auto& fraction : fractions_1) {
		outFile_1 << fraction;
	}
	outFile_1.close();
	ifstream inFile_1("fractions_1.bin", ios::binary);
	inFile_1.seekg(-2 * static_cast<streamoff>(sizeof(Fraction)), ios::end);
	Fraction fraction_1;
	inFile_1 >> fraction_1;
	inFile_1.close();
	fraction_1.print();
}


