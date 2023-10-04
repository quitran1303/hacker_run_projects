# Use a base image with a C development environment
FROM gcc:latest

# Update the package list and install GCC and related tools
RUN apt-get update && apt-get install -y gcc g++ make

# Set the working directory in the container
WORKDIR /app

# Copy your project files into the container
COPY . .

# Install any dependencies if needed (e.g., if your project relies on external libraries)

# Build the project using the Makefile
#RUN make

# Run the unit tests using Unity
CMD ["make", "test"]
