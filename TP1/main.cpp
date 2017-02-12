//
//  main.cpp
//  TP1
//
//  Created by Jules Thuillier on 11/02/2017.
//  Copyright © 2017 VR Tracker. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

/*
 * Count the number of lines (numbers) in file
 */
int countLines(string path){
    int number_of_lines = 0;
    std::string line;
    std::ifstream myfile(path);
    
    while (std::getline(myfile, line))
        ++number_of_lines;
    return number_of_lines;
}

// FROM : http://www.algolist.net/Algorithms/Sorting/Quicksort


/*
 * Bubble sort algorithm
 * @ERWAN J'ai modifié l'algo de l'example pour prendre en entier le tableau complet
 * et travailler uniquement sur la portion voulue
 */
void bubbleSort(int arr[], int left, int right) {
    bool swapped = true;
    int j = 0;
    int tmp;
    while (swapped) {
        swapped = false;
        j++;
        for (int i = 0; i < (right-left + 1) - j; i++) {
            if (arr[left+i] > arr[left + i + 1]) {
                tmp = arr[left + i];
                arr[left + i] = arr[left + i + 1];
                arr[left + i + 1] = tmp;
                swapped = true;
            }
        }
    }
}


/**
 * Quick Sort with random pivot and recursivity threshold at 1
 */
void quickSortPivotRandomRecuOne(int arr[], int left, int right) {
    int i = left, j = right;
    int tmp;
    int pivot = left + (std::rand()%(right-left)); // @ERWAN : Random value chosen, please verify that's ok
    std::cout << "Pivot: " << std::rand()%(right-left) << std::endl;
    /* partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };
    
    /* recursion */
    if (left < j)
        quickSortPivotRandomRecuOne(arr, left, j);
    if (i < right)
        quickSortPivotRandomRecuOne(arr, i, right);
}

/**
 * Quick Sort with first element as pivot and recursivity threshold at 1
 */
void quickSortPivotFirstRecuOne(int arr[], int left, int right) {
    int i = left, j = right;
    int tmp;
    int pivot = arr[0]; // Get first element as Pivot
    
    /* partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };
    
    /* recursion */
    if (left < j)
        quickSortPivotFirstRecuOne(arr, left, j);
    if (i < right)
        quickSortPivotFirstRecuOne(arr, i, right);
}

/**
 * Quick Sort with random pivot and recursivity threshold at X
 */
void quickSortPivotRandomRecuChosen(int arr[], int left, int right, int seuil) {
    int i = left, j = right;
    int tmp;
    int pivot = left + rand() % (right-left) ; // @ERWAN : Random value chosen, please verify that's ok
    
    /* partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };
    
    /* recursion */
    if(j-left < seuil && right-i < seuil){
        if (left < j)
            bubbleSort(arr, left, j);
        if (i < right)
            bubbleSort(arr, i, right);
    }
    else {
        if (left < j)
            quickSortPivotRandomRecuChosen(arr, left, j, seuil);
        if (i < right)
            quickSortPivotRandomRecuChosen(arr, i, right, seuil);
    }
}

/**
 * Quick Sort with first element as pivot and recursivity threshold at X
 */
void quickSortPivotFirstRecuChosen(int arr[], int left, int right, int seuil) {
    int i = left, j = right;
    int tmp;
    int pivot = arr[0]; // Get first element as Pivot
    
    /* partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };
    
    /* recursion */
    if(j-left < seuil && right-i < seuil){
        if (left < j)
            bubbleSort(arr, left, j);
        if (i < right)
            bubbleSort(arr, i, right);
    }
    else {
        if (left < j)
            quickSortPivotFirstRecuChosen(arr, left, j, seuil);
        if (i < right)
            quickSortPivotFirstRecuChosen(arr, i, right, seuil);
    }
}


/*
 * Read file into the array
 */
void readNumbers(int numbers[], int lines, string path){
    std::string line;
    std::ifstream myfile(path);
    for (int i=0; i<lines; i++){
        std::getline(myfile, line);
        numbers[i] = std::stoi(line);
    }
    
}


int main(int argc, const char * argv[]) {
    
    if(argc >= 3){
        string algo = argv[1];
        string path = argv[2];
        bool print = false;
        bool time = false;
        
        for(int i=3; i<argc; i++){
            if(strncmp(argv[i], "-p", 2) == 0)
                print = true;
            else if(strncmp(argv[i], "-t", 2) == 0)
                time = true;
        }
        
        std::cout << "Algorithm: " << algo << std::endl;
        std::cout << "File path: " << path << std::endl;
        std::cout << "Print: " << print << std::endl;
        std::cout << "Time: " << time << std::endl;
        
        
        int lines = countLines(path);
        
        if(lines == 0){
            std::cout << "Error reading file. Path not found" << lines;
            return -1;
        }
        
        int numbers[lines];
        readNumbers(numbers, lines, path);
        
        std::srand(std::time(0));
        
        // Start time counter
        high_resolution_clock::time_point startTime = high_resolution_clock::now();
        
        // TODO
        if(algo == "counting"){
        }
        else if(algo == "quick"){
            std::cout << "In " << lines << std::endl;
            quickSortPivotRandomRecuOne(numbers, 0, lines-1);
            std::cout << "Out " << std::endl;
        }
        else if(algo == "quickRandom"){
            
        }
        else if(algo == "quickSeuil"){
            
        }
        else if(algo == "quickRandomSeuil"){
            
        }
        else {
            std::cout << "Error: wrong algorithm argument" << std::endl;
        }
        
        // End time counter
        high_resolution_clock::time_point endTime = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>( endTime - startTime ).count();
        
        // Print execution time
        if(time)
            std::cout << "Duration: " << duration;
        
        // Print numbers
        if(print){
            for(int i=0; i<lines; i++){
                std::cout << numbers[i] << std::endl;
            }
        }
    }
    return 0;
}



