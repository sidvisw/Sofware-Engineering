# Imports
import json
import numpy as np
from PIL import Image


class Dataset(object):
    '''
        A class for the dataset that will return data items as per the given index
    '''

    def __init__(self, annotation_file, transforms=None):
        '''
            Arguments:
            annotation_file: path to the annotation file
            transforms: list of transforms (class instances)
                        For instance, [<class 'RandomCrop'>, <class 'Rotate'>]
        '''
        # Initializing the variables
        self.annotation_file = annotation_file
        self.transforms = transforms
        # Importing data from annotations file
        self.data = []
        with open(self.annotation_file) as f:
            for line in f:
                self.data.append(json.loads(line))

    def __len__(self):
        '''
            return the number of data points in the dataset
        '''
        # Return the length of data
        return len(self.data)

    def __getitem__(self, idx):
        '''
            return the dataset element for the index: "idx"
            Arguments:
                idx: index of the data element.

            Returns: A dictionary with:
                image: image (in the form of a numpy array) (shape: (3, H, W))
                gt_png_ann: the segmentation annotation image (in the form of a numpy array) (shape: (1, H, W))
                gt_bboxes: N X 5 array where N is the number of bounding boxes, each 
                            consisting of [class, x1, y1, x2, y2]
                            x1 and x2 lie between 0 and width of the image,
                            y1 and y2 lie between 0 and height of the image.

            You need to do the following, 
            1. Extract the correct annotation using the idx provided.
            2. Read the image, png segmentation and convert it into a numpy array (wont be necessary
                with some libraries). The shape of the arrays would be (3, H, W) and (1, H, W), respectively.
            3. Scale the values in the arrays to be with [0, 1].
            4. Perform the desired transformations on the image.
            5. Return the dictionary of the transformed image and annotations as specified.
        '''
        # Get the data at index idx
        img_annotation = self.data[idx]
        # Open the corresponding images
        image = Image.open('./data/'+img_annotation['img_fn'])
        image2 = Image.open('./data/'+img_annotation['png_ann_fn'])
        # Perform the required transformations
        for transform in self.transforms:
            image = transform(image)
        # Do required conversions and transformations
        numpy_array = (np.transpose(np.array(image), (2, 0, 1))/255)
        numpy_array2 = np.array(image2)
        numpy_array2 = numpy_array2[:, :, np.newaxis]
        numpy_array2 = (np.transpose(numpy_array2, (2, 0, 1))/255)
        # Make the dictionery and return it
        dictionery = {'image': numpy_array, 'gt_png_ann': numpy_array2}
        return dictionery
