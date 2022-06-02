# Imports
from my_package.model import InstanceSegmentationModel
from my_package.data import Dataset
from my_package.analysis import plot_visualization
from my_package.data.transforms import FlipImage, RescaleImage, BlurImage, CropImage, RotateImage
import numpy as np
from PIL import Image
import json
import matplotlib.pyplot as plt


def getPredictions(dictionery, segmentor):
    '''
    Function to get the image with all the segmentation.

    Arguments: dictionery of Dataset class
               InstanceSegmentationModel type object

    Return: PIL Image with all the bounding boxes
    '''
    # Get predictions from the segmentor
    boxes, masks, Class, score = segmentor(dictionery['image'])
    # Take only top 3 results
    if len(score) > 3:
        boxes = boxes[:3]
        masks = masks[:3]
        Class = Class[:3]
        score = score[:3]
    # Construct the dictionery
    dictionery['gt_bboxes'] = []
    dictionery['gt_masks'] = []
    dictionery['gt_score'] = []
    for j in range(len(score)):
        dictionery['gt_bboxes'].append([Class[j]]+boxes[j])
        dictionery['gt_masks'].append(masks[j])
        dictionery['gt_score'].append(score[j])
    # Return the image with all the bounding boxes
    return plot_visualization(dictionery, dictionery['image'])


def experiment(annotation_file, segmentor, transforms, outputs):
    '''
        Function to perform the desired experiments

        Arguments:
        annotation_file: Path to annotation file
        segmentor: The image segmentor
        transforms: List of transformation classes
        outputs: path of the output folder to store the images
    '''

    if outputs == None:
        outputs = './outputs'

    # Create the instance of the dataset.
    dataset = Dataset(annotation_file, transforms)
    data = []
    with open(annotation_file) as f:
        for line in f:
            data.append(json.loads(line))

    # Iterate over all data items.
    for i in range(len(dataset)):
        dictionery = dataset[i]

    # Get the predictions from the segmentor.
        boxes, masks, Class, score = segmentor(dictionery['image'])
        # Take top 3 results only
        if len(score) > 3:
            boxes = boxes[:3]
            masks = masks[:3]
            Class = Class[:3]
            score = score[:3]
        dictionery['gt_bboxes'] = []
        dictionery['gt_masks'] = []
        dictionery['gt_score'] = []
        for j in range(len(score)):
            dictionery['gt_bboxes'].append([Class[j]]+boxes[j])
            dictionery['gt_masks'].append(masks[j])
            dictionery['gt_score'].append(score[j])

    # Draw the segmentation maps on the image and save them.
        image = plot_visualization(
            dictionery, dictionery['image'], outputs+'/'+data[i]['img_fn'].split('/')[-1])
        image.show()

    # Do the required analysis experiments.
    image = Image.open('./data/imgs/2.jpg')

    # Display original Image
    dataset = Dataset(annotation_file, [])
    plt.subplot(2, 4, 1)
    plt.title('Original Image')
    plt.imshow(getPredictions(dataset[2], segmentor))

    # Display horizontally flipped image
    dataset = Dataset(annotation_file, [FlipImage()])
    plt.subplot(2, 4, 2)
    plt.title('Horizontally Flipped Image')
    plt.imshow(getPredictions(dataset[2], segmentor))

    # Display blurred image
    dataset = Dataset(annotation_file, [BlurImage(1)])
    plt.subplot(2, 4, 3)
    plt.title('Blurred Image')
    plt.imshow(getPredictions(dataset[2], segmentor))

    # Display twice rescaled image
    dataset = Dataset(annotation_file, [RescaleImage(
        (2*image.size[1], 2*image.size[0]))])
    plt.subplot(2, 4, 4)
    plt.title('Twice Rescaled Image')
    plt.imshow(getPredictions(dataset[2], segmentor))

    # Display half rescaled image
    dataset = Dataset(annotation_file, [RescaleImage(
        (image.size[1]//2, image.size[0]//2))])
    plt.subplot(2, 4, 5)
    plt.title('Half Rescaled Image')
    plt.imshow(getPredictions(dataset[2], segmentor))

    # Display 90 degrees right rotated image
    dataset = Dataset(annotation_file, [RotateImage(-90)])
    plt.subplot(2, 4, 6)
    plt.title('90 deg Right Rotated Image')
    plt.imshow(getPredictions(dataset[2], segmentor))

    # Display 45 degrees left rotated image
    dataset = Dataset(annotation_file, [RotateImage(45)])
    plt.subplot(2, 4, 7)
    plt.title('45 deg Left Rotated Image')
    plt.imshow(getPredictions(dataset[2], segmentor))

    # Show the matplotlib plot of images
    plt.show()


def main():
    segmentor = InstanceSegmentationModel()
    # experiment('./data/annotations.jsonl', segmentor, [FlipImage(), BlurImage(5)], None) # Sample arguments to call experiment()
    # Sample arguments to call experiment()
    experiment('./data/annotations.jsonl', segmentor, [FlipImage()], None)


if __name__ == '__main__':
    main()
