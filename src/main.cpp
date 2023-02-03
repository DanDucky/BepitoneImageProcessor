#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <opencv2/imgcodecs.hpp>
#include <filesystem>

using namespace std;
using namespace cv;

static string folderName(string oldName) {
	oldName = oldName.substr(0, oldName.find_last_of('.'));
	if (oldName.find('/') != std::string::npos) {
		oldName = oldName.substr(oldName.find_last_of('/') + 1, oldName.length());
	}
	return oldName;
}

int main () {
	cout << "Welcome to bepitone list gumper\n";
    string filePath = "";
	cout << "Please input the path of the file you would like to bep: ";
	getline(cin, filePath);
	cout << "Input width of prints [5] ";
	string printWidthStr;
	getline(cin, printWidthStr);
	if (printWidthStr == "") {
		printWidthStr = "5";
	}
	int printWidth = stoi(printWidthStr);
    Mat src = imread(filePath, IMREAD_COLOR);
    string outFolder = folderName(filePath) + "_out";
    filesystem::remove_all(outFolder);
	mkdir(outFolder.c_str(), 0777);
	static short direction = 1;
	static unsigned int blockCount = 0;
	static float percent = 0.0;
	static int foundInLineCount = 0;
	int ii = 0;
	int fileCount = 0;
	for (int i = 0; i < src.cols; i+=printWidth) {
		ofstream log;
		log.open(outFolder + "/" + to_string(fileCount));
		log << to_string(fileCount) << "\n";
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
			cout << ".";
			if (foundInLineCount > 0) log << "\n";
			foundInLineCount = 0;
		}
		percent = static_cast<float>(i)/static_cast<float>(src.cols);
		cout << percent*100 << "%\n";
		direction = direction * -1;
		ii+=direction;
		log.close();
		fileCount++;
	}
	cout << "\nCompleted with " << blockCount << " to mine\n";
}
