#include <iostream>
#

bool checkIfEqual(int a, int b, int c, int d, int e, int f, int g, int h){
    int elements [8] = {};
    elements[0] = a;
    elements[1] = b;
    elements[2] = c;
    elements[3] = d;
    elements[4] = e;
    elements[5] = f;
    elements[6] = g;
    elements[7] = h;
    for (int i = 0; i <8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (elements[i] != elements[j])return false;

        }
    }
    return true;
}

int showSquare(int a, int b, int c,int d, int e, int f, int g, int h, int i){
    int sumA = a + b + c;
    int sumB = d + e + f;
    int sumC = g + h + i;
    int sumD = a + d + g;
    int sumE = b + e + h;
    int sumF = c + f + i;
    int sumG = a + e + i;
    int sumH = g + e + c;
    std::cout << "             " << sumH << std::endl;
    std::cout << "------------" << std::endl;
    std::cout << "| " << a << " | " << b << " | " << c << " |" << sumA <<std::endl;
    std::cout << "------------" << std::endl;
    std::cout << "| " << d << " | " << e << " | " << f << " |" << sumB <<std::endl;
    std::cout << "------------" << std::endl;
    std::cout << "| " << g << " | " << h << " | " << i << " |" << sumC << std::endl;
    std::cout << "------------" << std::endl;
    std::cout << sumD << "   " << sumE << "   " << sumF << "  " << sumG << std::endl;

    if (checkIfEqual(sumA,sumB,sumC,sumD,sumE,sumF,sumG,sumH)){
    std::cout << "Magic square" << std::endl;
        return 0;
}
    else {
        std::cout << "Parker square" << std::endl;
        return 1;
}
}


void generateNumbers(int max, int start){
    int squaresCounter = 0;
    int magicCounter = 0;
    for (int a = start; a < max; ++a) {
        for (int b = start; b < max; ++b) {
            for (int c = start; c < max; ++c) {
                for (int d = start; d < max; ++d) {
                    for (int e = start; e < max; ++e) {
                        for (int f = start; f < max; ++f) {
                            for (int g = start; g < max; ++g) {
                                for (int h = start; h < max; ++h) {
                                    for (int i = start; i < max; ++i) {
                                        int result = showSquare(a,b,c,d,e,f,g,h,i);
                                        squaresCounter++;
                                        if (result == 0){
                                            magicCounter++;
                                            std::string bla;
                                            std::cin >> bla;
                                        }
                                        std::cout << "Squares Calculated = " << squaresCounter << std::endl;
                                        std::cout << "Squares Correct = " << magicCounter << std::endl;

                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main(){
    generateNumbers(10,1);
    return 0;
}