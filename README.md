# RC4ALL



<img src="https://github.com/checkthistape/RC4ALL/blob/main/rc4all_logo2.png" width="300" height="300" align="left" alt="Made by David Krikovtsov"/>

RC4ALL takes a practical approach to remote presentation control, seamlessly integrating hardware and software components. The ESP8266 NodeMCU, serving as the client, establishes a WiFi connection without the need for hard-coded Arduino settings. Instead, the project employs the WifiManager library, simplifying the user experience by saving WiFi credentials after the initial connection.

For the first connection, RC4ALL initiates a unique access point with a captive portal and an HTML interface. This innovative setup allows users to connect the module to their WiFi effortlessly using a smartphone, eliminating the complexities of traditional configuration processes.

The communication framework relies on the efficient exchange of UDP packets between the client and server, ensuring a reliable and responsive data flow. The upcoming QT interface enhances user control, adding to the system's overall accessibility.

A notable feature of RC4ALL is its seamless compatibility with Windows systems. The server program, coded in C++ and leveraging winsock2.h and WS2tcpip.h libraries, interprets incoming UDP packets. It translates them into practical actions, such as mouse and keyboard events, empowering users to navigate and control presentations with simplicity.

In essence, RC4ALL prioritizes practicality and user accessibility, offering a straightforward solution for remote presentation control. The innovative use of the WifiManager library and captive portal underscores its commitment to a hassle-free user experience.
