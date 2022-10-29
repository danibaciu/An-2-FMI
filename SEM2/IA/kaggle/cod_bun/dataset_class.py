import os
import torchvision.transforms as transforms

from torch.utils.data import Dataset, DataLoader
from PIL import Image

class Data_Class_For_CNN(Dataset):
    def __init__(
            self,
            files_directory,
            file_txt_with_img_names,
            transformari_de_baza=None,
            augmentari_date=None,
            mode_de_folosire="test"
    ):
        self.files_directory = files_directory
        self.mode_images, self.mode_labels = self.get_imgs_and_labels(file_txt_with_img_names)
        self.transformari_de_baza = transformari_de_baza
        self.augmentari_date = augmentari_date
        self.mode_de_folosire = mode_de_folosire

    @staticmethod
    def get_imgs_and_labels(file_txt_with_img_names):
        file_lines = [x.strip() for x in open(file_txt_with_img_names, 'r').readlines()]

        mode_images = [lne.split(',')[0] for lne in file_lines]
        mode_labels = [int(lne.split(',')[1]) for lne in file_lines]

        return mode_images, mode_labels

    def __getitem__(self, index_to_image):
        path_to_image = os.path.join(self.files_directory, self.mode_images[index_to_image])

        this_image = Image.open(path_to_image)

        clasa = self.mode_labels[index_to_image]

        this_image_transformed = self.transformari_de_baza(this_image)

        if self.mode_de_folosire == "train":
            this_image_transformed = self.augmentari_date(this_image_transformed)

        return this_image_transformed, clasa

    def __len__(self):
        return len(self.mode_images)


def get_dataloader(files_directory, file_txt_with_img_names, mod_de_folosire, medie, deviatie_standard, dimensiune_batch=2, rearanjari=False):
    transformari_de_baza = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize(
            mean=medie,  # (R, G, B)
            std=deviatie_standard  # (R, G, B)
        )
    ])

    augmentari_date = transforms.Compose([
        transforms.RandomHorizontalFlip(p=0.2),
        transforms.RandomInvert(p=0.45),
        transforms.RandomAutocontrast(p=0.45),
    ])

    data_for_return = Data_Class_For_CNN(
        files_directory=files_directory,
        file_txt_with_img_names=file_txt_with_img_names,
        transformari_de_baza=transformari_de_baza,
        augmentari_date=augmentari_date,
        mode_de_folosire=mod_de_folosire
    )

    return DataLoader(
        data_for_return,
        batch_size=dimensiune_batch,
        shuffle=rearanjari
    )


if __name__ == '__main__':

    # train_dataloader = get_dataloader("./data/train_validation/", "./data/train_txt.txt", "train", (0.5,0.5,0.5), (0.5,0.5,0.5))

    pass

