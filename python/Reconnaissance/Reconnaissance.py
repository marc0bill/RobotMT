# Importer les différents packages
import os
import numpy as np
from picamera.array import PiRGBArray
from picamera import PiCamera
import tensorflow as tf
import sys
from utils import label_map_util

def Reconnaissance():

# Définir la résolution (plus elle sera petite, plus le programme sera rapide)
    IM_WIDTH = 640
    IM_HEIGHT = 480

    sys.path.append('..')

    MODEL_NAME = 'ssdlite_mobilenet_v2_coco_2018_05_09' #Nom du dossier contenant le module de detection d'objet

    CWD_PATH = os.getcwd()		#Copie le chemin du dossier de travail

# Chemin d'accès du graph de détection
    PATH_TO_CKPT = os.path.join(CWD_PATH,MODEL_NAME,'frozen_inference_graph.pb')  

# Chemin d'accès des labels
    PATH_TO_LABELS = os.path.join(CWD_PATH,'data','mscoco_label_map.pbtxt')

# Nombre de classe que le détectteur d'objet peut voir
    NUM_CLASSES = 90

# On charge la modèle permettant la détection d'objet
    label_map = label_map_util.load_labelmap(PATH_TO_LABELS)
    categories = label_map_util.convert_label_map_to_categories(label_map, max_num_classes=NUM_CLASSES, use_display_name=True)
    category_index = label_map_util.create_category_index(categories)

# Charge le modèle Tensorflow dans la memoire.
    detection_graph = tf.Graph()
    with detection_graph.as_default():
        od_graph_def = tf.GraphDef()
        with tf.gfile.GFile(PATH_TO_CKPT, 'rb') as fid:
            serialized_graph = fid.read()
            od_graph_def.ParseFromString(serialized_graph)
            tf.import_graph_def(od_graph_def, name='')

        sess = tf.Session(graph=detection_graph)


# Définie les tensors d'entrées et de sortie (i.e. données) pour la classification des objets

# Le tensor en entrée est une image (frame)
    image_tensor = detection_graph.get_tensor_by_name('image_tensor:0')

# Les tensors en sorties sont les boxs, les classes les scores associés 
# Chaques box représente une partie de l'image où un objet a été détecté
    detection_boxes = detection_graph.get_tensor_by_name('detection_boxes:0')

# Chaque score représente le level de confience pour chaque objet détecté
    detection_scores = detection_graph.get_tensor_by_name('detection_scores:0')
    detection_classes = detection_graph.get_tensor_by_name('detection_classes:0')

# Nombres d'objets détectés
    num_detections = detection_graph.get_tensor_by_name('num_detections:0')


    camera = PiCamera()									#Initialise la camera
    camera.resolution = (IM_WIDTH,IM_HEIGHT)			#Choix de la résolution
    camera.framerate = 10								#Framerate de la caméra
    rawCapture = PiRGBArray(camera, size=(IM_WIDTH,IM_HEIGHT))		#Produit un tableau 3D à partir de la vidéo
    rawCapture.truncate(0)											#Remplie le tableau avec des zéros

    frame = camera.capture_continuous(rawCapture, format="bgr",use_video_port=True):   #capture la caméra en continue 

	# Récupére une frame et change sa dimension de telle manière à avoir un tableau à une seule colonne, où chaque valeur représente un pixel
    frame.setflags(write=1)			#autorise l'écriture
    frame_expanded = np.expand_dims(frame, axis=0)

    # Réalise la détection avec en entrée l'image issue de la vidéo et stocke les résultats dans des tableaux
    (boxes, scores, classes, num) = sess.run([detection_boxes, detection_scores, detection_classes, num_detections],feed_dict={image_tensor: frame_expanded})
    

    rawCapture.truncate(0)
 
    camera.close()

    return (boxes,scores,classes,num)


