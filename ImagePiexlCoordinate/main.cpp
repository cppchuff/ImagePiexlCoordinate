#include<opencv2\opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
bool flag = false;
int index = 0;
int xvalue = 0;
int yvalue = 0;
Mat image, image1, image2;
struct CSVDATA {
	int index;
	int x;
	int y;
};
vector<CSVDATA> datalist{};
ofstream outFile;
void mousecallback(int event, int x, int y, int flags, void* userdata);
int main(int argc, char* argv[])
{
	cout << "请将要操作的图片拖入控制台窗口：";
	string path;
	cin >> path;
	namedWindow("imageshow", 0);
	Mat image = imread(path, 1);
	if (!image.data)
	{
		cout << "the image is error" << endl;
		return -1;
	}
	outFile.open("./csvTest.csv", ios::out);
	imshow("imageshow", image);
	image.copyTo(image1);
	cv::setMouseCallback("imageshow", mousecallback, 0);
	waitKey(0);
	outFile.close();
	return 0;
}
void mousecallback(int event, int x, int y, int flags, void* userdata)
{
	image1.copyTo(image2);
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
	{
		flag = true;
		index++;
	}
	break;
	case EVENT_LBUTTONUP:
	{
		if (flag)
		{
			xvalue = x;
			yvalue = y;
			flag = 0;

			cout << index << " " << "X: " << xvalue << "Y: " << yvalue << endl;
			string x = to_string(xvalue);
			string y = to_string(yvalue);
			CSVDATA rowdata{ index,xvalue,yvalue };
			datalist.push_back(rowdata);
			outFile << index << "," << x << "," << y  << endl;
		}
	}
	break;
	}
}
