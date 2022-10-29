import os
import torchvision.transforms as transforms
import numpy as np

from torch.utils.data import Dataset, DataLoader
from PIL import Image

class ToyDataset(Dataset) :
    def __init__(
            self,
            data_dir,
            data_txt,
            base_transforms = None,
            augs = None,
            mode="test"
    ):
        self.data_dir = data_dir
        self.images, self.labels = self._get_imgs_and_labels(data_txt)
        self.base_transforms = base_transforms
        self.augs = augs
        self.mode = mode

    @staticmethod
    def _get_imgs_and_labels(data_txt):
        with open(data_txt, 'r') as f:
            lines = [x.strip() for x in f.readlines()]

        images = [x.split(',')[0] for x in lines]
        labels = [int(x.split(',')[1]) - 1 for x in lines]

        return images, labels

    def __getitem__(self, idx):
        # Create the path to the image
        img_path = os.path.join(self.data_dir, self.images[idx])

        # Read the image
        img = Image.open(img_path)

        # Read the image label
        label = self.labels[idx]

        # Apply base transforms (all the modes)
        img_transformed = self.base_transforms(img)

        # Appy augs
        if self.mode == "train":
            img_transformed = self.augs(img_transformed)

        # # Delete me later (used only to see augmented image)
        # test = (np.transpose(img_transormed.numpy(), (1, 2, 0)) * 255).astype(np.uint8)
        # test = Image.fromarray(test)

        return img_transformed, label

    def __len__(self):
        return len(self.images)

def get_dataloader(data_dir, data_txt, mode, batch_size=2, shuffle=False):
    base_transforms_ = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize(
            mean=(0.5, 0.5, 0.5),  # (R, G, B)
            std=(0.2, 0.1, 0.3)  # (R, G, B)
        )
    ])

    augs_ = transforms.RandomHorizontalFlip(p=1.)

    dataset = ToyDataset(
        data_dir=data_dir,
        data_txt=data_txt,
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


if __name__ == "__main__" :

    # DATA_DIR = "C:/Users/danib/Downloads/toy_data"
    # DATA_TXT = "C:/Users/danib/Downloads/toy_data/train.txt"
    #
    # base_transforms_ = transforms.Compose([
    #     transforms.ToTensor(),
    #     transforms.Normalize(
    #         mean=(0.5, 0.5, 0.5),  # (R, G, B)
    #         std=(0.2, 0.1, 0.3)  # (R, G, B)
    #     )
    # ])
    #
    # augs_ = transforms.RandomHorizontalFlip(p=1.)
    #
    # dataset = ToyDataset(
    #     data_dir=DATA_DIR,
    #     data_txt=DATA_TXT,
    #     base_transforms=base_transforms_,
    #     augs=augs_
    # )
    #
    # next(iter(dataset))

    print("lalalalallala")

