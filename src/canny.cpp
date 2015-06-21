//
// пример работы детектора границ Кенни - cvCanny()
//
// http://robocraft.ru/blog/computervision/484.html
//

#include <opencv2/cv.h>
#include <opencv2/highgui.h>
#include <stdlib.h>
#include <stdio.h>

IplImage* image = 0;
IplImage* gray = 0;
IplImage* dst = 0;

int main(int argc, char* argv[])
{
        // имя картинки задаётся первым параметром
        char* filename = argc == 2 ? argv[1] : "../tests/rectangle_5_1_6.jpg";
        // получаем картинку
        image = cvLoadImage(filename,1);

        printf("[i] image: %s\n", filename);
        assert( image != 0 );

        // создаём одноканальные картинки
        gray = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
        dst = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );

        // окно для отображения картинки
        cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
        cvNamedWindow("gray",CV_WINDOW_AUTOSIZE);
        cvNamedWindow("cvCanny",CV_WINDOW_AUTOSIZE);

        // преобразуем в градации серого
        cvCvtColor(image, gray, CV_RGB2GRAY);

        // получаем границы
        cvCanny(gray, dst, 10, 100, 3);

        // показываем картинки
        cvShowImage("original",image);
        cvShowImage("gray",gray);
        cvShowImage("cvCanny", dst );

        // ждём нажатия клавиши
        cvWaitKey(0);

        // освобождаем ресурсы
        cvReleaseImage(&image);
        cvReleaseImage(&gray);
        cvReleaseImage(&dst);
        // удаляем окна
        cvDestroyAllWindows();
        return 0;
}