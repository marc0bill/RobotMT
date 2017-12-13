from dynamixel import *
import time


X = ServoController()
X.SetPosition(1, 512) # Set servo ID 1 to position 512 (straight up)
