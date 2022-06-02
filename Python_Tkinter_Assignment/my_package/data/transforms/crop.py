# Imports
import random


class CropImage(object):
    '''
        Performs either random cropping or center cropping.
    '''

    def __init__(self, shape, crop_type='center'):
        '''
            Arguments:
            shape: output shape of the crop (h, w)
            crop_type: center crop or random crop. Default: center
        '''

        # Write your code here
        self.shape = shape
        self.crop_type = crop_type

    def __call__(self, image):
        '''
            Arguments:
            image (numpy array or PIL image)

            Returns:
            image (numpy array or PIL image)
        '''

        # Write your code here
        width, height = image.size
        if self.crop_type == 'center':
            return image.crop((int((width-self.shape[1])/2), int((height-self.shape[0])/2), int((width+self.shape[1])/2), int((height+self.shape[0])/2)))
        elif self.crop_type == 'random':
            x = random.randint(0, width-self.shape[1]+1)
            y = random.randint(0, height-self.shape[0]+1)
            return image.crop((int(x), int(y), int(x+self.shape[1]), int(y+self.shape[0])))
