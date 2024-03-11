import subprocess
import platform
import ipaddress
import time
from Kobuki import Robot

# detecting if we are running under wsl
on_wsl = "microsoft" in platform.uname().release.lower() and platform.platform().lower().startswith("linux")

# supposing that Kobuki Simulator running on windows host
# we have to resolve its ip on local virtual network
if on_wsl:
    cmd = "ip route show | grep -i default | awk '{ print $3}'"
    result = subprocess.check_output(cmd, shell = True, executable = "/bin/bash", stderr = subprocess.STDOUT)

    windowsHost = ipaddress.ip_address( result.decode('utf-8').strip() )
    ipaddressLaser = str(windowsHost)
    ipaddressRobot = str(windowsHost)
    print(f'WSL detected, trying to connect to windows host {ipaddressRobot}')
else:
    ipaddressLaser = '127.0.0.1'
    ipaddressRobot = ipaddressLaser
    print(f'Trying to connect to local host {ipaddressLaser}')

eps = 0.01
x_req = 0.3
flag_done = False

def control_callback(robot, rawData):
    global flag_done
    c = robot.getLastCoordinates()
    print(c)
    if c.x < x_req - eps:
        robot.setTranslationSpeed(100)
    elif c.x > x_req + eps:
        robot.setTranslationSpeed(-100)
    else:
        robot.setTranslationSpeed(0)
        flag_done = True

rob = Robot(ipaddressLaser=ipaddressLaser, ipaddressRobot=ipaddressRobot, robcallback=control_callback)
rob.robotStart()
rob.waitConnection()

while not flag_done:
    time.sleep(0.1)

print("Destination has been reached!")
