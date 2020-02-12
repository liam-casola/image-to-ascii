This program renders an image in ascii characters. There are 3 arguments it will accept in this order.
```sh
$ ./image2ascii [filename] [width] [invert]
```

  1. filname: the full filename of the image. If the image is not in the same directory as the program you must specify the full path
  2. width: the number of characters wide the ascii representation should be. This value must be an integer greater than 0. If not specified the default width is 100 characters.
  3. invert: inverts the ascii representation so that darks become lights and lights become darks. this value can be 1 or 0. If not specified the default value is 0 where the ascii image is expected to have a white background and dark text
    
Images heights are automatically scaled with the width and then cut in half to stay proportional as text characters height are approximatly twice their width. The resizing method utalizes nearest neighbor.

The stb_image.h header file is utalized in this project to read image file formats
