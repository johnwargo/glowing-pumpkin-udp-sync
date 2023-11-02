# ===================================================
# Glowing Pumpkin
# By John M. Wargo
#
# UDP Sync Module (for Raspberry Pi Pico W)
# ===================================================
# References:
# https://forums.raspberrypi.com/viewtopic.php?t=258448
# https://forums.raspberrypi.com/viewtopic.php?t=345398

# external libraries
import time
import random
import network
import socket

# internal files
import config

bars = "=" * 40

# UDP settings
UDP_IP = config.udp_ip
UDP_PORT = config.udp_port
# Wi-Fi settings
wifi_ssid = config.wifi_ssid
wifi_password = config.wifi_password

# min and max delay between color change (in milliseconds)
delay_min = 5000
delay_max = 10000

broadcast_prefix = "pmpkn::"
host_name = "pumpkin-send"

# TODO: Ensure that the UDP settings aren't empty
# TODO: Ensure that the Wi-Fi network credentials aren't empty

# =========================================================
# Start here!
# =========================================================

print(bars)
print("UDP Sender Pi Pico")
print(bars)

# connect to the wi-fi network
print("Connecting to {}".format(wifi_ssid))
wlan = network.WLAN(network.STA_IF)
# wlan.config(hostname=host_name)
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
# Handle connection error
if wlan.status() != 3:
    raise RuntimeError('Wi-Fi connection failed')
else:
    status = wlan.ifconfig()
    print('Connected to ' + wifi_ssid + '. ' + 'Device IP: ' + status[0])

print("UDP target IP   :", UDP_IP)
print("UDP target port :", UDP_PORT)

random.seed(a=None, version=2)

while True:
    print("loop")
    try:
        msg = broadcast_prefix

        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.sendto(msg, (UDP_IP, UDP_PORT))
        sock.close()
        print("message sent")
    except:
        print("Network issue")

    # Sleep a random time between delay_min and delay_max
    time.sleep(random.randint(delay_min, delay_max))
