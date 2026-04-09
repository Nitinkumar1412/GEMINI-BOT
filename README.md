# SVN Bot - AI Chatbot
An intelligent conversational chatbot built in C++ that leverages **Google's Gemini 2.5 Flash API** to provide real-time AI-powered responses. SVN Bot stores chat history in markdown files for easy reference and record-keeping.

## Features

✨ **AI-Powered Conversations**
- Integrates with Google Gemini 2.5 Flash API for natural language processing
- Real-time response generation

📝 **Chat History Management**
- Automatically saves all conversations to markdown files
- Organized chat history in dedicated folder
- Persistent storage for future reference

🎨 **Enhanced User Interface**
- Color-coded terminal output (bold green text for bot responses)
- Typing indicator animation for better UX
- Text wrapping for improved readability
- Formatted markdown output in history files

⚙️ **Cross-Platform Ready**
- Built with CMake for flexible compilation
- Uses vcpkg for dependency management

## Prerequisites

Before you begin, ensure you have the following installed:

- **C++ Compiler**: MSVC or GCC with C++17 support
- **CMake**: Version 3.15 or higher
- **vcpkg**: Microsoft's C++ dependency manager
- **CURL Library**: For HTTP requests
- **nlohmann JSON**: For JSON parsing

## Installation

### 1. Clone or Download the Project
```bash
cd c:\Users\Nitin\Chatbot
```

### 2. Setup vcpkg (if not already done)
```bash
git clone https://github.com/Microsoft/vcpkg.git c:\Users\Nitin\vcpkg
cd c:\Users\Nitin\vcpkg
.\vcpkg\bootstrap-vcpkg.bat
```

### 3. Install Dependencies
```bash
# Install CURL
c:\Users\Nitin\vcpkg\vcpkg install curl:x64-windows

# Install nlohmann JSON
c:\Users\Nitin\vcpkg\vcpkg install nlohmann-json:x64-windows
```

### 4. Build the Project
```bash
cd c:\Users\Nitin\Chatbot
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### 5. Configure API Key
The project uses Google's Generative AI API. The API key is embedded in the source code:
```cpp
static const string API_KEY = "YOUR_API_KEY_HERE";
```

To update the API key:
1. Get your free API key from [Google AI Studio](https://aistudio.google.com)
2. Open `SVN_BOT.cpp`
3. Replace the `API_KEY` value with your own

### 6. SSL Certificate Setup
Update the CA certificate path in the code if needed:
```cpp
static const string CA_BUNDLE = "C:/curl/cacert.pem";
```

## Usage

### Running the Chatbot

```bash
./build/chatbot
```

### Starting a Conversation

```
-----------------------------------------------
            WELCOME TO SVN BOT  
-----------------------------------------------
     Designed by: Nitin
-----------------------------------------------
Type 'exit' anytime to quit.

Enter the name for the chat to be stored in history : my_conversation
You: What is artificial intelligence?
```

### Features During Chat

- **Type your messages** and press Enter to send
- **Type 'exit'** to end the conversation
- **Chat history** is automatically saved to `./chat history/` directory
- **Typing indicator** shows while waiting for AI response
- **Formatted output** with bold text and wrapping

## Project Structure

```
Chatbot/
├── SVN_BOT.cpp           # Main chatbot application
├── json.hpp              # JSON library header
├── build/                # Build output directory
├── chat history/         # Stored conversation files
│   ├── hello.md
│   ├── history.md
│   └── ... (other conversations)
├── include/
│   └── curl/            # CURL library headers
├── lib/                 # External libraries
└── README.md            # This file
```

## API Integration

### Google Gemini 2.5 Flash API

The chatbot uses Google's REST API endpoint:
```
POST https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash:generateContent
```

### Request Format

```json
{
  "contents": [
    {
      "role": "user",
      "parts": [
        {
          "text": "Your message here"
        }
      ]
    }
  ]
}
```

## Dependencies

- **libcurl**: HTTP client library
- **nlohmann/json**: Modern C++ JSON library
- **Windows API**: For Terminal colors and Sleep function

## Environment Variables

No environment variables required. Configuration is handled via:
- Hardcoded API key in source code (for local development)
- CA certificate path for CURL SSL verification

## Troubleshooting

### Curl Error
If you encounter CURL errors:
- Verify the CA certificate path is correct
- Update the `CA_BUNDLE` path in the code
- Ensure internet connection is available

### API Key Issues
- Check that your API key is valid
- Verify you haven't exceeded API quota
- Ensure the API is enabled in Google Cloud Console

### Build Errors
- Ensure vcpkg toolchain path is correct
- Verify C++17 support in your compiler
- Check that all dependencies are installed

## Credits

**Designed by**: 
- Nitin

## License

This project is provided as-is for educational and personal use.

## Contributing

Feel free to fork this project, make improvements, and submit pull requests.

## Support

For issues or questions, please create an issue in the project repository.
