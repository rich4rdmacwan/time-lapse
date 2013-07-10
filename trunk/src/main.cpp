#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <time.h>
#define DEFAULT_SNAPSHOT_INTERVAL 10
int main(int argc, char* argv[]){
    //Structure to hold an image
    cv::Mat frame;
    std::string outputFileName="out.avi";
    //Reference to a video source e.g. webcam
    cv::VideoCapture cap;
    int prevtime=0;
    bool isWebcam=false;
    int interval=DEFAULT_SNAPSHOT_INTERVAL;

    if(argc>1){
        if(argc>=4){
            outputFileName=argv[3];
        }
        if(argc>=3){
            interval = atoi(argv[1]);
            //std::cout<<interval;
            if(interval<=0){
                std::cout<<"Invalid snapshot interval specified. Using default"<<std::endl;
                interval=DEFAULT_SNAPSHOT_INTERVAL;
            }
            cap.open(std::string(argv[2]));
        }
        if(argc==2){
            interval=atoi(argv[1]);
            if(interval<=0){
                  //Interval was not specified. Use default
            std::cout<<"Using default snapshot interval of 10 seconds"<<std::endl;
            interval=DEFAULT_SNAPSHOT_INTERVAL;
            cap.open(std::string(argv[1]));
            }
            else{
                cap.open(0);
                isWebcam=true;
            }
        }
    }
    else{
        cap.open(0);
        isWebcam=true;
    }

    cap>>frame;
    if(frame.data){
        cv::VideoWriter writer(outputFileName.c_str(),CV_FOURCC('M','P','4','2'),30,frame.size(),true);
        if(!writer.isOpened()){
            std::cout<<"Failed to open VideoWriter!"<<std::endl;
            return -1;
        }
        std::cout<<"Generating timelapse video. Press Esc to cancel."<<std::endl;


        time_t starttime,elapsedtime;
        int diff=0;
        time(&starttime);

        for(;;){
            cap>>frame;
            if(!frame.data) break;
            cv::imshow("video",frame);

            if(cv::waitKey(30)==27) {
                break;
            }
            time(&elapsedtime);
            diff=difftime(elapsedtime,starttime);
            if(prevtime!=diff) {
                //std::cout<<"Elapsed time = "<<diff<<std::endl;
                if(diff%interval ==0){
                    //Time to save frame
                    std::cout<<"Elapsed time = "<<diff<<" seconds. Saving frame to video file"<<std::endl;
                    writer<<frame;
                }
                prevtime=diff;
            }
        }

    }
    else{
           std::cout<<std::endl;
           if(isWebcam)   std::cout<<"Webcam not found!"<<std::endl;
            else std::cout<<"Invalid source!"<<std::endl;
        std::cout<<"Usage : timelapse [snapshotinterval=10] [video file] [outputfileName.avi=out.avi]"<<std::endl;
        std::cout<<"To load the default webcam, run timelapse without an argument. If you are providing an output filename, make sure it's extension is .avi"<<std::endl;
    }
}
