//
//  main.cpp
//  TextCop
//
//  Created by 合田佑司 on 2014/10/19.
//  Copyright (c) 2014年 合田佑司. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char * argv[]) {
     //insert code here...
    ifstream ifs("/Users/YujiGoda/Project/TextCopy/textable.txt");
    if(!ifs){
        cout << "ERROR" << endl;
        return -1;
    }
    
    char str;
    int n = 0;
    ofstream ofs("/Users/YujiGoda/Project/TextCopy/textable2.txt");

    
    ofs << "\\begin{table*}" << endl << "\\caption{}" << endl << "\\label{}" << endl << "\\bigin{center}" << endl << "\\begin{tabular}{}" << "\\hline" << endl;
        
    while(ifs.get(str)){
        if(n == 0){
            ofs << str;
            n = 1;
        }
        else if(n != 0 && str != ' ' && str != '\n'){
            ofs << str;
        }
        else if(n != 0 && str == ' '){
            ofs << " " << "&" << " ";
        }
        if(str == '\n'){
            ofs << "\\\\" << endl << "\\hline" << endl;
            n = 0;
        }
        
    }
    
    ofs << "\\end{tabular}" << endl << "\\end{center}" << endl << "\\end{table*}";
    
    ifs.close();
    ofs.close();
    
    return 0;
}
