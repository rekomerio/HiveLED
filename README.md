# HiveLED

The idea of this project is to have multiple LED clients in network that is managed by one host controller.
Host controller will send all LED data to each controller when new frame is wanted.

Overall this will make synchronization of multiple strips much more easier and as all effects are calculated in the host, it will take much less effort to add new effects when instead of updating every controller, you only need to update the host controller.

## Tools
This project uses PlatformIO for building and uploading the code. I recommend getting VS Code and PlatformIO plugin if you want to use the code.

## React UI into SPIFFS
 - Build React app with npm run build
 - Copy the build folder contents into hive-host/data 
 - Run command pio run -t uploadfs
 
 ## Screenshots
 
![](https://raw.githubusercontent.com/rekomerio/HiveLED/main/hive-ui/screenshots/2.png)
![](https://raw.githubusercontent.com/rekomerio/HiveLED/main/hive-ui/screenshots/1.png)
![](https://raw.githubusercontent.com/rekomerio/HiveLED/main/hive-ui/screenshots/3.png)
