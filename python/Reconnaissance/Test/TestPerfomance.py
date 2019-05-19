import time
import Reconnaissance as RV1
import ReconnaissanceTest as R

start1=time.time()


c=0
while (c<3):
	(Liste,score)=RV1.Detection()
	print(Liste,score)
	c+=1

fin1=time.time()


#Test
(category_index,image_tensor,detection_boxes,detection_scores,detection_classes,num_detections,sess)=R.load_model()


c=0
while (c<3):
	(Liste,score)=R.Detection(category_index,image_tensor,detection_boxes,detection_scores,detection_classes,num_detections,sess)
	print(Liste,score)
	c+=1
	
fin2=time.time()

print("Différence de temps : Pour 1:", fin1-start1, " Pour 2:", fin2-fin1)
