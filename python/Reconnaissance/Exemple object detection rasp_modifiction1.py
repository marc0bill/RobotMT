# Importer les différents packages
import os
import numpy as np
from picamera.array import PiRGBArray
from picamera import PiCamera
import tensorflow as tf
import sys
from utils import label_map_util


# Définir la résolution (plus elle sera petite, plus le programme sera)
IM_WIDTH = 1280
IM_HEIGHT = 720

# This is needed since the working directory is the object_detection folder.
sys.path.append('..')

MODEL_NAME = 'ssdlite_mobilenet_v2_coco_2018_05_09' #Nom du dossier contenant le module de detection d'objet

CWD_PATH = os.getcwd()		#Copie le chemin du dossier de travail

# Chemin d'accès du graph de détection
PATH_TO_CKPT = os.path.join(CWD_PATH,MODEL_NAME,'frozen_inference_graph.pb')  

# Chemin d'accès des labels
PATH_TO_LABELS = os.path.join(CWD_PATH,'data','mscoco_label_map.pbtxt')

# Nombre de classe que le détectteur d'objet peut voir
NUM_CLASSES = 90

## Load the label map.
# Label maps map indices to category names, so that when the convolution
# network predicts `5`, we know that this corresponds to `airplane`.
# Here we use internal utility functions, but anything that returns a
# dictionary mapping integers to appropriate string labels would be fine
label_map = label_map_util.load_labelmap(PATH_TO_LABELS)
categories = label_map_util.convert_label_map_to_categories(label_map, max_num_classes=NUM_CLASSES, use_display_name=True)
category_index = label_map_util.create_category_index(categories)

# Charge le Tensorflow model dans la memoire.
detection_graph = tf.Graph()
with detection_graph.as_default():
    od_graph_def = tf.GraphDef()
    with tf.gfile.GFile(PATH_TO_CKPT, 'rb') as fid:
        serialized_graph = fid.read()
        od_graph_def.ParseFromString(serialized_graph)
        tf.import_graph_def(od_graph_def, name='')

    sess = tf.Session(graph=detection_graph)


# Define input and output tensors (i.e. data) for the object detection classifier

# Input tensor is the image
image_tensor = detection_graph.get_tensor_by_name('image_tensor:0')

# Output tensors are the detection boxes, scores, and classes
# Each box represents a part of the image where a particular object was detected
detection_boxes = detection_graph.get_tensor_by_name('detection_boxes:0')

# Each score represents level of confidence for each of the objects.
# The score is shown on the result image, together with the class label.
detection_scores = detection_graph.get_tensor_by_name('detection_scores:0')
detection_classes = detection_graph.get_tensor_by_name('detection_classes:0')

# Number of objects detected
num_detections = detection_graph.get_tensor_by_name('num_detections:0')


camera = PiCamera()									#Initialise la camera
camera.resolution = (IM_WIDTH,IM_HEIGHT)			#Choix de la résolution
camera.framerate = 10								#Framerate de la caméra
rawCapture = PiRGBArray(camera, size=(IM_WIDTH,IM_HEIGHT))		#Produit un tableau 3D à partir de la vidéo
rawCapture.truncate(0)											#Remplie le tableau avec des zéros

for frame1 in camera.capture_continuous(rawCapture, format="bgr",use_video_port=True):   #capture la caméra en continue 

    # Acquire frame and expand frame dimensions to have shape: [1, None, None, 3]
    # i.e. a single-column array, where each item in the column has the pixel RGB value
    frame = np.copy(frame1.array)  #copie le contenue du tableau frame1 dans frame
    frame.setflags(write=1)			#autorise l'écriture
    frame_expanded = np.expand_dims(frame, axis=0)

    # Perform the actual detection by running the model with the image as input
    global (boxes, scores, classes, num) = sess.run([detection_boxes, detection_scores, detection_classes, num_detections],feed_dict={image_tensor: frame_expanded})

    rawCapture.truncate(0)

    camera.close()


