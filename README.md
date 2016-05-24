# NeuralNetCpp

The aim of this project is was to create an easy to understnad, simple, and easily executable artificial neural network. 
It has built in support for Sigmoid, Tanh, Linear, Relu, and Softmax activation functions, L1 and L2 regularizations, square and log error functions as well as any shape of a neural network with arbitrary number of hidden layers.

## Optimization methods

Currently there are implementations of gradiend descent as well as simulated annealing methods. The latter is an experiment and so far there are no good results with it.


## Building

This repository contains .sln file. It can easily be imported into visual studio, code blocks, and most of other ides. I will work on including a makefile.

## Implementation

Everything is written in c++ and has no external dependencies.

## Structure

The code is written in an easy to understand and self explanatory way. It consists of several classes;
* Neuron.h, Neuron.cpp - artificial neuron
* NeuralLink.h, NeuralLink.cpp - link between two neurons
* NeuralLayer.h NeuralLayer.cpp - layer consisting of multiple neurons
* NeuralNetwork.h NeuralNetwork.cpp - main class containing forward and backward propagations, as well as weights update and annealing functions

There are also these supporting classes;
* mathFunction.h, mathFunction.cpp - a general class from which mathematical functions are derived
* MNIST.h, MNIST.cpp - a class for dealing with mnist data

## Running

The main file contains implementation for reading MNIST data dividing it into two sets and running gradiend descent or simulated annealing optimization.
The code with gradient descent method and one hidden layer with 28 neurons can reach 96.2% accuracy.

## TODO
* makefile
* Isolate project in a library
* Isolate examples in different files
* Loading the neural network from a file
* GPU support
* Convolutions
* Everything else
