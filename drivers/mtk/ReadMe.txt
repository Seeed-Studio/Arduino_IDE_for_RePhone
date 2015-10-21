ReadMe.txt

This application will install USB com port driver for MediaTek's device those IDs are listed below:

1."VID_0E8D&PID_0003"  (MTK USB Port)
2."VID_0E8D&PID_0023&MI_00" (MTK USB Modem Port)
3."VID_0E8D&PID_0023&MI_02" (MTK USB Debug Port)

And support the Windows 98SE/ME/2000/XP/Vist/Win7 platform.
 
The application user must belong to Administrator group or have the privilege to install driver.

the execution of the InstallDriver.exe will install the driver, and the UninstallDriver.exe is special for remove driver.
the InstallDriver.exe will remove the legacy version of driver before install current driver automatically.

Notes:
1. "2K_XP_COM, Vista, 98_MASS, 98ME_COM, Win7" folder must be put in the same directory with InstallDriver.exe
2. Running InstallDriver with command "-a" will install driver silently (means without GUI Windows). And remove driver command is "-u". "-au" or "-ua" will remove driver silently.
3. Windows 2003 use the INF files which under the 2K_XP_COM
4. The device which generates two com ports (USB Modem Port Driver & USB Modem Debug Driver) only support Systems after Win XP sp3 version. If you want to support these devices in Win XP Sp2, add these patchs:
http://support.microsoft.com/kb/918365/
http://support.microsoft.com/kb/935892/


[v1.0812.0]
     [New Feature]
     1.Pass WHQL certification for Windows XP 32 bit
[v1.0821.0]
     [New Feature]
     1.Support Windows XP 64 bit 
[v1.0830.0]
     [Bug Fix]
      1.Remove the entry referring "V.42bis", since none of our modem supports this protocol
[v1.0845.0]
     [New Feature]
     1. Pass WHQL certification for Windows Vista 32 bit
     2. Pass WHQL certification for Windows Vista 64 bit
[v1.0945.0]
     [New Feature]
     1.Support Win 7 32 bit
     2.Support Win 7 64 bit
     3.Remove the Installer.dll
[v1.0948.0]
     [New Feature]
     1.Support Windows 2003       
[v1.1023.0]
     [New Feature]
     1.Support Device VID_0E8D&PID_0023&MI_00
       Support Device VID_0E8D&PID_0023&MI_02

[v1.1032.0]
     [Bug Fix]
1.	Add the usbser.sys reference in the *.inf file .Since in Clean OS will need this reference to reference the correct driver file.
[New Feature]
1. Add "Remove" command , User can remove the driver with command ¡°-u¡± , As Notes section described.
2. The "Remove" command support windows XP operating system and later versions.
[v1.1032.1]
1.Add Bat file to release remove feature


      


