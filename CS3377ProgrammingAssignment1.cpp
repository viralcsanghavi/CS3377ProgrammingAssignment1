#include <iostream> // The following are the header files for implementing input, output, strings, and manipulating output
#include <string> // new comment added for makefile exercise
#include <iomanip>
#include "version.cpp"

using namespace std; // default namespace used

int main() // main function
{
    string url;                        // Following are the initializations/declarations of my necessary variables for indicating position of certain required punctuations, etc.
    int positionOfFirstColon = 0;
    string protocol;
    bool incorrectProtocol = false;   // Also, there are bool variables included to indicate when format of a specific part of the url is wrong
    int positionOfSecondColon = 0;
    int positionOfDoubleSlash = 0;
    string domain;
    int positionOfSecondSlash = 0;
    string port;
    bool incorrectDomain = false;
    bool incorrectPortNumber = false;
    int positionOfQuestionMark = 0;
    int positionOfFilePathPeriod = 0;
    bool incorrectFilePath = false;
    bool noPort = false;
    bool noParameter = false;
    
    displayVersion();
    cout << "Input a URL below: ";  // This simply asks user for url input
    cin >> url;
    
    positionOfFirstColon = url.find(":");  // this finds the position of the first colon after the protocol
    protocol = url.substr(0, positionOfFirstColon); // we can create the protocol substring based on the positionOfFirstColon variable
    
    if (protocol.compare("http") != 0 && protocol.compare("https") != 0 && protocol.compare("ftp") != 0 && protocol.compare("ftps") != 0) { 
        // this if statement checks if the substring includes one of the four valid protocols
	incorrectProtocol = true; // set to true if not a valid protocol
    }
    
    positionOfSecondColon = url.find(':', positionOfFirstColon + 1); // finds position of second colon
    positionOfDoubleSlash = url.find("//"); // finds position of double slash after first colon
    positionOfSecondSlash = url.find("/", positionOfDoubleSlash + 2); // finds position of second slash after domain/port
    if (positionOfSecondColon == string::npos) { // if the second colon is not found...
        noPort = true; // there is no port
        domain = url.substr((positionOfDoubleSlash + 2), (positionOfSecondSlash - positionOfDoubleSlash - 2)); // calculate domain substring differently
    }
    else {
        domain = url.substr((positionOfDoubleSlash + 2), (positionOfSecondColon - positionOfDoubleSlash - 2)); // if port exists, then calculate domain substring differently
    }
    int periodCounter = 0; // counts periods
    string host;
    bool incorrectFormatOfPeriods = false;
    for (int i = 0; i < domain.size(); ++i) { // loops through domain substring
        char c = domain[i]; // sets domain character at each index to variable c
        if (i == 0) {
            if (c == '.') { // if there is a period in the first index, then it's invalid
                incorrectDomain = true;
                incorrectFormatOfPeriods = true;
            }
        }
        if (c == '.') {
            ++periodCounter; // add to counter and continue
            continue;
        }
        if (periodCounter > 2) { // if counter is above 2, then invalid domain
            incorrectDomain = true;
            incorrectFormatOfPeriods = true;
            break;
        }
        if (periodCounter == 2) {
            host += c; // if counter is 2 as it should be, then add remaining characters to the host string
        }
    }
    if (periodCounter != 2) { // checks for when period counter could be 1 or 0
        incorrectDomain = true;
        incorrectFormatOfPeriods = true;
    }
    if (host != "com" && host != "net" && host != "edu" && host != "biz" && host != "gov") {
        incorrectDomain = true; // invalid if it doesn't match correct requirements for host
    }
    
    int portNumber;
    if (noPort == false) { // if there is a port...
        port = url.substr(positionOfSecondColon + 1, (positionOfSecondSlash - positionOfSecondColon - 1)); // calculate port substring 
        portNumber = stoi(port); // convert the string to integer to get portNumber
        if (portNumber < 1 || portNumber > 65535) {
            incorrectPortNumber = true; // checks invalid values for portNumber
        } 
    }
    
    string filePath;
    positionOfQuestionMark = url.find("?"); // finds position of question mark
    if (positionOfQuestionMark == string::npos) { // if question mark is not found, there will not be a parameter part
        noParameter = true;
        filePath = url.substr(positionOfSecondSlash); // substring from position of second slash to end of url string

    }
    else {
        filePath = url.substr(positionOfSecondSlash, positionOfQuestionMark - positionOfSecondSlash); // caluclate filePath substring differently for when parameter does exist
    }
    positionOfFilePathPeriod = filePath.find("."); // position of period that comes before html or htm
    string endOfFilePath;
    endOfFilePath = filePath.substr(positionOfFilePathPeriod + 1); // find the endOfFilePath substring so .html or .htm
    
    if (endOfFilePath != "html" && endOfFilePath != "htm") {
        incorrectFilePath = true; // for invalid endings
    }
    
    string parameter;
    if (noParameter == false) { // if parameter exists, calculate its substring
        parameter = url.substr(positionOfQuestionMark + 1, url.size() - positionOfQuestionMark);
    }

    if (incorrectProtocol == true || incorrectDomain == true || incorrectPortNumber == true || incorrectFilePath == true) { // if any parts are incorrect, print the corresponding messages
        cout << "Invalid URL with the following erroneous components:" << endl;   // so the following if statements check individually for if the parts are incorrect
        if (incorrectProtocol == true) {
            cout << setw(10) << left << "Protocol: "; // using setw for formatting
            cout << protocol << " is not a valid protocol." << endl;
        }
        if (incorrectFormatOfPeriods == true) {
            cout << setw(10) <<  left << "Domain:";
            cout << "The format of the number/placing of periods is incorrect." << endl;
        }
        else {
            if (incorrectDomain == true) {
            cout << setw(10) <<  left << "Domain:";
            cout << host << " is an invalid domain name." << endl;
            }
        }
        if (incorrectPortNumber == true) {
            cout << setw(10) << left << "Port:";
            cout << "Port number must be from the range of 1-65535." << endl;
        }
        if (incorrectFilePath == true) {
            cout << setw(10) << left << "File path:";
            cout << endOfFilePath << " is not a valid end to a file path." << endl;
        }
    }
    else { // else if they are all valid parts of a url, then print the part
        cout << setw(20) << left << "Protocol:" << protocol << endl;
        cout << setw(20) << left << "Domain:" << domain << endl;
        if (noPort == false) {
            cout << setw(20) << left << "Port:" << portNumber << endl;
        }
        cout << setw(20) << left << "File path:" << filePath << endl;
        if (noParameter == false) {
            cout << setw(20) << left << "Parameters:" << parameter << endl;
        }
    }
    

    return 0; // exit program with return 0 statement
}
