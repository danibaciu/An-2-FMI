import numpy as np
import pandas as pd

from PIL import Image

#------------------------------------------

def return_pixel_rgb_values(img_name, path_catre_folder = "../data/train_validation/") :
    return np.array(Image.open(path_catre_folder + img_name).getdata()).reshape((16, 16, 3))

#-----------------------------------------

def classifica_imaginea(imagini_train, labeluri_train, pixel_image, no_of_neigh = 1) :

    distante = np.sqrt(np.sum(np.power((imagini_train - pixel_image), 2), axis=1))

    indici_sortati = np.argsort(distante)

    indici_sortati = indici_sortati[ :no_of_neigh]

    preziceri = labeluri_train[indici_sortati]

    return np.argmax(np.bincount(preziceri))

#-----------------------------------------

def write_output_file(predictii, k):
    f = open("knn" + str(k) + ".txt", "w")
    f.write("id,label\n")
    i = 0
    for nume_img in fisier_txt_test.id :
        f.write(f"{nume_img},{predictii[i]}\n")
        i += 1
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

# incepem sa antrenam modelul

for no_of_neig in [10, 11, 12, 15, 20, 23, 25] :

    predictii = []

    for img in imagini_pentru_validation_standardizate:

        predictii.append(classifica_imaginea(img_train, labels_train, img, no_of_neig))

        # fac predictii pe imaginile de train plus cele rotite la 90

    predictii = np.array(predictii)

    print(f"Valoarea de prezicere pentru \tnr vecini = \t{no_of_neig} \teste = \t{(np.array(fisier_txt_validation.label) == predictii).mean()}")

#-----------------------------------------

# am gasit numarul de vecini 12 optim, deci facem predictiile pe el

predictii, nr_vecini = [], 12

for img in imagini_pentru_test_standardizate:

    predictii.append(classifica_imaginea(img_train, labels_train, img, nr_vecini))

predictii = np.array(predictii)

write_output_file(predictii, 1)

#-----------------------------------------