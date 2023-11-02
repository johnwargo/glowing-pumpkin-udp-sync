# ===================================================
# Glowing Pumpkin
# By John M. Wargo
#
# UDP Sync Module (for Raspberry Pi Pico W)
# ===================================================
# References:
# https://forums.raspberrypi.com/viewtopic.php?t=258448
# https://forums.raspberrypi.com/viewtopic.php?t=345398

# TODO: Ensure that the UDP settings aren't empty
# TODO: Ensure that the Wi-Fi network credentials aren't empty

# external libraries
import time
import random
import network
import socket
# internal configuration settings
import config

# make a line of equal signs 40 long to display in the console
# on startup
bars = "=" * 40

# ---------------------------------------------------------
# Configuration settings pulled in from the config.py file
# So you don't have to modify the source to change settings
# ---------------------------------------------------------
broadcast_prefix = config.broadcast_prefix
host_name = config.host_name
# min and max delay between color change (in seconds)
delay_min = config.delay_min
delay_max = config.delay_max
# UDP settings
UDP_IP = config.udp_ip
UDP_PORT = config.udp_port
# Wi-Fi settings
wifi_ssid = config.wifi_ssid
wifi_password = config.wifi_password

last_color = -1
max_color_idx = 5

# =========================================================
# Start here!
# =========================================================
print(bars)
print("* UDP Sender Pi Pico")
print(bars)
print()
print("UDP target IP: {}".format(UDP_IP))
print("UDP target port: {}".format(UDP_PORT))
print("Wi-FI SSID: {}".format(wifi_ssid))
print()

# connect to the wi-fi network
print("Connecting to {}".format(wifi_ssid))
wlan = network.WLAN(network.STA_IF)
wlan.config(hostname=host_name)
wlan.active(True)
wlan.connect(wifi_ssid, wifi_password)

# Wait for connect or fail
max_wait = 10
while max_wait > 0:
    if wlan.status() < 0 or wlan.status() >= 3:
        break
    max_wait -= 1
    print('Waiting for Wi-Fi connection...')
    time.sleep(1)

# Handle connection errors
if wlan.status() != 3:
    raise RuntimeError('Wi-Fi connection failed')
else:
    status = wlan.ifconfig()
    print('Connected to ' + wifi_ssid + '. ' + 'Device IP: ' + status[0])

random.seed(None)

while True:
    print("loop")

    # build the command string starting with the prefix
    cmd_str = broadcast_prefix
    # generate a random number between 1 and 10
    if random.randint(1, 10) > 8:  # flicker
        cmd_str += "f"
    else:  # change color
        cmd_str += "c"
        new_color = random.randint(0, max_color_idx)
        while last_color == new_color:
            new_color = random.randint(0, max_color_idx)
        # at this point, we have a new color selected
        last_color = new_color  # reset last color to the new color
        cmd_str += ":"
        cmd_str += str(last_color)
    print("Command: {}".format(cmd_str))
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.sendto(cmd_str, (UDP_IP, UDP_PORT))
        sock.close()
        print("message sent")
    except:
        print("Network issue")

    # Sleep a random time between delay_min and delay_max
    wait_delay = random.randint(delay_min, delay_max)
    print("Waiting {} seconds".format(wait_delay))
    time.sleep(wait_delay)
