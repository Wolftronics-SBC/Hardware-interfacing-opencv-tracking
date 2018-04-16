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
serial_port_base::baud_rate BAUD(38400);
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
volatile int currentPosY[3] ={0,0,0};
volatile int currentPosX[3] ={0,0,0};
int currentSetpoint = 54;
int currentP = 0;
int currentI = 0;
int currentD = 0;
int currentCompVal = 10;
bool useSerialCom = false;

void itoc(int input,char* output){
    string stx = "";
    stringstream cvstr;
    cvstr << input;
    stx = cvstr.str().c_str();
    strcpy(output,stx.c_str());
}

void positionControl(){
    int x[100];
    int i = 0;
    int numberoflines = 0;
    string line;
    ifstream myfile ("posPlan.txt");
    if(myfile.is_open()){

        while (getline (myfile,line)){
            x[numberoflines] = atoi(line.c_str());
            numberoflines++;
        }
        myfile.close();
    }
    else{
        cout << "Unable to access the posPlan text file" << endl;
    }
    cout << "Pos Plan: ";
    for (int y = 0; y < numberoflines;y++){
    cout << x[y] << ',';
    }
    cout << endl;


    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        currentSetpoint = x[i];
        if (i<numberoflines-1) i++;
        else i = 0;
    }
}


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
            if(c == 'A'){ //When the arduino asks for data
		// YPOS
                std::vector<char> transmission;
                std::vector<char> trans1;
            // fix the number of elements in the char array
                
                char cy[3];
                itoc(currentPosY[0],cy);
                if (cy[0] != NULL) transmission.push_back(cy[0]);
                if (cy[1] != NULL) transmission.push_back(cy[1]);
                if (cy[2] != NULL) transmission.push_back(cy[2]);
                transmission.push_back(',');


                // SetPoint Value
                char cSP[3];
                itoc(currentSetpoint,cSP);
                transmission.push_back(cSP[0]);
                transmission.push_back(cSP[1]);
                transmission.push_back(cSP[2]);
                transmission.push_back(',');

                // P Value
                char cPVal[3];
                itoc(currentP,cPVal);
                transmission.push_back(cPVal[0]);
                transmission.push_back(cPVal[1]);
                transmission.push_back(cPVal[2]);
                transmission.push_back(',');                

                // I Value
                char cIVal[3];
                itoc(currentI,cIVal);
                transmission.push_back(cIVal[0]);
                transmission.push_back(cIVal[1]);
                transmission.push_back(cIVal[2]);
                transmission.push_back(',');                  

                // D Value
                char cDVal[3];
                itoc(currentD,cDVal);
                transmission.push_back(cDVal[0]);
                transmission.push_back(cDVal[1]);
                transmission.push_back(cDVal[2]);
                transmission.push_back(',');  
                
                
                transmission.push_back('!'); 
                


                

                


                /*
                for (int u = 0; u < transmission.size();u++){
                    cout << transmission[u] << endl;
                }
                */
                // SENDING THE DATA
                // Y POSITION
                for(int i = 0; i < transmission.size();i++){
                    input = transmission[i];
                    unsigned char command[1] ={0};
                    command[0] = static_cast<unsigned char>(input);
                    write(port,buffer(command,1));
                }


           
                
                
                //GRAB DATA
            }
            
            else{

            }
        } cout << "Exiting Serial Comms while loop" << endl;
    } cout << "Exiting Serial Comms" << endl;
    
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
    int Value_Count = 0;
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
        ifstream myfile ("hsvharry.txt");
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
            Value_Count = i;
            for(int j = 0; j<Value_Count; j++){
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
    //createTrackbar("Setpoint", "SetPoint", &currentSetpoint, 200);
    createTrackbar("currentP", "SetPoint", &currentP, 200);
    createTrackbar("currentI", "SetPoint", &currentI, 200);
    createTrackbar("currentD", "SetPoint", &currentD, 200);
    createTrackbar("currentCompVal","SetPoint",&currentCompVal, 200);

    
    //Creating looped HSV Adjustment
    for(int i = 0; i < Value_Count; i++){
        std::ostringstream oss;
        oss << "Control " << i ;
        std::string windowName = oss.str();
        namedWindow(windowName, CV_WINDOW_AUTOSIZE); //create a window called "Control"
        //Create trackbars in "Control" window
        createTrackbar("LowH", windowName, &HSV_Values[i][0], 179); //Hue (0 - 179)
        createTrackbar("HighH", windowName, &HSV_Values[i][1], 179);
        createTrackbar("LowS", windowName, &HSV_Values[i][2], 255); //Saturation (0 - 255)
        createTrackbar("HighS", windowName, &HSV_Values[i][3], 255);

        createTrackbar("LowV", windowName, &HSV_Values[i][4], 255);//Value (0 - 255)
        createTrackbar("HighV", windowName, &HSV_Values[i][5], 255);
    }
    int dot_count = Value_Count ;

    // Used in the event that the last position is not obtained
    int iLastX[dot_count];
    for(int i = 0; i < Value_Count; i++){
        iLastX[i] = -1;
    }
    int iLastY[dot_count];
    for(int i = 0; i < Value_Count; i++){
        iLastY[i] = -1;
    }
    //Capture a temporary image from the camera
    Mat imgTmp;
    cap.read(imgTmp);

    //Create a black image with the size as the camera output
    Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );; // used for the dots

    while (true)
    {
        Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

        Mat imgHSV[dot_count];
        Mat imgThresholded[dot_count];
        
        for(int x = 0; x < dot_count;x++){
            cvtColor(imgOriginal, imgHSV[x], COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
            inRange(imgHSV[x], Scalar(HSV_Values[x][0], HSV_Values[x][2], HSV_Values[x][4]), Scalar(HSV_Values[x][1], HSV_Values[x][3], HSV_Values[x][5]), imgThresholded[x]); //Threshold the image
            //morphological opening (removes small objects from the foreground)
            erode(imgThresholded[x], imgThresholded[x], getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
            dilate( imgThresholded[x], imgThresholded[x], getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

            //morphological closing (removes small holes from the foreground)
            dilate( imgThresholded[x], imgThresholded[x], getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
            erode(imgThresholded[x], imgThresholded[x], getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        
        
        
            // Finding the positio of each dot
            //Calculate the moments of the thresholded image
            
            Moments oMoments = moments(imgThresholded[x]);
       

            double dM01 = oMoments.m01;
            double dM10 = oMoments.m10;
            double dArea = oMoments.m00;
            // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero
            if (dArea > 10000)
            {
                //calculate the position of the marker
                int posX = dM10 / dArea;
                int posY = dM01 / dArea;
                float output_startY = 1;
                float output_endY = 100;
                float input_startY = 390;
                float input_endY = 120;
                currentPosY[x] = (int)(output_startY + ((output_endY - output_startY) / (input_endY - input_startY)) * (posY - input_startY));
                iLastX[x] = posX;
                iLastY[x] = posY;
                imgLines = Scalar(5, 10, 15);
                if(x == 0){
                circle(imgLines, Point(posX,posY),10, Scalar(0,255,255),CV_FILLED, 8,0);
                }
                else if (x == 1){
                                    circle(imgLines, Point(posX,posY),10, Scalar(255,0,255),CV_FILLED, 8,0);
                }
                else{
                                    circle(imgLines, Point(posX,posY),10, Scalar(255,255,0),CV_FILLED, 8,0);

                }
                if(logdata){
                    std::string currentdata = to_string(currentPosY[0]);
                    currentdata.append(" ");
                    currentdata.append(to_string(currentSetpoint));
                    currentdata.append("\n");
                    logged_data.append(currentdata);
                }
            }
            
            std::ostringstream oss;
            oss << "Threshold Image " << x ;
            std::string windowName = oss.str();
            imshow(windowName, imgThresholded[x]); //show the thresholded image
            imgOriginal = imgOriginal + imgLines;
            cout<<"Current Y: " << currentPosY[x] << endl;
            cout<<"Current Setpoint: " << currentSetpoint << endl;
        }	
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
            logged_data = "";
            logdata = false;
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
    std::thread third (positionControl);
    std::cout << "Threads have now executed concurrently...\n";
    // synchronize threads:
    first.join();
    second.join();
    third.join();
    std::cout << "Completed.\n";
    return 0;
}
