#include <iostream>
#include <bitset>
#include <sstream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>


#define DEBUG 0

#if DEBUG
#define print(x) std::cout << x << std::endl;
unsigned int allocations_G = 0;
void* operator new(size_t size)
{
    ++allocations_G;
    return malloc(size);
}
#endif


char BinaryStringToText(std::bitset<8>& buffer) {
    unsigned long bin = buffer.to_ulong();
    
    if(bin > 126 || bin < 0 || (bin > -1 && bin < 32))
        bin = 46;

    return bin;
}

void printHelpMessage()
{
    std::cout << "Usage: c2b <filename>\n";
    std::cout << "       c2b <filename> <options>" << "\n";
    std::cout << "       c2b <filename> <filename> <options> : for output in specific file" << "\n";
    std::cout << "  Options:" << "\n";
    std::cout << "          -c          : for console output" << "\n";
    std::cout << "          -n <number> : to change the number of byte blocks per line" << "\n";
    std::cout << "  Both options can be combined, but if they are combined the" << "\n";
    std::cout << "  -c options has to be used before the -n one" << "\n";
}


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


bool terminationStringsAreSame(std::bitset<8>& buffer)
{
    if(buffer[0] == 0 && buffer[1] == 0 && buffer[2] == 1 && buffer[3] == 0 && buffer[4] == 0 && buffer[5] == 0 && buffer[6] == 0 && buffer[7] == 0)
        return true;
    else if(buffer[0] == 0 && buffer[1] == 0 && buffer[2] == 0 && buffer[3] == 0 && buffer[4] == 0 && buffer[5] == 0 && buffer[6] == 0 && buffer[7] == 0)
        return true;
    else if(buffer[0] == 0 && buffer[1] == 0 && buffer[2] == 1 && buffer[3] == 0 && buffer[4] == 1 && buffer[5] == 0 && buffer[6] == 0 && buffer[7] == 1)
        return true;

    return false;
}


std::string bitToString(std::vector<std::bitset<8>>& vec)
{
    std::string result;
    for(int i = 0; i < vec.size(); ++i)
    {
        result += vec[i].to_string() + ' ';
    }
    result += ' ';
    return result;
}


std::string charToString(std::vector<char>& vec)
{
    std::string result;
    for(int i = 0; i < vec.size(); ++i)
    {
        result += vec[i];
    }
    return result;
}



int main(int argc, char **argv)
{
    clock_t begin = clock();

    unsigned char BYTES_PER_LINE_M = 6;
    bool console_output = false;
    std::string file_name;


    //Input handling
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
    unsigned int longest_line = longest_line ^ longest_line;
    while(std::getline(input, c_line))
    {
        if(c_line.length() > longest_line)
            longest_line = c_line.length();
        ++line_counter;
    }

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




    unsigned int passed_bytes = passed_bytes ^ passed_bytes;
    unsigned int line_counter_T = line_counter_T ^ line_counter_T;


    //For the inner loop
    char one;
    std::bitset<8> bit_line; 
    std::vector<std::bitset<8>> bit_vec;
    std::vector<char> char_vec;

    bit_vec.reserve(BYTES_PER_LINE_M);
    char_vec.reserve(BYTES_PER_LINE_M);



    for(int j = 0; j < lines.size(); ++j)
    {
        if(!console_output)
        {
            if(lines[j].back() == 13)
                output << "    " << DecToHex(line_counter_T,8) << ":  " << lines[j];
            else
                output << "    " << DecToHex(line_counter_T,8) << ":  " << lines[j] << '\n';
        }
        else
        {
            if(lines[j].back() == 13)
                std::cout << "    " << DecToHex(line_counter_T,8) << ":  " << lines[j];
            else
                std::cout << "    " << DecToHex(line_counter_T,8) << ":  " << lines[j] << '\n';
        }


        for(std::size_t i = 0; i < lines[j].size(); ++i)
        {
            for(int k = 0; k < BYTES_PER_LINE_M; ++k)
            {
                bit_line = std::bitset<8>(lines[j].c_str()[i]);

                if(terminationStringsAreSame(bit_line))
                    one = '.';
                else
                    one = BinaryStringToText(bit_line);

                bit_vec.emplace_back(bit_line);
                char_vec.emplace_back(one);
                bit_line.reset();

                if(k != BYTES_PER_LINE_M - 1)
                    ++i;
            }


            if(!console_output)
                output << DecToHex(passed_bytes,8) << ":  " << bitToString(bit_vec) << charToString(char_vec) << "\n";
            else
                std::cout << DecToHex(passed_bytes,8) << ":  " << bitToString(bit_vec) << charToString(char_vec) << "\n";


            passed_bytes += BYTES_PER_LINE_M;

            bit_vec.clear();
            char_vec.clear();
            bit_line.reset();
        }
        ++line_counter_T;
    }
    output.close();

    #if DEBUG
    std::cout << "\nLines: " << std::hex << line_counter << std::dec << " [" << line_counter << "]" << std::endl;
    std::cout << "Longest line: " << longest_line << std::endl;
    std::cout << "Allocations: " << allocations_G << std::endl;
    #endif

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Execution time: " << time_spent << " sec(s)\n";
}