# File Compressor (Huffman Coding)
<img width="493" height="28" alt="Image" src="https://github.com/user-attachments/assets/e5290875-fe74-4a0c-a7b0-3d118e09f6da" />

A C++ tool that compresses and decompresses text files using the Huffman Coding algorithm. I built this project to understand how file compression works at a low level, specifically focusing on bit manipulation and data structures.



## 🚀 Key Features

* **Compress Files:** Reads a text file and converts it into a smaller binary `.bin` file.

* **Decompress Files:** Restores the original text from the binary file with 100% accuracy.

* **Efficiency:** Uses a **Min-Heap** and **Huffman Tree** to assign shorter binary codes to frequent characters.

* **Bit Manipulation:** Implements a custom buffer to pack variable-length codes into 8-bit bytes.



## 🛠️ How It Works

1.  **Frequency Analysis:** The program counts how many times each character appears in `input.txt`.

2.  **Building the Tree:** It uses a Priority Queue to build a Binary Tree where frequent characters are near the top (short path) and rare characters are at the bottom (long path).

3.  **Encoding:** It generates a unique binary code (like `0` or `1101`) for every character.

4.  **Writing Bits:** Since C++ can only write bytes (8 bits), I wrote a function to pack these bits into a buffer and flush them to the file.



## 💻 How to Run

1.  **Compile the code:**

    ```bash

    g++ huffman.cpp -o huffman

    ```

2.  **Run the application:**

    ```bash

    ./huffman

    ```

3.  **Follow the menu:**

    * Enter the filename (e.g., `input.txt`) to compress it.

    * The program will generate `compressed.bin` and then automatically decompress it back to `output.txt` to verify it works.

  

## 📊 Performance Analysis

I tested the compressor on various file types to measure efficiency.



| File Type | Original Size | Compressed Size | Reduction |

|-----------|---------------|-----------------|-----------|

| Text File (Essay) | 12 KB | 7.8 KB | ~35% |

| Code File (.cpp) | 4 KB | 2.9 KB | ~27% |

| Repeated Chars | 1 KB | 0.05 KB | ~95% |



*Note: Compression efficiency varies based on character frequency distribution. Files with high redundancy (like repeated characters) show the best results.*

## 🧪 Testing Strategy

Since this is a lossless compression tool, data integrity is critical. I validated the tool using the following manual test cases:



1.  **Empty File:** Verified the program handles 0-byte files without crashing.

2.  **Single Character:** Tested files with only one repeating character (e.g., "aaaaa") to ensure bit-packing logic works on edge cases.

3.  **Round-Trip Test:** * `./huffman` (Compress `input.txt` -> `compressed.bin`)

    * `./huffman` (Decompress `compressed.bin` -> `output.txt`)

    * `diff input.txt output.txt` (Command line tool to verify files are identical).

## 📚 Tech Stack

* **Language:** C++

* **Concepts:** Greedy Algorithms, File I/O (fstream), Pointers, STL (Map, Vector, Priority Queue).
