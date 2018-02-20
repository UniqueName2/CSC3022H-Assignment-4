#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Image.h"

using namespace ptlsah004;

TEST_CASE("Test Class Move/Copy Construction/Assignment", "[operators]")
{
    u_char* bfr1 = new u_char[9];
    
    bfr1[0] = (u_char)255;
    bfr1[1] = (u_char)255;
    bfr1[2] = (u_char)0;
    bfr1[3] = (u_char)255;
    bfr1[4] = (u_char)0;
    bfr1[5] = (u_char)0;
    bfr1[6] = (u_char)0;
    bfr1[7] = (u_char)255;
    bfr1[8] = (u_char)255;
    
    Image img1(&bfr1, 3, 3);
    
    REQUIRE(img1.getWidth() == 3);
    REQUIRE(img1.getHeight() == 3);

    SECTION("Test Copy Construction")
    {       
        Image img2(img1);
        REQUIRE(img1.getWidth() == 3);
        REQUIRE(img1.getHeight() == 3);
        REQUIRE(img2.getWidth() == 3);
        REQUIRE(img2.getHeight() == 3);
    }
    
    SECTION("Test Copy Assignment")
    {
        Image img2;
        img2 = img1;
        REQUIRE(img1.getWidth() == 3);
        REQUIRE(img1.getHeight() == 3);
        REQUIRE(img2.getWidth() == 3);
        REQUIRE(img2.getHeight() == 3);
    }

    SECTION("Test Move Construction")
    {
        Image img2(std::move(img1));
        REQUIRE(img1.getWidth() == 0);
        REQUIRE(img1.getHeight() == 0);
        REQUIRE(img2.getWidth() == 3);
        REQUIRE(img2.getHeight() == 3);
    }

    SECTION("Test Move Assignment")
    {
        Image img2;
        img2 = std::move(img1);
        REQUIRE(img1.getWidth() == 0);
        REQUIRE(img1.getHeight() == 0);
        REQUIRE(img2.getWidth() == 3);
        REQUIRE(img2.getHeight() == 3);
    }
}

TEST_CASE("Test Class Operators", "[operators]")
{
    u_char* bfr1 = new u_char[9];
    u_char* bfr2 = new u_char[9];

    bfr1[0] = (u_char)255;
    bfr1[1] = (u_char)255;
    bfr1[2] = (u_char)0;
    bfr1[3] = (u_char)255;
    bfr1[4] = (u_char)255;
    bfr1[5] = (u_char)255;
    bfr1[6] = (u_char)0;
    bfr1[7] = (u_char)0;
    bfr1[8] = (u_char)0;

    bfr2[0] = (u_char)0;
    bfr2[1] = (u_char)0;
    bfr2[2] = (u_char)0;
    bfr2[3] = (u_char)0;
    bfr2[4] = (u_char)0;
    bfr2[5] = (u_char)255;
    bfr2[6] = (u_char)255;
    bfr2[7] = (u_char)0;
    bfr2[8] = (u_char)255;

    Image img1(&bfr1, 3, 3);
    Image img2(&bfr2, 3, 3);
    
    SECTION("Test Inversion")
    {
        int arrImg[] = {0, 0, 255, 0, 0, 0, 255, 255, 255};
        Image alt = !img1;
        int i = 0;
        for(Image::iterator itrAlt = alt.begin(); itrAlt != alt.end(); ++itrAlt, i++)
        {
            REQUIRE(arrImg[i] == (int)(*itrAlt));
        } 
    }
    
    SECTION("Test Addition")
    {        
        int arrImg[] = {255, 255, 0, 255, 255, 255, 255, 0, 255};
        Image alt = img1 + img2;
        int i = 0;
        for(Image::iterator itrAlt = alt.begin(); itrAlt != alt.end(); ++itrAlt, i++)
        {
            REQUIRE(arrImg[i] == (int)(*itrAlt));
        }
    }
    
    SECTION("Test Subtraction")
    {
        int arrImg[] = {255, 255, 0, 255, 255, 0, 0, 0, 0};
        Image alt = img1 - img2;
        int i = 0;
        for(Image::iterator itrAlt = alt.begin(); itrAlt != alt.end(); ++itrAlt, i++)
        {
            REQUIRE(arrImg[i] == (int)(*itrAlt));
        } 
    }
    
    SECTION("Test Thresholding")
    {
        int arrImg[] = {255, 255, 0, 255, 255, 255, 0, 0, 0};
        Image alt = img1 * 110;
        int i = 0;
        for(Image::iterator itrAlt = alt.begin(); itrAlt != alt.end(); ++itrAlt, i++)
        {
            REQUIRE(arrImg[i] == (int)(*itrAlt));
        } 
    }

    SECTION("Test Masking")
    {
        int arrImg[] = {0, 0, 0, 0, 0, 255, 0, 0, 0};
        Image alt = img1 / img2;
        int i = 0;
        for(Image::iterator itrAlt = alt.begin(); itrAlt != alt.end(); ++itrAlt, i++)
        {
            REQUIRE(arrImg[i] == (int)(*itrAlt));
        } 
    }  
}
