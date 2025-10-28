# INFORMATION

- This mini icon-resizer was made with the API provided in the .GIT repo: [https://github.com/nothings/stb](https://github.com/nothings/stb).
- The header files do not belong to this project and were taken from the repository mentioned above, and all the the rights are copyrighted.

- Only (experimented) supports IMAGE/: PNG, JPG, JPEG.
- It will create the sizes: 16, 22, 24, 32, 48, 64, 128, 256, 512, if any more size needed can just adjust the `std::vector<int> sizes` array in `icon_resizer.cpp`

# COMPILE

- To compile, run: `g++ -O2 -std=c++17 icon_resizer.cpp -o iconresizer`.
- If you want to, you can put executable into /usr/bin and reuse it in bash anytime.
