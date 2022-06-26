#include <JuceHeader.h>
#include "MainContainer.h"

class Application : public juce::JUCEApplication
{
public:
    //==============================================================================
    Application() = default;

    const juce::String getApplicationName() override       { return "Audio Visualiser"; }
    const juce::String getApplicationVersion() override    { return "1.0.0"; }

    void initialise (const juce::String &cmdLine) override
    {
        mainWindow.reset(new MainWindow());
    }

    void shutdown() override
    {
        mainWindow.reset(nullptr);
    }

private:
    class MainWindow : public juce::DocumentWindow
    {
    public:
        MainWindow()
            : DocumentWindow(
                juce::JUCEApplication::getInstance()->getApplicationName(),
                juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
                    ResizableWindow::backgroundColourId
                ),
                juce::DocumentWindow::allButtons
            )
        {
            setVisible(true);
            setUsingNativeTitleBar(true);
#if JUCE_ANDROID || JUCE_IOS
            setFullScreen (true);
#else
            centreWithSize(1280, 720);
            setResizable(true, false);
            setResizeLimits(800, 600, 3840, 2160);
#endif

            setContentOwned(new MainContainer(), true);
        }

        void closeButtonPressed() override
        {
            juce::JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION (Application)
