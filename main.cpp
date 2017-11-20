//whoop whoop
//Adding Multiple colors
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <string>
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

//Defines
#define PORT "/dev/ttyACM0"

//SERIAL PORT SETTINGS
// Base serial settings
serial_port_base::baud_rate BAUD(9600);
serial_port_base::flow_control FLOW( serial_port_base::flow_control::none );
serial_port_base::parity PARITY( serial_port_base::parity::none );
serial_port_base::stop_bits STOP( serial_port_base::stop_bits::one );

//Keeping a log of previous results
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

//DATA LOGGING
std::string logged_data ;
bool logdata = false;

//CROSS THREAD COM'S
volatile int currentPos = 0;
int currentSetpoint = 0;
int currentP = 0;
int currentI = 0;
int currentD = 0;
int currentCompVal = 10;
bool useSerialCom = false;

//Serial Communication Thread
void serialcom()
{
    if(useSerialCom){
        io_service io;
        serial_port port( io, PORT );
        // Setup port - using port settings above
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

            read(port,buffer(&c,1)); // Read current input buffer in to character c

            //cout << c << endl;//DEBUGGING - used to display current serial buffer

            if(c == 'A'){ //When the arduino asks for data
		// YPOS
                char cx[3];
                string stx = "";
                stringstream cvstr;
                cvstr << currentPos;
                stx = cvstr.str().c_str();
                strcpy(cx,stx.c_str());

		// SetPoint Value
                char cSP[3];
                string stxSP = "";
                stringstream cvstrSP;
                cvstrSP << currentSetpoint;
                stxSP = cvstrSP.str().c_str();
                strcpy(cSP,stxSP.c_str());

                // P Value
                char cPVal[3];
                string stPVal = "";
                stringstream cvstrSPVal;
                cvstrSPVal << currentP;
                stPVal = cvstrSPVal.str().c_str();
                strcpy(cPVal,stPVal.c_str());

                // I Value
                char cIVal[3];
                string stIVal = "";
                stringstream cvstrSIVal;
                cvstrSIVal << currentI;
                stIVal = cvstrSIVal.str().c_str();
                strcpy(cIVal,stIVal.c_str());

                // D Value
		char cDVal[3];
                string stDVal = "";
                stringstream cvstrSDVal;
                cvstrSDVal << currentD;
                stDVal = cvstrSDVal.str().c_str();
                strcpy(cDVal,stDVal.c_str());

		// Comp Value
		char cCompVal[3];
                string stCompVal = "";
                stringstream cvstrSCompVal;
                cvstrSCompVal << currentCompVal;
                stCompVal = cvstrSCompVal.str().c_str();
                strcpy(cCompVal,stCompVal.c_str());

                // Y POSITION
                for(int i = 0; i < strlen(cx);i++){
                    input = cx[i];
                    unsigned char command[1] ={0};
                    command[0] = static_cast<unsigned char>(input);
                    write(port,buffer(command,1));
                }

		// Comma in communciation to indicate new data
                unsigned char command[1] ={0};
                input = ',';
                command[0] = static_cast<unsigned char>(input);
                write(port,buffer(command,1));

                // SETPOINT
                for(int i = 0; i < strlen(cSP);i++){
                    input = cSP[i];
                    unsigned char command[1] ={0};
                    command[0] = static_cast<unsigned char>(input);
                    write(port,buffer(command,1));
                }

		// Comma in communciation to indicate new data
	        input = ',';
                command[0] = static_cast<unsigned char>(input);
                write(port,buffer(command,1));

                // P VALUE
                for(int i = 0; i < strlen(cPVal);i++){
                    input = cPVal[i];
                    unsigned char command[1] ={0};
                    command[0] = static_cast<unsigned char>(input);
                    write(port,buffer(command,1));
                }

                // Comma in communciation to indicate new data
                input = ',';
                command[0] = static_cast<unsigned char>(input);
                write(port,buffer(command,1));

                // I VALUE
                for(int i = 0; i < strlen(cIVal);i++){
                    input = cIVal[i];
                    unsigned char command[1] ={0};
                    command[0] = static_cast<unsigned char>(input);
                    write(port,buffer(command,1));
                }

                // Comma in communciation to indicate new data
                input = ',';
                command[0] = static_cast<unsigned char>(input);
                write(port,buffer(command,1));

                // D VALUE
                for(int i = 0; i < strlen(cDVal);i++){
                    input = cDVal[i];
                    unsigned char command[1] ={0};
                    command[0] = static_cast<unsigned char>(input);
                    write(port,buffer(command,1));
                }

		// Comma in communciation to indicate new data
	        input = ',';
                command[0] = static_cast<unsigned char>(input);
                write(port,buffer(command,1));

                // COMP VALUE
                for(int i = 0; i < strlen(cCompVal);i++){
                    input = cCompVal[i];
                    unsigned char command[1] ={0};
                    command[0] = static_cast<unsigned char>(input);
                    write(port,buffer(command,1));
                }

                // END OF TRANSMITION
                input = '!';
                command[0] = static_cast<unsigned char>(input);
                write(port,buffer(command,1));
            }
            else{

            }
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
    int HSV_Values [3][6];
    /*
    int iLowH = 0;
    int iHighH = 179;

    int iLowS = 0;
    int iHighS = 255;

    int iLowV = 0;
    int iHighV = 255;
	*/

    //Ask if user wants to use last HSV Values
    string useLastVals;
    bool openFile;
    std::cout << "Do you want to use the last HSV values ? (y / n): " ;
    std::cin >> useLastVals;
    if(useLastVals == "y"){openFile = true;}
    else{openFile = false;}

    if(openFile==true)
    {
        std::string input[3];
        string line;
        ifstream myfile ("hsv.txt");
        if (myfile.is_open())
        {
			int i = 0;
            while ( getline (myfile,line) )
            {
                cout << line << '\n';
                input[i] = line;
				i++;
            }
            myfile.close();

			for(int j = 0; j<i; j++){
				vector <string> tokens;

				std::istringstream ss(input[j]);
				std::string token;

				while(std::getline(ss, token, ','))
				{
					tokens.push_back(token);
				}
				vector<int> input_int = vecstr_to_vecint(tokens);
				HSV_Values [j][0] = input_int[0];
				HSV_Values [j][1] = input_int[1];

				HSV_Values [j][2] = input_int[2];
				HSV_Values [j][3] = input_int[3];

				HSV_Values [j][4] = input_int[4];
				HSV_Values [j][5] = input_int[5];
			}
        }
        else cout << "Unable to open file, using defult";
    }
	
    namedWindow("SetPoint",CV_WINDOW_AUTOSIZE);
    createTrackbar("Setpoint", "SetPoint", &currentSetpoint, 200);
    createTrackbar("currentP", "SetPoint", &currentP, 200);
    createTrackbar("currentI", "SetPoint", &currentI, 200);
    createTrackbar("currentD", "SetPoint", &currentD, 200);
    createTrackbar("currentCompVal","SetPoint",&currentCompVal, 200);
	
	
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
            //calculate the position of the marker
            int posX = dM10 / dArea;
            int posY = dM01 / dArea;
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
            imgLines = Scalar(5, 10, 15);
            circle(imgLines, Point(posX,posY),10, Scalar(255,255,255),CV_FILLED, 8,0);
            if(logdata){
                std::string currentdata = to_string(currentPos);
                currentdata.append(" ");
                currentdata.append(to_string(currentSetpoint));
                currentdata.append("\n");
                logged_data.append(currentdata);
            }
        }
        imshow("Thresholded Image", imgThresholded); //show the thresholded image
		
		
        imshow("Original", imgOriginal); //show the original image

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break;
        }
        if(waitKey(30) == 108){
            cout << "Data loging has started" << endl;
            logdata = true;
        }
        if (waitKey(30) == 115){
            cout << "Data logging has been stopped and data will be saved to file" << endl;
            ofstream myfile;
            myfile.open ("log.txt",ios::out);
            myfile << logged_data;
            myfile.close();
        }

    }

}


int main()
{
    //Ask if user wants to use serial com
    string useLastVals;
    std::cout << "Do you want to use serial communication ? (y / n): " ;
    std::cin >> useLastVals;
    if(useLastVals == "y"){useSerialCom = true;}
    else{useSerialCom = false;}
    std::thread first (serialcom);
    std::thread second (visualcontrol);
    std::cout << "Threads have now executed concurrently...\n";
    // synchronize threads:
    first.join();
    second.join();
    std::cout << "Completed.\n";
    return 0;
}
