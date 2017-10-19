// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
 
 #include <boost/asio.hpp> 
using namespace::boost::asio;  
using namespace std;

#define PORT "/dev/ttyACM1"

// Base serial settings
serial_port_base::baud_rate BAUD(9600);
serial_port_base::flow_control FLOW( serial_port_base::flow_control::none );
serial_port_base::parity PARITY( serial_port_base::parity::none );
// serial_port_base::stop_bits STOP( serial_port_base::stop_bits::one );
serial_port_base::stop_bits STOP( serial_port_base::stop_bits::one );

volatile int ypos = 0;

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
      /*
    // Send -------------------------------------------------------------------
    // What to send
    cin >> input;

    // Output buffer
    unsigned char command[1] = {0};

    // Convert and send
    command[0] = static_cast<unsigned char>( input );
    write(port, buffer(command, 1));
*/
    // Receive response -------------------------------------------------------
    
    
      input = 'B';
    unsigned char command[1] ={0};
    command[0] = static_cast<unsigned char>(input);
    
    read(port,buffer(&c,1));
    
    
    if(c == 'A'){ //When the arduino asks for y pos
        char cx[3];
        string stx = "";
        stringstream cvstr;
        cvstr << ypos;
        stx = cvstr.str().c_str();
        strcpy(cx,stx.c_str());
        //cout << strlen(cx) << endl;
        
        for(int i; i < strlen(cx);i++){
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

