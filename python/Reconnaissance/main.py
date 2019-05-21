import ReconnaissanceV2 as RV2
import serial

(category_index,image_tensor,detection_boxes,detection_scores,detection_classes,num_detections,sess)=RV2.load_model()

(Liste,score)=RV2.Detection(category_index,image_tensor,detection_boxes,detection_scores,detection_classes,num_detections,sess)



#Configuration du port série :
S = serial.Serial("/dev/ttyS0",9600)

for x in Liste:
	if x='laptop':
		data='VtsM 50 50'
		S.write(data.encode('ascii'))
		receive=S.readline(len(data1))
		print(receive.decode("utf-8"))
		data='Stop'
		S.write(data.encode('ascii'))
		receive=S.readline(len(data))
		print(receive.decode("utf-8"))


S.close()
