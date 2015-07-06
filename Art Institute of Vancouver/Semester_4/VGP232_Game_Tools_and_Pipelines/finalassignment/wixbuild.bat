set WIXDIR=F:\Semester_4\VGP232_Game_Tools_and_Pipelines\finalassignment\WIX\bin
del bmp_terr_gen_installer.wixobj
%WIXDIR%\candle.exe -out bmp_terr_gen_installer.wixobj -ext %WIXDIR%\WixUIExtension.dll bmp_terr_gen_installer.wxs
%WIXDIR%\Light.exe -cultures:en-US -ext %WIXDIR%\WixUIExtension.dll -out bmp_terr_gen_installer.msi bmp_terr_gen_installer.wixobj