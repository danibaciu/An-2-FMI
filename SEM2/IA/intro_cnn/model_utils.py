import torch
import torch.nn as nn

class ToyModel(nn.Module):
    def __init__(self):
        super().__init__()
        self.layer1 = nn.Sequential(
            nn.Conv2d(in_channels=3, out_channels=64, kernel_size=7, stride=2, padding="valid"),

            # Please read the paper or some blog
            nn.BatchNorm2d(num_features=64), # la fel cu out channels

            # this is a must
            nn.ReLU(), # Please read paper

            # # this is optional
            # nn.MaxPool2d(kernel_size=2)
        )
        self.layer2 = nn.Sequential(
            nn.Conv2d(in_channels=64, out_channels=128, kernel_size=7, stride=2, padding="valid"),

            # Please read the paper or some blog
            nn.BatchNorm2d(num_features=128), # la fel cu out channels

            # this is a must
            nn.ReLU(), # Please read paper

            # # this is optional
            # nn.MaxPool2d(kernel_size=2)
        )
        self.final = nn.Linear(in_features=128, out_features=2)

    def forward(self, x):
        # x.shape = (3, 224, 224)
        # Convolutia fiind valida, face si downsize
        x = self.layer1(x)
        # x.shape = (64, 109, 109)
        x = self.layer2(x)
        # x.shape = (128, 52, 52)

        # This is a trick. Remove me
        # x.shape [N, 128, 52, 52] -> [N, 128, 1, 1]
        x = nn.functional.avg_pool2d(x, (52, 52))
        # [N, C, 1, 1] -> [N, C]
        x = torch.squeeze(x)

        # Atentie la shape [N, C]
        x = self.final(x)

        return x


if __name__ == '__main__':
    #                   (N, C,   H,   W)
    x = torch.rand(size=(1, 3, 224, 224))
    model = ToyModel()

    # Debug purpuse
    model(x)
