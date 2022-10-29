import os
import torch

from torch.nn.functional import softmax
from tqdm import tqdm
from dataset_load import get_dataloader
from model_utils import ToyModel
from torch.optim import SGD
from torch.utils.tensorboard import SummaryWriter

def main(data_dir, data_txt) :
    # hyper params
    lr = 0.1
    epochs = 10
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

    # init the data model
    train_data_loader = get_dataloader(data_dir, data_txt, mode="train", shuffle=True)

    # init the model
    model = ToyModel()
    model = model.to(device)

    # init the optimizer
    optimizer = SGD(params=model.parameters(), lr=lr)

    # init the loss function
    criterion = torch.nn.CrossEntropyLoss()

    writer = SummaryWriter(log_dir="./")

    # train the model
    for epoch in range(epochs):
        # train
        train_model(model, optimizer, criterion, train_data_loader, device, epoch, writer)

        # validate
        eval_model(model, criterion, train_data_loader, device, epoch, writer)


def train_model(model, optimizer, criterion, data_loader, device, epoch, writer):
    # pune modelul in modul de train
    # sunt stocati gradientii si folositi la update
    model.train()

    all_loss = 0.

    for images, labels in tqdm(data_loader, desc="Train") :
        images = images.to(device)
        labels = labels.to(device)

        # compute the scors for each image per class
        logits = model(images)

        # compute the loss
        loss = criterion(logits, labels)

        # curata valoarea gradientilor din fiecare param din model
        optimizer.zero_grad()

        # calculam gradientii in raport cu fct de loss pt fiecare param din model
        loss.backward()

        # update al parametrilor
        optimizer.step()

        all_loss += loss.item() * len(images)

        print(loss.item())

    all_loss = all_loss / len(data_loader.dataset)

    writer.add_scalar(tag="Loss/Train",scalar_value=all_loss, global_step=epoch)
    writer.flush()

def eval_model(model, criterion, data_loader, device, epoch, writer):
    # pune modelul in modul de train
    # sunt stocati gradientii si folositi la update
    model.eval()
    all_loss = 0.0
    true_preds = 0

    with torch.no_grad() :
        for images, labels in tqdm(data_loader, desc="Eval") :
            images = images.to(device)
            labels = labels.to(device)

            # compute the scors for each image per class
            logits = model(images)

            # compute the loss
            loss = criterion(logits, labels)

            # compute accuracy
            scores = softmax(logits, dim=1)

            pred_label = torch.argmax(scores, dim=1)

            true_preds += (pred_label == labels).sum()

            all_loss += loss.item() * len(images)

            print(loss.item())

        acc = true_preds / len(data_loader.dataset)
        writer.add_scalar(scalar_value=acc, tag="Acc/Valid", global_step=epoch)

        all_loss = all_loss / len(data_loader.dataset)
        writer.add_scalar(scalar_value=all_loss, tag="Loss/Valid", global_step=epoch)
        writer.flush()

if __name__ == '__main__':
    DATA_DIR = "C:/Users/danib/Downloads/toy_data"
    DATA_TXT = "C:/Users/danib/Downloads/toy_data/train.txt"
    main(DATA_DIR, DATA_TXT)
