#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

int main () {
	cout << "Welcome to bepitone list gumper\n";
    string filePath = "../../test/test.png";
	cout << "Please input the path of the file you would like to bep: ";
	getline(cin, filePath);
	cout << "Input width of prints [3] ";
	string printWidthStr;
	getline(cin, printWidthStr);
	int printWidth = stoi(printWidthStr);
    Mat src = imread(filePath, IMREAD_COLOR);
    string outFolder = "out";
	if (mkdir(outFolder.c_str(), 0777) == -1) {
	    cout << "Borken\n";
	}
	static short direction = 1;
	static bool used = false;
	static bool found = false;
	int ii = 0;
	int fileCount = 0;
	for (int i = 0; i < src.cols; i+=printWidth) {
		ofstream log;
		log.open(outFolder + "/" + to_string(fileCount));
		cout << "\nbeginning log " << fileCount << "\n              └─> ";
		for (; ii < src.rows && ii >= 0; ii+=direction) {
			for (int iii = i; iii < i + 3 && iii <= src.cols; iii++) {
				Vec3b color = src.at<Vec3b>(Point(iii,ii));
				if (color[0] < 150 && color[1] < 150 && color[2] < 150) {
					log << ii << " " << iii << "\n";
					used = true;
					found = true;
				}
			}
			if (found == true) {
				cout << "●";
			} else {
				cout << "○";
			}
			found = false;
		}
		if (!used) {
			log << "EMPTY\n";
		}
		used = false;
		direction = direction * -1;
		ii+=direction;
		log.close();
		fileCount++;
	}
}
