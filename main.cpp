#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE][RGB];
unsigned char flipp[SIZE][SIZE][RGB];

void BW(){
    for (int i=0;i<SIZE;i++){
        for (int j=0;j<SIZE;j++){
            for (int k=0;k<RGB;k++){
                int avr = (image[i][j][0]+image[i][j][1]+image[i][j][2])/3;
                if (avr > 127) image[i][j][k] = 255;
                else image[i][j][k] = 0;
            }
        }
    }
}
void invert() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k=0;k<RGB;k++){
                image[i][j][k] = 255 - image[i][j][k];
            }
            }

        }

}
void mirror(char string1[100] , char c1){
    if (c1 == 'l'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for (int k = 0; k < RGB; k++)
                    image[i][256 - j][k] = image[i][j][k];

            }
        }
    }
    else if (c1 == 'r'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for (int k=0;k<RGB;k++){
                    image[i][j][k] = image[i][256-j][k];
                }
            }
        }
    }
    else if (c1 == 'u'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for (int k=0;k<RGB;k++){
                    image[256-i][j][k] = image[i][j][k];
                }
            }
        }
    }
    else if (c1 == 'd'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for (int k=0;k<RGB;k++){
                    image[i][j][k] = image[256-i][j][k];
                }
            }
        }
    }
}
void flip(char string1[100] , char cc){
    if (cc == 'h'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< (SIZE/2); j++) {
                for (int k=0;k<RGB;k++){
                    flipp[i][j][k] = image[i][256-j][k];
                    image[i][256-j][k] = image[i][j][k];
                    image[i][j][k] = flipp[i][j][k];
                }
            }
        }
    }
    else if (cc == 'v'){
        for (int i = 0; i < (SIZE/2); i++) {
            for (int j = 0; j< (SIZE); j++) {
                for (int k=0;k<RGB;k++){
                    flipp[i][j][k] = image[256-i][j][k];
                    image[256-i][j][k] = image[i][j][k];
                    image[i][j][k] = flipp[i][j][k];
                }
            }
        }
    }
}
void crop(char string1[100] , int x,int y,int l,int w){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k=0;k<RGB;k++){
                if (i>=x and j >= y and (i<=(l+x)) and (j<=(w+y))) {
                    image[i][j][k] = image[i][j][k];
                }
                else {
                    image[i][j][k] = 255;
                }
            }
        }
    }
}
void detect(char string1[100]){
    BW();
    for (int i=0;i < SIZE;i++){
        for (int j=0;j < SIZE ; j++) {
            for (int k=0;k<RGB;k++){
                if (( (image[i][j][k] - image[i][j+1][k] >= 30) or (image[i][j+1][k] - image[i][j][k] >= 30))
                    or ((image [i][j][k] - image[i+1][j][k]>=30) or(image[i+1][j][k] - image[i][j][k] >= 30))){
                    image[i][j][k] =0;
                }
                else {
                    image[i][j][k] = 255;
                }
            }
        }
    }
}
void blurImg()
{
    for (int row = 0; row < SIZE; ++row)
    {
        for (int coloum = 0; coloum <SIZE; ++coloum)
        {
            for(int rg=0; rg<3; rg++)
            {
                int val=0;
                int cnt=0;
                for (int i = 0; i <10 ; ++i)
                {
                    for (int j = 0; j <10 ; ++j)
                    {
                        if(i+row< SIZE &&j+coloum<SIZE)
                        {
                            val+=image[i+row][j+coloum][rg];
                            cnt++;
                        }
                    }
                }
                image[row][coloum][rg]=val/cnt;
            }


        }
    }

}
void skewRGB() {
    char n;
    std::cout << "h-Horizontally\nv-Vertically\n";
    std::cin >> n;

    // Read the skew angle in degrees
    double rad;
    std::cout << "Please enter degree to skew right: ";
    std::cin >> rad;

    // Convert the angle to radians
    rad = (rad * M_PI) / 180.0;

    // Calculate the amount of horizontal movement (no need to calculate `mov` here)
    double mov = tan(rad);

    // Create a temporary image array with the skewed dimensions
    unsigned char resultRGB[SIZE][SIZE][RGB];

    // Initialize the temporary image with white pixels
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                resultRGB[i][j][k] = 255;
            }
        }
    }

    if (n == 'h' || n == 'H') {
        // Horizontal skew
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                int newJ = j + static_cast<int>(mov * (SIZE / 2 - i));
                if (newJ >= 0 && newJ < SIZE) {
                    for (int k = 0; k < RGB; k++) {
                        resultRGB[i][newJ][k] = image[i][j][k];
                    }
                }
            }
        }
    } else {
        // Vertical skew
        for (int j = 0; j < SIZE; j++) {
            for (int i = 0; i < SIZE; i++) {
                int newI = i + static_cast<int>(mov * (SIZE / 2 - j));
                if (newI >= 0 && newI < SIZE) {
                    for (int k = 0; k < RGB; k++) {
                        resultRGB[newI][j][k] = image[i][j][k];
                    }
                }
            }
        }
    }

    // Copy the skewed image from resultRGB back to imageRGB
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                image[i][j][k] = resultRGB[i][j][k];
            }
        }
    }
    showRGBBMP(image);
}


void mergeImg()
{
    unsigned char Mergeimage[SIZE][SIZE][RGB];
    //First we store the data of array image in mergeImage array
    for (int row = 0; row < SIZE; ++row)
    {
        for (int coloum = 0; coloum <SIZE ; ++coloum)
        {
            for (int k = 0 ; k<RGB ; k++)
            {
                Mergeimage[row][coloum][k]=image[row][coloum][k];

            }
        }
    }
}

void Rotate90(unsigned char img[][SIZE][RGB])
{
    unsigned char temp[SIZE][SIZE][RGB];
    int row=0,col=0;
    for (int r = SIZE - 1; r >= 0 ; --r)
    {
        for (int c = 0; c < SIZE ; ++c)
        {
            for(int rg=0; rg<3; rg++)
            {
                temp[row][col][rg]=img[r][c][rg];
            }
            col++;
        }
        row++;
        col=0;
    }
    // fill the img grid with the temp after rotate 90
    for (int r = 0; r < SIZE ; ++r)
    {
        for (int c = 0; c < SIZE ; ++c)
        {
            for(int rg=0; rg<3; rg++)
            {
                img[r][c][rg]=temp[c][r][rg];
            }
        }
    }
}
/*
* This function we use it to make all rotation angle we need
* like 180 , 270 .. if we need to make that we call function Rotate90
*/
void rotateImg()
{
    while (true)
    {
        int choice;
        cout<<"Rotate (90), (180) or (360) degrees? \n ";
        cin>>choice;

        if(choice==90)
        {
            Rotate90(image);
            break;
        }

        else if(choice==180)
        {

            Rotate90(image);
            Rotate90(image);
            break;
        }

        else if(choice==270)
        {
            Rotate90(image);
            Rotate90(image);
            Rotate90(image);
            break;
        }
        else
        {
            cout<<"Invalid angle rotation\n";
        }
    }


}
void EnlargeImg()
{

    while (true)
    {
        int part;
        cout<<"Which quarter to enlarge 1, 2, 3 or 4? \n";
        cin>>part;
        if(part>4 ||part<0)
        {
            cout<<"Invalid input try again\n";
            continue;
        }
        int row=0,col=0;
        unsigned char tempImg[SIZE/2+1][SIZE/2+1][RGB];
        if(part==1)
        {
            //row from 0 to 127 ,coloum from 0 to 127
            for (int i = 0; i <SIZE/2 ; ++i)
            {
                for (int j = 0; j <SIZE/2 ; ++j)
                {
                    for(int rg=0; rg<3; rg++)
                    {
                        tempImg[row][col][rg]=image[i][j][rg];

                    }
                    col++;
                }
                row++;
                col=0;
            }

        }
        else if(part==2)
        {
            //row from 0 to 127 ,coloum from 127 to 255
            for (int i = 0; i <SIZE/2 ; ++i)
            {
                for (int j = 127; j <SIZE ; ++j)
                {
                    for(int rg=0; rg<3; rg++)
                    {
                        tempImg[row][col][rg]=image[i][j][rg];

                    }
                    col++;
                }
                row++;
                col=0;
            }
        }
        else if(part==3)
        {
            //row from 127 to 255 ,coloum from 0 to 128
            for (int i = 127; i <SIZE ; ++i)
            {
                for (int j = 0; j <SIZE/2 ; ++j)
                {
                    for(int rg=0; rg<3; rg++)
                    {
                        tempImg[row][col][rg]=image[i][j][rg];
                    }

                    col++;
                }
                row++;
                col=0;

            }
        }
        else if (part==4)
        {
            //row from 127 to 255 ,coloum from 127 to 256
            for (int i = 127; i <SIZE ; ++i)
            {
                for (int j = 127; j <SIZE ; ++j)
                {
                    for(int rg=0; rg<3; rg++)
                    {
                        tempImg[row][col][rg]=image[i][j][rg];
                    }
                    col++;
                }
                row++;
                col=0;
            }
        }
        row=0,col=0;
        for (int i = 0; i <SIZE/2 ; ++i)
        {
            for (int j = 0; j <SIZE/2 ; ++j)
            {
                for(int rg=0; rg<3; rg++)
                {
                    if(row<SIZE &&col<SIZE)
                    {
                        image[row][col][rg]=  tempImg[i][j][rg];
                    }
                    if(row<SIZE &&col+1<SIZE)
                    {
                        image[row][col+1][rg]=  tempImg[i][j][rg];
                    }
                    if(row+1<SIZE &&col<SIZE)
                    {
                        image[row+1][col][rg]=tempImg[i][j][rg];
                    }
                    if(row+1<SIZE &&col+1<SIZE)
                    {
                        image[row+1][col+1][rg]=tempImg[i][j][rg];
                    }
                }
                col+=2;
            }
            row+=2;
            col=0;
        }
        break;
    }


}

void shuffleImg()
{
    cout<<"New order of quarters ? \n";
    int parts[5];
    for (int i = 1; i <=4 ; ++i)
    {
        cin>>parts[i];
    }
    int size=(SIZE/2+1)*(SIZE/2+1)*(RGB+1);
    int grid[5][size];
    //store first part from image from 0 to 127 row ,0 to 127 column
    int index=0;
    for (int row = 0; row <SIZE/2 ; ++row)
    {
        for (int column = 0; column <SIZE/2 ; ++column)
        {
            for(int rg=0; rg<3; rg++)
            {
                grid[1][index]=image[row][column][rg];
                index++;
            }

        }
    }
    index=0;
    //store second part from image from 0 to 127 row ,127 to 255 column
    for (int row = 0; row <SIZE/2 ; ++row)
    {
        for (int column = SIZE/2; column <SIZE; ++column)
        {
            for(int rg=0; rg<3; rg++)
            {
                grid[2][index]=image[row][column][rg];
                index++;
            }

        }
    }
    for (int row = SIZE/2; row <SIZE ; ++row)
    {
        for (int column =0; column <SIZE/2; ++column)
        {
            for(int rg=0; rg<3; rg++)
            {
                grid[3][index]=image[row][column][rg];
                index++;
            }

        }
    }
    index=0;
    for (int row = SIZE/2; row <SIZE ; ++row)
    {
        for (int column =SIZE/2; column <SIZE; ++column)
        {
            for(int rg=0; rg<3; rg++)
            {
                grid[4][index]=image[row][column][rg];
                index++;
            }

        }
    }
    index=0;
    for (int row = 0; row <SIZE/2 ; ++row)
    {
        for (int column = 0; column <SIZE/2 ; ++column)
        {
            for(int rg=0; rg<3; rg++)
            {
                image[row][column][rg]=grid[parts[1]][index]; // [2][2]   // [1][0]
                index++;
            }

        }
    }
    index=0;
    for (int row = 0; row <SIZE/2 ; ++row)
    {
        for (int column = SIZE/2; column <SIZE; ++column)
        {
            for(int rg=0; rg<3; rg++)
            {
                image[row][column][rg]=grid[parts[2]][index];
                index++;
            }

        }
    }
    index=0;
    for (int row = SIZE/2; row <SIZE ; ++row)
    {
        for (int column =0; column <SIZE/2; ++column)
        {
            for(int rg=0; rg<3; rg++)
            {
                image[row][column][rg]=grid[parts[3]][index];
                index++;
            }

        }
    }
    index=0;
    for (int row = SIZE/2; row <SIZE ; ++row)
    {
        for (int column =SIZE/2; column <SIZE; ++column)
        {
            for(int rg=0; rg<3; rg++)
            {
                image[row][column][rg]=grid[parts[4]][index];
                index++;
            }

        }
    }
}

void shrinkImg()
{
    int op;
    unsigned char ImageShrink[SIZE][SIZE][RGB];
    for (int row = 0; row <SIZE ; ++row)
    {
        for (int coloum = 0; coloum <SIZE ; ++coloum)
        {
            for(int rg=0; rg<3; rg++)
            {
                ImageShrink[row][coloum][rg]=255;
            }

        }
    }
    cout<<"1-Shrink to (1/2)\n";
    cout<<"2-Shrink to (1/3)\n";
    cout<<"3-Shrink to (1/4)\n";
    int r=0,c=0;
    cin>>op;
    if(op==1)
    {

        for (int row = 0; row <SIZE ; row+=2)
        {
            for (int coloum = 0; coloum <SIZE ; coloum+=2)
            {
                for(int rg=0; rg<3; rg++)
                {
                    ImageShrink[r][c][rg]=image[row][coloum][rg];
                }

                c++;
            }
            c=0;
            r++;
        }

    }
    else if(op==2)
    {
        for (int row = 0; row <SIZE ; row+=3)
        {
            for (int coloum = 0; coloum <SIZE ; coloum+=3)
            {
                for(int rg=0; rg<3; rg++)
                {
                    ImageShrink[r][c][rg]=image[row][coloum][rg];
                }

                c++;
            }
            c=0;
            r++;
        }
    }
    else if(op==3)
    {
        for (int row = 0; row <SIZE ; row+=4)
        {
            for (int coloum = 0; coloum <SIZE ; coloum+=4)
            {
                for(int rg=0; rg<3; rg++)
                {
                    ImageShrink[r][c][rg]=image[row][coloum][rg];

                }

                c++;
            }
            c=0;
            r++;
        }
    }

    for (int row = 0; row <SIZE ; ++row)
    {
        for (int coloum = 0; coloum <SIZE ; ++coloum)
        {
            for(int rg=0; rg<3; rg++)
            {
                image[row][coloum][rg]= ImageShrink[row][coloum][rg];
            }

        }
    }
}



int main(){
    char imageFileName[100];

    cout << "Enter the source image file name: ";
    cin >> imageFileName;



    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);

    bool flag = true;
    int number;
    while (flag) {
        cout << "Please choose a filter\n"
                "1-Black & White Filter\n"
                "2-Invert Image \n"
                "3-mirror Image  \n"
                "4-Flip Image\n"
                "5-Rotate Image\n"
                "6-Darken and Lighten Image \n"
                "7- Merge Image\n"
                "8- Rotate Image\n"
                "9- Enlarge Image\n"
                "10- Shuffle Image\n"
                "11- Shrink Image\n"
                "12- blur image\n"
                "13- crop image\n"
                "14- skew image right or up\n"
                "15- Save the image to a file\n" ;
                "0-Exit/n";
        cin >> number;
        switch (number) {
            case 1:
                BW();
                break;

            case 2:
                invert();
                break;

            case 3:
                char ccc;
                cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side? "<<'\n';
                cin>>ccc;
                mirror(imageFileName , ccc);
                break;

            case 4:
                char ch;
                cout<<"flip (h)orizontally or (v)ertically ?"<<'\n';
                cin>>ch;
                flip(imageFileName,ch);
                break;

            case 5:
                int xx,yy,length,width;
                cout<<"Please enter x , y , length ,  width : ";
                cin>>xx>>yy>>length>>width;
                crop(imageFileName,xx,yy,length,width);
                break;

            case 6:
                detect(imageFileName);
                break;
            case 7:
                void mergeImg();
                break;
            case 8:
                void rotateImg();
                break;
            case 9:
                void EnlargeImg();
                break;
            case 10:
                void shuffleImg();
                break;
            case 11:
                void shrinkImg();
                break;
            
            case 12:
                blurImg();
                break;

            case 13:
                int xx, yy, length, width;
                cout << "Please enter x , y , length ,  width : ";
                cin >> xx >> yy >> length >> width;
                crop(imageFileName, xx, yy, length, width);
                break;


            case 14:
                skewRGB();
                break;
            case 15:
                strcat (imageFileName, ".bmp");
                writeRGBBMP(imageFileName, image);
                cout<<endl<<"Successfully Saved ! \n"<<endl;
                break;

            case 0:
                cout << "Exit";
                cout<<endl<<" final result is Successfully Saved ! \n"<<endl;
                flag = false;
                break;

        }
    }
    return 0;
}
