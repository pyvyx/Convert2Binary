#include <iostream>
#include <bitset>
#include <sstream>
#include <vector>
#include <fstream>
#include <cmath>

#define BYTES_PER_LINE_M 6


int convert(int& n) {
  int dec = 0, i = 0, rem;

  while (n!=0) {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    ++i;
  }

  return dec;
}


char BinaryStringToText(const std::string& binaryString) {
    //std::string text = "";
    //std::stringstream sstream(binaryString);
    //while (sstream.good())
    //{
    //    std::bitset<8> bits;
    //    sstream >> bits;
    //    text += char(bits.to_ulong());
    //}
    int binary_int = atoi(binaryString.c_str());
    char bin = convert(binary_int);
    
    if(bin > 126 || bin < 0 || (bin >= 0 && bin < 32))
        bin = 46;

    return bin;
}


int main(int argc, char **argv)
{
    bool console_output = false;
    std::string file_name;

    if(argc < 2 || argc > 3)
    {
        std::cout << "Usage: convert2binary <filename>" << std::endl;
        std::cout << std::hex << 12 <<std::endl;
        return -1;
    }
    else if(argc == 3 && (std::string(argv[2]) == "-c" || std::string(argv[2]) == "-C"))
        console_output = true;
    else if(argc == 3)
        file_name = std::string(argv[2]);
    else
        file_name = std::string(argv[1]) + "-Binary.txt";


    std::ifstream input(argv[1]);
    std::string c_line;
    std::vector<std::string> lines;

    while(std::getline(input, c_line))
        lines.push_back(c_line);

    input.close();


    std::ofstream output;
    if(!console_output)
        output.open(file_name);

    unsigned int passed_bytes = 0;
    for(int j = 0; j < lines.size(); ++j)
    {
        if(!console_output)
            output << lines[j] << std::endl;
        else
            std::cout << lines[j] << std::endl;

        for(std::size_t i = 0; i < lines[j].size(); ++i)
        {
            std::string binary_string;
            std::stringstream ss;
            std::stringstream ss2;
            char one;
            std::bitset<8> bit_line; 

            for(int k = 0; k < BYTES_PER_LINE_M; ++k)
            {
                bit_line = std::bitset<8>(lines[j].c_str()[i]);
                binary_string = bit_line.to_string();

                if(binary_string == "00100000" || binary_string == "00000000" || binary_string == "00001001")
                    one = '.';
                else
                    one = BinaryStringToText(binary_string);

                ss << binary_string << ' ';
                ss2 << one;
                if(k != BYTES_PER_LINE_M - 1)
                    ++i;
            }

            ss << ' ';
            binary_string = ss.str();

            std::stringstream hex_stream;
            hex_stream << std::hex << passed_bytes;
            std::string hex_string = hex_stream.str();
            unsigned int hex_length = hex_string.length();
            while(hex_length != 8 && hex_length < 9)
            {
                hex_string.insert(0,1, '0');
                ++hex_length;
            }


            if(!console_output)
                output << hex_string << ":  " << binary_string << ss2.str() << std::endl;
            else
                std::cout << binary_string << ss2.str() << std::endl;
            passed_bytes += BYTES_PER_LINE_M;
        }
    }
    output.close();

    return 0;
}