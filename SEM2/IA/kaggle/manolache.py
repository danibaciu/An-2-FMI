# This file contains the custom model.

import torch
import torch.nn as nn

class CustomNet(nn.Module):
    """ Our custom model.
    """
    def __init__(self):
        super(CustomNet, self).__init__()

        self.conv1 = nn.Sequential(
            nn.Conv2d(3, 64, 3, padding=1),
            nn.BatchNorm2d(64),
            nn.ReLU(),)
        self.conv11 = nn.Sequential(
            nn.Conv2d(64, 64, 3, padding=1),
            nn.BatchNorm2d(64),
            nn.ReLU(),
            nn.MaxPool2d(2, 2)
        )

        self.conv2 = nn.Sequential(
            nn.Conv2d(64, 128, 3, padding=1),
            nn.BatchNorm2d(128),
            nn.ReLU(),)
        self.conv22 = nn.Sequential(

            nn.Conv2d(128, 128, 3, padding=1),
            nn.BatchNorm2d(128),
            nn.ReLU(),
            nn.MaxPool2d(2, 1)
        )

        self.conv3 = nn.Sequential(
            nn.Conv2d(128, 256, 3, padding=1),
            nn.BatchNorm2d(256),
            nn.ReLU(),)
        self.conv33 = nn.Sequential(

            nn.Conv2d(256, 256, 3),
            nn.BatchNorm2d(256),
            nn.ReLU(),
            nn.MaxPool2d(2, 1)
        )

        self.conv4 = nn.Sequential(
            nn.Conv2d(256, 512, 3),
            nn.BatchNorm2d(512),
            nn.ReLU(),)
        self.conv44 = nn.Sequential(

            nn.Conv2d(512, 512, 3),
            nn.BatchNorm2d(512),
            nn.ReLU(),
            nn.MaxPool2d(2, 1)
        )

        self.conv5 = nn.Sequential(
            nn.Conv2d(512, 1024, 3),
            nn.BatchNorm2d(1024),
            nn.ReLU(),)
        self.conv55 = nn.Sequential(

            nn.Conv2d(1024, 1024, 3),
            nn.BatchNorm2d(1024),
            nn.ReLU(),
            nn.MaxPool2d(2, 1)
        )

        self.fc1 = nn.Linear(4096, 1024)

        self.fc2 = nn.Linear(1024, 256)

        self.fc3 = nn.Linear(256, 8)

        self.relu = nn.ReLU()

    def forward(self, x):

        # print(f'in: {x.shape}')
        x = self.conv1(x)
        # print(f'c1: {x.shape}')
        x = self.conv11(x)
        # print(f'c11: {x.shape}')

        x = self.conv2(x)
        # print(f'c2: {x.shape}')
        x = self.conv22(x)
        # print(f'c22: {x.shape}')

        x = self.conv3(x)
        # print(f'c3: {x.shape}')
        x = self.conv33(x)
        # print(f'c33: {x.shape}')

        x = self.conv4(x)
        # print(f'c4: {x.shape}')

        x = self.conv44(x)
        # print(f'c44: {x.shape}')

        x = self.conv5(x)
        # print(f'c5: {x.shape}')

        x = self.conv55(x)
        # print(f'c55: {x.shape}')

        x = x.view(x.shape[0], -1)

        x = self.relu(x)

        x = self.fc1(x)

        x = self.relu(x)

        x = self.fc2(x)

        x = self.relu(x)

        x = self.fc3(x)

        return x


if __name__ == '__main__':
    x = torch.rand(size=(32, 3, 16, 16))
    model = CustomNet()

    model(x)