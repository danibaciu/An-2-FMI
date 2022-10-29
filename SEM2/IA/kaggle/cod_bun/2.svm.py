#------------------------------------------

# am preluat codul pana la standardizari de la knn

import numpy as np
import pandas as pd

from PIL import Image
from sklearn.svm import SVC

#------------------------------------------

def return_pixel_rgb_values(img_name, path_catre_folder = "../data/train_validation/") :
    return np.array(Image.open(path_catre_folder + img_name).getdata()).reshape((16, 16, 3))

#-----------------------------------------

def write_output_file(predictii, k):
    f = open("svm" + str(k) + ".txt", "w")
    f.write("id,label\n")
    i = 0
    for nume_img in fisier_txt_test.id :
        f.write(f"{nume_img},{predictii[i]}\n")
        i += 1

#-----------------------------------------

def create_model(_images_for_train, _labels_for_train, c_parameter = 1.0, kernel = "linear") :

    model_SVM = SVC(C=c_parameter, kernel=kernel)

    model_SVM.fit(_images_for_train, _labels_for_train)

    return model_SVM

#-----------------------------------------

fisier_txt_train = pd.read_csv("../data/train.txt", sep=',')

fisier_txt_validation = pd.read_csv("../data/validation.txt", sep=',')

fisier_txt_test = pd.read_csv("../data/test.txt", sep=',')

#-----------------------------------------

# print(fisier_txt_train.id[4:8])
# print("----------------------------")
# print(fisier_txt_train.id[5:7])

#-----------------------------------------

# image_name_test = fisier_txt_train.id[3]
#
# image = return_pixel_rgb_values(image_name_test)

# print(image[0])
# print(image.shape)

#-----------------------------------------

imagini_pentru_train = np.array([return_pixel_rgb_values(x) for x in fisier_txt_train.id])

imagini_pentru_validation = np.array([return_pixel_rgb_values(x) for x in fisier_txt_validation.id]).reshape((1173, 768)) / 255

imagini_pentru_test = np.array([return_pixel_rgb_values(x, "../data/test/") for x in fisier_txt_test.id]).reshape((2819, 768)) / 255

imagini_pentru_train_rotire_90 = np.rot90(imagini_pentru_train, k=1, axes =(0, 1)).reshape((8000,768)) / 255

imagini_pentru_train = imagini_pentru_train.reshape((8000, 768))/255

#-----------------------------------------

imagini_pentru_train_mean = np.mean(imagini_pentru_train, axis=0)

imagini_pentru_train_rotire_90_mean = np.mean(imagini_pentru_train_rotire_90, axis=0)

imagini_pentru_validation_mean = np.mean(imagini_pentru_validation, axis=0)

imagini_pentru_test_mean = np.mean(imagini_pentru_test, axis=0)

#-----------------------------------------

imagini_pentru_train_standardizate = imagini_pentru_train - imagini_pentru_train_mean / np.std(imagini_pentru_train)

imagini_pentru_train_rotire_90_standardizate = imagini_pentru_train_rotire_90 - imagini_pentru_train_rotire_90_mean / np.std(imagini_pentru_train_rotire_90)

imagini_pentru_validation_standardizate = imagini_pentru_validation - imagini_pentru_validation_mean/np.std(imagini_pentru_validation)

imagini_pentru_test_standardizate = imagini_pentru_test - imagini_pentru_test_mean / np.std(imagini_pentru_test)

#-----------------------------------------

#nu am mai folosit perturbari

# images_perturbed = []

# for img in imagini_pentru_train_standardizate :

#     images_perturbed.append(img + np.random.normal(loc=0.0,scale=0.01, size=(768,)))

# images_perturbed = np.array(images_perturbed)

#-----------------------------------------

# concatenez la setul de train si imagini rotite cu 90 grade

img_train = np.concatenate((imagini_pentru_train_standardizate, imagini_pentru_train_rotire_90_standardizate), axis=0)
labels_train = np.concatenate((np.array(fisier_txt_train.label),np.array(fisier_txt_train.label)), axis=0)

#-----------------------------------------

for c in [0.1, 0.5, 1.0, 1.1, 1.8, 2.2, 3.0, 3.3] :

    # for kernel in ["linear", "poly", "rbf", "sigmoid"]:
    for kernel in ["linear", "poly", "rbf"]:

        model_svm = create_model(img_train, labels_train, c_parameter=c, kernel=kernel)

        print(f"Valoarea pt \t kernel =\t{kernel}\t si c =\t{c}\t este = \t{(model_svm.predict(imagini_pentru_validation_standardizate) == np.array(fisier_txt_validation.label)).mean()}")

    print("\n-------------------------------------------------------------\n")

#-----------------------------------------

# observam ca parametrii optimi pentru c sunt 1.1 si 3.3, iar kernelul este "rbf" asa ca vom face predictii pe ei

pred_img= np.concatenate((img_train, imagini_pentru_validation_standardizate), axis=0)
pred_labels = np.concatenate((labels_train, np.array(fisier_txt_validation.label)), axis=0)

for c in [1.1, 3.3] :

    model_svm = create_model(pred_img, pred_labels, c_parameter=c, kernel = "rbf")

    labels = model_svm.predict(imagini_pentru_test_standardizate)

    write_output_file(labels, "svm" + str(c) + ".txt")





