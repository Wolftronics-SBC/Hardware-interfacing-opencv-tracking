# Hardware-interfacing-opencv-tracking

find.sh is a shell script I created to display all currently connected devices to the image tracking computer.

### Dependencies 

You will need to have Boost installed on your linux system for the asio lib to be linked.

```
sudo apt-get install libboost-all-dev
```

Make sure you g++ with correct links to boost dir. 

```
g++ main.cpp -isystem /usr/include/boost -L/usr/include/ -lboost_system -std=gnu++11 -pthread -o test
```


### How to run ?

``` 
./run.sh
```



#### Potential run-time errors
```
terminate called after throwing an instance of 'boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::system::system_error> >'
  what():  open: No such file or directory
```

This is caused when the device the program is trying to connect to is either not connected or the wrong port has been set with in the main.cpp code.

Run this command:
```
./find.sh
```

and you should find the arduino, you may need to set the correct write permissions, to do so write.

```
sudo chmod a+rw /dev/ttyACM0 
```

replacing ttyACM0 with the device location previously found using ./find.sh. Then you need to change the define line within main.cpp to reflect the correct device file. 

### Logging Data
A logging feature was added to allow for the data to be graphed and stored for later comparasion of control system values. To start logging the data, click on one of the opencv windows and press the "l" key and a message in the terminal should appear saying that the logging has started. To end the logging press the "s" key to save the logged data to the "log.txt" file. The data is collected at every new position value which is obtained, along with the setpoint. The data is then plotted using MATLAB function "visualise.m". 