My motivation for developing this app

I decided to write this "Simple Text Editor" because I need to further develop my skills in C++ (I was already familiar with it), as well as get my first experience in creating a GUI using the Qt framework (because of its convenience and the ability to create cross-platform applications with it - from desktop to iOS/Android applications).

Why Notepad?

Because I've been using a standard Windows application for a long time, and I've been waiting for the user interface (namely the design) to be updated with each system update. But that didn't happen. Then I thought about creating my own software, which would have the ability to dynamically change its design at the request of the user.

In this regard, it is not necessary to assume that I have not used or do not use other text editors (Notepad++, Sublime Text, etc.). But, in my opinion, they look less attractive, but better than the standard notepad from Microsoft.

The main features of my app are:
- ability to change the theme of the app (dark, light);
- ability to change the background of the text area and the font itself;
- ability to change the text font itself;
- subsequent launch of the application with its previous settings;
- ability to expand the active area (remove unnecessary user interface);
- and the following standard functions: search and replace text (with color selection of the found / replaced word, print the document, preview the document before printing.

You can see that the main focus of my implementation of this application was on improving the design compared to the above-mentioned editors.

📌The app is currently under active development and will only improve over time.

Keyboard shortcuts:
- F1-Settings
- F5-display the current date and time in the editable field
- Ctrl + P-Print
- Ctrl +"+", Ctrl +" -", Ctrl + " 0 " - zoom in, zoom out and zoom out by default, respectively
- Ctrl + Shift + P - preview the document before printing
- Ctrl + H-replace word
- Ctrl + F-find a word
- Ctrl + G-go to line

You can run the application on your computer by downloading the archive from this repository SimpleTextEditor.rar
The application is cross-platform, as in the current archive I have collected all the necessary plugins and compiler libraries for its stable operation.