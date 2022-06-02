# Imports
from PIL import Image, ImageDraw, ImageFont, ImageOps
import numpy as np


# Write the required arguments
def plot_visualization(dictionery, image, saveLocation=None, segmentation=True, boundingBoxes=True):

    # The function should plot the predicted segmentation maps and the bounding boxes on the images and save them.
    # Tip: keep the dimensions of the output image less than 800 to avoid RAM crashes.

    # Scale up the numpy array of image
    image = (np.transpose(image, (1, 2, 0)))*255
    # Convert numpy array to PIL Image object
    image = Image.fromarray(image.astype('uint8'), 'RGB')
    # Iterate over all dictionery elements
    for i in range(len(dictionery['gt_bboxes'])):
        if segmentation:
            Mask = (np.transpose(dictionery['gt_masks'][i], (1, 2, 0)))*255

            # Making the mask numpy array from (H, W, 1) to (H, W)
            temp = []
            for k in range(image.size[1]):
                temp1 = []
                for j in range(image.size[0]):
                    temp1.append(Mask[k][j][0])
                temp.append(temp1)
            Mask = np.array(temp)
            # Creating a temporary image to Mask our output image with
            # R, G, B colours respectively
            img = []
            for l in range(image.size[1]):
                temp = []
                for m in range(image.size[0]):
                    if Mask[l][m] == 0:
                        temp.append([0, 0, 0])
                    else:
                        if i == 0:
                            temp.append([Mask[l][m], 0, 0])
                        elif i == 1:
                            temp.append([0, Mask[l][m], 0])
                        else:
                            temp.append([0, 0, Mask[l][m]])
                img.append(temp)
            img = np.array(img)

            img = Image.fromarray(img.astype('uint8'), 'RGB')
            Mask = Image.fromarray(Mask.astype('uint8'), 'L')
            # Using composite function to mask the image
            image = Image.composite(img, image, Mask)
        if boundingBoxes:
            # Draw the corresponding boxes and classes
            Draw = ImageDraw.Draw(image)
            Draw.rectangle([dictionery['gt_bboxes'][i][1],
                            dictionery['gt_bboxes'][i][2]], outline='green', width=3)
            Font = ImageFont.truetype('times.ttf', 15)
            Draw.text((dictionery['gt_bboxes'][i][1][0], dictionery['gt_bboxes'][i][1][1]-19),
                      dictionery['gt_bboxes'][i][0]+str(dictionery['gt_score'][i]), font=Font, fill=(255, 255, 255))

    if saveLocation:
        # Save the image if save location is given
        image.save(saveLocation)
    # Return the image after modifications
    return image
