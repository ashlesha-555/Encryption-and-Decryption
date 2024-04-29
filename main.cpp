#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <vector>

using namespace std;

vector<int> concatenateNumber(const string& str, int number) {
    string concatenatedNumber;
    while (concatenatedNumber.length() < str.length()) {
        concatenatedNumber += to_string(number);
    }

    concatenatedNumber = concatenatedNumber.substr(0, str.length());

    vector<int> result;
    for (char c : concatenatedNumber) {
        result.push_back(c - '0');
    }

    return result;
}

vector<int> stringToAsciiArray(const string& str) {
    vector<int> asciiArray;
    for (char c : str) {
        asciiArray.push_back(static_cast<int>(c));
    }
    return asciiArray;
}

string circularLeftShift(const string& binaryStr, int shift) {
    int n = binaryStr.length();
    return binaryStr.substr(shift % n) + binaryStr.substr(0, shift % n);
}

string circularRightShift(const string& binaryStr, int shift) {
    int n = binaryStr.length();
    return binaryStr.substr(n - shift % n) + binaryStr.substr(0, n - shift % n);
}

int binaryToDecimal(const string& binaryStr) {
    return bitset<8>(binaryStr).to_ulong();
}

string asciiArrayToString(const vector<int>& asciiArray) {
    string result;
    for (int ascii : asciiArray) {
        result += static_cast<char>(ascii);
    }
    return result;
}

vector<int> calculate_expression(const string& a, const vector<int>& b) {
    vector<int> result;

    if (a.length() != b.size()) {
        cerr << "Error: Strings have different lengths." << endl;
        return result;
    }

    for (size_t i = 0; i < a.length(); ++i) {
        int ascii_val = static_cast<int>(a[i]);
        int num_b = b[i];

        int expr_result = ascii_val + i * num_b;

        result.push_back(expr_result);
    }

    return result;
}

string decrypt_expression(const vector<int>& result, const vector<int>& b) {
    string decrypted = "";

    for (size_t i = 0; i < result.size(); ++i) {
        int num_b = b[i];

        int ascii_val = result[i] - i * num_b;

        decrypted += static_cast<char>(ascii_val);
    }

    return decrypted;
}


int main(int argc, char* argv[]) {
    if (argc != 6) {
        cerr << "Usage: " << argv[0] << " <Encrypt|Decrypt> <xrot|xplus> <Password> <InputFile> <OutputFile>" << endl;
        return 1;
    }

    string choice1 = argv[1];
    string choice2 = argv[2];
    int password = stoi(argv[3]);
    string inputFile = argv[4];
    string outputFile = argv[5];

    ifstream input(inputFile);
    ofstream output(outputFile);

    if (!input.is_open()) {
        cerr << "Error: Unable to open " << inputFile << endl;
        return 1;
    }

    if (!output.is_open()) {
        cerr << "Error: Unable to create " << outputFile << endl;
        return 1;
    }

    string inputStr;
    getline(input, inputStr);

    vector<int> extendedPass = concatenateNumber(inputStr, password);
    vector<int> asciiArray = stringToAsciiArray(inputStr);

    if (choice1 == "Encrypt") {
        if (choice2 == "xrot") {
            vector<int> encoded;

            for (size_t i = 0; i < asciiArray.size(); i++) {
                string binaryStr = bitset<8>(asciiArray[i]).to_string();
                int shift = extendedPass[i];
                string shiftedBinaryStr = circularLeftShift(binaryStr, shift);
                int temp = binaryToDecimal(shiftedBinaryStr);
                encoded.push_back(temp);
            }

            string result = asciiArrayToString(encoded);

            output << result << endl;
        } else {
            vector<int> encoded = calculate_expression(inputStr, extendedPass);
            string result = asciiArrayToString(encoded);
            output << result << endl;
        }
    } else {
        if (choice2 == "xrot") {
            vector<int> decoded;

            for (size_t i = 0; i < asciiArray.size(); i++) {
                string binaryStr = bitset<8>(asciiArray[i]).to_string();
                int shift = extendedPass[i];
                string shiftedBinaryStr = circularRightShift(binaryStr, shift);
                int temp = binaryToDecimal(shiftedBinaryStr);
                decoded.push_back(temp);
            }

            string result = asciiArrayToString(decoded);

            output << result << endl;
        } else {
            string result = decrypt_expression(asciiArray, extendedPass);
            output << result << endl;
        }
    }

    input.close();
    output.close();

    return 0;
}
