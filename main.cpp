#include <iostream> //iostream library for output
#include <CL/cl.hpp> //includes the opencl library
#include <vector> //Inclue the c++ library for vectors
#include <string> //Include C++ Library for Strings
#define OPENCL_ERROR 2

bool checkIfEqual(int a, int b, int c, int d, int e, int f, int g, int h){   //Function to check if 9  Integers are equal
    int elements [8] = {}; //Initializes the array that contains the 9 Numbers
    elements[0] = a;  //Writes every argument into the array
    elements[1] = b; //Loops through the numbers
    elements[2] = c;
    elements[3] = d;
    elements[4] = e;
    elements[5] = f;
    elements[6] = g;
    elements[7] = h;
    for (int i = 0; i <8; ++i) {  //checks if the elements 1 to 8 are equal to any other element
        for (int j = 0; j < 8; ++j) {
            if (elements[i] != elements[j])return false;  //Returns false if any elements aren't equal

        }
    }
    return true; //returns true if all elements are equal
}

int showSquare(int a, int b, int c,int d, int e, int f, int g, int h, int i){
    int sumA = a + b + c;
    int sumB = d + e + f;
    int sumC = g + h + i;
    int sumD = a + d + g;
    int sumE = b + e + h;
    int sumF = c + f + i;
    int sumG = a + e + i;
    int sumH = g + e + c;
    std::cout << "             " << sumH << std::endl;
    std::cout << "------------" << std::endl;
    std::cout << "| " << a << " | " << b << " | " << c << " |" << sumA <<std::endl;
    std::cout << "------------" << std::endl;
    std::cout << "| " << d << " | " << e << " | " << f << " |" << sumB <<std::endl;
    std::cout << "------------" << std::endl;
    std::cout << "| " << g << " | " << h << " | " << i << " |" << sumC << std::endl;
    std::cout << "------------" << std::endl;
    std::cout << sumD << "   " << sumE << "   " << sumF << "  " << sumG << std::endl;

    if (checkIfEqual(sumA,sumB,sumC,sumD,sumE,sumF,sumG,sumH)){
    std::cout << "Magic square" << std::endl;
        return 0;
}
    else {
        std::cout << "Parker square" << std::endl;
        return 1;
}
}


void generateNumbers(int max, int start){
    int squaresCounter = 0;
    int magicCounter = 0;
    for (int a = start; a < max; ++a) {
        for (int b = start; b < max; ++b) {
            for (int c = start; c < max; ++c) {
                for (int d = start; d < max; ++d) {
                    for (int e = start; e < max; ++e) {
                        for (int f = start; f < max; ++f) {
                            for (int g = start; g < max; ++g) {
                                for (int h = start; h < max; ++h) {
                                    for (int i = start; i < max; ++i) {
                                        int result = showSquare(a,b,c,d,e,f,g,h,i);
                                        squaresCounter++;
                                        if (result == 0){
                                            magicCounter++;
                                            std::string bla;
                                            std::cin >> bla;
                                        }
                                        std::cout << "Squares Calculated = " << squaresCounter << std::endl;
                                        std::cout << "Squares Correct = " << magicCounter << std::endl;

                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main(){
    //get all available opencl Platforms
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);

    //If none available stop programm
    if (all_platforms.size()==0){
        std::cout << "No platforms found. Check OpenCL Installation \n";
        return OPENCL_ERROR;
    }

    //Use the first platform as defualt platform
    cl::Platform default_platform=all_platforms[0];

    //Print name of the used platfom
    std::cout << "Using platform " << default_platform.getInfo<CL_PLATFORM_NAME>() << std::endl;

    //create a vector to contain the devices
    std::vector<cl::Device> all_devices;

    //get all devices of the default platform
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);

    //if no devices are found print an error an stop the program
    if (all_devices.size()==0){
        std::cout << " No devices found check OpenCL installation!\n";
        return OPENCL_ERROR;
    }

    //Use first device of the default platform as the default device
    cl::Device default_device = all_devices[0];

    //Print the name of the used device
    std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << std::endl;

    //create the context for the default_device (runtime Link between device and platform)
    cl::Context context({default_device});

    //Create the program that is executed on the OpenCL Device
    cl::Program::Sources sources;

    //Kernel calculates for each element C=A+B
    std::string kernel_code =
            "void kernel simple_add(global const int* A, global const int* B, global int* C){"
            "C[get_global_id(0)]=A[get_global_id(0)]+B[get_global_id(0)];                    "
            "}                                                                               ";
    sources.push_back({kernel_code.c_str(),kernel_code.length()});

    //Build the program and if not successful stop the program
    cl::Program program(context,sources);
    if(program.build({default_device}) != CL_SUCCESS){
        std::cout << "Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << std::endl;
        return OPENCL_ERROR;
    }

    //create buffers on the device
    cl::Buffer buffer_A(context,CL_MEM_READ_WRITE,sizeof(int)*10);
    cl::Buffer buffer_B(context,CL_MEM_READ_WRITE,sizeof(int)*10);
    cl::Buffer buffer_C(context,CL_MEM_READ_WRITE,sizeof(int)*10);

    int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int B[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0};

    //create queue to which we will push command for the device
    cl::CommandQueue queue(context,default_device);

    //write array a and b to the device
    queue.enqueueWriteBuffer(buffer_A,CL_TRUE,0,sizeof(int)*10,A);
    queue.enqueueWriteBuffer(buffer_B,CL_TRUE,0,sizeof(int)*10,B);

    //Run the program on the device
    cl::Kernel simple_add(program,"simple_add");
    simple_add.setArg(0,buffer_A);
    simple_add.setArg(0,buffer_B);
    simple_add.setArg(0,buffer_C);
    queue.enqueueNDRangeKernel(simple_add,cl::NullRange,cl::NDRange(10),cl::NullRange);
    queue.finish();

    //Array to store the results
    int C[10];
    
    //read results from the device and store them in the array C
    queue.enqueueReadBuffer(buffer_C,CL_TRUE,0, sizeof(int)*10,C);

    //Display the results
    std::cout << "Results" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout  << C[i] << " ";
    }
    
    //generateNumbers(10,1);
    return 0;
}