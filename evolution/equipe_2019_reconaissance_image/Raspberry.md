# Raspebrry Pi

Les objectifs de la carte Raspberry Pi sont les suivants:
	- Récupérer la flux video de la camera 
	- Analyser ce flux video au moyen d'un algorithme de reconnaissance d'image
	- Asservir le robot en fonction des résultats des objets reconnues à travers l'envoie de commande UART

## Recuperation du flux vidéo de la camera

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

La dernière étape est 
