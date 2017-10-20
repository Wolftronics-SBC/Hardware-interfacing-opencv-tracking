# Hardware-interfacing-opencv-tracking

find.sh is a shell script I created to display all currently connected devices to the image tracking computer.


### Potential run-time errors
```

terminate called after throwing an instance of 'boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::system::system_error> >'
  what():  open: No such file or directory
```

This is caused when the device the program is trying to connect to is either not connected or the wrong port has been set with in the main.cpp code.

Run
```

./find.sh
```

and you should find the arduino, you may need to set the correct write permissions, to do so write.

```

sudo chmod a+rw /dev/ttyACM0 
```

replacing ttyACM0 with the device location previously found using ./find.sh. Then you need to change the define line within main.cpp to reflect the correct device file. 
