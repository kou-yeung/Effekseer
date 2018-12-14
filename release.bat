SET RDIR=Effekseer141
SET RDIR_R=EffekseerRuntime141

rmdir %RDIR%
mkdir %RDIR%

rmdir %RDIR_R%
mkdir %RDIR_R%

echo Compile Editor
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" Dev\Editor\Effekseer.sln /p:configuration=Release
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" Dev\Cpp\EffekseerSoundXAudio2.sln /p:configuration=Release

echo Copy application

mkdir %RDIR%\Tool

copy Dev\release\Effekseer.exe %RDIR%\Tool\.
copy Dev\release\Effekseer.exe.config %RDIR%\Tool\.
copy Dev\release\EffekseerCore.dll %RDIR%\Tool\.
copy Dev\release\EffekseerViewer.dll %RDIR%\Tool\.
copy Dev\release\IronPython.dll %RDIR%\Tool\.
copy Dev\release\IronPython.Modules.dll %RDIR%\Tool\.
copy Dev\release\Microsoft.Dynamic.dll %RDIR%\Tool\.
copy Dev\release\Microsoft.Scripting.dll %RDIR%\Tool\.
copy Dev\release\Viewer.dll %RDIR%\Tool\.

mkdir %RDIR%\Tool\scripts
mkdir %RDIR%\Tool\scripts\export
copy Dev\release\scripts\export\Default.cs %RDIR%\Tool\scripts\export\.

mkdir %RDIR%\Tool\tools
copy Dev\release\tools\fbxToEffekseerModelConverter.exe %RDIR%\Tool\tools\.
copy Dev\release\tools\mqoToEffekseerModelConverter.exe %RDIR%\Tool\tools\.

mkdir %RDIR%\Tool\resources
robocopy Dev\release\resources\ %RDIR%\Tool\resources\. /s


echo Copy runtime
mkdir %RDIR_R%\RuntimeSample\
mkdir %RDIR_R%\RuntimeSample\lib
mkdir %RDIR_R%\RuntimeSample\include

mkdir %RDIR_R%\src
mkdir %RDIR_R%\src\include
mkdir %RDIR_R%\src\lib

copy Dev\Cpp\Effekseer\Effekseer.h %RDIR_R%\src\include\.
copy Dev\Cpp\EffekseerRendererDX9\EffekseerRendererDX9.h %RDIR_R%\src\include\.
copy Dev\Cpp\EffekseerRendererDX11\EffekseerRendererDX11.h %RDIR_R%\src\include\.
copy Dev\Cpp\EffekseerRendererGL\EffekseerRendererGL.h %RDIR_R%\src\include\.
copy Dev\Cpp\EffekseerSoundXAudio2\EffekseerSoundXAudio2.h %RDIR_R%\src\include\.
copy Dev\Cpp\EffekseerSoundAL\EffekseerSoundAL.h %RDIR_R%\src\include\.

copy Dev\Cpp\EffekseerRendererDX9.sln %RDIR_R%\src\.
copy Dev\Cpp\EffekseerRendererDX11.sln %RDIR_R%\src\.
copy Dev\Cpp\EffekseerRendererGL.sln %RDIR_R%\src\.

mkdir %RDIR_R%\src\Effekseer
robocopy Dev\Cpp\Effekseer %RDIR_R%\src\Effekseer *.h *.cpp *.filters *.vcxproj *.fx /mir /S

mkdir %RDIR_R%\src\EffekseerRendererDX9
robocopy Dev\Cpp\EffekseerRendererDX9 %RDIR_R%\src\EffekseerRendererDX9 *.h *.cpp *.filters *.vcxproj *.fx /mir /S

mkdir %RDIR_R%\src\EffekseerRendererDX11
robocopy Dev\Cpp\EffekseerRendererDX11 %RDIR_R%\src\EffekseerRendererDX11 *.h *.cpp *.filters *.vcxproj *.fx /mir /S

mkdir %RDIR_R%\src\EffekseerRendererGL
robocopy Dev\Cpp\EffekseerRendererGL %RDIR_R%\src\EffekseerRendererGL *.h *.cpp *.filters *.vcxproj *.fx /mir /S

mkdir %RDIR_R%\src\EffekseerRendererCommon
robocopy Dev\Cpp\EffekseerRendererCommon %RDIR_R%\src\EffekseerRendererCommon *.h *.cpp *.filters *.vcxproj *.fx /mir /S

mkdir %RDIR_R%\src\EffekseerSoundXAudio2
robocopy Dev\Cpp\EffekseerSoundXAudio2 %RDIR_R%\src\EffekseerSoundXAudio2 *.h *.cpp *.filters *.vcxproj *.fx /mir /S

mkdir %RDIR_R%\src\EffekseerSoundAL
robocopy Dev\Cpp\EffekseerSoundAL %RDIR_R%\src\EffekseerSoundAL *.h *.cpp *.filters *.vcxproj *.fx /mir /S


echo �����^�C���g�ݍ��݃T���v��
robocopy Release\RuntimeSample %RDIR_R%\RuntimeSample\ *.h *.cpp *.filters *.vcxproj *.fx *.efk *.wav *.png *.sln /mir /S
rmdir %RDIR_R%\RuntimeSample\include /S /Q
rmdir %RDIR_R%\RuntimeSample\lib /S /Q

mkdir %RDIR_R%\RuntimeSample\include
mkdir %RDIR_R%\RuntimeSample\lib

copy Dev\Cpp\Effekseer\Effekseer.h %RDIR_R%\RuntimeSample\include\.
copy Dev\Cpp\EffekseerRendererDX9\EffekseerRendererDX9.h %RDIR_R%\RuntimeSample\include\.
copy Dev\Cpp\EffekseerRendererDX11\EffekseerRendererDX11.h %RDIR_R%\RuntimeSample\include\.
copy Dev\Cpp\EffekseerRendererGL\EffekseerRendererGL.h %RDIR_R%\RuntimeSample\include\.
copy Dev\Cpp\EffekseerSoundXAudio2\EffekseerSoundXAudio2.h %RDIR_R%\RuntimeSample\include\.
copy Dev\Cpp\EffekseerSoundAL\EffekseerSoundAL.h %RDIR_R%\RuntimeSample\include\.

copy Dev\Cpp\lib\x86\Effekseer.Debug.lib %RDIR_R%\RuntimeSample\lib\.
copy Dev\Cpp\lib\x86\EffekseerRendererDX9.Debug.lib %RDIR_R%\RuntimeSample\lib\.
copy Dev\Cpp\lib\x86\EffekseerRendererDX11.Debug.lib %RDIR_R%\RuntimeSample\lib\.
copy Dev\Cpp\lib\x86\EffekseerRendererGL.Debug.lib %RDIR_R%\RuntimeSample\lib\.
copy Dev\Cpp\lib\x86\EffekseerSoundXAudio2.Debug.lib %RDIR_R%\RuntimeSample\lib\.
copy Dev\Cpp\lib\x86\EffekseerSoundAL.Debug.lib %RDIR_R%\RuntimeSample\lib\.

copy Dev\Cpp\lib\x86\Effekseer.Release.lib %RDIR_R%\RuntimeSample\lib\.
copy Dev\Cpp\lib\x86\EffekseerRendererDX9.Release.lib %RDIR_R%\RuntimeSample\lib\.
copy Dev\Cpp\lib\x86\EffekseerRendererDX11.Release.lib %RDIR_R%\RuntimeSample\lib\.
copy Dev\Cpp\lib\x86\EffekseerRendererGL.Release.lib %RDIR_R%\RuntimeSample\lib\.
copy Dev\Cpp\lib\x86\EffekseerSoundXAudio2.Release.lib %RDIR_R%\RuntimeSample\lib\.
copy Dev\Cpp\lib\x86\EffekseerSoundAL.Release.lib %RDIR_R%\RuntimeSample\lib\.

copy Dev\Cpp\CMakeLists.txt %RDIR_R%\src\.

echo �T���v��

mkdir %RDIR%\Sample
robocopy Release\Sample %RDIR%\Sample *.efkproj *.efkmodel *.txt *.png *.mqo *.fbx /mir /S

echo ���C�Z���X
cp Release/LICENSE.txt %RDIR_R%/LICENSE.txt

echo Readme
copy readme_tool_win.txt %RDIR%\readme.txt
copy readme_runtime.txt %RDIR_R%\readme.txt

echo �w���v
mkdir %RDIR%\Help

robocopy docs\Help_Tool %RDIR%\Help *.html *.css *.efkproj *.png *.gif *.zip /mir /S

mkdir %RDIR_R%\Help
robocopy docs\Help_Runtime %RDIR_R%\Help *.html *.css *.efkproj *.png /mir /S

echo doxygen(exe or bat)
call doxygen.bat doxygen.template
call doxygen.exe doxygen.template

mkdir %RDIR_R%\Help\html\doxygen
robocopy html %RDIR_R%\Help\html\doxygen /mir /S

echo Readme2
copy docs\readme_sample.txt %RDIR%\Sample\readme.txt

echo VS

mkdir %RDIR_R%\Compiled\

echo Compile VS14
rmdir /S /Q VS14
mkdir VS14

cd VS14
call cmake.bat -G "Visual Studio 14"  -D USE_MSVC_RUNTIME_LIBRARY_DLL:BOOL=OFF -D USE_XAUDIO2=ON ../Dev/Cpp/
cmake.exe -G "Visual Studio 14"  -D USE_MSVC_RUNTIME_LIBRARY_DLL:BOOL=OFF -D USE_XAUDIO2=ON ../Dev/Cpp/

"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" Effekseer.sln /p:configuration=Debug
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" Effekseer.sln /p:configuration=Release
cd ..


mkdir %RDIR_R%\Compiled\\include\
mkdir %RDIR_R%\Compiled\\lib\

mkdir %RDIR_R%\Compiled\\lib\VS2015\

robocopy VS14\Debug %RDIR_R%\Compiled\\lib\VS2015\Debug *.lib /mir /S
robocopy VS14\Release %RDIR_R%\Compiled\\lib\VS2015\Release *.lib /mir /S

copy VS14\EffekseerSoundXAudio2\Debug\EffekseerSoundXAudio2.lib %RDIR_R%\Compiled\\lib\VS2015\Debug\.
copy VS14\EffekseerSoundXAudio2\Release\EffekseerSoundXAudio2.lib %RDIR_R%\Compiled\\lib\VS2015\Release\.

copy Dev\Cpp\Effekseer\Effekseer.h %RDIR_R%\Compiled\\include\.
copy Dev\Cpp\EffekseerRendererDX9\EffekseerRendererDX9.h %RDIR_R%\Compiled\\include\.
copy Dev\Cpp\EffekseerRendererDX11\EffekseerRendererDX11.h %RDIR_R%\Compiled\include\.
copy Dev\Cpp\EffekseerRendererGL\EffekseerRendererGL.h %RDIR_R%\Compiled\\include\.
copy Dev\Cpp\EffekseerSoundXAudio2\EffekseerSoundXAudio2.h %RDIR_R%\Compiled\\include\.
copy Dev\Cpp\EffekseerSoundAL\EffekseerSoundAL.h %RDIR_R%\Compiled\\include\.

pause

pause

