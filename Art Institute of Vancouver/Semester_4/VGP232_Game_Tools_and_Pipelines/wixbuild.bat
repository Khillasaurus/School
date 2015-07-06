set WIXDIR=F:\WIX\bin
del installer.wixobj
%WIXDIR%\candle.exe -out installer.wixobj -ext %WIXDIR%\WixUIExtension.dll installer.wxs
%WIXDIR%\Light.exe -cultures:en-US -ext %WIXDIR%\WixUIExtension.dll -out installer.msi installer.wixobj