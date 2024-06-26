# Use an ARM-based Debian image suitable for Raspberry Pi
FROM arm32v7/debian:buster-slim

# Install necessary packages for installing ROS
RUN apt-get update && \
    apt-get install -y \
    curl \
    gnupg2 \
    lsb-release \
    && rm -rf /var/lib/apt/lists/*

# Add the ROS 2 apt repository
RUN curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.key | apt-key add - && \
    echo "deb [arch=armhf] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" > /etc/apt/sources.list.d/ros2-latest.list
    
# Update the package list and install ROS 2 Humble
RUN apt-get update && \
    apt-get install -y \
    ros-humble-ros-base \
    && rm -rf /var/lib/apt/lists/*

# Install necessary packages for compiling and running your C++ code
RUN apt-get update && \
    apt-get install -y \
    g++ \
    cmake \
    libpigpio-dev \
    && rm -rf /var/lib/apt/lists/*

# Source ROS 2 setup script
SHELL ["/bin/bash", "-c"]
RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
RUN source /opt/ros/humble/setup.bash

# Set the working directory in the container
WORKDIR /app

# Copy the entire current directory into the container
COPY . .

# Compile your C++ code
RUN mkdir build && \
    cd build && \
    cmake .. && \
    make

# Command to run your tests (adjust as per your project)
CMD ["./build/your_executable"]

