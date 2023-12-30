#include <unistd.h>
#include "LibCamera.h"
#include <string.h>

int main() {
    time_t start_time = time(0);
    int frame_count = 0;
    LibCamera cam;
    LibCamera cam2;
    uint32_t width = 9152;
    uint32_t height = 6944;
    uint32_t stride;

    std::shared_ptr<CameraManager> cm = std::make_unique<CameraManager>();
    int ret = cm->start();
    if (ret){
        std::cout << "Failed to start camera manager: "
                  << ret << std::endl;

        return ret;
    }

    ret = cam.initCamera(0,cm);
    cam.configureStill(width, height, formats::BGR888, 1, 0);
    ControlList controls_;
    int64_t frame_time = 1000000 / 10;
    controls_.set(controls::FrameDurationLimits, libcamera::Span<const int64_t, 2>({ frame_time, frame_time }));
    controls_.set(controls::Brightness, 0.5);
    controls_.set(controls::Contrast, 1.5);
    controls_.set(controls::ExposureTime, 20000);
    cam.set(controls_);
    if (!ret) {
        bool flag;
        LibcameraOutData frameData;
        cam.startCamera();
        cam.VideoStream(&width, &height, &stride);

        while (true) {
            flag = cam.readFrame(&frameData);
            if (!flag)
                continue;

            frame_count++;
            if ((time(0) - start_time) >= 1){
                printf("fps: %d\n", frame_count);
                frame_count = 0;
                start_time = time(0);
            }
            cam.returnFrameBuffer(frameData);
            break;
        }
    }

    //cam.stopCamera();
    //cam.closeCamera();
return 0; //EXIT HERE FOR THE EXAMPLE
    int ret2 = cam2.initCamera(1,cm);
    cam2.configureStill(width, height, formats::YUV420, 1, 0);
    ControlList controls2_;
    frame_time = 1000000 / 10;
    controls2_.set(controls::FrameDurationLimits, libcamera::Span<const int64_t, 2>({ frame_time, frame_time }));
    controls2_.set(controls::Brightness, 0.5);
    controls2_.set(controls::Contrast, 1.5);
    controls2_.set(controls::ExposureTime, 20000);
    cam2.set(controls2_);
    if (!ret2) {
        bool flag;
        LibcameraOutData frameData;

        cam2.startCamera();
        cam2.VideoStream(&width, &height, &stride);

        while (true) {
            flag = cam2.readFrame(&frameData);
            if (!flag)
                continue;

            frame_count++;
            if ((time(0) - start_time) >= 1){
                printf("fps: %d\n", frame_count);
                frame_count = 0;
                start_time = time(0);
            }
            cam2.returnFrameBuffer(frameData);
            break;
        }
    }

    cam2.stopCamera();
    cam2.closeCamera();
    return 0;
}
