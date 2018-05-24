import time
import serial
 
ser = serial.Serial('COM3', 57600, timeout=0, parity=serial.PARITY_EVEN, rtscts=1)
s = ser.read(100)

canvas = Canvas(fenetre, width=150, height=150, background='white')
canvas.pack(expand=YES, fill=BOTH)

widget = Label(canvas, text=s, fg='white', bg='black')
widget.pack()
canvas.create_window(100, 100, window=widget)       
mainloop()
