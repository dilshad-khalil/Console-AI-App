# Console-AI

Console-AI is a console application developed using C++. It offers various features that allow users to interact with OpenAI's APIs and perform tasks like conversation generation and image generation using prompts.

## Features

- Account registration and login functionality
- OpenAI's chatGPT integration for conversation generation
- Dall-E2 integration for image generation based on prompts
- Downloading generated images to a local folder
- Saving chatGPT API responses to a text file
- Animated response display for chatGPT API

## Prerequisites

To run the Console-AI application, follow these steps:

1. **Get the API Key:**
   - Visit the [RapidAPI website](https://rapidapi.com/openai-api-openai-api-default/api/openai80) to obtain an API key.
   
2. **Install Visual Studio and vcpkg:**
   - Install [Visual Studio](https://visualstudio.microsoft.com/) on your machine.
   - Install [vcpkg](https://github.com/microsoft/vcpkg) package manager.

3. **Install required libraries:**
   - Using vcpkg, install the following libraries:
     - CURL: `vcpkg install curl`
     - rapidjson: `vcpkg install rapidjson`
     - OpenCV: `vcpkg install opencv`

4. **Obtain the source files:**
   - Clone or download the Console-AI source code from the repository.

## Usage

1. **API Key Setup:**
   - Replace `YOUR_API_KEY` or the api key that is in the source code with the API key obtained from RapidAPI.

2. **Building and Running the Application:**
   - Open the Console-AI project in Visual Studio.
   - Build the project to generate the executable file.
   - Run the executable file to start the application.

3. **Application Flow:**
   - Register an account or log in with existing credentials.
   - After logging in, you will have four options:
     - ChatGPT: Interact with OpenAI's chatGPT API for conversation generation.
     - Dall-E2: Generate images based on prompts using Dall-E2.
     - Downloaded Images: View and access the downloaded images.
     - Quit: Exit the application.

## Libraries Used

- C++ OOP (Object-Oriented Programming)
- CURL: A library for making HTTP requests.
- rapidjson: A fast JSON parser/generator for C++.
- OpenCV: A computer vision library.

## Contributions

Contributions to Console-AI are welcome! If you find any issues or have suggestions for improvements, please feel free to open an issue or submit a pull request.

