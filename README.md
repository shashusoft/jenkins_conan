# jenkins_conan
Integration of Jenkins and Conan for automating C++ Project operational cycle
-----------------------------------------------------------------------------
C++ UG Mannheim     
cugmannheim@simple-robot.de	
https://www.meetup.com/Mannheim-C-Developers-Meetup/

Jenkins Install (Linux Platform)
--------------------------------
Add key:\
    wget -q -O - https://pkg.jenkins.io/debian-stable/jenkins.io.key | sudo apt-key add -\
Then add the following entry in your /etc/apt/sources.list:\
    deb https://pkg.jenkins.io/debian-stable binary/\
Update your local package index, then finally install Jenkins:\
    sudo apt-get update\
    sudo apt-get install jenkins\
Start Jenkins from Web-browser:\
   http://localhost:8080/\
If some issue, check if Jenkins service is started:
    systemctl status jenkins
jenkins, password is available at :
    var/lib/jenkins/secrets/initialAdminPassword

Jenkins Getting Started
-----------------------
After password is set, select “Install suggested plugins” in http://localhost:8080/		
Select “Install Suggested Plugins”
Create user and admin password
Set URL for your jenkins configuration (customised)
Jenkins is ready to use
Refresh browser with http://localhost:8080/		

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
    
    


