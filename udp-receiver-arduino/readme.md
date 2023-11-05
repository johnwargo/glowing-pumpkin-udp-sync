# Glowing Pumpkin USP Sync Receiver

This is the [Glowing Pumpkin Xiao 5x5 BFF](https://github.com/johnwargo/glowing-pumpkin-xiao-bff) project with a UDP broadcast listener added to you can control the LEDs from separate device running the [Sender](https://github.com/johnwargo/glowing-pumpkin-udp-sync/tree/main/udp-sender-arduino) version of the sketch. 

To use it, configure network settings for the sketch as described in the following section then compile and deploy the sketch on one or more *Glowing Pumpkin Xiao 5x5 BFF* devices. Once you configure and deploy the Sender sketch and power it on, all of the *Glowing Pumpkin Xiao 5x5 BFF* devices on the same network should start synchronizing the color display on the connected LED matrix.

## Configuring Settings

To keep my network settings out of the repo and to keep from forcing you to modify the source code to configure local  settings, I coded the sketch so it reads the settings from a separate file called `constants.h`. Included in the repository is a filed called `constants.h.rename`; rename that file to `constants.h` (basically by removing the `.rename`) from the end of the file name. Inside the file you'll find the following code:

```c
#define BROADCAST_PREFIX "pmpkn::"
#define UDP_PORT 65001
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
```

The following table describes the configuration options:

| Setting            | Description |
| ------------------ | ----------- |
| `BROADCAST_PREFIX` | Defines the string at the beginning of every command sent by the Sender. This receiver sketch will only process UDP broadcast messages that start with this prefix. If you change it on the Sender, you must make the exact same change hers. |
| `UDP_PORT`         | The UDP Port the sketch sends broadcast messages on. If you changed it in the Sender, you must make the same change here as well. |
| `WIFI_SSID`        | Enter your local Wi-Fi network name (SSID). |
| `WIFI_PASSWORD`    | Enter your local Wi-Fi network password. |

When you're done, the file should look something like this (with your information in it, of course):

```c
#define BROADCAST_PREFIX "pmpkn::"
#define UDP_PORT 65001
#define WIFI_SSID "My Network"
#define WIFI_PASSWORD "mynetworkpassword"
```

**Note:** The Wi-Fi SSID and password values are case sensitive; if your device doesn't connect correctly to the network, double check the credentials.

## The Code

Normally I'd spend a lot of time here documenting everything I can tell you about the code. I'm not going to do that here because it's a lot of code to go through. I put a lot of comments in the code to help you understand what I did and why. If you have questions, ask them in an [issue](https://github.com/johnwargo/glowing-pumpkin-udp-sync/issues) in this repository and I'll answer when I can.

***

You can find information on many different topics on my [personal blog](http://www.johnwargo.com). Learn about all of my publications at [John Wargo Books](http://www.johnwargobooks.com).

If you find this code useful and feel like thanking me for providing it, please consider <a href="https://www.buymeacoffee.com/johnwargo" target="_blank">Buying Me a Coffee</a>, or making a purchase from [my Amazon Wish List](https://amzn.com/w/1WI6AAUKPT5P9).
