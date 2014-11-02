//
//  main.cpp
//  kawanokadai1
//
//  Created by 合田佑司 on 2014/10/23.
//  Copyright (c) 2014年 合田佑司. All rights reserved.
//

#include <iostream>
#include "opencv2/opencv.hpp"
#include <fstream>
#include <random>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    
    ofstream of("/Users/YujiGoda/Project/kawanokadai1/maTresult.txt", ios::trunc);
    ofstream of2("/Users/YujiGoda/Project/kawanokadai1/yx.txt" , ios::trunc);
    ofstream of3("/Users/YujiGoda/Project/kawanokadai1/G.txt", ios::trunc);
    
    
    std::minstd_rand rnd;
    std::default_random_engine engine(rnd);
    std::normal_distribution<> dist(0,1);
    double pi = 3.14159265;
    
    double y[50], x[50];
    double g[31][50];
    
    double G[1550];
    //double GT[1550];
    
    for(int i = 0; i < 50; i++){
        x[i] = -3 - 0.12245 * i;
        y[i] = sin(pi*x[i]) + 0.1*x[i] + 0.05 * dist(engine);
        
        for(int j=0; j < 31; j++){
            if(j==0){
                g[j][i] = 1;
            }
            else{
                int w = j % 2;
                if(w == 0){
                    g[j][i] = cos(((j/2)*x[i])/2);
                }
                else{
                    g[j][i] = sin((((j+1)/2)*x[i])/2);
                }
            }
        }
    }
    
    for(int j=0; j<50;j++){
        for(int i=0; i<31; i++){
            G[i*j]=g[i][j];
        }
    }
    
    Mat matG(50, 31, CV_64F , G);
    Mat matGT(31, 50, CV_64F );
    Mat matGTG(31, 31, CV_64F );
    Mat matY(50, 1, CV_64F , y);
    Mat matGTGGT(31, 50, CV_64F );
    Mat matA(31, 1, CV_64F);
    
    matGT = matG.t();
    
    
    matGTG = matGT * matG;
    matGTGGT = matGTG.inv() * matGT;
    matA = matGTGGT * matY;
    
    cout << matGTGGT << endl;
    
    for(int i = 0; i < 50; i++){
        of2 << i+1 <<"  x = " << x[i] << ", y = " << y[i] << endl;
    }
    for(int i =0; i<31; i++){
        of << i+1 << "  " << matA.at<double>(i,0) << endl;
    }
    
    
    of.close();
    of2.close();
    of3.close();
    
    
    
    return 0;
}