import numpy as np
import pandas as pd
import torch

from PIL import Image
from torch.optim import SGD
from tqdm import tqdm
from torch.nn.functional import softmax
from torch.utils.tensorboard import SummaryWriter

from dataset_class import get_dataloader
from cnn_class import CnnModel_testing1

#-----------------------------------------

rulare_device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

print(f" Rulam pe {rulare_device}")

#-----------------------------------------

def return_pixel_rgb_values(img_name, path_catre_folder = "../data/train_validation/") :
    return np.array(Image.open(path_catre_folder + img_name).getdata()).reshape((16, 16, 3))

#-----------------------------------------

def write_output_file(running_device, date_de_test, fisier_txt_test, k):
    f = open("cnn_" + str(k) + ".txt", 'w')
    f.write("id,label\n")
    i = 0

    cnn_model = CnnModel_testing1()
    cnn_model.to(running_device)
    cnn_model.load_state_dict(torch.load("../models/model_test_cnn_" + str(k)))

    with torch.no_grad():

        for imgs, _ in date_de_test:

            imgs = imgs.to(running_device)

            output = cnn_model(imgs)

            _, labeluri_prezise = torch.max(output.data, 1)

            for label in labeluri_prezise:
                f.write(f"{fisier_txt_test.id[i]},{label}\n")
                i += 1

    f.close()

#-----------------------------------------

def _train_cnn_model_(cnn_model, optimizator_pentru_cnn, criterion_pentru_cnn, imgs_dataloader_train, running_device, epoca_de_rulare, grafic) :

    cnn_model.train()

    running_loss = 0.0

    for images_batch, labels_batch in tqdm(imgs_dataloader_train, "Train"):

        images_batch = images_batch.to(running_device)
        labels_batch = labels_batch.to(running_device)

        output_labels = cnn_model(images_batch)

        loss_actual = criterion_pentru_cnn(output_labels, labels_batch)

        optimizator_pentru_cnn.zero_grad()

        loss_actual.backward()

        optimizator_pentru_cnn.step()

        running_loss += loss_actual.item() * len(images_batch)

    running_loss /= len(imgs_dataloader_train.dataset)

    grafic.add_scalar(tag="Loss/Train", scalar_value=running_loss, global_step=epoca_de_rulare)
    grafic.flush()

#-----------------------------------------

def save_cnn_model(model, path, model_no):
    torch.save(model.state_dict(), path + f"model{model_no}.pth")
    print("am salvat modelul")

#-----------------------------------------

def _evaluate_cnn_model_(cnn_model, criterion_pentru_cnn, imgs_dataloader_validation,  running_device, epoca_de_rulare, grafic, best_loss, best_accuracy):
    cnn_model.eval()

    running_loss = 0.0

    true_predictions_cnn = 0

    with torch.no_grad():

        for images_batch, labels_batch in tqdm(imgs_dataloader_validation, "Validation"):

            images_batch = images_batch.to(running_device)
            labels_batch = labels_batch.to(running_device)

            output_labels = cnn_model(images_batch)

            loss_actual = criterion_pentru_cnn(output_labels, labels_batch)

            scor = softmax(output_labels, dim=1)

            predicted_label = torch.argmax(scor, dim=1)

            true_predictions_cnn += (predicted_label == labels_batch).sum()

            running_loss += loss_actual.item() * len(images_batch)

        accuracy = true_predictions_cnn / len(imgs_dataloader_validation.dataset)
        running_loss = running_loss / len(imgs_dataloader_validation.dataset)

        print(f"acc is {accuracy}")

        grafic.add_scalar(scalar_value=accuracy, tag="Acc/Valid", global_step=epoca_de_rulare)
        grafic.add_scalar(scalar_value=running_loss, tag="Loss/Valid", global_step=epoca_de_rulare)

        grafic.flush()

        if running_loss < best_loss :
             save_cnn_model(cnn_model, "../models/", "best_loss")
             best_loss = running_loss
             print(" am salvat modelul cu best loss")

        if accuracy > best_accuracy :
             save_cnn_model(cnn_model, "../models/", "best_accuracy")
             best_accuracy = accuracy
             print(" am salvat modelul cu best acc")

#-----------------------------------------

def _run_cnn_model(_imgs_for_train_, _imgs_for_validation_, learning_rate_cnn, numar_epoci_model, running_device, nume_fisier_log):
    best_loss = 99999.0
    best_accuracy = 0.0

    cnn_model = CnnModel_testing1()

    cnn_model = cnn_model.to(running_device)

    optimizator_cnn = SGD(cnn_model.parameters(), lr = learning_rate_cnn)

    criterion_for_cnn = torch.nn.CrossEntropyLoss()

    _plotare_grafic_ = SummaryWriter(log_dir="../logs/model_" + nume_fisier_log)

    for epoca_curenta in range(numar_epoci_model) :
        _train_cnn_model_(cnn_model, optimizator_cnn, criterion_for_cnn, _imgs_for_train_, running_device, epoca_curenta, _plotare_grafic_)

        _evaluate_cnn_model_(cnn_model, criterion_for_cnn, _imgs_for_validation_, running_device, epoca_curenta, _plotare_grafic_, best_loss, best_accuracy)

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

imagini_pentru_train = np.array([return_pixel_rgb_values(x) for x in fisier_txt_train.id])/255

imagini_pentru_validation = np.array([return_pixel_rgb_values(x) for x in fisier_txt_validation.id])/255

imagini_pentru_test = np.array([return_pixel_rgb_values(x, "../data/test/") for x in fisier_txt_test.id])/255

#-----------------------------------------

imagini_pentru_train_mean = np.mean(imagini_pentru_train, axis=(0,1,2))

imagini_pentru_validation_mean = np.mean(imagini_pentru_validation, axis=(0,1,2))

imagini_pentru_test_mean = np.mean(imagini_pentru_test, axis=(0,1,2))

#-----------------------------------------

imagini_pentru_train_std = np.std(imagini_pentru_train, axis=(0,1,2))

imagini_pentru_validation_std = np.std(imagini_pentru_validation, axis=(0,1,2))

imagini_pentru_test_std = np.std(imagini_pentru_test, axis=(0,1,2))

#-----------------------------------------

_train_images_dataloader = get_dataloader("../data/train_validation/", "../data/train_txt.txt", "train", tuple(imagini_pentru_train_mean), tuple(imagini_pentru_train_std), batch_size=7)

_validation_images_dataloader = get_dataloader("../data/train_validation/", "../data/validation_txt.txt", "validation", tuple(imagini_pentru_validation_mean), tuple(imagini_pentru_validation_std), batch_size=7)

_test_images_dataloader = get_dataloader("../data/test/", "../data/sample_submission.txt", "test", imagini_pentru_test_mean, imagini_pentru_test_std)

#-----------------------------------------

no_of_the_testing_model = 1

numar_epoci = 400

for _learning_rate in [0.01, 0.1] :

    _run_cnn_model(_train_images_dataloader, _validation_images_dataloader, _learning_rate, numar_epoci, rulare_device, "test_cnn_" + str(no_of_the_testing_model))

    no_of_the_testing_model += 1

#facem preziceri pe modelele salvate

for i in range(no_of_the_testing_model) :

    write_output_file(rulare_device, _test_images_dataloader, fisier_txt_test, i)
