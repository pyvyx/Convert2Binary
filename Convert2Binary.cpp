#include <iostream>
#include <bitset>
#include <sstream>
#include <vector>
#include <fstream>
#include <cmath>

//#define BYTES_PER_LINE_M 6


std::string DecToHex(const unsigned int& decimal_number, const unsigned int& length_G)
{
    std::stringstream hex_stream;
    hex_stream << std::hex << decimal_number;
    std::string hex_string = hex_stream.str();
    unsigned int hex_length = hex_string.length();
    while(hex_length != length_G && hex_length < length_G+1)
    {
        hex_string.insert(0,1, '0');
        ++hex_length;
    }

    return hex_string;
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
    
    if(bin > 126 || bin < 0 || (bin >= 0 && bin < 32))
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
    {
        lines.push_back(c_line);
        ++line_counter;
    }

    //std::cout << "Lines: " << DecToHex(line_counter, 0) << " [" << line_counter << "]" << "\n";
    input.close();


    std::ofstream output;
    if(!console_output)
        output.open(file_name);

    unsigned int passed_bytes = 0;
    unsigned int line_counter_T = line_counter_T ^ line_counter_T;
    for(int j = 0; j < lines.size(); ++j)
    {
        std::string line_hex = DecToHex(line_counter_T, 8);

        if(!console_output)
        {
            if(lines[j].back() == 13)
                output << "    " << line_hex << ":  " << lines[j];
            else
                output << "    " << line_hex << ":  " << lines[j] << '\n';
        }
        else
        {
            if(lines[j].back() == 13)
                std::cout << "    " << line_hex << ":  " << lines[j];
            else
                std::cout << "    " << line_hex << ":  " << lines[j] << '\n';
        }

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

            // store line count as hex number
            //std::stringstream hex_stream;
            //hex_stream << std::hex << passed_bytes;
            //std::string hex_string = hex_stream.str();
            //unsigned int hex_length = hex_string.length();
            //while(hex_length != 8 && hex_length < 9)
            //{
            //    hex_string.insert(0,1, '0');
            //    ++hex_length;
            //}
            std::string hex_string = DecToHex(passed_bytes, 8);


            if(!console_output)
                output << hex_string << ":  " << binary_string << ss2.str() << "\n";
            else
                std::cout << hex_string << ":  " << binary_string << ss2.str() << "\n";
            passed_bytes += BYTES_PER_LINE_M;
        }
        ++line_counter_T;
    }
    
    output.close();
    std::cout << "\nLines: " << DecToHex(line_counter, 0) << " [" << line_counter << "]" << "\n";

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Time Spent: " << time_spent << "\n";
    return 0;
}