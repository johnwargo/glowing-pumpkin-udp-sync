# Glowing Pumpkin USP Sync Sender (Raspberry Pi Pico W)

This is the Raspberry Pi Pico W version of the [Sender](https://github.com/johnwargo/glowing-pumpkin-udp-sync/tree/main/udp-sender-arduino) sketch. I created this version when I couldn't get the Arduino Sender sketch working correctly; I was eventually able to get it working, but I kept this version in the repo just in case you want to play with a Python version of the Sender. It works on the Raspberry Pi Pico, but should run on the standard Raspberry Pi as well (although I did not test it).

To use it, configure the settings for the program as described in the following section then deploy it to a Raspberry Pi Pico W device (the W is important because that's the only Pico with Wi-Fi network support). When you run the program, all of the *Glowing Pumpkin Xiao 5x5 BFF* Receiver devices on the same network should start synchronizing the color display on the connected LED matrix.

## Configuring Settings

To keep my network settings out of the repo and to keep from forcing you to modify the source code to configure local settings for the program, The code reads settings from a separate file called `config.py`. Included in the repository is a filed called `config.rename`; rename that file to `config.py`. Inside the file you'll find the following code:

```python
broadcast_prefix = "pmpkn::"
delay_max = 10
delay_min = 5
host_name = "pumpkin-send"
udp_ip = ""
udp_port = 65001
wifi_ssid = ""
wifi_password = ""
```

The following table describes the configuration options:

| Setting            | Description |
| ------------------ | ----------- |
| `broadcast_prefix` | Defines the string at the beginning of every command sent by the Sender. This receiver sketch will only process UDP broadcast messages that start with this prefix. You can generally leave this setting alone, but if you change it, be sure to make the exact same change in the Sender sketch configuration. |
| `delay_max`        | Between sending UDP commands, the program waits a random number of seconds between `delay_min` and `delay_max` before sending the next command. Adjust this value to change the maximum number of seconds. |
| `delay_min`        | Between sending UDP commands, the program waits a random number of seconds between `delay_min` and `delay_max` before sending the next command. Adjust this value to change the minimum number of seconds. |
| `host_name`        | The program sets this network name for the device when it connects to the Wi-Fi network. |
| `udp_ip`           | Set the address to the sender device IP address with 255 as the last dot number. For example, if the device's IP address is `192.168.86.23` then set the `UDP_ADDRESS` to `192.168.86.255`. |
| `udp_port`         | The receiver uses a hard-coded UDP Port number of 65001 (I should probably change that and pull the value into the configuration file there too). If you change the port here, likely do to another application on the network using that port, make sure you make the same change in the Receiver sketch. |
| `wifi_ssid`        | Enter your local Wi-Fi network name (SSID). |
| `wifi_ssid`        | Enter your local Wi-Fi network password.|

When you're done, the file should look something like this (with your information in it, of course):

```python
broadcast_prefix = "pmpkn::"
delay_max = 10
delay_min = 5
host_name = "pumpkin-send"
udp_ip = "192.168.86.255""
udp_port = 65001
wifi_ssid = "My Network"
wifi_password = "mynetworkpassword"
```

**Note:** The Broadcast Prefix and the Wi-Fi SSID and password are case sensitive; if your device doesn't connect correctly to the network, double check the credentials.

## The Code

Normally I'd spend a lot of time here documenting everything I can tell you about the code. I'm not going to do that here because it's a lot of code to go through. I put a lot of comments in the code to help you understand what I did and why. If you have questions, ask them in an [issue](https://github.com/johnwargo/glowing-pumpkin-udp-sync/issues) in this repository and I'll answer when I can.

***

You can find information on many different topics on my [personal blog](http://www.johnwargo.com). Learn about all of my publications at [John Wargo Books](http://www.johnwargobooks.com).

If you find this code useful and feel like thanking me for providing it, please consider <a href="https://www.buymeacoffee.com/johnwargo" target="_blank">Buying Me a Coffee</a>, or making a purchase from [my Amazon Wish List](https://amzn.com/w/1WI6AAUKPT5P9).
