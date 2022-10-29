import os
import numpy as np
import torchvision.transforms as transforms

from torch.utils.data import Dataset, DataLoader
from PIL import Image


class LoadDataset(Dataset):
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

def calculate_base_transforms(image_array):
    return transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize(
            mean=image_array.mean(axis=(0,1,2)),
            std=np.std(image_array, axis=(0,1,2))
        )
    ])

def return_pixel_rgb_values(img_name, path = "./data/train_validation/") :
    return np.array(list(Image.open(path + img_name).getdata())).reshape((16, 16, 3))

def get_dataloader(data_dir, data_txt, mode, batch_size=2, shuffle=False):

    b

    augmentation_transform_data = transforms.Compose([
        transforms.RandomHorizontalFlip(p=0.2),
        # transforms.RandAugment()
    ])

    dataset = LoadDataset(
        images=images,
        labels=labels,
        base_transforms=base_transforms_,
        augs=augs_,
        mode=mode
    )

    dataloader = DataLoader(
        dataset,
        batch_size=batch_size,
        shuffle=shuffle
    )

    return dataloader