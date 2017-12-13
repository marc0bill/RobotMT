import time
from PinceClass import PinceClass

Pince=PinceClass()
print Pince.ServoRead(0x01, 0x11, 1)

print Pince.ServoRead(0x01, 'GlobalPos', 2)

Pince.Open()
time.sleep(1)
Pince.Close()
time.sleep(1.5)
Pince.Up()
time.sleep(1)
Pince.Down()
time.sleep(1)
Pince.Stop()

Pince.Led_OFF()