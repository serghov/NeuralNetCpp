cmake_minimum_required(VERSION 3.6)
project(NeuralNetCpp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    Activations.cpp
    Activations.h
    ErrorFunctions.cpp
    ErrorFunctions.h
    main.cpp
    mathFunction.cpp
    mathFunction.h
    MNIST.cpp
    MNIST.h
    NeuralLayer.cpp
    NeuralLayer.h
    NeuralLink.cpp
    NeuralLink.h
    NeuralNetwork.cpp
    NeuralNetwork.h
    Neuron.cpp
    Neuron.h
    Regularizations.cpp
    Regularizations.h)

add_executable(NeuralNetCpp ${SOURCE_FILES})