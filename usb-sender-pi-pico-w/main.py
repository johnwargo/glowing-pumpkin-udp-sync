# ===================================================
# Glowing Pumpkin
# By John M. Wargo
#
# UDP Sync Module (for Raspberry Pi Pico W)
# ===================================================

# external libraries
import time
import network
import socket

# internal files
import config

# UDP settings
UDP_IP = config.UDP_IP
UDP_PORT = config.UDP_PORT
# Wi-Fi settings
wifi_ssid = config.wifi_ssid
wifi_password = config.wifi_password

# TODO: Ensure that the UDP settings aren't empty
# TODO: Ensure that the Wi-Fi network credentials aren't empty

# connect to the wi-fi network
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(wifi_ssid, wifi_password)

# Wait for connect or fail
max_wait = 10

while max_wait > 0:
    if wlan.status() < 0 or wlan.status() >= 3:
        break
    max_wait -= 1
    print('waiting for connection...')
    time.sleep(1)



MESSAGE  = "Hello, World!"

print("UDP target IP   :", UDP_IP)
print("UDP target port :", UDP_PORT)
print("Message         :", MESSAGE)

sock = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )
sock.sendto( MESSAGE, (UDP_IP, UDP_PORT) )
sock.close()




# ============================================
UDP_IP = "192.168.1.93"
UDP_PORT = 5001


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Wait for connect or fail
max_wait = 10

while max_wait > 0:
    if wlan.status() < 0 or wlan.status() >= 3:
        break
    max_wait -= 1
    print('waiting for connection...')
    time.sleep(1)

# Handle connection error
if wlan.status() != 3:
    raise RuntimeError('network connection failed')
else:
    status = wlan.ifconfig()
    print('Connected to ' + wifi_ssid + '. ' + 'Device IP: ' + status[0])

while True:
    time.sleep(2)

    try:
        message = "Hello World"
        sock.sendto(message.encode(), (UDP_IP, UDP_PORT))
        print("message sent")
    except:
        print("Network issue")
