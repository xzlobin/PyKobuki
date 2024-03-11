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

rob = Robot(ipaddressLaser=ipaddressLaser, ipaddressRobot=ipaddressRobot)
rob.robotStart()
rob.waitConnection()

for i in range(10):
    print(rob.getLastCoordinates())
    rob.setTranslationSpeed(10*i)
    
    time.sleep(0.5)

rob.setTranslationSpeed(0)
