#include <opencv2/opencv.hpp>
#include <iostream>

const int screenWidth = 320*2;
const int screenHeight = 240*2;
const int cols = 320*2;
const int rows = 240*2;
const float damping = 0.99f;

float current[cols][rows] = {0};
float previous[cols][rows] = {0};

void onMouse(int event, int x, int y, int flags, void* userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        // Ensure x and y are within bounds
        x = std::min(std::max(x, 0), cols - 1);
        y = std::min(std::max(y, 0), rows - 1);
        
        // Add vibration at click point
        previous[x][y] = 255;
    }
}

int main() {
    cv::Mat noiseImage(screenHeight, screenWidth, CV_8UC3);

    // Initialize VideoWriter
    cv::VideoWriter video("water_animation.mp4", cv::VideoWriter::fourcc('m','p','4','v'), 30, cv::Size(screenWidth, screenHeight));

    // Initialize
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            current[i][j] = 0;
            previous[i][j] = 0;
        }
    }
    previous[screenHeight/2][screenWidth/2] = 255;

    cv::namedWindow("Water Animation", cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback("Water Animation", onMouse, nullptr);

    while (true) {
        // Kernel Math for simple water animation
        for (int i = 1; i < cols-1; i++) {
            for (int j = 1; j < rows-1; j++) {
                current[i][j] = (previous[i-1][j] + previous[i+1][j] +
                                 previous[i][j-1] + previous[i][j+1] +
                                 previous[i-1][j-1] + previous[i-1][j+1] +
                                 previous[i+1][j-1] + previous[i+1][j+1]) / 4 - current[i][j];

                current[i][j] *= damping;

                uchar value = static_cast<uchar>(std::abs(current[i][j]) * 255);
                noiseImage.at<cv::Vec3b>(j, i) = cv::Vec3b(value, value/2, 0);
            }
        }

        // Swap
        std::swap(previous, current);

        // Write frame to video
        video.write(noiseImage);

        // Display
        cv::imshow("Water Animation", noiseImage);

        // Exit if 'q' is pressed
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Release the VideoWriter
    video.release();

    return 0;
}
