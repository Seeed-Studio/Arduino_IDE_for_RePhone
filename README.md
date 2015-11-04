# RePhone_Arduino
![](https://ksr-ugc.imgix.net/projects/1975885/photo-original.jpg?v=1444251465&w=1536&h=1152&fit=crop&auto=format&q=92&s=d301d98b1595a481fb18a5e312948ed6)

RePhone is an open source and modular phone kit.

With Rephone you can:

1.Create your own phone in minutes with the slim MODULES, accessible SOFTWARE, and customizable Phone Enclosures.

2.Hack anything around you, **giving inanimate objects the power of cellular communication**. Have a conversation with your pets, plants, toys, motorcycle helmets, robots, or drones through RePhone’s GSM and 3G functions.

RePhone is a set of tools and components that allows everyone including students, teachers, makers, hackers, geeks, artists, developers and engineers rethink, remix, redesign and remake the phone. 

#Usage

Before you download the Arduino IDE for RePhone, make sure you have an operation system as following:

Windows **XP/Vista/7/8/8.1**

##Install the Driver

###Disable Driver Signature Enforcement under Windows 8/8.1

If you are using the Windows8/8.1, you would need to disable Driver Signature Enforcement first to be able to install the driver.

You should save the files you are editing before trying to turn off the 'Driver Signature Enforcement' as your system will be shut down during the operation.

1. Now follow the instructions below to disable the 'Driver Signature Enforcement.' 
2. Press “Windows Key” +"R" 
3. Enter shutdown.exe /r /o /f /t 00 
4. Click the "OK" button.
5. System will restart to a "Choose an option" screen
6. Select "Troubleshoot" from "Choose an option" screen
7. Select "Advanced options" from "Troubleshoot" screen
8. Select "Windows Startup Settings" from "Advanced options" screen
9. Click "Restart" button
10. System will restart to "Advanced Boot Options" screen
11. Select "Disable Driver Signature Enforcement"
12. Once the system starts, you can install the Arduino drivers as same as Windows

###Driver Installation

1.Firstly, power up your RePhone by **plug in the battery** to the battery socket on the Xadow GSM+BLE, **press and hold the power key (PWR) for 2 second to turn it ON** (LED indicator shows **GREEN**), then connect your RePhone to PC with a Micro USB cable. 

![](http://www.seeedstudio.com/wiki/images/a/ab/Connect_Xadow_GSM%2BBLE_to_PC.png)

2.Open **Device Manager** by clicking the Start button, clicking Control Panel, clicking System and Security, and then, under System, clicking Device Manager. If you're prompted for an administrator password or confirmation, type the password or provide confirmation. 
In the Device Manager, you'll be seeing unknown devices as shown below: 

![](http://www.seeedstudio.com/wiki/images/1/18/Driver_Installation_Unknown_Devices.png)

3.Right click on one of the unknown devices, choose **Update Driver Software**.

![](http://www.seeedstudio.com/wiki/images/6/63/Driver_Installation_Update_Driver_Software.png)

4.Choose **Browse my computer for driver software**.

![](http://www.seeedstudio.com/wiki/images/e/ef/Driver_Installation_Browse_my_computer_for_driver_software.png)

5.Click **Browse** and the locate the folder which you've unzipped the Arduino IDE for RePhone .. \Arduino_IDE_for_RePhone\drivers\mtk . Click **Next** to start the driver installation.

![](http://www.seeedstudio.com/wiki/images/0/01/Driver_Installation_Locate_Driver.png)

6.When the driver software is successfully installed, you will be able to see the following **complete** page, click **Close** and **start over from step 1 to 6 to install the driver for another unknown device.**

![](http://www.seeedstudio.com/wiki/images/thumb/c/c1/Driver_Installation_complete_page.png/600px-Driver_Installation_complete_page.png)


##Update/Flash the Firmware

To make use of the Arduino IDE for RePhone, you would have to update/flash the firmware as well. The process is as simple as following:

1.**Disconnect your RePhone with PC, press and hold the power key(PWR) for 2 seconds to turn it OFF** (LED indicator turn **RED** and then goes out)

2.Open the FirmwareUpdate.exe under the path \Arduino_IDE_for_RePhone\hardware\tools\mtk, click **Download**. 

![](http://www.seeedstudio.com/wiki/images/c/c2/Updatefirmware.png)

3.Now you will be asked to connect your RePhone to PC via USB cable, make sure your RePhone has been turned **OFF**. 

![](http://www.seeedstudio.com/wiki/images/6/64/Updatefirmware_pluginrephone.png)

4.Wait until the downloading finish. 

![](http://www.seeedstudio.com/wiki/images/1/1e/Updatefirmware_downloading.png)

5.In the Complete page click OK to finish the firmware update.

![](http://www.seeedstudio.com/wiki/images/4/47/Updatefirmware_complete.png)


##Hello World

Now you've prepared things required, and we are ready to rock on with RePhone.

Let's start with a simple program **Hello World**

1.Press and hold the power key (PWR) for 2 seconds to turn it ON (LED indicator shows GREEN) 

2.Open the **Arduino_IDE_for_RePhone.exe** in the folder where you unzipped the Arduino IDE for RePhone, the software interface is as following:

![](http://www.seeedstudio.com/wiki/images/f/f7/Arduino_IDE_for_RePhone_interface.png)

3.Open **Device Manager** to check for the COM ports. There will be **two COM ports**:


* MTK USB Debug Port is used for uploading code
* MTK USB Modem Port is used for logs, like printing messages in the serial monitor with Serial.println()

![](http://www.seeedstudio.com/wiki/images/9/9f/Arduino_IDE_for_RePhone_COM_Ports.png)

4.On the Arduino IDE window, click **Tool > Port**, select **MTK USB Debug Port**, which is **COM20** in this case, the COM number might be different in your PC, just make sure it corresponds to the Debug Port. 

![](http://www.seeedstudio.com/wiki/images/4/42/Arduino_IDE_for_RePhone_Debug_Port.png)

5.On the Arduino IDE window, click **Tool > Board**, select RePhone

![](http://www.seeedstudio.com/wiki/images/a/a9/Arduino_IDE_for_RePhone_Board.png)

6. Now copy the following code to your Arduino IDE:


	// hello world for test RePhone
	// loovee@10-18-2015
   
    void setup() {
    	Serial.begin(115200);
    }
       
    void loop() {
    	// put your main code here, to run repeatedly:
    	Serial.println("Hello World, Hello RePhone!");
    	delay(100);
    }
    
7.Now press the Upload button to upload the code to your RePhone. You will see the **Done uploading** when the code is successfully uploaded.

![](http://www.seeedstudio.com/wiki/images/7/77/Arduino_IDE_for_RePhone_upload.png)

8.As RePhone use different COM ports for uploading software and logs, to read the logs, we need to switch the selected COM Port to **MTK USB Modem Port**. On the Arduino IDE window, click **Tool > Port**, select **MTK USB Modem Port**, which is **COM48** in this case.
Then open the **Serial Monitor**

![](http://www.seeedstudio.com/wiki/images/6/6c/Arduino_IDE_for_RePhone_Serial_Monitor.png)

9.Now we can see the **Hello World** we have printed with **Serial.println()** . 

![](http://www.seeedstudio.com/wiki/images/c/c8/Arduino_IDE_for_RePhone_Helloworld.png)


#References

[RePhone mian Page](www.seeed.cc/rephone)

[Wiki for Arduino_IDE_for_RePhone](http://www.seeedstudio.com/wiki/Arduino_IDE_for_RePhone_Kit)

[Kickstarter page for RePhone](https://www.kickstarter.com/projects/seeed/rephone-kit-worlds-first-open-source-and-modular-p)

