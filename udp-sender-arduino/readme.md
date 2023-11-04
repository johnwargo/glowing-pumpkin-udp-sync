# Glowing Pumpkin USP Sync Sender

This is the [Glowing Pumpkin Xiao 5x5 BFF](https://github.com/johnwargo/glowing-pumpkin-xiao-bff) project with a UDP broadcast sender added to you can control the LEDs on other devices on the network running the [Receiver](https://github.com/johnwargo/glowing-pumpkin-udp-sync/tree/main/udp-receiver-arduino) version of the sketch. 

To use it, configure the settings for the sketch as described in the following section then compile and deploy the sketch on a single *Glowing Pumpkin Xiao 5x5 BFF* devices connected to the same Wi-Fi network as the Receiver devices. Once you configure and deploy the sketch and power it on with receiver devices on the network as well, all of the *Glowing Pumpkin Xiao 5x5 BFF* devices on the same network should start synchronizing the color display on the connected LED matrix.

## Configuring Network Settings

To keep my network settings out of the repo and to keep from forcing you to modify the source code to configure your local network settings, I coded the sketch so it reads the Wi-Fi settings from a separate file called `constants.h`. Included in the repository is a filed called `constants.h.rename`; rename that file to `constants.h`  (basically by removing the `.rename`) from the end of the file name. Inside the file you'll find the following code:

```c
#define BROADCAST_PREFIX "pmpkn::"
// Set the address to the sender device IP address
// with 255 as the last dot number
// for example, if the device's IP address is 192.168.86.23
// set the UDP_ADDRESS to 192.168.86.255
#define UDP_ADDRESS ""
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

```


Enter your local Wi-Fi network name (SSID) between the quotes in the `WIDI_SSID` define and the network password in the quotes in the `WIFI_PASSWORD` quotes. When you're done, it will look something like this (but with your network credentials):

```c
#define WIFI_SSID "My Network"
#define WIFI_PASSWORD "mynetworkpassword"
```

**Note:** Wi-Fi SSID and passwords are case sensitive, so if your device doesn't connect correctly to the network, double check the credentials.

## The Code

Normally I'd spend a lot of time here documenting everything I can tell you about the code. I'm not going to do that here because it's a lot of code to go through. I put a lot of comments in the code to help you understand what I did and why. If you have questions, ask them in an [issue](https://github.com/johnwargo/glowing-pumpkin-udp-sync/issues) in this repository and I'll answer when I can.

***

You can find information on many different topics on my [personal blog](http://www.johnwargo.com). Learn about all of my publications at [John Wargo Books](http://www.johnwargobooks.com).

If you find this code useful and feel like thanking me for providing it, please consider <a href="https://www.buymeacoffee.com/johnwargo" target="_blank">Buying Me a Coffee</a>, or making a purchase from [my Amazon Wish List](https://amzn.com/w/1WI6AAUKPT5P9).
