#include<math.h>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;
int main()
{
	VideoCapture capture("420410377230.avi");
	Mat src, dst,dst1,dst2;
	
	while (1)
	{
		capture >> src;
		imshow("input", src);
		inRange(src, Scalar(0, 0, 80), Scalar(34, 255, 255), dst1);
		//inRange(src, Scalar(156, 100, 60), Scalar(180, 200, 220), dst2);
		dst = dst1 ;
		dst2 = src ;
		Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(dst, dst, kernel);
		imshow("output", dst);

		namedWindow("output2");
		vector<vector<Point>> contours;
		findContours(dst, contours, RETR_LIST,CHAIN_APPROX_SIMPLE );
		Mat drawing=Mat::zeros(dst.size(),CV_8UC3); 
		vector<RotatedRect> minrectangle(contours.size());
		
		int t = 0;
		Point2f pointer2f[4];
		Point2f pointcenter;
		Point2f c;
		float r=0;
		for (int i = 0; i < contours.size(); i++)
		{
			drawContours(drawing, contours, i, Scalar(255, 255, 255),2);
			cout << abs(contourArea(contours[i], true))<<endl;
			//printf("%lf\n",abs(contourArea(contours[i], true)));

			if (abs(contourArea(contours[i], true)) > 2000 && abs(contourArea(contours[i], true)) < 3000)
			{
				minrectangle[i] = minAreaRect(Mat(contours[i]));
				minrectangle[i].points(pointer2f);
				r = sqrt((pointer2f[0].x - pointer2f[1].x)*(pointer2f[0].x - pointer2f[1].x)
					+ (pointer2f[0].y - pointer2f[1].y)*(pointer2f[0].y - pointer2f[1].y));
				 c = minrectangle[i].center;
				 printf("OK\n");
			}

			else if (abs(contourArea(contours[i], true)) > 500 && abs(contourArea(contours[i], true) < 700))
			{
				minrectangle[i] = minAreaRect(Mat(contours[i]));
				minrectangle[i].points(pointer2f);
				for (int j = 0; j < 4; j++)
				{
					line(drawing, pointer2f[j], pointer2f[(j + 1) % 4], Scalar(100, 100, 100),5);
				}
				pointcenter = minrectangle[i].center;
				
				//if (sqrt((c.x - pointcenter.x)*(c.x - pointcenter.x)
				//	+ (c.y - pointcenter.y)*(c.y - pointcenter.y)) < r)
				//{
				//	circle(drawing, pointcenter, 3, Scalar(24, 100, 255), 3);
				//}
				
			}

			if (sqrt((c.x - pointcenter.x)*(c.x - pointcenter.x)
				+ (c.y - pointcenter.y)*(c.y - pointcenter.y)) < r)
			{
				circle(drawing, pointcenter, 3, Scalar(24, 100, 255), 3);
				circle(dst2, pointcenter, 3, Scalar(24, 100, 255), 3);
			}

			//minrectangle[i]=minAreaRect(Mat(contours[i]));
			//minrectangle[i].points(pointer2f);
			//for (int j = 0; j < 4; j++)
			//{
			//	line(drawing, pointer2f[j], pointer2f[(j + 1) % 4], Scalar(100, 100, 100),5);
			//}
		}
		printf("\n");

		imshow("output2", drawing);
		imshow("Ð§¹ûÍ¼",dst2);
		waitKey(100);
	}

	waitKey(0);
}