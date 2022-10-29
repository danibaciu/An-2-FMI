import torch
import torch.nn as nn

class CnnModel_testing2(nn.Module):
    def __init__(self):
        super().__init__()
        self.cnn_layer1_conv = nn.Sequential(
            nn.Conv2d(in_channels=3, out_channels=32, kernel_size=5, padding=1),
            nn.BatchNorm2d(num_features=32),
            nn.ReLU(),
        )

        self.cnn_layer1_maxpool_conv = nn.Sequential(
            nn.Conv2d(in_channels=32, out_channels=32, kernel_size=3, padding=1),
            nn.BatchNorm2d(num_features=32),
            nn.ReLU(),
            nn.MaxPool2d(2, 3)
        )

        self.cnn_layer2_conv = nn.Sequential(
            nn.Conv2d(in_channels=32, out_channels=64, kernel_size=3, padding=1),
            nn.BatchNorm2d(num_features=64),
            nn.ReLU(),
        )

        self.cnn_layer2_maxpool_conv = nn.Sequential(
            nn.Conv2d(in_channels=64, out_channels=64, kernel_size=3, padding=1),
            nn.BatchNorm2d(num_features=64),
            nn.ReLU(),
            nn.MaxPool2d(2, 2)
        )

        self.cnn_reduction_function1 = nn.Linear(in_features=256, out_features=7)

        self.relu_function = nn.ReLU()

    def forward(self, x):
        # print(f'in: {x.shape}')
        x = self.cnn_layer1_conv(x)
        # print(f'c1: {x.shape}')

        x = self.cnn_layer1_maxpool_conv(x)
        # print(f'c1 maxpool: {x.shape}')

        x = self.cnn_layer2_conv(x)

        # print(f'c2: {x.shape}')

        x = self.cnn_layer2_maxpool_conv(x)
        # print(f'c2 maxpool: {x.shape}')

        x = torch.flatten(x, start_dim=1)

        x = self.relu_function(x)

        x = self.cnn_reduction_function1(x)

        # print(f'f1: {x.shape}')

        return x


if __name__ == '__main__':

    x = torch.rand(size=(10, 3, 16, 16))

    model = CnnModel_testing2()

    model(x)
