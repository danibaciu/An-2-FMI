import numpy as np
import pandas as pd

from PIL import Image

#------------------------------------------

def return_pixel_rgb_values(img_name, path_catre_folder = "./data/train_validation/") :
    return np.array(Image.open(path_catre_folder + img_name).getdata()).reshape((16, 16, 3))

#-----------------------------------------

fisier_txt_train = pd.read_csv("./data/train.txt", sep=',')

fisier_txt_validation = pd.read_csv("./data/validation.txt", sep=',')

fisier_txt_test = pd.read_csv("./data/test.txt", sep=',')

#-----------------------------------------

print(fisier_txt_train.id[4:8])
print("----------------------------")
print(fisier_txt_train.id[5:7])

#-----------------------------------------

image_name_test = fisier_txt_train.id[3]

image = return_pixel_rgb_values(image_name_test)

# print(image[0])
print(image.shape)

#-----------------------------------------

#-----------------------------------------

#-----------------------------------------

#-----------------------------------------
