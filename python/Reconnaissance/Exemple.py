
from __future__ import absolute_import, division, print_function
 
# TensorFlow and tf.keras
import tensorflow as tf
from tensorflow import keras
 
# Helper libraries
import numpy as np
import matplotlib.pyplot as plt
 

fashion_mnist = keras.datasets.fashion_mnist
                                                            #Récupération du set d'image
(train_images, train_labels), (test_images, test_labels) = fashion_mnist.load_data()



class_names = ['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat', 
               'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']



train_images = train_images / 255.0                 # Tensorflow n'accepte que le '0' ou '1'
test_images = test_images / 255.0


#plt.figure(figsize=(10,10))
#for i in range(25):
   # plt.subplot(5,5,i+1)
   # plt.xticks([])
   # plt.yticks([])
   # plt.grid(False)
   # plt.imshow(train_images[i], cmap=plt.cm.binary)
   # plt.xlabel(class_names[train_labels[i]])


model = keras.Sequential([
    keras.layers.Flatten(input_shape=(28, 28)),
    keras.layers.Dense(128, activation='relu'),         #construction reseau de neurones
    keras.layers.Dense(10, activation='softmax')
])

model.compile(optimizer='adam', 
              loss='sparse_categorical_crossentropy',       #compile le modèle
              metrics=['accuracy'])

model.fit(train_images, train_labels, epochs=5)             #entraine le modèle


test_loss, test_acc = model.evaluate(test_images, test_labels)  #validation

print('\nTest accuracy:', test_acc)

predictions = model.predict(test_images)            #prediction

print(np.argmax(predictions[0])
, test_labels[0])