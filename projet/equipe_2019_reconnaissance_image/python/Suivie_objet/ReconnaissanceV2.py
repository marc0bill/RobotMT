# Importer les différents packages
import os
import numpy as np
from picamera.array import PiRGBArray
from picamera import PiCamera
import tensorflow as tf
import sys
from utils import label_map_util


#Fonction permetant de charger le modèle Tensorflow dans la mémoire
def load_model():

    sys.path.append('..')
    
#Nom du dossier contenant le module de detection d'objet

    MODEL_NAME = 'ssdlite_mobilenet_v2_coco_2018_05_09' 

# Chemin d'accès du graph de détection

#Copie le chemin du dossier de travail
    CWD_PATH = os.getcwd()	

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
# Chaque box représente une partie de l'image où un objet a été détecté
    detection_boxes = detection_graph.get_tensor_by_name('detection_boxes:0')

# Chaque score représente le level de confience pour chaque objet détecté
    detection_scores = detection_graph.get_tensor_by_name('detection_scores:0')

# Classe = Nom de l'objet détecté 
    detection_classes = detection_graph.get_tensor_by_name('detection_classes:0')

# Nombres d'objets détectés
    num_detections = detection_graph.get_tensor_by_name('num_detections:0')


    return (category_index,image_tensor,detection_boxes,detection_scores,detection_classes,num_detections,sess)

#Fonction permettant la detection d'image
def Detection(category_index,image_tensor,detection_boxes,detection_scores,detection_classes,num_detections,sess):

# Définir la résolution (plus elle sera petite, plus le programme sera rapide)
    IM_WIDTH = 640
    IM_HEIGHT = 480
    camera = PiCamera()									#Initialise la camera
    camera.resolution = (IM_WIDTH,IM_HEIGHT)			#Choix de la résolution
    camera.framerate = 10								#Framerate de la caméra
    rawCapture = PiRGBArray(camera, size=(IM_WIDTH,IM_HEIGHT))		#Produit un tableau 3D à partir de la vidéo
    rawCapture.truncate(0)											#Remplie le tableau avec des zéros

# Récupére une frame et change sa dimension de telle manière à avoir un tableau à une seule colonne, où chaque valeur représente un pixel
    camera.capture(rawCapture, format="bgr",use_video_port=True)
    frame = np.copy(rawCapture.array)
    frame.setflags(write=1)
    frame_expanded = np.expand_dims(frame, axis=0)

# Réalise la détection avec en entrée l'image issue de la vidéo et stocke les résultats dans des tableaux
    (boxes, scores, classes, num) = sess.run([detection_boxes, detection_scores, detection_classes, num_detections],feed_dict={image_tensor: frame_expanded})

   
# On retourne les objets détectés et leurs scores associés:
	#Les résultats renvoyés par tensorflow sont des tableaux de tableaux, pour pouvoir les exploiter facilement, on réduit leurs dimensions avec np.squeeze.
    classes=np.squeeze(classes).astype(np.int32)
    scores=np.squeeze(scores).tolist()
    boxes=np.squeeze(boxes).tolist()
    objets=[[],[],[],[]]
    c=0
    #On se limite ici au quatre premiers objets détectés sur l'image: 
    for i in range (0,4):
        if scores[i]==0:
            break
        objets[i].append(category_index[classes[i]]['name'])
        objets[i].append(scores[i])
        objets[i].append(boxes[i][0])
        objets[i].append(boxes[i][1])
        objets[i].append(boxes[i][2])
        objets[i].append(boxes[i][3])
        c+=1
 
 	#Ne pas oublier de fermer la caméra sinon elle ne sera plus utilisable par le programme
    camera.close()
    return (objets[0:c])
