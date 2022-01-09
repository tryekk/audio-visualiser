# Customisable Cross-Platform Audio Visualiser


### How to build/start/run/compile the project

#### macOS:
Clone the GitHub project.<br>
Open the folder named 'AudioVisualiser'.<br>
Run the file 'AudioVisualiser.app'.<br><br>
*Please make sure that you allow microphone permission or have an alternative audio input device connected to your computer (such as an audio interface with an instrumant as an input).*<br><br>
Test project can be found at 'audio-visualiser/Builds/MacOSX/Audio Visualiser Tests.xcodeproj'
<br>
#### Windows:
Clone the GitHub project.<br>
Open the folder named 'AudioVisualiser'.<br>
Run the file 'AudioVisualiser.exe'.<br><br>
*Please make sure that you allow microphone permission or have an alternative audio input device connected to your computer (such as an audio interface with an instrumant as an input).*
<br><br>

### Details of important assumptions I made during design and development

The main selling points of the application are that is is cross-platform, customisable and runs in real-time; all while being easy to use for users of any background.<br><br>
Some assumptions I made based on this were:<br>
• Users can be from any background and any have any level of understanding of music theory or computer science.<br>
• The software must handle audio information in real-time and must be as responsive as possible on a wide range of hardware.<br>
• The framework used for audio processing and graphics (JUCE) has cross-platform support and any libraries or frameworks used now or in future must support at least the same platforms (macOS, Linux, Windows).
• UI elements should be clear and unambiguous and a readable size on all display sizes. Labels and controls must be clear and concise, without causing the user confusion.
<br><br>

### A link to requirements or a list of requirements (unless you are using the features for requirements gathering and monitoring provided in your source control application)

• As a user, I should see a visual representation of my audio input<br>
• As a user, configure the visual display using the settings menu<br>
• As a user, I want the GUI to be clear and concise but provide me with a range of customisation options<br>
• The application should be able to run on multiple operating systems<br>
• As a user, I would like to be able to resize the window or make it full screen with no borders<br>
• As a user, I would like to be able to toggle UI elements visibility in order to maintain a clean view of the visualiser when needed<br>
• As a user, I would like the option to allow the application access to use the computer microphone<br>
• As a user, I want the software to be responsive and clear to enable creative flow<br>
• As a user, I want the interface to be intuitive so that I don't need to learn anything to use it
<br><br>

### Links to the documentation/websites of the frameworks, languages, libraries I used and why they have been used

*C++ programming language <br>
(Official Documentation): https://www.cplusplus.com/reference/<br>
(Microsoft documentation): https://docs.microsoft.com/en-us/cpp/cpp/?view=msvc-170*
<br><br>
I decided to use C++ for this project because of the frameworks available to use for creating graphics and for processing digital audio data.
<br><br>
C++ is a very flexible language that allows for deep control over system resources and processor behaviour. Because of this, it can run faster than most languages and allows for a fine level of control that enables efficient execution of complex code. This enables real-time displays for dynamic audio data.
<br><br>

*JUCE audio processing and graphics framework for C++:
https://docs.juce.com/master/index.html*
<br><br>
This framework was used for handling audio inputs and processing their digital audio data.
I also used this framework for cresting the GUI and graphical elements of the application, such as the audio visualiser component itself and the GUI used to customise/control the visualiser.
<br><br>
This framework was used in addition to the C++ standard library primarily due to the fact that it has built-in functions that handle audio input data. This was a huge time saver for me as the algorithm for processing audio data (Fast Fourier Transform / FFT) already exists and has been implemented in the JUCE framework. This meant that I did not need to reinvent the wheel and kept the project within the scope of the time requirement.
<br><br>
Another reason for its use was that it includes a graphics library that enabled me to make a clean and clear GUI within the scope of the project time.
<br><br>
Another important reason is that JUCE is cross-platform.<br>
I wanted the application to be available to as many users as possible, and for its platform support to not get in the way of a production, such as a studio or event needing to hire a certain machine in order to use the application
