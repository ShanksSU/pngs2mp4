#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>

using namespace std;
using namespace cv;
namespace fs = filesystem;

bool compareFilenames(const string& a, const string& b) {
    string filenameA = fs::path(a).filename().string();
    string filenameB = fs::path(b).filename().string();

    int numberA = stoi(filenameA);
    int numberB = stoi(filenameB);

    return numberA < numberB;
}

void pngs2mp4(vector<string> png_list, string savePath, string title = "output") {
    sort(png_list.begin(), png_list.end(), compareFilenames);
    Mat img = imread(png_list[0]);
    int height = img.rows;
    int width = img.cols;
    int layers = png_list.size();
    int fps = 24;
    string filename = savePath + title + ".mp4";

    VideoWriter video(filename, VideoWriter::fourcc('m', 'p', '4', 'v'), fps, Size(width, height));
    for (string png_file : png_list) {
        img = imread(png_file);
        video.write(img);
        cout << png_file << endl;
    }
    video.release();
}

int main() {
    vector<string> png_list;
    string path = "./resources/boll_img/";
    string savePath = "./resources/boll_img/video/";
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.path().extension() == ".png") {
            png_list.push_back(entry.path().string());
        }
    }
    pngs2mp4(png_list, savePath);
    return 0;
}
