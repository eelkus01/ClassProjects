#include "BinaryIO.h"

#include <algorithm>
#include <bitset>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

const string __ZAPFILE_STAMP = "ZAP";

/* Given binary file ++filename++ which was created by BinaryIO::writeFile(),
 * decodes into a serialized tree and an encoded string of 0s and 1s.
 * Returns a 2-element vector: element 0 contains the serialized tree,
 * and element 1 contains the encoded message.
 */
pair<string, string> BinaryIO::readFile(const string &filename) {
    ifstream bin_file;
    open_or_die(bin_file, filename);

    // First verify that the file starts off with the expected stamp.
    // If not, throw exception.
    for (auto &c : __ZAPFILE_STAMP) {
        char read_c;
        bin_file.get(read_c);
        if (c != read_c) {
            throw runtime_error(
                "BinaryIO::readFile() expected zap file. "
                "Given: " +
                filename);
        }
    }

    // First 4 bytes of file should be length of the serialized tree.
    int tree_len;
    bin_file.read(reinterpret_cast<char *>(&tree_len), sizeof(uint32_t));
    // Next, we have the tree itself.
    stringstream tree_stream;
    while (tree_len > 0) {
        char c;
        bin_file.get(c);
        tree_stream << c;
        tree_len--;
    }

    // Next 4 bytes of file should be length of the subsequent binary encoding.
    int strlen;
    bin_file.read(reinterpret_cast<char *>(&strlen), sizeof(uint32_t));

    // Next: Read 1 byte at a time, then send each bit of the byte to bitstream.
    char currChar;
    stringstream bitstream;
    while (bin_file.get(currChar)) {
        bitset<8> byt(currChar);
        for (int i = 7; i >= max(0, 8 - strlen); i--) {
            bitstream << byt[i];
        }
        strlen -= 8;
    }
    bin_file.close();
    return make_pair(tree_stream.str(), bitstream.str());
}

/* Given a ++filename++, a serialized tree ++serial_tree++ , and
 * a string of 0s and 1s ++bitstring++, converts ++serial_tree++ and
 *  ++bitstring++ to actual bits, and writes them to the binary file
 * named by ++filename++.
 *
 * Return: void.
 *
 * Possible exceptions: Will raise runtime error if given ++serial_tree++
 * or ++bitstring++ are larger than 2^32. Will also raise error upon
 * failure to open ++filename++.
 */
void BinaryIO::writeFile(const string &filename, const string &serial_tree,
                         const string &bitstring) {
    ofstream bin_file;
    open_or_die(bin_file, filename);

    // We will use uint32_t to store the size of the encoding, so if
    // the size is larger than 2^32, then it's too big.
    if ((bitstring.length() > pow(2, 32)) or
        (serial_tree.length() > pow(2, 32))) {
        throw runtime_error("Given string is too large to write to " +
                            filename);
    }

    // First put the zapfile stamp on the file.
    for (auto &c : __ZAPFILE_STAMP) {
        bin_file.put(c);
    }

    // Next 4 bytes will be serialized tree length, followed by tree itself.
    uint32_t treelen = serial_tree.length();
    bin_file.write(reinterpret_cast<char *>(&treelen), sizeof(treelen));
    for (auto &c : serial_tree) {
        bin_file.put(c);
    }

    uint32_t strlen = bitstring.length();

    // Next 4 bytes in the file will be the length of the encoded message.
    bin_file.write(reinterpret_cast<char *>(&strlen), sizeof(strlen));

    // Read bits from bitstring
    uint32_t curr_bit = 0;
    while (curr_bit < strlen) {
        // We read bits 8 at a time. Or, if there are fewer than 8 bits
        // remaining, we read the remaining number of bits.
        int bitset_length =
            min(8, static_cast<int>(bitstring.length() - curr_bit));
        bitset<8> byt(bitstring.substr(curr_bit, bitset_length));

        // If there were fewer than 8 bits remaining, need to shift bits left.
        byt <<= (8 - bitset_length);

        // Convert bitset to char, and write char to file.
        char c = (byt.to_ulong() & 0xFF);
        bin_file.put(c);
        curr_bit += 8;
    }

    bin_file.close();
}

template <typename streamtype>
void BinaryIO::open_or_die(streamtype &stream, const string &filename) {
    stream.open(filename, ios::binary);
    if (not stream.is_open())
        throw runtime_error("Unable to open file " + filename);
}
