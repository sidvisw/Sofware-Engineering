import setuptools

with open("README.md", "r", encoding="utf-8") as f:
    long_description = f.read()

setuptools.setup(
    name="Assignment3_20CS10082",  # Replace with your own username
    version="0.0.1",
    author="Sidharth Vishwakarma",
    author_email="sid1232100@gmail.com",
    description="Image Segmentor Package",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/dasabir/CS29006_SW_Lab_Spr2022",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: IIT License",
        "Operating System :: OS Independent",
    ],
    python_requires='>=3.6',
)
