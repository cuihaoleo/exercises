#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <CL/cl.h>

const char* programSource = "\
__kernel void prime_test( \
        ulong n, \
        __global uchar *not_prime) { \
    int gid = get_global_id(0); \
    int divisor = gid == 0 ? 2 : gid * 2 + 1; \
    if (n % divisor == 0) \
        *not_prime = 1; \
}";

void printPlatformInfo(cl_platform_id id) {
    const char* attributeNames[] = {
        "Name", "Vendor", "Version", "Profile", "Extensions" };
    const cl_platform_info attributeTypes[] = {
        CL_PLATFORM_NAME,
        CL_PLATFORM_VENDOR,
        CL_PLATFORM_VERSION,
        CL_PLATFORM_PROFILE,
        CL_PLATFORM_EXTENSIONS };
    const int attributeCount = sizeof(attributeNames) / sizeof(char*);
     
    for (size_t j=0; j<attributeCount; j++) {
        size_t infoSize;
        char *info;

        clGetPlatformInfo(
                id,
                attributeTypes[j],
                0,
                NULL,
                &infoSize);

        clGetPlatformInfo(
                id,
                attributeTypes[j],
                infoSize,
                info = (char*)malloc(infoSize),
                NULL);

        printf("  %-16s: %s\n", attributeNames[j], info);
        free(info);
    }
}

void printDeviceInfo(cl_device_id id) {
    const char* attributeNames[] = {
        "Name", "Vendor", "Version", "Driver" "Profile", "Extensions" };
    const cl_platform_info attributeTypes[] = {
        CL_DEVICE_NAME,
        CL_DEVICE_VENDOR,
        CL_DEVICE_VERSION,
        CL_DRIVER_VERSION,
        CL_DEVICE_PROFILE,
        CL_DEVICE_EXTENSIONS };
    const int attributeCount = sizeof(attributeNames) / sizeof(char*);

    for (size_t j=0; j<attributeCount; j++) {
        size_t infoSize;
        char *info;

        clGetDeviceInfo(
                id,
                attributeTypes[j],
                0,
                NULL,
                &infoSize);

        clGetDeviceInfo(
                id,
                attributeTypes[j],
                infoSize,
                info = (char*)malloc(infoSize),
                NULL);

        printf("  %-16s: %s\n", attributeNames[j], info);
        free(info);
    }

    cl_uint maxComputeUnits;
    clGetDeviceInfo(
            id,
            CL_DEVICE_MAX_COMPUTE_UNITS,
            sizeof(maxComputeUnits),
            &maxComputeUnits,
            NULL);
    printf("  %-16s: %u\n", "Computing Units", (unsigned)maxComputeUnits);
 
}

unsigned long measure_time_ms(bool reset) {
    static clock_t begin = 0;

    if (reset) {
        begin = clock();
        return 0;
    } else {
        clock_t end = clock();
        return 1000 * (end - begin) / CLOCKS_PER_SEC;
    }
}

int main() {
    int retVal = 0;
    cl_int status;

#define CL_CHECK_STATUS(x,s) \
    if ((x) != CL_SUCCESS) { \
        fprintf(stderr, "%s\n", s); \
        goto fail; \
    } 

    cl_uint numPlatforms;
    cl_platform_id *platforms = NULL;
    unsigned selectedPlatform = 0;

    cl_uint numDevices;
    cl_device_id *devices = NULL;
    unsigned selectedDevice = 0;

    cl_context context = NULL;
    cl_command_queue cmdQueue = NULL;
    cl_mem bufferResult = NULL;
    cl_program program = NULL;
    cl_kernel kernel = NULL;
    char *buildMessage = NULL;

    unsigned long long number;
    cl_ulong numberCl;
    cl_uchar result = 0;

    // Discover and initialize the platforms
    status = clGetPlatformIDs(0, NULL, &numPlatforms);
    CL_CHECK_STATUS(status, "clGetPlatformIDs failed!");

    platforms = (cl_platform_id*)malloc(numPlatforms*sizeof(cl_platform_id));

    status = clGetPlatformIDs(numPlatforms, platforms, NULL);
    CL_CHECK_STATUS(status, "clGetPlatformIDs failed!");

    for (size_t i=0; i<numPlatforms; i++) {
        printf("[Platform #%zu]\n", i);
        printPlatformInfo(platforms[i]);
    }

    if (numPlatforms > 1) {
        do {
            printf("Please select a platform: ");
            scanf("%u", &selectedPlatform);
            while (getchar() != '\n') continue;
        } while (selectedPlatform >= numPlatforms);
    } else if (numPlatforms == 1) {
        selectedPlatform = 0;
    } else {
        fprintf(stderr, "No supported platform!");
        goto fail;
    }

    printf("Platform #%d is selected.\n\n", selectedPlatform);

    // Discover and initialize the devices
    status = clGetDeviceIDs(
            platforms[selectedPlatform],
            CL_DEVICE_TYPE_ALL, 
            0, 
            NULL, 
            &numDevices);
    CL_CHECK_STATUS(status, "clGetDeviceIDs failed!");

    devices = (cl_device_id*)malloc(numDevices*sizeof(cl_device_id));

    status = clGetDeviceIDs(
            platforms[selectedPlatform],
            CL_DEVICE_TYPE_ALL, 
            numDevices, 
            devices, 
            NULL);
    CL_CHECK_STATUS(status, "clGetDeviceIDs failed!");

    for (size_t i=0; i<numDevices; i++) {
        printf("[Device #%zu]\n", i);
        printDeviceInfo(devices[i]);
    }

    if (numDevices > 1) {
        do {
            printf("Please select a device: ");
            scanf("%u", &selectedDevice);
            while (getchar() != '\n') continue;
        } while (selectedDevice >= numDevices);
    } else if (numDevices == 1) {
        selectedDevice = 0;
    } else {
        fprintf(stderr, "No supported device!");
        goto fail;
    }

    printf("Device #%d is selected.\n\n", selectedDevice);

    // Create a context associated with the devices
    context = clCreateContext(
        NULL, 
        numDevices, 
        devices, 
        NULL, 
        NULL, 
        &status);
    CL_CHECK_STATUS(status, "clCreateContext failed!");

    bufferResult = clCreateBuffer(
        context, 
        CL_MEM_WRITE_ONLY,                 
        sizeof(cl_uchar),
        NULL, 
        &status);
    CL_CHECK_STATUS(status, "clCreateBuffer failed!");

    // Create a command queue
    cmdQueue = clCreateCommandQueue(
        context, 
        devices[selectedDevice], 
        0, 
        &status);
    CL_CHECK_STATUS(status, "clCreateCommandQueue failed!");

    status = clEnqueueFillBuffer(
        cmdQueue,
        bufferResult,
        &result,
        sizeof(cl_uchar),
        0,
        sizeof(cl_uchar),
        0,
        NULL,
        NULL);
    CL_CHECK_STATUS(status, "clEnqueueFillBuffer failed!");
 
    // Create and compile the program
    program = clCreateProgramWithSource(
        context, 
        1, 
        (const char**)&programSource,                                 
        NULL, 
        &status);
    CL_CHECK_STATUS(status, "clCreateProgramWithSource failed!");

    status = clBuildProgram(
        program, 
        1, 
        devices + selectedDevice,
        NULL,
        NULL, 
        NULL);

    if (status != CL_SUCCESS) {
        size_t buildMessageLength;

        status = clGetProgramBuildInfo(
                program,
                devices[selectedDevice],
                CL_PROGRAM_BUILD_LOG,
                0,
                NULL,
                &buildMessageLength);
        CL_CHECK_STATUS(status, "clGetProgramBuildInfo failed!");

        status = clGetProgramBuildInfo(
                program,
                devices[selectedDevice],
                CL_PROGRAM_BUILD_LOG,
                buildMessageLength,
                buildMessage = malloc(buildMessageLength),
                NULL);
        CL_CHECK_STATUS(status, "clGetProgramBuildInfo failed!");

        fputs(buildMessage, stderr);
        fputc('\n', stderr);

        free(buildMessage);
        buildMessage = NULL;

        goto fail;
    }

    // Create the kernel
    kernel = clCreateKernel(program, "prime_test", &status);
    CL_CHECK_STATUS(status, "clCreateKernel failed!");

    printf("Number to test: ");
    scanf("%llu", &number);

    // Set the kernel arguments
    numberCl = number;
    status = clSetKernelArg(
            kernel,
            0,
            sizeof(cl_ulong),
            &numberCl);
    status |= clSetKernelArg(
            kernel,
            1,
            sizeof(cl_mem),
            &bufferResult);
    CL_CHECK_STATUS(status, "clSetKernelArg failed!");

    // Configure the work-item structure
    size_t workSize = ((int)floor(sqrt(number)) + 1) / 2;
    size_t globalWorkSize[1] = { workSize };
    
    // Enqueue the kernel for execution
    measure_time_ms(true);
    status = clEnqueueNDRangeKernel(
        cmdQueue, 
        kernel, 
        1, 
        NULL, 
        globalWorkSize, 
        NULL, 
        0, 
        NULL, 
        NULL);
    CL_CHECK_STATUS(status, "clEnqueueNDRangeKernel failed!");

    // Read the output buffer back to the host
    status = clEnqueueReadBuffer(
        cmdQueue, 
        bufferResult, 
        CL_TRUE, 
        0, 
        sizeof(cl_uchar),
        &result, 
        0, 
        NULL, 
        NULL);
    CL_CHECK_STATUS(status, "clEnqueueReadBuffer failed!");

    printf("%lu ms taken.\n\n", measure_time_ms(false));

    // Print result
    if (result == 0)
        printf("%llu is prime\n", number);
    else
        printf("%llu is not prime\n", number);

end:
    if (platforms != NULL) free(platforms);
    if (devices != NULL) free(devices);
    if (kernel != NULL) clReleaseKernel(kernel);
    if (program != NULL) clReleaseProgram(program);
    if (buildMessage != NULL) free(buildMessage);
    if (cmdQueue != NULL) clReleaseCommandQueue(cmdQueue);
    if (bufferResult != NULL) clReleaseMemObject(bufferResult);
    if (context != NULL) clReleaseContext(context);

    return retVal;

fail:
    retVal = -1;
    goto end;

#undef CL_CHECK_STATUS
}
