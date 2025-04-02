# CanonicalTest Project
This C++ project uses `libcurl` library for handling HTTP requests and the `nlohmann/json` library for JSON manipulation. 

## Dependencies
This project requires the following libraries:
- `libcurl`: For making HTTP requests.
- `nlohmann/json`: For parsing and manipulating JSON data.

## Command Supported:
./main --listAll : Returns list of all currently supported Ubuntu releases for AMD64 architecture.
./main --currentLTSVersion : Returns the current Ubuntu LTS version
./main --sha256 release : Returns the sha256 of the disk1.img item of a given Ubuntu release
If user doesnt specify the option i.e just passes ./main then the code will ask the user to enter the valid option

## Output
I've included the screenshots of the outputs in report.pdf file
  
### Note:
I've tested the code on Windows and Linux. 
Due to a lack of access to a Mac, I couldn't test it on macOS. 
However, with libcurl installed (brew install curl), this code should work on macOS as well.