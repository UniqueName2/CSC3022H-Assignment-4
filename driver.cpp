#include <iostream>
#include <string>

#include "Image.h"

void howToUse()
{
   std::cout << "imageops <option> outputImageName.pgm";
   std::cout << "\nOptions:\n";
   std::cout <<"\tInverse:   "<< "\t-i img1" <<"\n";
   std::cout <<"\tAdd:       "<< "\t-a img1 img2" <<"\n";
   std::cout <<"\tSubtract:  "<< "\t-s img1 img2" <<"\n";
   std::cout <<"\tMask:      "<< "\t-l img1 img2" <<"\n";
   std::cout <<"\tThresehold:"<< "\t-t img1 f" <<std::endl;
}

int main(int argc, char* argv[])
{
    using namespace ptlsah004;
    
    std::string op = argv[1];
    Image orig;
    Image alt;
    Image img1; 
    Image img2;
    std::string inFname;
    std::string oFname;

    if (argc == 4)
    {   
        //Invert
        if(op == "-i")
        {
            inFname = argv[2];
            oFname = argv[3];
            
            orig.load(inFname);
            alt = !orig;
            alt.save(oFname);
            
            std::cout << "Inverted " << inFname << "." << std::endl;
            std::cout << "Result saved to " << oFname << "." << std::endl;
        }
        else
        {
            std::cout<< "Error:\t No. Args given: "<<argc<<"\nCorrect usage:"<<std::endl;
            howToUse();
        }
    }

    else if(argc == 5)
    {   
        oFname = argv[4];

        if (op == "-s" || op == "-a" || op == "-l")
        {
            std::string file_1;
            std::string file_2;
             
            file_1 = argv[2];
            file_2 = argv[3];
            
            img1.load(file_1);
            img2.load(file_2);

            //Add
            if(op == "-a")
            {   
                alt = img1 + img2;   
                std::cout <<"Added"<< file_1 << " to " << file_2 << std::endl;
            }
            //Subtract
            else if(op == "-s")
            {
                alt = img1 - img2;
                std::cout <<"Subtracted"<< file_2 << " from " << file_1 << std::endl;
            }
            //Mask
            else if(op == "-l")
            {   
                alt = img1 / img2;
                std::cout << "Masked" <<file_1 << " with " << file_2 << std::endl;
            }
            alt.save(oFname);
            std::cout<<"New Image saved to: " << oFname << std::endl;

        }
        //Threshold
        else if(op == "-t")
        {
            inFname = argv[2];
            int threshold = std::stoi(argv[3]);
            
            orig.load(inFname);
            alt = orig * threshold;
            
            std::cout << "Thresholded " << inFname << " with " << threshold << std::endl;
            alt.save(oFname);
            std::cout<<"New Image saved to: " << oFname << std::endl;
        }

        else
        {
            std::cout<< "Error:\t No. Args given: "<<argc<<"\nCorrect usage:"<<std::endl;
            howToUse();
        }
        
    }
    else
    {
        std::cout<< "Error:\t No. Args given: "<<argc<<"\nCorrect usage:"<<std::endl;
        howToUse();
    }
    
    return 0;
}