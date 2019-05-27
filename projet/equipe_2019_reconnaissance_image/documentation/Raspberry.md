# Raspebrry Pi

Les objectifs de la carte Raspberry Pi sont les suivants:
	- Récupérer la flux video de la camera 
	- Analyser ce flux video au moyen d'un algorithme de reconnaissance d'image
	- Asservir le robot en fonction des résultats des objets reconnues à travers l'envoie de commande UART

## Test de la camera

Après avoir branché la camera, nous pouvons tester son fonctionnement en prenant une photo par la commande suivante:
```
raspistill -o test_camera_01.jpg -t 5000
```
Ici test_camera_01.jpg sera le nom de l'image enregistrée (au format JPEG) et 5000 représente le temps d'affichage de l'image (en ms) à la fin de la capture.

Ce test étant concluant, nous pouvons tester l'enregistrement d'une vidéo avec la commande suivante:
```
raspivid -o video_01.h264 -t 5000
```
Cette commande enregistre une vidéo de d'une durée de 5s (5000 ms) portant le nom video_01.h264 (format MP4)
Nous pouvons ensuite visualiser cette vidéo avec:
```
omxplayer video_01.h264
```

Ce test est concluant. Néanmoins nous remarquons qu'à la lecture de la video, celle-ci est accélérée deux fois (en enregistrement de 10s est lue en 20s). Ce problème peut-être soit du à l'enregistrement soit à la lecture. Néanmoins pour l'utilisation que nous comptons en faire, cela ne pose pas de réel problème. Nous reviendront dessus en cas de problème de traitement vidéo ou si nous avons le temps.

La prochaine étape sera de récupérer ce flux vidéo dans un script python afin de pouvoir l'echantilloner et le traiter.
Pour cela nous auront besoins de plusieurs librairies. En particulier la librairie tensorflow qui est l'algorithme de reconnaissance d'image (dévellopé par Google) que nous utiliserons. Cette algorithme s'appuie sur un réseau de neurones au préalablement entrainé. Le fonctionnement de l'algorithme est détaillé dans la documentation correspondante.

## Traitement du flux vidéo

Pour réaliser la suite des objectifs de la raspberry pi nous nous sommes inspirés d'un projet déjà existant sur github: https://github.com/EdjeElectronics/TensorFlow-Object-Detection-on-the-Raspberry-Pi

Nous avons donc installer l'ensemble des librairies nécessaire à l'aide des commandes suivante. Chacune de ces commandes sont détaillées sur le projet original cité ci-dessus. Nous nous contenterons uniquement de les lister ici.
```
sudo apt-get update
sudo apt-get dist-upgrade

mkdir tf
cd tf

wget https://github.com/lhelontra/tensorflow-on-arm/releases/download/v1.13.1/tensorflow-1.13.1-cp35-none-linux_armv7l.whl (penser à prendre la dernière version disponible et fonctionnelle : https://github.com/lhelontra/tensorflow-on-arm/releases)

sudo pip3 install /home/pi/tf/tensorflow-1.8.0-cp35-none-linux_armv7l.whl
sudo pip3 install pillow lxml jupyter matplotlib cython
sudo apt-get install python-tk

sudo apt-get install libjpeg-dev libtiff5-dev libjasper-dev libpng12-dev
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt-get install libxvidcore-dev libx264-dev
sudo apt-get install qt4-dev-tools
pip3 install opencv-python

sudo apt-get install autoconf automake libtool curl

wget https://github.com/protocolbuffers/protobuf/releases/download/v3.7.1/protobuf-all-3.7.1.tar.gz (dernière version : https://github.com/protocolbuffers/protobuf/releases)

tar -zxvf protobuf-all-3.5.1.tar.gz
cd protobuf-3.5.1
make
make check
sudo make install
cd python
export LD_LIBRARY_PATH=../src/.libs
python3 setup.py build --cpp_implementation 
python3 setup.py test --cpp_implementation
sudo python3 setup.py install --cpp_implementationexport PROTOCOL_BUFFERS_PYTHON_IMPLEMENTATION=cpp
export PROTOCOL_BUFFERS_PYTHON_IMPLEMENTATION_VERSION=3sudo ldconfig
protoc
sudo reboot now

mkdir tensorflow1
cd tensorflow1
git clone --recurse-submodules https://github.com/tensorflow/models.git
sudo nano ~/.bashrc
export PYTHONPATH=$PYTHONPATH:/home/pi/tensorflow1/models/research:/home/pi/tensorflow1/models/research/slim
cd /home/pi/tensorflow1/models/research
protoc object_detection/protos/*.proto --python_out=.
cd /home/pi/tensorflow1/models/research/object_detection
wget http://download.tensorflow.org/models/object_detection/ssdlite_mobilenet_v2_coco_2018_05_09.tar.gz
tar -xzvf ssdlite_mobilenet_v2_coco_2018_05_09.tar.gz

wget https://raw.githubusercontent.com/EdjeElectronics/TensorFlow-Object-Detection-on-the-Raspberry-Pi/master/Object_detection_picamera.py

```

Nous téléchargeons ensuite un scripts python appliquant l'algorithme tensorflow aux flux vidéo de la camera et nous renvoyant un flux vidéo traité. 

```
wget https://raw.githubusercontent.com/EdjeElectronics/TensorFlow-Object-Detection-on-the-Raspberry-Pi/master/Object_detection_picamera.py
```
Comme nous pouvons le voir les objets reconnus sont encadrés d'une boite comportant le nom de l'objet reconnue ainsi que la probabilité que la reconnaissance soit correcte (ou le degré de certitude de l'algorithme dans ce cas précis).

<p align="center">
  <img src="..\ressources\Presentation\images\vue_rasp.jpeg">
</p>

La reconnaissance d'image fonctionne alors correctement.

Dans notre documentation tensorflow, nous expliquonns comment nous avons repris ce scripts afin de pouvoir utilisé et formatter les résulats de la reconnaissance d'image dans le but d'être utilisés par le programme d'asservissement.