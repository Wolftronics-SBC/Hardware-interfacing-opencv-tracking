// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread

#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <unistd.h>
#include <stdio.h>
#include <fstream>
 #include <cstring>

 #include <iostream>
#include <fstream>
#include <unistd.h>
#include <sstream>
#include <numeric>
#include <string> //text manipulation
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


 
 #include <boost/asio.hpp> 
using namespace::boost::asio;  
using namespace std;
using namespace cv;

#define PORT "/dev/ttyACM0"

// Base serial settings
serial_port_base::baud_rate BAUD(9600);
serial_port_base::flow_control FLOW( serial_port_base::flow_control::none );
serial_port_base::parity PARITY( serial_port_base::parity::none );
// serial_port_base::stop_bits STOP( serial_port_base::stop_bits::one );
serial_port_base::stop_bits STOP( serial_port_base::stop_bits::one );


vector<int> vecstr_to_vecint(vector<string> vs)
{
    vector<int> ret;
    for(vector<string>::iterator it=vs.begin();it!=vs.end();++it)
    {
        istringstream iss(*it);
        int temp;
        iss >> temp;
        ret.push_back(temp);
    }  
    return ret;
}


//CROSS THREAD COM'S
volatile int currentPos = 0;

void serialcom() 
{
  io_service io;
  serial_port port( io, PORT );
  // Setup port - base settings
  port.set_option( BAUD );
  port.set_option( FLOW );
  port.set_option( PARITY );
  port.set_option( STOP );
  
  unsigned char input;
  char c;
  while(1){
    //----- EXAMPLE READ AND WRITE TO SERIAL ------

    /*
    cin >> input;

    // Output buffer
    unsigned char command[1] = {0};

    // Convert and send
    command[0] = static_cast<unsigned char>( input );
    write(port, buffer(command, 1));
    */
    
    read(port,buffer(&c,1));
    //cout << c << endl;
    
    if(c == 'A'){ //When the arduino asks for y pos
        
        
        char cx[3];
        string stx = "";
        stringstream cvstr;
        cvstr << currentPos;
        stx = cvstr.str().c_str();
        strcpy(cx,stx.c_str());
        
        

        //cout << strlen(cx) << endl;
        
        for(int i = 0; i < strlen(cx);i++){
            input = cx[i];
            unsigned char command[1] ={0};
            command[0] = static_cast<unsigned char>(input);
            write(port,buffer(command,1));
        }
        // END OF TRANSMITION
        input = '!';
        unsigned char command[1] ={0};
        command[0] = static_cast<unsigned char>(input);
        write(port,buffer(command,1));
    }
    else{
    //cout << c << endl;
    }
  }
}

void visualcontrol()
{

     VideoCapture cap(0); //capture the video from webcam

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
    
        
    }
	

	// setting up serial output	
	//create default HSV Values
	
	int iLowH = 170;
	int iHighH = 179;

	int iLowS = 150; 
	int iHighS = 255;

	int iLowV = 60;
	int iHighV = 255;
	
	
	//Ask if user wants to use last HSV Values
	string useLastVals;
	bool openFile;
	std::cout << "Do you want to use the last HSV values ? (y / n): " ;
	std::cin >> useLastVals;
	if(useLastVals == "y"){openFile = true;}
	else{openFile = false;}
	
	std::string input = "";
	string line;
	ifstream myfile ("hsv.txt");
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			cout << line << '\n';
			input = line;
		}
		myfile.close();
	}

	else cout << "Unable to open file"; 


	vector <string> tokens;
	
	std::istringstream ss(input);
	std::string token;

	while(std::getline(ss, token, ',')) {
		
		tokens.push_back(token);
	}
	vector<int> input_int = vecstr_to_vecint(tokens);
	iLowH = input_int[0];
	iHighH = input_int[1];

	iLowS = input_int[2]; 
	iHighS = input_int[3];

	iLowV = input_int[4];
	iHighV = input_int[5];	

	
	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
  //Create trackbars in "Control" window
 createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
 createTrackbar("HighH", "Control", &iHighH, 179);

  createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
 createTrackbar("HighS", "Control", &iHighS, 255);

  createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
 createTrackbar("HighV", "Control", &iHighV, 255);

  int iLastX = -1; 
 int iLastY = -1;

  //Capture a temporary image from the camera
 Mat imgTmp;
 cap.read(imgTmp); 

  //Create a black image with the size as the camera output
 Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;
 
    int timer = 0;

    while (true)
    {
        Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video



         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

    Mat imgHSV;

   cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
 
  Mat imgThresholded;

   inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
      
  //morphological opening (removes small objects from the foreground)
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

   //morphological closing (removes small holes from the foreground)
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

   //Calculate the moments of the thresholded image
  Moments oMoments = moments(imgThresholded);

   double dM01 = oMoments.m01;
  double dM10 = oMoments.m10;
  double dArea = oMoments.m00;

   // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
  if (dArea > 10000)
  {
   //calculate the position of the ball
   int posX = dM10 / dArea;
   int posY = dM01 / dArea;        
    //cout << posY << endl;
   float output_start = 1;
   float output_end = 100;
   float input_start = 390;
   float input_end = 120;
   currentPos = (int)(output_start + ((output_end - output_start) / (input_end - input_start)) * (posY - input_start));
    cout<< currentPos << endl;
			
   if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
   {
    //Draw a red line from the previous point to the current point
    //line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0,0,255), 2);
   }

    iLastX = posX;
   iLastY = posY;
  // circle(imgLines, Point(posX,posY),10, Scalar(255,255,255),CV_FILLED, 8,0);
  }

   imshow("Thresholded Image", imgThresholded); //show the thresholded image

   imgOriginal = imgOriginal + imgLines;
  imshow("Original", imgOriginal); //show the original image

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
			break; 
       }
    }
    
    
    
}

int main() 
{
  std::thread first (serialcom);     // spawn new thread that calls foo()
  std::thread second (visualcontrol);  // spawn new thread that calls bar(0)

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes

  std::cout << "foo and bar completed.\n";

  return 0;
}

