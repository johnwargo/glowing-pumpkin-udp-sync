# Glowing Pumpkin Sync UDP

This is a version of the [Glowing Pumpkin Xiao 5x5 BFF](https://github.com/johnwargo/glowing-pumpkin-xiao-bff) project that allows multiple devices to synchronize LED Matrix colors so all devices display the same color. I built this project because I wanted to place one of the *Glowing Pumpkin Xiao 5x5 BFF* devices in each of the front dormers in my house and synchrinoze the display across all of them. 

The way it works is you deploy one of the devices with the [sender](https://github.com/johnwargo/glowing-pumpkin-udp-sync/tree/main/udp-sender-arduino) sketch and all of the remaining devices with the [receiver](https://github.com/johnwargo/glowing-pumpkin-udp-sync/tree/main/udp-receiver-arduino) sketch. As long as all of the devices are on the same Wi-Fi network segment, the sender sends an UDP broadcast message on the network notifying all of the other devices to switch to the same color. The sender sketch periodically a flicker broadcast and all devices flicker with white light like lightning or sparks. 

![](images/connection.png)

There are multiple folders in this repo; the following table describes the purpose of each:

| Folder                 | Description | 
| ---------------------- | ----------- |
| `udp-sender-arduino`   | Hosts the Arduino version of the Sender sketch. Configure and deploy this sketch on a single Glowing Pumpkin Xiao 5x5 BFF device. |
| `udp-receiver-arduino` | Hosts the **Receiver** sketch. Configure and deploy this sketch on all of the remaining Glowing Pumpkin Xiao 5x5 BFF devices used for this project. |
| `udp-sender-pi-pico-w` | I had a lot of trouble getting the `udp-sender-arduino` sketch working, so I decided try to get it working on another platform, in this case the Raspberry Pi Pico W, so I could exercise the Receiver running on multiple devices. As you can tell, I eventually got the Arduino Sender working, but left this version in the repo in case anyone wanted to play with it. I have some plans to enhance this one, but I have no idea when I'll get to it. | 


***

You can find information on many different topics on my [personal blog](http://www.johnwargo.com). Learn about all of my publications at [John Wargo Books](http://www.johnwargobooks.com).

If you find this code useful and feel like thanking me for providing it, please consider <a href="https://www.buymeacoffee.com/johnwargo" target="_blank">Buying Me a Coffee</a>, or making a purchase from [my Amazon Wish List](https://amzn.com/w/1WI6AAUKPT5P9).
