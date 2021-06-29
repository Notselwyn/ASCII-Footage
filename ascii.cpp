#include <opencv2/opencv.hpp>
#include <iostream>
#include <windows.h>
#include <cstdlib>

using namespace std;
using namespace cv;

int main() {
    Mat frame;
    char ascii_chars[] = {' ', ' ', ' ', ' ', '.', '\'', '`', '^', '"', ',', ':', ';', 'I', 'l', '!', 'i', '>', '<', '~', '+', '_', '-', '?', ']', '[', '}', '{', '1', ')', '(', '|', '/', 't', 'f', 'j', 'r', 'x', 'n', 'u', 'v', 'c', 'z', 'X', 'Y', 'U', 'J', 'C', 'L', 'Q', '0', 'O', 'Z', 'm', 'w', 'q', 'p', 'd', 'b', 'k', 'h', 'a', 'o', '*', '#', 'M', 'W', '&', '8', '%', 'B', '@', '$'};
    string file_path;
    string fps;
    cout << "Enter a path for the video (0 for webcam): ";
    cin >> file_path;
    cout << "Enter FPS: ";
    cin >> fps;
    float fps_delay = 1 / stof(fps) * 1000;
    VideoCapture cap;
    if (file_path == "0") {
        cap.open(0);
    } else {
        cap.open(file_path);
    }
    if (!cap.isOpened()) {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    while (true){
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top;

        cap >> frame;
        if (frame.empty()) {
            break;
        }

        resize(frame, frame, Size (columns, rows));
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        Size s = frame.size();
        string frame_text = "";

        Sleep(fps_delay);
        cout << fps_delay << " " << fps << endl;

        for (int y=0; y < s.height; y++) {
            for (int x=0; x < s.width; x++) {
                frame_text += ascii_chars[(sizeof(ascii_chars) - 1) * frame.at<uchar>(y, x) / 255];
            }
            frame_text += "\n";
        }
        cout << frame_text;
    }
    cap.release();
    return 0;
}
