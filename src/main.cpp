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
	int ii = 0;
	int fileCount = 0;
	for (int i = 0; i < src.cols; i+=printWidth) {
		ofstream log;
		log.open(outFolder + "/" + to_string(fileCount) + "-" + to_string(printWidth) + ".path");
		for (; ii < src.rows && ii >= 0; ii+=direction) {
			for (int iii = i; iii < i + 3; iii++) {
				Vec3b color = src.at<Vec3b>(Point(ii,iii));
				if (color[0] < 150 && color[1] < 150 && color[2] < 150) {
					log << ii << " " << iii << "\n";
				}
			}
		}
		direction = direction * -1;
		ii+=direction;
		log.close();
		fileCount++;
	}
}
