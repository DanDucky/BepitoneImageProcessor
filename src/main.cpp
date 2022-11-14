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
    string filePath = "";
	cout << "Please input the path of the file you would like to bep: ";
	getline(cin, filePath);
	cout << "Input width of prints [3] ";
	string printWidthStr;
	getline(cin, printWidthStr);
	if (printWidthStr == "") {
		printWidthStr = "3";
	}
	int printWidth = stoi(printWidthStr);
    Mat src = imread(filePath, IMREAD_COLOR);
    string outFolder = "out";
	if (mkdir(outFolder.c_str(), 0777) == -1) {
	    cout << "Borken\n";
	}
	static short direction = 1;
	static unsigned int blockCount = 0;
	static int foundInLineCount = 0;
	int ii = 0;
	int fileCount = 0;
	for (int i = 0; i < src.cols; i+=printWidth) {
		ofstream log;
		log.open(outFolder + "/" + to_string(fileCount));
		for (; ii < src.rows && ii >= 0; ii+=direction) {
			for (int iii = i; iii < i + printWidth && iii < src.cols; iii++) {
				Vec3b color = src.at<Vec3b>(Point(iii,ii));
				if (color[0] < 150 && color[1] < 150 && color[2] < 150) {
					if (foundInLineCount != 0 && foundInLineCount - 1 < printWidth) {
						log << "#";
					}
					log << iii << " " << ii;
					foundInLineCount++;
					blockCount++;
				}
			}
			foundInLineCount = 0;
			log << "\n";
		}
		direction = direction * -1;
		ii+=direction;
		log.close();
		fileCount++;
	}
	cout << "\nCompleted with " << blockCount << " to mine\n";
}
