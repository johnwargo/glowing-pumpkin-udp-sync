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

Here's a video of the [project in action](https://youtu.be/beevHJM8poQ).

## Parts

For this project, I used:

* [Seeed Studio XIAO ESP32S3](https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html)
* [Adafruit 5x5 NeoPixel Grid BFF Add-On for QT Py and Xiao](https://www.adafruit.com/product/5646)

The Adafruit 5x5 board comes pre-configured to connect to pin A3 on the Xiao, but supports other options as well. Refer to the Adafruit documentation for details.

## Assembly

Assembling the device is super easy, you can solder the device back to back (which is pretty cool) or you can use headers to connect them together. I used male headers to connect the two boards together as shown in the following figure.

![An image of the connected devices](images/image-01.png)

It took me a while to figure out how to orient the two devices when connecting them together. When you put them together back to back, with the USB connector for the Xiao board pointing up, the 5x5 board should be facing up as well, with the text at the bottom and the power pads (`+` and `-` pads) at the top as shown in the following figure.

![An image showing board orientation](images/image-02.png)

## Configuring Network Settings

To keep my network settings out of the repo and to keep from forcing you to modify the source code to configure your local network settings, I coded the sketch so it reads the Wi-Fi settings from a separate file called `constants.h`. Included in the repository is a filed called `constants.h.rename`; rename that file to `constants.h`  (basically by removing the `.rename`) from the end of the file name. Inside the file you'll find the following code:

```c
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

Normally I'd spend a lot of time here documenting everything I can tell you about the code. I'm not going to do that here because it's a lot of code to go through. I put a lot of comments in the code to help you understand what I did and why. If you have questions, ask them in an [issue](https://github.com/johnwargo/glowing-pumpkin-receiver-udp/issues) in this repository and I'll answer when I can.

I spent a fair amount of effort organizing the code into multiple files to make it easy to tell what's going on in the sketch. I also split the code onto separate processor cores. I did this partically to show off that I knew how to do that but also so I could dedicate the UDP listener to a dedicated processor core. While the sketch is messing around with the LEDs and such, the UDP listener gets all the processor cycles it needs to process incoming requests.

## The API

This sketch implements a listener/receiver, responding to commands from the mobile app. The API exposed through this sketch looks like this:

| Method       | Description |
| ------------ | ----------- |
| `/color:#`   | Lights all of the NeoPixels with a specific color. The command accepts a single parameter, the array index for the selected color. So, for example, to illuminate all of the LEDs Purple, the command is `color:3` as Purple is the 4th color in the array (with an index of 3 since C arrays start at 0). To illuminate the LEDs Blue, the command is `color:0`. |
| `/flash:#:#` | Flash the LED matrix a specific color a specific number of times. For example, to flash the LED matrix Blue three times, the command is `flash:0:3`. |
| `/lightning` | Flash the LED matrix White a random number of times for a random amount of time for each flash in an attempt to simulate lightning or electrical flashes inside the pumpkin. |
| `/off`       | Turns off the LED Matrix (sets all NeoPixels to `CRGB::Black`). |
| `/random`    | Enables random mode where the ESP32 device randomly picks a color from the array and displays it for a random amount of time (seconds) before picking another color and starting all over again. |


***

You can find information on many different topics on my [personal blog](http://www.johnwargo.com). Learn about all of my publications at [John Wargo Books](http://www.johnwargobooks.com).

If you find this code useful and feel like thanking me for providing it, please consider <a href="https://www.buymeacoffee.com/johnwargo" target="_blank">Buying Me a Coffee</a>, or making a purchase from [my Amazon Wish List](https://amzn.com/w/1WI6AAUKPT5P9).
