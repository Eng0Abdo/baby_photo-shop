// file name: CS112_A3_Part1_S15,16_20230100_20230211_20230246.cpp
// description: the program has 5 filters, user choose one of them to apply in his photo.
// Filter 1: Grayscale Conversion & Filter 4: Merge Images        => by   Peter Girgs Sayed          ID:20230100     S:15,16
// Filter 2: Black and White & Filter 7: Darken and Lighten Image => by   Abdelrhman Emad Mahmoud    ID:20230211     S:15,16
// Filter 3: Invert Image                                         => by   Ammar Ali Ghazi            ID:20230246     S:15,16
#include "Image_Class.h"
#include <iostream>
using namespace std;
void gray_scale() {
  string filename;
  cout << "Pls enter colored image name to turn to gray scale: ";
  cin >> filename;
  Image image(filename);
  for (int i = 0; i < image.width; i++) {
    for (int j = 0; j < image.height; j++) {
      unsigned int avg = 0;
      for (int k = 0; k < image.channels; k++) {
        avg += image(i, j, k);
      }
      avg /= 3;
      image(i, j, 0) = avg;
      image(i, j, 1) = avg;
      image(i, j, 2) = avg;
    }
  }
  cout << "Pls enter image name to store new image\n";
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";
  cin >> filename;
  image.saveImage(filename);
}
void black_and_white() {
  string photoName;
  cout << "Pls enter colored image name to turn to black and white: ";
  cin >> photoName;
  Image image(photoName);
  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      unsigned int avg = 0;
      for (int k = 0; k < 3; k++) {
        avg += image(i, j, k);
      }
      avg /= 3;
      for (int k = 0; k < 3; k++) {
        if (avg > 128) {
          image(i, j, k) = 255;
        } else if (avg < 128) {
          image(i, j, k) = 0;
        }
      }
    }
  }
  cout << "Pls enter image name to store new image\n";
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";
  cin >> photoName;
  image.saveImage(photoName);
}
void invert_image() {
  string filename;
  cout << "Pls enter colored image name to turn to inverted colors: ";
  cin >> filename;
  Image image(filename);
  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      for (int k = 0; k < 3; ++k) {
        image(i, j, k) = 255 - image(i, j, k);
      }
    }
  }
  cout << "Pls enter image name to store new image\n";
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";
  cin >> filename;
  image.saveImage(filename);
}
void merge_images() {
  string filename_1;
  string filename_2;
  cout << "Pls enter first image path: ";
  cin >> filename_1;
  cout << "Pls enter second image path: ";
  cin >> filename_2;
  Image image1(filename_1);
  Image image2(filename_2);
  Image new_image(image2.width, image2.height);
  for (int i = 0; i < new_image.width; i++) {
    for (int j = 0; j < new_image.height; j++) {
      for (int k = 0; k < new_image.channels; k++) {
        new_image(i, j, k) =
            image1(int(i * (double(image1.width)) / new_image.width),
                   int(j * (double(image1.height) / new_image.height)), k);
      }
    }
  }
  for (int i = 0; i < new_image.width; i++) {
    for (int j = 0; j < new_image.height; j++) {
      for (int k = 0; k < new_image.channels; k++) {
        new_image(i, j, k) = ((image2(i, j, k) + new_image(i, j, k)) / 2);
      }
    }
  }
  cout << "Pls enter image name to store new image\n";
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";
  string filename;
  cin >> filename;
  new_image.saveImage(filename);
}

void rotate_image() {
  string filename;
  cout << "Pls enter colored image name to turn to rotate: ";
  cin >> filename;

  Image image(filename);

  int degree_rotate = 0;
  cout << "choose degree to rotate(90, 180, 270): ";
  cin >> degree_rotate;

  Image image2(image.height, image.width);
  Image image3(image.width, image.height);

  if (degree_rotate == 270) {
      for (int i = 0; i < image.width; ++i) {
          for (int j = 0; j < image.height; ++j) {
              image2(j, image2.height - i - 1, 0) = image(i, j, 0);
              image2(j, image2.height - i - 1, 1) = image(i, j, 1);
              image2(j, image2.height - i - 1, 2) = image(i, j, 2);
          }
      }
  }
  else if (degree_rotate == 180) {
      for (int i = 0; i < image.width; ++i) {
          for (int j = 0; j < image.height; ++j) {
              image3(image3.width - i - 1, image3.height - j - 1, 0) = image(i, j, 0);
              image3(image3.width - i - 1, image3.height - j - 1, 1) = image(i, j, 1);
              image3(image3.width - i - 1, image3.height - j - 1, 2) = image(i, j, 2);
          }
      }
  }
  else {
      for (int i = 0; i < image.width; ++i) {
          for (int j = 0; j < image.height; ++j) {
              image2(image2.width - j - 1, i, 0) = image(i, j, 0);
              image2(image2.width - j - 1, i, 1) = image(i, j, 1);
              image2(image2.width - j - 1, i, 2) = image(i, j, 2);
          }
      }
  }

  cout << "Pls enter image name to store new image\n";
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";

  cin >> filename;
  if (degree_rotate == 180) {
      image3.saveImage(filename);
  }
  else {
      image2.saveImage(filename);
  }
}

void darken_lighten() {
  string photo;
  cout << "please inter your coloured photo: ";
  cin >> photo;
  Image Photo(photo);
  string choice;
  cout << "please inter what do you want \n";
  cout << "[A] to Lighten your image\n";
  cout << "[B] to Darken your image\n>> ";
  cin >> choice;
  if (choice == "A" || choice == "a") {
    for (int i = 0; i < Photo.width; i++) {
      for (int j = 0; j < Photo.height; j++) {
        int red = Photo(i, j, 0) * 2;
        int green = Photo(i, j, 1) * 2;
        int blue = Photo(i, j, 2) * 2;
        if (red > 255) {
          red = 255;
        }
        if (green > 255) {
          green = 255;
        }
        if (blue > 255) {
          blue = 255;
        }
        Photo(i, j, 0) = red;
        Photo(i, j, 1) = green;
        Photo(i, j, 2) = blue;
      }
    }
  } else if (choice == "B" || choice == "b") {
    for (int i = 0; i < Photo.width; i++) {
      for (int j = 0; j < Photo.height; j++) {
        Photo(i, j, 0) /= 2;
        Photo(i, j, 1) /= 2;
        Photo(i, j, 2) /= 2;
      }
    }
  }
  string photoname;
  cout << "Pls enter image name to store new image and specify extension .jpg, "
          ".bmp, .png, .tga: \n";
  cin >> photoname;
  Photo.saveImage(photoname);
  system(photoname.c_str());
}

void resize()
{
    string photoName;
    cout << "Pls enter your image name to resize it: ";
    cin >> photoName;
    Image image(photoName);
    int new_width,new_height;
    cout << "pls enter your photo width\n";
    cin >> new_width;
    cout << "pls enter your photo height ";
    cin >> new_height;
    Image new_image(new_width,new_height);
    double width_ratio,height_ratio;
    width_ratio = (static_cast<double>(image.width) / static_cast<double>(new_width));
    height_ratio = (static_cast<double>(image.height) / static_cast<double>(new_height));
    for (int i = 0; i < new_width; i++) {
        for (int j = 0; j < new_height; j++) {
            for(int k = 0; k < 3; k++) {
            new_image(i,j,k) = image(round(i*width_ratio),round(j*height_ratio),k);
            }
        }
    }

  cout << "Pls enter image name to store new image and specify extension .jpg, .bmp, .png, .tga: \n";
    cin >> photoName;
    new_image.saveImage(photoName);
    system(photoName.c_str());
}

void purple_look() {
    string filename;
    cout << "Pls enter colored image name to turn to gray scale: ";
    cin >> filename;
    Image image(filename);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int purple = 0; 
            for (int k = 1; k < 3; ++k) {
                purple += image(i, j, k);
            }
            purple /= 2;
            for (int k = 1; k < 3; ++k) {
                image(i, j, k) = purple;
            }
        }
    }
    cout << "Pls enter image name to store new image and specify extension .jpg, .bmp, .png, .tga: \n";
    cin >> filename;
    image.saveImage(filename);
    system(filename.c_str());

}


int main(){
  cout << "welcome, that program add some filters to your picture,\n";
  while (true) {
    cout << "please choose filter: \n"
            "1)filter_1(gray_scale).\n"
            "2)filter_2(black_and_white).\n"
            "3)filter_3(invert_image).\n"
            "4)filter_4(merge_images).\n"
            "5)filter_7(darken_lighten).\n"
            "6)filter_6(rotate_image).\n"
            "7)filter_11(Resizing Images).\n"
            "8)filter_16(purple_look).\n"
            "9)exit.\n";
    string choice = "";
    getline(cin, choice);
    if(choice.length() != 1) {choice = '9';}
    if (choice[0] == '9') {break;}
    else if (choice[0] == '1') {gray_scale();}
    else if (choice[0] == '2') {black_and_white();}
    else if (choice[0] == '3') {invert_image();}
    else if (choice[0] == '4') {merge_images();}
    else if (choice[0] == '5') {darken_lighten();}
    else if (choice[0] == '6') {rotate_image();}
    else if (choice[0] == '7') {resize();}
    else if (choice[0] == '8') {purple_look();}
    else {
      cout << "enter valid number,\n";
      continue;
    }
    cin.ignore();
  }
  return 0;
}