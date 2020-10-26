# HiveLED

The idea of this project is to have multiple LED clients in network that is managed by one host controller.
Host controller will send all LED data to each controller when new frame is wanted.

Overall this will make synchronization of multiple strips much more easier and as all effects are calculated in the host, it will take much less effort to add new effects when instead of updating every controller, you only need to update the host controller.

## Tools
This project uses PlatformIO for building and uploading the code. I recommend getting VS Code and PlatformIO plugin if you want to use the code.

## TODO
- [ ] Add master client to UI to control all clients
- [ ] Add palettes and a way to request all palette names
- [ ] Add customizable timed events for all clients
- [ ] Add more effects
- [ ] Create method to discover host ip in local network
- [ ] Add physical button to host to toggle all client LED's on and off
- [ ] Add static IP to host and make client choose which access point to use based on signal strength
