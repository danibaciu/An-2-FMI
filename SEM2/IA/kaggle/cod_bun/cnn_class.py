import torch
import torch.nn as nn

class CnnModel_testing1(nn.Module):
    def __init__(self):
        super().__init__()
        self.cnn_layer1_conv = nn.Sequential(
            nn.Conv2d(in_channels=3, out_channels=32, kernel_size=3, padding=1),
            nn.BatchNorm2d(num_features=32),
            nn.ReLU(),
        )

        self.cnn_layer1_maxpool_conv = nn.Sequential(
            nn.Conv2d(in_channels=32, out_channels=32, kernel_size=3, padding=1),
            nn.BatchNorm2d(num_features=32),
            nn.ReLU(),
            nn.MaxPool2d(2, 2)
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

        self.cnn_layer3_conv = nn.Sequential(
            nn.Conv2d(in_channels=64, out_channels=128, kernel_size=3, padding=1),
            nn.BatchNorm2d(num_features=128),
            nn.ReLU(),
        )

        self.cnn_layer3_maxpool_conv = nn.Sequential(
            nn.Conv2d(in_channels=128, out_channels=128, kernel_size=3, padding=1),
            nn.BatchNorm2d(num_features=128),
            nn.ReLU(),
            nn.MaxPool2d(2, 2)
        )

        self.cnn_reduction_function1 = nn.Linear(in_features=512, out_features=7)

        # self.cnn_reduction_function1 = nn.Linear(in_features=512, out_features=128)
        #
        # self.cnn_reduction_function2 = nn.Linear(in_features=128, out_features=7)

        self.relu_function = nn.ReLU()

    def forward(self, x):
        # print(f'intrare : {x.shape}')
        x = self.cnn_layer1_conv(x)
        # print(f'dupa layer1: {x.shape}')

        x = self.cnn_layer1_maxpool_conv(x)
        # print(f'dupa layer1 maxpool: {x.shape}')

        x = self.cnn_layer2_conv(x)
        # print(f'dupa layer2: {x.shape}')

        x = self.cnn_layer2_maxpool_conv(x)
        # print(f'dupa layer2 maxpool: {x.shape}')

        x = self.cnn_layer3_conv(x)
        # print(f'dupa layer3: {x.shape}')

        x = self.cnn_layer3_maxpool_conv(x)
        # print(f'dupa layer3 maxpool: {x.shape}')

        x = torch.flatten(x, start_dim=1)

        x = self.relu_function(x)

        x = self.cnn_reduction_function1(x)

        # print(f'dupa fct1: {x.shape}')

        # x = self.relu_function(x)
        #
        # x = self.cnn_reduction_function2(x)
        # print(f'dupa fct2: {x.shape}')

        return x


if __name__ == '__main__':

    x = torch.rand(size=(93, 3, 16, 16))

    model = CnnModel_testing1()

    model(x)