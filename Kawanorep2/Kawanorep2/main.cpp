//
//  main.cpp
//  Kawanorep2
//
//  Created by 合田佑司 on 2014/10/29.
//  Copyright (c) 2014年 合田佑司. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <random>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//double gaussk(double x1, double x[50]){
//    double f=0.0;
//    for(int i=0; i<5; i++){
//    }
//}

int main(int argc, const char * argv[]) {
    
    ofstream of("maTresult.txt", ios::trunc);
    ofstream of2("yx.txt" , ios::trunc);
    ofstream of3("G.txt", ios::trunc);
    
    
    std::minstd_rand rnd;
    std::default_random_engine engine(rnd);
    std::normal_distribution<> dist(0,1);
    double pi = 3.14159265;
    
    float h = 0.3;
    float ome = 0.1;
    
    double y[50], x[50];
    double first[50];
    double fx=0.0;

    
    for(int i = 0; i < 50; i++){
        x[i] = -3 + 0.12245 * i;
        y[i] = sin(pi*x[i])/(pi*x[i]) + 0.1*x[i] + 0.05 * dist(engine);
        first[i] = i;
    }
    
    
    Mat matA(50, 1, CV_64F, first);
    Mat matAT(1, 50, CV_64F);
    Mat matA1(50,1,CV_64F);
    Mat matB(50, 1, CV_64F);
    Mat matC(1,1,CV_64F);
    Mat matD(1,1,CV_64F);
    Mat matE(1,1,CV_64F,ome);
    Mat matF(50,1,CV_64F);
    Mat matG(1,1,CV_64F);
    
    double a=5.0;
    int k =0;
    
    
    
    //for(int i=0; i < 50; i++){
    while( a > 0.1){
        int i = rand() % 50 + 1;
        matB = Scalar(0);
        matA1 = Scalar(0);
        matC = Scalar(0);
        matF = Scalar(0);
        for(int j=0; j<50; j++){
            matB.at<double>(j,0)= exp(-((x[i]-x[j])*(x[i]-x[j]))/ (2*h*h));
        }
        matA1 = matA.clone();
        matAT = matA.t();
        matC = matAT*matB;
        //cout << matB << endl;
        fx = matC.at<double>(0,0);
        matD.at<double>(0,0) = fx-y[i];
        matB = matB * matD;
        cout << matD << endl;
        matB = matB * matE;
        matA = matA - matB;
        
        matF = matA-matA1;
        matG = matF.t() * matF;
        a = sqrt(matG.at<double>(0,0));
        k = k + 1;
        //if(a < 0.15){
        //    cout << "i=" << i << endl;
        //    break;
        //}
    }
    //}
    
    cout << "k=" << k << endl;
    cout << matA << endl;
    
    
    
    return 0;
}
