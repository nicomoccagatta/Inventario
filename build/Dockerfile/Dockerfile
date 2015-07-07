FROM ubuntu
RUN apt-get -y update
RUN apt-get install -y git
RUN apt-get install -y cmake
RUN apt-get install -y libgtkmm-2.4-dev
RUN apt-get install -y libtinyxml-dev
RUN mkdir OpenCV
RUN apt-get -qq remove ffmpeg x264 libx264-dev
RUN apt-get -qq install -y libopencv-dev build-essential checkinstall cmake pkg-config yasm libjpeg-dev libjasper-dev libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev libxine-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev python-dev python-numpy libtbb-dev libqt4-dev libgtk2.0-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev x264 v4l-utils cmake qt5-default checkinstall
RUN apt-get install -y wget
RUN cd /OpenCV && wget -O OpenCV-3.0.0.zip http://sourceforge.net/projects/opencvlibrary/files/opencv-unix/3.0.0/opencv-3.0.0.zip/download
RUN apt-get install -y unzip
RUN cd /OpenCV && unzip OpenCV-3.0.0.zip
RUN mkdir /OpenCV/opencv-3.0.0/build
RUN cd /OpenCV/opencv-3.0.0/build && cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=OFF -D INSTALL_PYTHON_EXAMPLES=OFF -D BUILD_EXAMPLES=OFF -D WITH_QT=ON -D WITH_OPENGL=ON ..
RUN cd /OpenCV/opencv-3.0.0/build && make -j2
RUN cd /OpenCV/opencv-3.0.0/build && checkinstall
RUN cd /OpenCV/opencv-3.0.0/build && sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
RUN cd /OpenCV/opencv-3.0.0/build && ldconfig
RUN cd /OpenCV/opencv-3.0.0/build && cmake ..
RUN cd /OpenCV/opencv-3.0.0/build && make install
RUN cp /usr/local/include/opencv2/opencv.hpp /usr/local/include/opencv/opencv.hpp
RUN mkdir xfeatures2d
RUN cd /xfeatures2d && git clone https://github.com/itseez/opencv_contrib
RUN cd /xfeatures2d/opencv_contrib && mkdir build
RUN cd /xfeatures2d/opencv_contrib/build && cmake -DOPENCV_EXTRA_MODULES_PATH=/xfeatures2d/opencv_contrib/modules /OpenCV/opencv-3.0.0
RUN cd /xfeatures2d/opencv_contrib/build && make -j5
RUN cd /xfeatures2d/opencv_contrib/build && make -j5 install
RUN apt-get install -qqy x11-apps
RUN apt-get install -qqy build-essential
RUN apt-get install -qqy cmake libgtk2.0-dev pkg-config
ENV DISPLAY :0
RUN mkdir root/.local/
RUN mkdir root/.local/share/
RUN touch root/.local/share/recentrly-used.xbel