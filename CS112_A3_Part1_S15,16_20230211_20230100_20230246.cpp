// file name: CS112_A3_Part1_S15,16_20230100_20230211_20230246.cpp
// description: the program has 5 filters, user choose one of them to apply in
// his photo. Filter 1: Grayscale Conversion & Filter 4: Merge Images        =>
// by   Peter Girgs Sayed          ID:20230100     S:15,16 Filter 2: Black and
// White & Filter 7: Darken and Lighten Image => by   Abdelrhman Emad Mahmoud
// ID:20230211     S:15,16 Filter 3: Invert Image => by   Ammar Ali Ghazi
// ID:20230246     S:15,16

#include "Image_Class.h"
#include <cmath>
#include <iostream>
#include <random>
#include <string>

using namespace std;
void choose_ext(string & extension) {
    cout << "inter photo name to store it: ";
    cin >> extension;
    cout << "choose extension:  [a] jpg     [b] bmp     [c] png     [d] tga\n";
    while (true)
    {
        string choice;
        cin >> choice;
        if(choice == "a"|| choice == "A") {
            extension += ".jpg";
            break;
        }
        else if(choice == "b"|| choice == "B") {
            extension += ".bmp";
            break;
        }
        else if(choice == "c"|| choice == "C") {
            extension += ".png";
            break;
        }
        else if(choice == "d"|| choice == "D") {
            extension += ".tga";
            break;
        }
        else {
            cout << "enter a valid choice \n";
        }
        cin.ignore();
    }
}

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

Image black_and_white(string photoName) {
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
  return image;
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

Image flip(string photoName) {
  string choice;
  cout << "[a] to Flip Vertically";
  cout << "\n[b] to Flip Horizontally\n";
  cin >> choice;
  Image image(photoName);
  Image image1(photoName);
  if (choice == "a" || choice == "A") {
    for (int i = 0; i < image.width; ++i) {
      for (int j = 0; j < image.height; ++j) {
        for (int k = 0; k < 3; ++k) {
          image(i, j, k) = image1(i, image.height - j - 1, k);
        }
      }
    }
  } else if (choice == "b" || choice == "B") {
    for (int i = 0; i < image.width; ++i) {
      for (int j = 0; j < image.height; ++j) {
        for (int k = 0; k < 3; ++k) {
          image(i, j, k) = image1(image.width - i - 1, j, k);
        }
      }
    }
  }
  return image;
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
  } else if (degree_rotate == 180) {
    for (int i = 0; i < image.width; ++i) {
      for (int j = 0; j < image.height; ++j) {
        image3(image3.width - i - 1, image3.height - j - 1, 0) = image(i, j, 0);
        image3(image3.width - i - 1, image3.height - j - 1, 1) = image(i, j, 1);
        image3(image3.width - i - 1, image3.height - j - 1, 2) = image(i, j, 2);
      }
    }
  } else {
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
  } else {
    image2.saveImage(filename);
  }
}

Image darken_lighten(string photo) {
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
  return Photo;
}

void crop() {
  string filename_1;
  cout << "Please enter image path";
  cin >> filename_1;

  Image cropped_image(600, 600);
  Image image(filename_1);

  for (int i = 0; i < 600; i++) {
    for (int j = 0; j < 600; j++) {
      for (int k = 0; k < image.channels; k++) {
        cropped_image(i, j, k) = image(700 + i, 700 + j, k);
      }
    }
  }
  cropped_image.saveImage("cropped.png");
}

void frame() {
  string filename;
  cout << "Pls enter colored image name to turn to gray scale: ";
  cin >> filename;

  Image image(filename);

  for (int i = 0; i < image.width / 100; ++i) {
    for (int j = 0; j < image.height; ++j) {
      image(i, j, 0) = 93;
      image(i, j, 1) = 63;
      image(i, j, 2) = 211;

      image(image.width - i - 1, j, 0) = 93;
      image(image.width - i - 1, j, 1) = 63;
      image(image.width - i - 1, j, 2) = 211;
    }
  }

  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height / 100; ++j) {
      image(i, j, 0) = 93;
      image(i, j, 1) = 63;
      image(i, j, 2) = 211;

      image(i, image.height - j - 1, 0) = 93;
      image(i, image.height - j - 1, 1) = 63;
      image(i, image.height - j - 1, 2) = 211;
    }
  }

  for (int j = 0; j < image.height; ++j) {
    for (int k = 0; k < 3; ++k) {
      image(0, j, k) = 255;

      image(image.width - 1, j, k) = 255;
    }
  }

  for (int i = 0; i < image.width; ++i) {
    for (int k = 0; k < 3; ++k) {
      image(i, 0, k) = 255;

      image(i, image.height - 1, k) = 255;
    }
  }

  int simple_fancy = 0;
  cout << "1)simple.\n2)fancy.\n>> ";
  cin >> simple_fancy;

  if (simple_fancy == 2) {
    for (int j = 0; j < image.height; ++j) {
      for (int k = 0; k < 3; ++k) {
        image(image.width / 100, j, k) = 255;

        image(image.width - (image.width / 100) - 1, j, k) = 255;

        image((image.width / 100) - 3, j, k) = 255;

        image(image.width - (image.width / 100) + 3 - 1, j, k) = 255;
      }
    }

    for (int i = 0; i < image.width; ++i) {
      for (int k = 0; k < 3; ++k) {
        image(i, image.height / 100, k) = 255;

        image(i, image.height - (image.height / 100) - 1, k) = 255;

        image(i, (image.height / 100) - 3, k) = 255;

        image(i, image.height - (image.height / 100) + 3 - 1, k) = 255;
      }
    }

    for (int i = image.width / 100; i < (image.width / 100) + 5; ++i) {
      for (int j = image.height / 100; j < (image.height / 100) + 5; ++j) {
        for (int k = 0; k < 3; ++k) {
          image(i, j, k) = 255;

          image(image.width - i - 1, j, k) = 255;

          image(i, image.height - j - 1, k) = 255;

          image(image.width - i - 1, image.height - j - 1, k) = 255;
        }
      }
    }

    for (int i = (image.width / 100) + 12; i < (image.width / 100) + 15; ++i) {
      for (int j = image.height / 100; j < (image.height / 100) + 15; ++j) {
        for (int k = 0; k < 3; ++k) {
          image(i, j, k) = 255;

          image(image.width - i - 1, j, k) = 255;

          image(i, image.height - j - 1, k) = 255;

          image(image.width - i - 1, image.height - j - 1, k) = 255;
        }
      }
    }

    for (int i = image.width / 100; i < (image.width / 100) + 15; ++i) {
      for (int j = (image.height / 100) + 12; j < (image.height / 100) + 15;
           ++j) {
        for (int k = 0; k < 3; ++k) {
          image(i, j, k) = 255;

          image(image.width - i - 1, j, k) = 255;

          image(i, image.height - j - 1, k) = 255;

          image(image.width - i - 1, image.height - j - 1, k) = 255;
        }
      }
    }

    for (int j = image.height / 100; j < (image.height / 100) + 8; ++j) {
      for (int k = 0; k < 3; ++k) {
        image((image.width / 100) + 8, j, k) = 255;

        image(image.width - (image.width / 100) - 8 - 1, j, k) = 255;

        image((image.width / 100) + 8, image.height - j - 1, k) = 255;

        image(image.width - (image.width / 100) - 8 - 1, image.height - j - 1,
              k) = 255;
      }
    }

    for (int i = image.width / 100; i < (image.width / 100) + 9; ++i) {
      for (int k = 0; k < 3; ++k) {
        image(i, (image.height / 100) + 8, k) = 255;

        image(i, image.height - (image.height / 100) - 8 - 1, k) = 255;

        image(image.width - i - 1, (image.height / 100) + 8, k) = 255;

        image(image.width - i - 1, image.height - (image.height / 100) - 8 - 1,
              k) = 255;
      }
    }
  }

  cout << "Pls enter image name to store new image\n";
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";

  cin >> filename;
  image.saveImage(filename);
}

void detect_image_edges() {
  string filename;
  cout << "Pls enter colored image name :" << endl;
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

  int width = image.width;
  int height = image.height;
  Image edges(width, height);

  for (int y = 1; y < height - 1; ++y) {
    for (int x = 1; x < width - 1; ++x) {
      int Gx = image(x + 1, y, 0) - image(x - 1, y, 0);
      int Gy = image(x, y + 1, 0) - image(x, y - 1, 0);

      if (abs(Gx) + abs(Gy) > 128) {
        edges(x, y, 0) = edges(x, y, 1) = edges(x, y, 2) = 0;
      } else {
        edges(x, y, 0) = edges(x, y, 1) = edges(x, y, 2) = 255;
      }
    }
  }

  cout << "Pls enter image name to store new image\n";
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";
  cin >> filename;
  edges.saveImage(filename);
}

Image resize(string photoName) {
  Image image(photoName);
  int new_width, new_height;
  cout << "pls enter your photo width\n";
  cin >> new_width;
  cout << "pls enter your photo height ";
  cin >> new_height;
  Image new_image(new_width, new_height);
  double width_ratio, height_ratio;
  width_ratio =
      (static_cast<double>(image.width) / static_cast<double>(new_width));
  height_ratio =
      (static_cast<double>(image.height) / static_cast<double>(new_height));
  for (int i = 0; i < new_width; i++) {
    for (int j = 0; j < new_height; j++) {
      for (int k = 0; k < 3; k++) {
        new_image(i, j, k) =
            image(round(i * width_ratio), round(j * height_ratio), k);
      }
    }
  }

  return new_image;
}

void blur() {
  string filename;
  cout << "Pls enter colored image name to turn to blur: ";
  cin >> filename;

  Image image(filename);

  int n = 3;
  int count = (n + n) * (n + n);

  for (int y = n; y < image.width - n; ++y) {
    for (int x = n; x < image.height - n; ++x) {
      for (int k = 0; k < 3; ++k) {
        int sum = 0;
        for (int ky = -n; ky < n; ++ky) {
          for (int kx = -n; kx < n; kx++) {
            int ny = y + ky;
            int nx = x + kx;
            sum += image(ny, nx, k);
          }
        }
        image(y, x, k) = sum / count;
      }
    }
  }

  cout << "Pls enter image name to store new image\n";
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";

  cin >> filename;
  image.saveImage(filename);
}

int randomBetween(int low, int high) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(low, high);
  return dis(gen);
}

void tv() {
  string filename;
  cout << "Pls enter colored image name to turn to gray scale: ";
  getline(cin, filename);

  Image image(filename);

  for (int i = 0; i < image.width; i += 2) {
    for (int j = 0; j < image.height; j += 2) {
      for (int k = 0; k < 3; ++k) {
        if (image(i, j, k) > 64) {
          image(i, j, k) = (image(i, j, k) + randomBetween(192, 255)) % 255;
        }
      }
    }
  }

  cout << "Pls enter image name to store new image\n";
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";

  getline(cin, filename);
  image.saveImage(filename);
}

Image purple_look(string filename) {
    Image image(filename);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int purple = 0; 
            
            purple += image(i, j, 0);
            purple += image(i, j, 2);
            purple /= 2;
            if(purple > 255) {
                purple = 255;
            } 
            image(i, j, 0) = purple;
            image(i, j, 2) = purple;
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) { 
            unsigned int red = image(i, j, 0)* 1.8;
            if(red > 255) {
                red = 255;
            }     
            image(i, j, 0) = red;
        }
    }
  return image;
}

int main() {
  cout << "welcome, that program add some filters to your picture,\n";
  Image image;
  string filename1;
  while (true)
  {
    string choice;
    cout << "choose what do you want [a] load image  [b] exit\n";
    cin >> choice;
    if(choice == "a" || choice == "A") {
      while (true) {  
        cout << "Pls enter your photo name to edit it: ";
        cin >> filename1;
        try {

            if(image.loadNewImage(filename1)) {
                break;
            }
        }
        catch(...) {
        }
        cin.ignore();
      }

      while (true) {
        cout << "please choose filter: \n"
              "a)filter_1(gray_scale).                  b)filter_2(black_and_white).   c)filter_3(invert_image).\n"
              "d)filter_4(merge_images).                e)filter_5(Flip Image).        f)filter_6(rotate_image).\n"
              "g)filter_7(Darken and Lighten Image).    h)filter_8(crop).              i)filter_9(ِAdding a Frame ).\n"
              "j)filter_10(ِdetect image edges).         k)filter_11(resizing_image).   l)filter_12(Blur Images).\n"
              "m)filter_15(TV images).                  n)filter_16(purple_look).      o)exit.\n";
        string choice;
        cin >> choice;
        cin.clear();
        cin.ignore(100, '\n');
        if (choice == "M" || choice == "m") {
          break;
        } else if (choice == "A" || choice == "a") {
          gray_scale();
        } else if (choice == "B" || choice == "b") {
          string extension = "";    
          cout << "\n[a] continue editing   [b]save and return to start menu   [c] don't save\n";
          string choice1;
          cin >> choice1;
          if(choice1 == "a"|| choice1 == "A") {
            image = black_and_white(filename1);
            continue;
          }
          else if(choice1 == "b" || choice1 == "B") {
            image = black_and_white(filename1);
            choose_ext(extension);
            image.saveImage(extension);
            break;
          }
          else {
            break;
          }
        } else if (choice == "C" || choice == "c") {
          invert_image();
        } else if (choice == "D" || choice == "d") {
          merge_images();
        } else if (choice == "E" || choice == "e") {
          string extension = "";    
          cout << "\n[a] continue editing   [b]save and return to start menu   [c] don't save\n";
          string choice1;
          cin >> choice1;
          if(choice1 == "a"|| choice1 == "A") {
            image = flip(filename1);
            continue;
          }
          else if(choice1 == "b" || choice1 == "B") {
            image = flip(filename1);
            choose_ext(extension);
            image.saveImage(extension);
            break;
          }
          else {
            break;
          }
        } else if (choice == "F" || choice == "f") {
          rotate_image();
        } else if (choice == "G" || choice == "g") {
          string extension = "";    
          cout << "\n[a] continue editing   [b]save and return to start menu   [c] don't save\n";
          string choice1;
          cin >> choice1;
          if(choice1 == "a"|| choice1 == "A") {
            image = darken_lighten(filename1);
            continue;
          }
          else if(choice1 == "b" || choice1 == "B") {
            image = darken_lighten(filename1);
            choose_ext(extension);
            image.saveImage(extension);
            break;
          }
          else {
            break;
          }
        } else if (choice == "H" || choice == "h") {
          crop();
        } else if (choice == "I" || choice == "i") {
          frame();
        } else if (choice == "J" || choice == "j") {
          detect_image_edges();
        } else if (choice == "K" || choice == "k") {
          string extension = "";    
          cout << "\n[a] continue editing   [b]save and return to start menu   [c] don't save\n";
          string choice1;
          cin >> choice1;
          if(choice1 == "a"|| choice1 == "A") {
            image = resize(filename1);
            continue;
          }
          else if(choice1 == "b" || choice1 == "B") {
            image = resize(filename1);
            choose_ext(extension);
            image.saveImage(extension);
            break;
          }
          else {
            break;
          }
        } else if (choice == "L" || choice == "l") {
          blur();
        } else if (choice == "M" || choice == "m") {
          tv();
        } else if (choice == "n" || choice == "n") {
          string extension = "";    
          cout << "\n[a] continue editing   [b]save and return to start menu   [c] don't save\n";
          string choice1;
          cin >> choice1;
          if(choice1 == "a"|| choice1 == "A") {
            image = purple_look(filename1);
            continue;
          }
          else if(choice1 == "b" || choice1 == "B") {
            image = purple_look(filename1);
            choose_ext(extension);
            image.saveImage(extension);
            break;
          }
          else {
            break;
          }

        } else if (choice == "o" || choice == "O") {
          break;
        }
        else {
          cout << "enter valid choice,\n";
          continue;
        }
      }
    }
    else if(choice == "b" || choice == "B") {
      break;
    }

  }
  return 0;
}