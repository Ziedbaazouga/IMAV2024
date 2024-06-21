# Use an ARM-based Debian image suitable for Raspberry Pi
FROM arm32v7/debian:buster-slim

# Install ROS (adjust according to your ROS version and distribution)
RUN apt-get update && \
    apt-get install -y \
    ros-<your-ros-distro>-ros-base \
    ros-<your-ros-distro>-<additional-ros-packages> \
    && rm -rf /var/lib/apt/lists/*

# Install necessary packages for compiling and running your C++ code
RUN apt-get update && \
    apt-get install -y \
    g++ \
    cmake \
    libpigpio-dev \
    && rm -rf /var/lib/apt/lists/*

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

