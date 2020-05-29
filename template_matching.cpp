#include <iostream>
#include <opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture capture(0);
	int cnt = 0;
	Mat frame;	//存储每一帧的图像
	Mat tempMat;
	Mat refMat;
	Mat resMat;
	Mat disMat;
	while (1)
	{
		capture >> frame;	//读取当前帧
		if (cnt == 0) 
		{
			Rect2d r;
			r = selectROI(frame, true);
			tempMat = frame(r);
			tempMat.copyTo(refMat);
			destroyAllWindows();
		}

		int match_method = 0;
		matchTemplate(frame, refMat, resMat, match_method);
		normalize(resMat, resMat, 0, 1, NORM_MINMAX, -1, Mat());

		double minVal; double maxVal; Point minLoc; Point maxLoc; Point matchLoc;
		minMaxLoc(resMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

		if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
			matchLoc = minLoc;
		else
			matchLoc = maxLoc;

		frame.copyTo(disMat);
		rectangle(disMat, matchLoc, Point(matchLoc.x + refMat.cols, matchLoc.y + refMat.rows), Scalar::all(0), 2, 8, 0);
		cnt++;

		imshow("template", refMat);
		imshow("dispMat", disMat);
		waitKey(30);
	}
	return 0;
}
