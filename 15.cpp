#include <iostream>
#include <bitset>
#include <sstream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>

#define print(x) std::cout << x << std::endl;
unsigned int allocations_G = 0;
void* operator new(size_t size)
{
    ++allocations_G;
    return malloc(size);
}


int convert(unsigned long long& n) {
  int dec = 0, i = 0, rem;

  while (n!=0) {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    ++i;
  }

  return dec;
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
    //
    if(bin > 126 || bin < 0 || (bin > -1 && bin < 32))
        bin = 46;
//
    return bin;
    //return 0;
}


char BinaryStringToText(unsigned long long& binaryString) {
    //std::string text = "";
    //std::stringstream sstream(binaryString);
    //while (sstream.good())
    //{
    //    std::bitset<8> bits;
    //    sstream >> bits;
    //    text += char(bits.to_ulong());
    //}
    //int binary_int = atoi(binaryString.c_str());
    char bin = convert(binaryString);
    
    if(bin > 126 || bin < 0 || (bin > -1 && bin < 32))
        bin = 46;

    return bin;
}


char BinaryStringToText(std::bitset<8>& buffer) {
    //std::string text = "";
    //std::stringstream sstream(binaryString);
    //while (sstream.good())
    //{
    //    std::bitset<8> bits;
    //    sstream >> bits;
    //    text += char(bits.to_ulong());
    //}
    //int binary_int = atoi(binaryString.c_str());
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


bool terminationStringsAreSame(const char* buffer)
{
    if(buffer[0] == '0' && buffer[1] == '0' && buffer[2] == '1' && buffer[3] == '0' && buffer[4] == '0' && buffer[5] == '0' && buffer[6] == '0' && buffer[7] == '0')
        return true;
    else if(buffer[0] == '0' && buffer[1] == '0' && buffer[2] == '0' && buffer[3] == '0' && buffer[4] == '0' && buffer[5] == '0' && buffer[6] == '0' && buffer[7] == '0')
        return true;
    else if(buffer[0] == '0' && buffer[1] == '0' && buffer[2] == '1' && buffer[3] == '0' && buffer[4] == '1' && buffer[5] == '0' && buffer[6] == '0' && buffer[7] == '1')
        return true;

    return false;
}


bool terminationStringsAreSame(unsigned long long& buffer)
{
    if((buffer ^ 00100000) == 0 || (buffer ^ 00000000) == 0|| (buffer ^ 00001001) == 0)
        return true;
    return false;
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


int main()
{
    clock_t begin = clock();

    unsigned char BYTES_PER_LINE_M = 6;
    bool console_output = false;
    std::string file_name;


    std::ifstream input("MaintenanceTool.exe", std::ios::binary);
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
        output.open("MaintenanceTool.exe-Binary.txt");
    
    if(!output)
    {
        std::cout << "Couldn't open the output file\n";
        return -1;
    }




    unsigned int passed_bytes = 0;
    unsigned int line_counter_T = line_counter_T ^ line_counter_T;


    //For the inner loop
    //char* buffer = new char[longest_line + 1];
    char buffer_8[9];
    buffer_8[8] = NULL;
    std::string binary_string;
    const char* binary_string_2;
    std::stringstream ss;
    std::stringstream ss2;
    char one;
    std::bitset<8> bit_line; 
    unsigned long long bit_int = 0;


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
                //strncpy(buffer_8, bit_line.to_string().c_str(), 8);
                //bit_int = bit_line.to_ullong();
                //print(bit_line.to_ullong());
                if(terminationStringsAreSame(bit_line))
                    one = '.';
                else
                    one = BinaryStringToText(bit_line);

                ss << bit_line << ' ';
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







    //char *buffer = (char*)malloc( sizeof(char) * ( longest_line + 1 ) );
    //char* buffer = new char[longest_line + 1];
//
    //for(int i = 0; i < longest_line; ++i)
    //    buffer[i] = 'c';
    //buffer[longest_line + 1] = '\n';
//
    //std::cout << "Size: " << sizeof(*buffer) / sizeof(buffer[0]) << std::endl;
    //std::cout << "Length: " << strlen(buffer) << std::endl;

    //delete[] buffer;
    std::cout << "Longest line: " << longest_line << std::endl;
    std::cout << "Allocations: " << allocations_G << std::endl;
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Time spent: " << time_spent << " sec(s)\n";
}