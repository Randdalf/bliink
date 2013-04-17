/****************************************************************************
*  Sample shell for specific tracker instance
*
*  This is very dependent on what tracker and API you are using
* 
*  This example is a conceptual template of how it would look
*
******************************************************************************/
#include "cbase.h"
#include "opencv_interface.h"
#include "c_baseplayer.h"
#include "baseplayer_shared.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "tier0/threadtools.h"
#include "baseplayer_shared.h"
#include "gamerules.h"

#include <math.h>
#include <iostream>
#include <stdio.h>
#include "tier0/memdbgon.h"
#include <fstream>

 using namespace std;
 using namespace cv;
 
/****************************************************************************
*  Constructor 
******************************************************************************/
OpenCVController::OpenCVController() {
				
	// Capture the Image from the webcam
/*CvCapture *pCapturedImage = cvCreateCameraCapture(0);

// Get the frame
IplImage *pSaveImg = cvQueryFrame(pCapturedImage);

// Save the frame into a file
cvSaveImage("opencvtest.jpg" ,pSaveImg);*/
	cap = new cv::VideoCapture( 0 );
				TrackerSetup();
				  cascade = (CvHaarClassifierCascade*)cvLoad( "haarcascade_frontalface_alt.xml" );
				  blink = false;
				  seeface = false;
				  engine->ClientCmd( "BlinkPanelOff\n" );
				  loop = true;

			//	 face_cascade.load("haarcascade_frontalface_alt.xml");


	//			 for (int i =0; i < 10; i++) { 

  //}

	//Put in code here that is needed to connect to your tracker and initialize it
}

 
/****************************************************************************
*  Destructor
******************************************************************************/
OpenCVController::~OpenCVController(){
	loop = false;
	delete cap;
}

void OpenCVController::Startcap() {
	cap = new cv::VideoCapture( 0 );
}


bool	OpenCVController::CallThreadFunction()
	{
		CallWorker( CALL_FUNC );
		return true;
	}

int OpenCVController::Run() {

	unsigned nCall;
	//while(WaitForCall( &nCall ) )
	loop = true;
	track = false;
    while(loop)
	{    
		C_BasePlayer *pLocalPlayer = C_BasePlayer::GetLocalPlayer();
		if (pLocalPlayer) {
			if (pLocalPlayer->IsAlive())   //Only do blinks when player is alive
				track = true;
			else
				track = false;
		}
		else 
		  track = false;

			if (!loop)        //Stop looping user exits
			{
				Reply( 1 );
				break;
			}
			Reply( 1 );
			if (track)
              TrackerLoop();
        }
        return 1;

}

void OpenCVController::TrackerSetup() {
		height = (int) cap->get(CV_CAP_PROP_FRAME_HEIGHT);
        width  = (int) cap->get(CV_CAP_PROP_FRAME_WIDTH);
		count = 0;
}

void OpenCVController::TrackerLoop() {
	 // create and grab a frame
          //      cv::Mat frame;
                *cap >> frame;
 
                // Convert the frame to gray for better processing
                cvtColor( frame, frame, CV_BGR2GRAY );
                a.create(frame.size(), frame.type());
 
                if (count == 0)
                {
                        // Copy over the frame into a
                        for (int i = 0; i < frame.rows; i++)
                        {
                                for (int j = 0; j < frame.cols; j++)
                                {
                                        a.at<uchar>(i, j) = frame.at<uchar>(i, j);
                                }
                        }
 
                        count = 1;
                        Ix = cv::Mat(frame.rows-1, frame.cols-1, CV_64FC1);
                        Iy = cv::Mat(frame.rows-1, frame.cols-1, CV_64FC1);
                        It = cv::Mat(frame.rows, frame.cols, CV_64FC1);
                }
 
                else
                {
                        derivatives (Ix, Iy, It, a, frame);
 
                        // Take a copy of the original image
                        cv::Mat original = a.clone();
                        LKTracker (original, Ix, Iy, It);
 
                        scale(Ix);
                        scale(Iy);
                        scale(It);
 
                        // Update a
                        for (int i = 0; i < frame.rows; i++)
                        {
                                for (int j = 0; j < frame.cols; j++)
                                {
                                        a.at<uchar>(i, j) = frame.at<uchar>(i, j);
                                }
                        }
                }
				//cv::imshow("Original Video", frame);
}

 
/****************************************************************************
*  Cues the tracker for an update
*
******************************************************************************/
void OpenCVController::Display() {
 
		//Here use your tracker API/SDK to perform any per-frame steps that must
		//be called to update the tracker
		//my_tracking_api.update();
	//	cv::Mat frame;
    //     *cap >> frame;
	    //        frame = cvQueryFrame( capture );
				 imshow( "Name", frame);
			//	 imshow( "Name", LKframe);
			//	imshow("NAme", imageEye);
}

bool OpenCVController::hasBlunk() {
	return blink;
}

bool OpenCVController::faceSeen() {
	return seeface;
}


void OpenCVController::derivatives (cv::Mat &Ix, cv::Mat &Iy, cv::Mat &It, cv::Mat &frame1, cv::Mat &frame2)
{
	
        double a;
        double b;
        double c;
        double d;
        double e;
        double f;
        double g;
        double h;
 
        for (int i = 0; i < frame1.rows-1; i++)
        {
                for (int j = 0; j < frame1.cols-1; j++)
                {
                        a = (double)frame1.at<uchar>(i, j);
                        b = (double)frame1.at<uchar>(i, j+1);
                        c = (double)frame1.at<uchar>(i+1, j);
                        d = (double)frame1.at<uchar>(i+1, j+1);
 
                        e = (double)frame2.at<uchar>(i, j);
                        f = (double)frame2.at<uchar>(i, j+1);
                        g = (double)frame2.at<uchar>(i+1, j);
                        h = (double)frame2.at<uchar>(i+1, j+1);
 
                        Ix.at<double>(i,j) = (((b-a) + (d-c) + (f-e) + (h-g)) / 4);
                        Iy.at<double>(i,j) = (((c-a) + (d-b) + (g-e) + (h-f)) / 4);
                        It.at<double>(i,j) = (((e-a) + (f-b) + (g-c) + (h-d)) / 4);
                }
        }
}
 
 
void OpenCVController::LKTracker (cv::Mat image, cv::Mat &Ix, cv::Mat &Iy, cv::Mat &It)
{

	C_BasePlayer *pLocalPlayer = C_BasePlayer::GetLocalPlayer();
        cv::Mat A = cv::Mat(2, 2, CV_64FC1);
        cv::Mat invA = cv::Mat(2, 2, CV_64FC1);
        cv::Mat b = cv::Mat(2, 1, CV_64FC1);
        cv::Mat v = cv::Mat(2, 1, CV_64FC1);

		cv::Mat A2 = cv::Mat(2, 2, CV_64FC1);
        cv::Mat invA2 = cv::Mat(2, 2, CV_64FC1);
        cv::Mat b2 = cv::Mat(2, 1, CV_64FC1);
        cv::Mat v2 = cv::Mat(2, 1, CV_64FC1);
		
		 Mat frame_gray;

//  cvtColor( image, frame_gray, CV_BGR2GRAY );
  equalizeHist( image, frame_gray );

  MemStorage storage(cvCreateMemStorage(0));
    CvMat _image = frame_gray;
    CvSeq* obs = cvHaarDetectObjects( &_image, cascade, storage, 1.1,
                                           2, 0 |CV_HAAR_DO_ROUGH_SEARCH |CV_HAAR_FIND_BIGGEST_OBJECT, Size(30, 30) );

	vector<CvRect> faces;

	for( int i = 0; i < obs->total; i++ )
    {
        CvRect face_rect = *(CvRect*)cvGetSeqElem( obs, 0);
		faces.push_back(face_rect);
	}

		 int lface = 0;
		 if (faces.size() != 0) {
	  if (faces.size() > 1) {
	  int large = faces[0].height * faces[0].width;
	  for (int i = 1; i < faces.size(); i++) {
		  int temp = faces[i].height * faces[i].width;
		  if (temp > large) {
			  large = temp;
			  lface = i;
		  }
	  }

	  }
		 }
		 
 
	  cv:: Mat ixEye;
	  cv:: Mat iyEye;
	  cv:: Mat itEye;

	   cv:: Mat imageEye2;
	  cv:: Mat ixEye2;
	  cv:: Mat iyEye2;
	  cv:: Mat itEye2;
	  
     if (faces.size() != 0 ) {
	//	 engine->ClientCmd( "NoFacePanelOff\n" );

		 seeface = true;


		imageEye = image(Rect(faces[lface].x + faces[lface].width * 0.22,faces[lface].y + faces[lface].height * 0.28,faces[lface].width * 0.6,faces[lface].height * 0.15));
		ixEye = Ix(Rect(faces[lface].x + faces[lface].width * 0.22,faces[lface].y + faces[lface].height * 0.28,faces[lface].width * 0.6,faces[lface].height * 0.15));
		iyEye = Iy(Rect(faces[lface].x + faces[lface].width * 0.22,faces[lface].y + faces[lface].height * 0.28,faces[lface].width * 0.6,faces[lface].height * 0.15));
		itEye = It(Rect(faces[lface].x + faces[lface].width * 0.22,faces[lface].y + faces[lface].height * 0.28,faces[lface].width * 0.6,faces[lface].height * 0.15));



     
        int regionSize = 6;
 
        // Find out how many times the region size fits into the column and row size
        int rowNum = imageEye.rows / regionSize;
        int colNum = imageEye.cols / regionSize;
 
        // Check to see if there is a remainder and round up if there is
        if ((imageEye.rows % regionSize) != 0) rowNum++;
        if ((imageEye.cols  % regionSize) != 0) colNum++;
 
        cv:: Mat IxPadded;
        cv:: Mat IyPadded;
        cv:: Mat ItPadded;
 
        // Declare the new matrices to be bigger to accomodate for padding
        IxPadded = cv::Mat((rowNum*regionSize), (colNum*regionSize), CV_64FC1);
        IyPadded = cv::Mat((rowNum*regionSize), (colNum*regionSize), CV_64FC1);
        ItPadded = cv::Mat((rowNum*regionSize), (colNum*regionSize), CV_64FC1);
 
        // Original image plus the padding on the right and bottom
        // For the bottom and right part you want to know how many more extra pixels you need to add on to pad, hence why not 0
 /*       copyMakeBorder(Ix, IxPadded, 0, (rowNum*regionSize-Ix.rows), 0, (colNum*regionSize-Ix.cols), IPL_BORDER_CONSTANT, 0);
        copyMakeBorder(Iy, IyPadded, 0, (rowNum*regionSize-Iy.rows), 0, (colNum*regionSize-Iy.cols), IPL_BORDER_CONSTANT, 0);
        copyMakeBorder(It, ItPadded, 0, (rowNum*regionSize-It.rows), 0, (colNum*regionSize-It.cols), IPL_BORDER_CONSTANT, 0); */
 
        // Copy over the contents from Ix into the padded version
        for (int i = 0; i < ixEye.rows; i++)
        {
                for (int j = 0; j < ixEye.cols; j++)
                {
                        IxPadded.at<double>(i, j) = ixEye.at<double>(i, j);
                }
        }
 
        // Copy over the contents from Iy into the padded version
        for (int i = 0; i < iyEye.rows; i++)
        {
                for (int j = 0; j < iyEye.cols; j++)
                {
                        IyPadded.at<double>(i, j) = iyEye.at<double>(i, j);
                }
        }
 
        // Copy over the contents from It into the padded version
        for (int i = 0; i < itEye.rows; i++)
        {
                for (int j = 0; j < itEye.cols; j++)
                {
                        ItPadded.at<double>(i, j) = itEye.at<double>(i, j);
                }
        }
 
        // Find out how many regions there are in the image
        int regionSizeNum = rowNum * colNum;
 
        std::vector<cv::Point> points;
        cv::Point singlePoint;
 
        // Find out all the coordinates for each of the regions in the padded image and store in a vector
        // Use the padded image so that the boxes fit
        for (int i = 0; i < regionSizeNum; i++)
        {
                // Want to go to the largest number out of width and height of the video
                if (IxPadded.cols > IxPadded.rows)
                {
                        singlePoint.x = (regionSize * i) % IxPadded.cols;
                        singlePoint.y = ((regionSize * i) / IxPadded.cols) * regionSize;
                        points.push_back(singlePoint);
                }
                else
                {
                        singlePoint.x = (regionSize * i) % IxPadded.rows;
                        singlePoint.y = ((regionSize * i) / IxPadded.rows) * regionSize;
                        points.push_back(singlePoint);
 
                }
        }
 
		int numleft = 0;
		int numright = 0;
		int numup = 0;
		int numdown = 0;
        // You want to do the algorithm on each of the regions
        for (int k = 0; k < regionSizeNum; k++)
        {
                double Ix2 = 0.0;
                double Iy2 = 0.0;
                double IxIy = 0.0;
                double IxIt = 0.0;
                double IyIt = 0.0;
 
                // Start from y and then x as data is accessed as y, x
                for (int i = points[k].y; i < regionSize + points[k].y; i++)
                {
                        for (int j = points[k].x; j < regionSize + points[k].x; j++)
                        {
                                Ix2 += (pow(IxPadded.at<double>(i, j), 2));
                                Iy2 += (pow(IyPadded.at<double>(i, j), 2));
                                IxIy += IxPadded.at<double>(i, j) * IyPadded.at<double>(i, j);
                                IxIt += IxPadded.at<double>(i, j) * ItPadded.at<double>(i, j);
                                IyIt += IyPadded.at<double>(i, j) * ItPadded.at<double>(i, j);
                        }
                }
                IxIt = IxIt * -1.0;
                IyIt = IyIt * -1.0;
 
                A.at<double>(0, 0) = Ix2;
                A.at<double>(0, 1) = IxIy;
                A.at<double>(1, 0) = IxIy;
                A.at<double>(1, 1) = Iy2;
 
                invA = A.inv();
 
                b.at<double>(0, 0) = IxIt;
                b.at<double>(0, 1) = IyIt;
 
                v = invA * b;
 
                int midPointX = points[k].x + regionSize / 2;
                int midPointY = points[k].y + regionSize / 2;
				

				if (v.at<double>(0,0) > 4) {
					numleft++;
				}
				else if ((v.at<double>(0,0) < -4)) {
					numright++;
				}

				if (v.at<double>(0,1) > 4) {
					numup++;
				}
				else if ((v.at<double>(0,1) < -4)) {
					numdown++;
				}

                cv::line(imageEye, cv::Point(midPointX, midPointY), cv::Point(midPointX + v.at<double>(0,0), midPointY + v.at<double>(0,1)), CV_RGB(0, 0, 255));
		}
		
	imageEye2 = image(Rect(faces[lface].x + faces[lface].width * 0.22,faces[lface].y + faces[lface].height * 0.45,faces[lface].width * 0.6,faces[lface].height * 0.4));
		ixEye2 = Ix(Rect(faces[lface].x + faces[lface].width * 0.22,faces[lface].y + faces[lface].height * 0.45,faces[lface].width * 0.6,faces[lface].height * 0.4));
		iyEye2 = Iy(Rect(faces[lface].x + faces[lface].width * 0.22,faces[lface].y + faces[lface].height * 0.45,faces[lface].width * 0.6,faces[lface].height * 0.4));
		itEye2 = It(Rect(faces[lface].x + faces[lface].width * 0.22,faces[lface].y + faces[lface].height * 0.45,faces[lface].width * 0.6,faces[lface].height * 0.4));

        int regionSize2 = 6;
 
        // Find out how many times the region size fits into the column and row size
        int rowNum2 = imageEye2.rows / regionSize2;
        int colNum2 = imageEye2.cols / regionSize2;
 
        // Check to see if there is a remainder and round up if there is
        if ((imageEye2.rows % regionSize2) != 0) rowNum2++;
        if ((imageEye2.cols  % regionSize2) != 0) colNum2++;
 
        cv:: Mat IxPadded2;
        cv:: Mat IyPadded2;
        cv:: Mat ItPadded2;
 
        // Declare the new matrices to be bigger to accomodate for padding
        IxPadded2 = cv::Mat((rowNum2*regionSize2), (colNum2*regionSize2), CV_64FC1);
        IyPadded2 = cv::Mat((rowNum2*regionSize2), (colNum2*regionSize2), CV_64FC1);
        ItPadded2 = cv::Mat((rowNum2*regionSize2), (colNum2*regionSize2), CV_64FC1);
 
        // Original image plus the padding on the right and bottom
        // For the bottom and right part you want to know how many more extra pixels you need to add on to pad, hence why not 0
 /*       copyMakeBorder(Ix, IxPadded, 0, (rowNum*regionSize-Ix.rows), 0, (colNum*regionSize-Ix.cols), IPL_BORDER_CONSTANT, 0);
        copyMakeBorder(Iy, IyPadded, 0, (rowNum*regionSize-Iy.rows), 0, (colNum*regionSize-Iy.cols), IPL_BORDER_CONSTANT, 0);
        copyMakeBorder(It, ItPadded, 0, (rowNum*regionSize-It.rows), 0, (colNum*regionSize-It.cols), IPL_BORDER_CONSTANT, 0); */
 
        // Copy over the contents from Ix into the padded version
        for (int i = 0; i < ixEye2.rows; i++)
        {
                for (int j = 0; j < ixEye2.cols; j++)
                {
                        IxPadded2.at<double>(i, j) = ixEye2.at<double>(i, j);
                }
        }
 
        // Copy over the contents from Iy into the padded version
        for (int i = 0; i < iyEye2.rows; i++)
        {
                for (int j = 0; j < iyEye2.cols; j++)
                {
                        IyPadded2.at<double>(i, j) = iyEye2.at<double>(i, j);
                }
        }
 
        // Copy over the contents from It into the padded version
        for (int i = 0; i < itEye2.rows; i++)
        {
                for (int j = 0; j < itEye2.cols; j++)
                {
                        ItPadded2.at<double>(i, j) = itEye2.at<double>(i, j);
                }
        }
 
        // Find out how many regions there are in the image
        int regionSizeNum2 = rowNum2 * colNum2;
 
        std::vector<cv::Point> points2;
        cv::Point singlePoint2;
 
        // Find out all the coordinates for each of the regions in the padded image and store in a vector
        // Use the padded image so that the boxes fit
        for (int i = 0; i < regionSizeNum2; i++)
        {
                // Want to go to the largest number out of width and height of the video
                if (IxPadded2.cols > IxPadded2.rows)
                {
                        singlePoint2.x = (regionSize2 * i) % IxPadded2.cols;
                        singlePoint2.y = ((regionSize2 * i) / IxPadded2.cols) * regionSize2;
                        points2.push_back(singlePoint2);
                }
                else
                {
                        singlePoint2.x = (regionSize2 * i) % IxPadded2.rows;
                        singlePoint2.y = ((regionSize2 * i) / IxPadded2.rows) * regionSize2;
                        points2.push_back(singlePoint2);
 
                }
        }
 
		int numleft2 = 0;
		int numright2 = 0;
		int numup2 = 0;
		int numdown2 = 0;
        // You want to do the algorithm on each of the regions
        for (int k = 0; k < regionSizeNum2; k++)
        {
                double Ix22 = 0.0;
                double Iy22 = 0.0;
                double IxIy2 = 0.0;
                double IxIt2 = 0.0;
                double IyIt2 = 0.0;
 
                // Start from y and then x as data is accessed as y, x
                for (int i = points2[k].y; i < regionSize2 + points2[k].y; i++)
                {
                        for (int j = points2[k].x; j < regionSize2 + points2[k].x; j++)
                        {
                                Ix22 += (pow(IxPadded2.at<double>(i, j), 2));
                                Iy22 += (pow(IyPadded2.at<double>(i, j), 2));
                                IxIy2 += IxPadded2.at<double>(i, j) * IyPadded2.at<double>(i, j);
                                IxIt2 += IxPadded2.at<double>(i, j) * ItPadded2.at<double>(i, j);
                                IyIt2 += IyPadded2.at<double>(i, j) * ItPadded2.at<double>(i, j);
                        }
                }
                IxIt2 = IxIt2 * -1.0;
                IyIt2 = IyIt2 * -1.0;
 
                A2.at<double>(0, 0) = Ix22;
                A2.at<double>(0, 1) = IxIy2;
                A2.at<double>(1, 0) = IxIy2;
                A2.at<double>(1, 1) = Iy22;
 
                invA2 = A2.inv();
 
                b2.at<double>(0, 0) = IxIt2;
                b2.at<double>(0, 1) = IyIt2;
 
                v2 = invA2 * b2;
 
                int midPointX2 = points2[k].x + regionSize2 / 2;
                int midPointY2 = points2[k].y + regionSize2 / 2;
				

				if (v2.at<double>(0,0) > 4) {
					numleft2++;
				}
				else if ((v2.at<double>(0,0) < -4)) {
					numright2++;
				}

				if (v2.at<double>(0,1) > 4) {
					numup2++;
				}
				else if ((v2.at<double>(0,1) < -4)) {
					numdown2++;
				}

                cv::line(imageEye2, cv::Point(midPointX2, midPointY2), cv::Point(midPointX2 + v2.at<double>(0,0), midPointY2 + v2.at<double>(0,1)), CV_RGB(0, 0, 255));
		}


		int eyetotal = numup+numdown+numleft+numright;
		int othertotal = numup2+numdown2+numleft2+numright2;
		
		if (othertotal < 2) {
		if (eyetotal > 1) {
			if ((numup > 2) || (numleft > 2) || (numright > 2) || (numdown > 2)) {
		//printf("up - %d, down - %d, left - %d, right - %d\n", numup,numdown,numleft,numright);
		//	Msg("BLINK!\n");
			blink = true;
			engine->ClientCmd( "BlinkPanelOn\n" );
			if (pLocalPlayer) {
			pLocalPlayer->pl.blinkflag = true;
			pLocalPlayer->BlinkNotice(pLocalPlayer);
			}
			}
			else {
				blink = false;
		engine->ClientCmd( "BlinkPanelOff\n" );
          if (pLocalPlayer) {
			pLocalPlayer->pl.blinkflag = false;
			}
		  }
		}
		else {
			blink = false;
		engine->ClientCmd( "BlinkPanelOff\n" );
        if (pLocalPlayer) {
			pLocalPlayer->pl.blinkflag = false;
			}
		}
		}
		else {
			blink = false;
		engine->ClientCmd( "BlinkPanelOff\n" );
	    if (pLocalPlayer) {
			pLocalPlayer->pl.blinkflag = false;
			}
		}
	/*	else {
			LKframe.create(image.size(), image.type());
	 for (int i = 0; i < image.rows; i++)
                        {
                                for (int j = 0; j < image.cols; j++)
                                {
                                        LKframe.at<uchar>(i, j) = image.at<uchar>(i, j);
                                }
                        }

		} */

		
		}
		else {
			engine->ClientCmd( "BlinkPanelOn\n" );
			seeface = false;
			//pLocalPlayer->pl.blinkflag = false;
		}


}
 
void OpenCVController::scale (cv::Mat image)
{
        double min = 255.0;
        double max = 0.0;
        double range = 0.0;
 
        for (int i = 0; i < image.rows; i++)
        {
                for (int j = 0; j < image.cols; j++)
                {
                        if (image.at<double>(i, j) < min) min = image.at<double>(i, j);
                        if (image.at<double>(i, j) > max) max = image.at<double>(i, j);
                }
        }
 
        range = max - min;
 
        for (int i = 0; i < image.rows; i++)
        {
                for (int j = 0; j < image.cols; j++)
                {
                        image.at<double>(i,j) = (image.at<double>(i,j) - min) / range;
                }
        }
}







 
