# jenkins_conan
Integration of Jenkins and Conan for automating C++ Project operational cycle
-----------------------------------------------------------------------------
C++ UG Mannheim     
cugmannheim@simple-robot.de	
https://www.meetup.com/Mannheim-C-Developers-Meetup/

Jenkins Install (Linux Platform)
--------------------------------
**Add key:**\
    wget -q -O - https://pkg.jenkins.io/debian-stable/jenkins.io.key | sudo apt-key add -\
**Then add the following entry in your /etc/apt/sources.list:**\
    deb https://pkg.jenkins.io/debian-stable binary/\
**Update your local package index, then finally install Jenkins:**\
    sudo apt-get update\
    sudo apt-get install jenkins\
**Start Jenkins from Web-browser:**\
   http://localhost:8080/\
**If some issue, check if Jenkins service is started:**\
    systemctl status jenkins\
**jenkins, password is available at :**\
    var/lib/jenkins/secrets/initialAdminPassword\

Jenkins Getting Started
-----------------------
After password is set, select “Install suggested plugins” in http://localhost:8080/\		
Select “Install Suggested Plugins”\
Create user and admin password\
Set URL for your jenkins configuration (customised)\
Jenkins is ready to use\
Refresh browser with http://localhost:8080/\		

Create C++ Project with Jenkins
-------------------------------
    Select “New Item” in jenkins web interface
    Enter an item name “MP3_Encoder”. Chose your specific project name. 
    Our small C++   Project is available in GitHub
    in jenkins web interface, Select “Freestyle Project”
    Click “Ok”
    in “Source Code Management” option
        Select “Git”
        Enter for example GitHub repository link “***.git”
        Enter credentials
    in “Build Triggers” option
        write script according to cron specification. It defines, build triggers with respect to     	minute, hour, day(s), week(s) and month(s)
	e.g. H * * * * (poll once hour)
    in “Build” option
	select “Execute Shell”
           write “cmake .”
	select “Execute Shell”
	write “make” 
    Note: If you are using cmake utility, then select above commands. 
    Save and Apply
    
C++ Conan Package Manager [Reference : https://docs.conan.io/en/latest/getting_started.html]\

Note: Jfrog artifactory is available for Conan. It contains some of the widely used C++ packages\

Installation of Conan (Linux Environment)\
    $pip install conan\

**Check if Conan is installed correctly. Run the following command in your console:**\
    conan --version\

##Getting started:\	
    **Create project folder inside your devlopment environment**\
    $mkdir md5_test_project\

    Create the following source file inside a folder. This will be the source file of our application:\
    
   md5.cpp\
   #include "Poco/MD5Engine.h"\
   #include "Poco/DigestStream.h"\

   #include <iostream>\
  
   int main(int argc, char** argv)\
   {\
       Poco::MD5Engine md5;\
       Poco::DigestOutputStream ds(md5);\
       ds << "abcdefghijklmnopqrstuvwxyz";\
       ds.close();\
       std::cout << Poco::DigestEngine::digestToHex(md5.digest()) << std::endl;\
       return 0;\
   }\
    We know that our application relies on the Poco libraries. Let’s look for it in the \
    Conan Center remote:\
    $conan search poco –remote=conan-center\
    Output\
    Existing package recipes:\

      poco/1.8.1\
      poco/1.9.3\
      poco/1.9.4\
Create conanfile.txt with build utility and library info\
    $vi conanfile.txt\
   [requires]\
  poco/1.9.4\
  [generators]\
  cmake\
  
**We are going to install the required dependencies and generate the information for the build system:**\
    $conan profile new default --detect  # Generates default profile \
    $conan profile update settings.compiler.libcxx=libstdc++11 default  \
You can create many conan profiles. Then each will be specific to your build environment\
 Now do:\
     $ mkdir build && cd build\
     $ conan install ..\
     
Conan will install all needed libraries and generates cmake files inside build folder\
 E.g. conanbuildinfo.cmake\
 Now ceate CmakeLists.txt file with following info\
 
 cmake_minimum_required(VERSION 2.8.12)\
 project(MD5Encrypter)\
 add_definitions("-std=c++11")\
 include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)\
 conan_basic_setup()\
 add_executable(md5 md5.cpp)\
 target_link_libraries(md5 ${CONAN_LIBS})\
 Now, we are ready to build our project
     cmake .. -G “Unix MakeFiles” -DCMAKE_BUILD_TYPE=Release\
     cmake  --build .   \
  
Run the binary:\
    ./bin/md5\


