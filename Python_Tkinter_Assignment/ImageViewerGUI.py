####### REQUIRED IMPORTS FROM THE PREVIOUS ASSIGNMENT #######
import tkinter
from my_package.model import InstanceSegmentationModel
from my_package.data import Dataset
from my_package.analysis import plot_visualization
from my_package.data.transforms import FlipImage, RescaleImage, BlurImage, CropImage, RotateImage
from PIL import Image

####### ADD THE ADDITIONAL IMPORTS FOR THIS ASSIGNMENT HERE #######
from tkinter import *
from tkinter import filedialog
from PIL import Image,ImageTk
from PIL.Image import new
from functools import partial

# create a temporaray image to show the output
outputImage = new('RGB', (500, 500))

# Define the function you want to call when the filebrowser button is clicked.
def fileClick(clicked, dataset, segmentor):

	####### CODE REQUIRED (START) #######
	# This function should pop-up a dialog for the user to select an input image file.
	# Once the image is selected by the user, it should automatically get the corresponding outputs from the segmentor.
	# Hint: Call the segmentor from here, then compute the output images from using the `plot_visualization` function and save it as an image.
	# Once the output is computed it should be shown automatically based on choice the dropdown button is at.
	# To have a better clarity, please check out the sample video.
	file = filedialog.askopenfilename(initialdir = "/",title = "Select file",filetypes = (("jpeg files","*.jpg"),("all files","*.*")))
	e.delete(0,END)
	e.insert(0,file)
	dictionery = dataset[int(e.get()[-5])]
	boxes, masks, Class, score = segmentor(dictionery['image'])
	if len(score) > 3:
		boxes = boxes[:3]
		masks = masks[:3]
		Class = Class[:3]
		score = score[:3]
	dictionery['gt_bboxes']=[]
	dictionery['gt_masks']=[]
	dictionery['gt_score']=[]
	for j in range(len(score)):
		dictionery['gt_bboxes'].append([Class[j]]+boxes[j])
		dictionery['gt_masks'].append(masks[j])
		dictionery['gt_score'].append(score[j])
	plot_visualization(dictionery,dictionery['image'],'./outputs/segmentationImage.jpg',True,False)
	plot_visualization(dictionery,dictionery['image'],'./outputs/boundingBoxesImage.jpg',False,True)
	####### CODE REQUIRED (END) #######

# `process` function definition starts from here.
# will process the output when clicked.
def process(clicked):
	
	####### CODE REQUIRED (START) #######
	# Should show the corresponding segmentation or bounding boxes over the input image wrt the choice provided.
	# Note: this function will just show the output, which should have been already computed in the `fileClick` function above.
	# Note: also you should handle the case if the user clicks on the `Process` button without selecting any image file.
	if e.get()=="":
		Root=Toplevel()
		Root.title("Error")
		Root.geometry("300x100")
		Label(Root,text="Please select an image file").pack()
		Button(Root,text="OK",command=Root.destroy).pack()
		Root.mainloop()
		return
	if clicked.get()=='Segmentation':
		Root = Toplevel()
		Root.title("Segmentation Image")
		originalImage = Image.open(e.get())
		outputImage = Image.open('./outputs/segmentationImage.jpg')
		originalImage = ImageTk.PhotoImage(originalImage)
		outputImage = ImageTk.PhotoImage(outputImage)
		originalImageLabel = Label(Root, image=originalImage)
		outputImageLabel = Label(Root, image=outputImage)
		originalImageLabel.grid(row=0, column=0)
		outputImageLabel.grid(row=0, column=1)
		Root.mainloop()
	else:
		Root = Toplevel()
		Root.title("Bounding Boxes Image")
		originalImage = Image.open(e.get())
		outputImage = Image.open('./outputs/boundingBoxesImage.jpg')
		originalImage = ImageTk.PhotoImage(originalImage)
		outputImage = ImageTk.PhotoImage(outputImage)
		originalImageLabel = Label(Root, image=originalImage)
		outputImageLabel = Label(Root, image=outputImage)
		originalImageLabel.grid(row=0, column=0)
		outputImageLabel.grid(row=0, column=1)
		Root.mainloop()
	####### CODE REQUIRED (END) #######

# `main` function definition starts from here.
if __name__ == '__main__':

	####### CODE REQUIRED (START) ####### (2 lines)
	# Instantiate the root window.
	# Provide a title to the root window.
	root=Tk()
	root.title("Image Segmentation and Bounding Boxes")
	####### CODE REQUIRED (END) #######

	# Setting up the segmentor model.
	annotation_file = './data/annotations.jsonl'
	transforms = []

	# Instantiate the segmentor model.
	segmentor = InstanceSegmentationModel()
	# Instantiate the dataset.
	dataset = Dataset(annotation_file, transforms=transforms)

	
	# Declare the options.
	options = ["Segmentation", "Bounding-box"]
	clicked = StringVar()
	clicked.set(options[0])

	e = Entry(root, width=70)
	e.grid(row=0, column=0)

	####### CODE REQUIRED (START) #######
	# Declare the file browsing button
	fileBrowsingbutton = Button(root, text="Browse", command=lambda: fileClick(clicked, dataset, segmentor))
	fileBrowsingbutton.grid(row=0, column=1)
	####### CODE REQUIRED (END) #######

	####### CODE REQUIRED (START) #######
	# Declare the drop-down button
	dropdown = OptionMenu(root, clicked, *options)
	dropdown.grid(row=0, column=2)
	####### CODE REQUIRED (END) #######

	# This is a `Process` button, check out the sample video to know about its functionality
	myButton = Button(root, text="Process", command=partial(process, clicked))
	myButton.grid(row=0, column=3)

	
	####### CODE REQUIRED (START) ####### (1 line)
	# Execute with mainloop()
	root.mainloop()
	####### CODE REQUIRED (END) #######