#include <iostream>
#include <bitset>
#include <sstream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>

//#define BYTES_PER_LINE_M 6
//#define print(x) std::cout << x << std::endl;
//unsigned int allocations_G = 0;
//void* operator new(size_t size)
//{
//    ++allocations_G;
//    return malloc(size);
//}


std::stringstream hex_stream_G;
std::string hex_string_G;
const char* DecToHex(const unsigned int& decimal_number, const unsigned int& length_G)
{
    hex_stream_G << std::hex << decimal_number;
    hex_string_G = hex_stream_G.str();
    unsigned int hex_length = hex_string_G.length();
    while(hex_length != length_G && hex_length < length_G+1)
    {
        hex_string_G.insert(0,1, '0');
        ++hex_length;
    }
    hex_stream_G.str("");
    hex_stream_G.clear();
    return hex_string_G.c_str();
}


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
    
    if(bin > 126 || bin < 0 || (bin > -1 && bin < 32))
        bin = 46;

    return bin;
}


int main(int argc, char **argv)
{
    clock_t begin = clock();

    unsigned char BYTES_PER_LINE_M = 6;
    bool console_output = false;
    std::string file_name;

    if(argc < 2 || argc > 5)
    {
        std::cout << "Usage: c2b <filename>" << std::endl;
        return -1;
    }
    else if(argc == 2 && (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h"))
    {
        std::cout << "Usage: c2b <filename>\n";
        std::cout << "       c2b <filename> <options>" << "\n";
        std::cout << "       c2b <filename> <filename> <options> : for output in specific file" << "\n";
        std::cout << "  Options:" << "\n";
        std::cout << "          -c          : for console output" << "\n";
        std::cout << "          -n <number> : to change the number of byte blocks per line" << "\n";
        std::cout << "  Both options can be combined, but if they are combined the" << "\n";
        std::cout << "  -c options has to be used before the -n one" << "\n";
        return -1;
    }
    else if(argc == 3 && (std::string(argv[2]) == "-c" || std::string(argv[2]) == "-C"))
    {
        console_output = true;
    }

    else if(argc == 3)
        file_name = std::string(argv[2]);
    else
        file_name = std::string(argv[1]) + "-Binary.txt";


    if(argc > 2 && (std::string(argv[2]) == "-n" || std::string(argv[2]) == "-N"))
    {
        try {
            BYTES_PER_LINE_M = std::stoi(argv[3]);
        }
        catch (...){
            std::cout << "No valid integer input\n";
            return -1;
        }
    }
    else if(argc == 4 && (std::string(argv[2]) == "-c" || std::string(argv[2]) == "-C") && (std::string(argv[3]) == "-n" || std::string(argv[3]) == "-N"))
    {
       try {
            BYTES_PER_LINE_M = std::stoi(argv[4]);
            console_output = true;
        }
        catch (...){
            std::cout << "No valid integer input\n";
            return -1;
        } 
    }


    std::ifstream input(argv[1], std::ios::binary);
    if(!input) {
        std::cout << "Couldn't open the file\n";
        input.close();
        return -1;
    }

    std::string c_line;
    std::vector<std::string> lines;
    unsigned int line_counter = line_counter ^ line_counter;
    while(std::getline(input, c_line))
        ++line_counter;

    input.clear();
    input.seekg(0, input.beg);
    lines.reserve(line_counter);

    while(std::getline(input, c_line))
        lines.emplace_back(c_line);

    input.close();


    std::ofstream output;
    if(!console_output)
        output.open(file_name);
    
    if(!output)
    {
        std::cout << "Couldn't open the output file\n";
        return -1;
    }

    unsigned int passed_bytes = 0;
    unsigned int line_counter_T = line_counter_T ^ line_counter_T;


    //For the inner loop
    std::string binary_string;
    const char* binary_string_2;
    std::stringstream ss;
    std::stringstream ss2;
    std::stringstream ss3;
    char one;
    std::bitset<8> bit_line; 


    for(int j = 0; j < lines.size(); ++j)
    {
        if(!console_output)
        {
            if(lines[j].back() == 13)
                output << "    " << DecToHex(line_counter_T, 8) << ":  " << lines[j];
            else
                output << "    " << DecToHex(line_counter_T, 8) << ":  " << lines[j] << '\n';
        }
        else
        {
            if(lines[j].back() == 13)
                std::cout << "    " << DecToHex(line_counter_T, 8) << ":  " << lines[j];
            else
                std::cout << "    " << DecToHex(line_counter_T, 8) << ":  " << lines[j] << '\n';
        }


        for(std::size_t i = 0; i < lines[j].size(); ++i)
        {

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
                bit_line.reset();

                if(k != BYTES_PER_LINE_M - 1)
                    ++i;
            }

            ss << ' ';

            if(!console_output)
                output << DecToHex(passed_bytes, 8) << ":  " << ss.str() << ss2.str() << "\n";
            else
                std::cout << DecToHex(passed_bytes, 8) << ":  " << ss.str() << ss2.str() << "\n";
            passed_bytes += BYTES_PER_LINE_M;

            ss.str("");
            ss.clear();

            ss2.str("");
            ss2.clear();

            bit_line.reset();
        }
        ++line_counter_T;
    }

    output.close();
    std::cout << "\nLines: " << DecToHex(line_counter, 0) << " [" << line_counter << "]" << "\n";

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Time spent: " << time_spent << " sec(s)\n";
    //std::cout << "Allocations: " << allocations_G << "\n";
    return 0;
}