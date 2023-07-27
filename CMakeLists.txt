cmake_minimum_required(VERSION 3.15)
project(Piferi_Exam_01 VERSION 0.0.1)

# set up the markov library as a separate part of the build
add_library(markov-lib src/MarkovManager.cpp  src/MarkovChain.cpp)
set_property(TARGET markov-lib PROPERTY CXX_STANDARD 14)
# add a new target for quickly experimenting with the Markov
add_executable(markov-expts src/MarkovExperiments.cpp)
set_property(TARGET markov-expts PROPERTY CXX_STANDARD 14)
# link the markov lib to the experiments executable
target_link_libraries(markov-expts  markov-lib)

add_subdirectory(/Applications/JUCE ./JUCE)
juce_add_plugin(Piferi_Exam_01
        # VERSION ...                               # Set this if the plugin version is different to the project version
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...
        COMPANY_NAME Piferi                          # Specify the name of the plugin's author
        IS_SYNTH TRUE                       # Is this a synth or an effect?
        NEEDS_MIDI_INPUT TRUE               # Does the plugin need midi input?
        # NEEDS_MIDI_OUTPUT TRUE/FALSE              # Does the plugin need midi output?
        # IS_MIDI_EFFECT TRUE/FALSE                 # Is this plugin a MIDI effect?
        NEEDS_MIDI_OUTPUT TRUE
        # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE    # Does the editor need keyboard focus?
        COPY_PLUGIN_AFTER_BUILD TRUE        # Should the plugin be installed to a default location after building?
        PLUGIN_MANUFACTURER_CODE Coco               # A four-character manufacturer id with at least one upper-case character
        PLUGIN_CODE Fp00                            # A unique four-character plugin id with exactly one upper-case character
        # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
        FORMATS AU VST3 Standalone                  # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
        PRODUCT_NAME "Piferi_Exam_01")        # The name of the final executable, which can differ from the target name

juce_generate_juce_header(Piferi_Exam_01)

target_sources(Piferi_Exam_01
        PRIVATE
        src/PluginEditor.cpp
        src/PluginProcessor.cpp
        src/MarkovManager.cpp
        src/MarkovChain.cpp
        src/SineOscillator.cpp
        src/Armonizer.cpp
        src/ExamPifAudioProcessorEditorModifyArmonizerPage.cpp
        )

target_compile_definitions(Piferi_Exam_01
        PUBLIC # 
        JUCE_ALSA=1
        JUCE_DIRECTSOUND=1
        JUCE_DISABLE_CAUTIOUS_PARAMETER_ID_CHECKING=1
        JUCE_USE_OGGVORBIS=1
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(Piferi_Exam_01
        PRIVATE
        juce::juce_audio_utils
        PUBLIC
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
        juce::juce_recommended_config_flags)
