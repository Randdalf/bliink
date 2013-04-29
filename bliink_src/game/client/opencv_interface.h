#ifdef _WIN32
#pragma once
#endif 

#include "cbase.h"
 #include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"

class OpenCVController: public CWorkerThread {
 
/************************** Member Functions **************************/
public:
 
	bool loop;
	bool track;
	bool hascam;

	OpenCVController();
 
	/**
	*  Destructor  Closes tracker and performs clean up
	*/
	~OpenCVController();

	enum
	{
		CALL_FUNC,
		EXIT,
	};


	int Run(void);
	void Startcap(void);
	bool CallThreadFunction(void);
	void	Display(void);
	bool	hasBlunk(void);
	bool	faceSeen(void);
	void	TrackerSetup(void);
	void	TrackerLoop(void);
	void derivatives (cv::Mat &Ix, cv::Mat &Iy, cv::Mat &It, cv::Mat &frame1, cv::Mat &frame2);
void scale (cv::Mat image);
void LKTracker (cv::Mat image, cv::Mat &Ix, cv::Mat &Iy, cv::Mat &It);
 
private:
	cv::VideoCapture * cap;
	cv::Mat Ix;
	cv::Mat frame;
	cv::Mat LKframe;
	cv::CascadeClassifier face_cascade;
	CvHaarClassifierCascade* cascade;
    cv::Mat Iy;
    cv::Mat It;
	int height;
	int width;
	int count;
	cv::Mat a;
	cv::Mat eyesmat;
	cv:: Mat imageEye;
	bool blink;
	bool seeface;
};