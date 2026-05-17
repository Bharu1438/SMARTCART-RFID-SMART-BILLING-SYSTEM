SET PATH=C:\Keil\ARM\ARMCC\bin\;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\MinGW\bin;C:\Program Files\Git\cmd;C:\Users\HP\AppData\Local\Microsoft\WindowsApps;C:\Users\HP\AppData\Local\Programs\Microsoft VS Code\bin
SET CPU_TYPE=LPC2148
SET CPU_VENDOR=NXP
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"C:\Keil\ARM\ARMCC\bin\ArmAsm" --Via ".\startup._ia"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\uart0_file.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\uart1_file.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\interrupt_file.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\lcd_file.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\keypad_file.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\main.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\buzzer_file.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\rf_reader_file.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\delay_file.__i"
"C:\Keil\ARM\ARMCC\bin\ArmLink" --Via ".\Majot_project.lnp"
"C:\Keil\ARM\ARMCC\bin\fromelf.exe" ".\Majot_project.axf" --i32combined --output ".\Majot_project.hex"
