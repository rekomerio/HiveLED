# HiveLED

The idea of this project is to have multiple LED clients in network that is managed by one host controller.
Host controller will send all LED data to each controller when new frame is wanted.

Overall this will make synchronization of multiple strips much more easier and as all effects are calculated in the host, it will be much less effort to add new effects when instead of updating every controller, you only need to update the host controller.
